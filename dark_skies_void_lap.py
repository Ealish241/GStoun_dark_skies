import numpy as np
import serial
import csv
import matplotlib.pyplot as plt
import datetime
import pandas as pd


###############################################################
####################       SET UP       #######################
###############################################################

#ser = serial.Serial('COM6', 9600)
#ser.flushInput()




houses = ["Bruce","Cumming", "Duffus","Round Square","Hopeman","Plewlands","Windmill"]
house_cols =  ['#008000', '#ffbf00', '#000000', '#ff0000', '#0000ff', '#ff00ff', '#ffff00']
laps = [0,0,0,0,0,0,0]
fastest_lap = [100000000000000,100000000000000,100000000000000,100000000000000,100000000000000,100000000000000,100000000000000]
# fastest_lap = 1000000000000000000000000000000000000000000000
#card_times = [0]
#tag_times = [0]
file_names_arr = np.array(["dark_sky_data/B_data.csv",
                      "dark_sky_data/C_data.csv",
                      "dark_sky_data/D_data.csv",
                      "dark_sky_data/R_data.csv",
                      "dark_sky_data/H_data.csv",
                      "dark_sky_data/P_data.csv",
                      "dark_sky_data/W_data.csv"])

file_names_processed_arr = np.array(["dark_sky_data/B_data_processed.csv", 
                                 "dark_sky_data/C_data_processed.csv",
                                 "dark_sky_data/D_data_processed.csv",
                                 "dark_sky_data/R_data_processed.csv",
                                 "dark_sky_data/H_data_processed.csv",
                                 "dark_sky_data/P_data_processed.csv",
                                 "dark_sky_data/W_data_processed.csv"
                                 ])



for i in range(len(file_names_arr)):
    with open(file_names_arr[i], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow([1,0])
        
for i in range(len(file_names_processed_arr)):
    with open(file_names_processed_arr[i], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(['Runner','Time(s)', 'Time(mm:ss)'])
        


###############################################################
#################       FUNCTIONS       #######################
###############################################################


def write_to_csv_RAW(data):
    house_id = int(data[0])
    file_names = file_names_arr
    with open(file_names[house_id-1], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(data)
       


def write_to_csv_processed(data, time):
    house_id = int(data[0])
    file_names = file_names_processed_arr
    with open(file_names[house_id-1], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(time)
        
def void_lap(data):
    void_id = int(data[0])-7
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[void_id -1])
    df = df[:-1]
    df.to_csv(file_names[void_id -1], header=['Runner','Time(s)', 'Time(mm:ss)'], index=False)

def timing_calcs(data):
    house_id = int(data[0]) - 1
    with open(str(file_names_arr[house_id]), "r") as f:
        lines = f.readlines()
        last_line = lines[-2].strip()
    last_val = last_line[2:len(last_line)+1]
    true_time = (float(data[1])-float(last_val))/1000
    return true_time

        
def add_laps(data):
    house_id = int(data[0]) - 1
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[house_id])
    column = df['Time(s)']
    lapcount = len(column)
    laps[house_id] = int(lapcount)
    return laps
    
# def speedy_fella(time):
#     if time < fastest_lap:
#         t = time
#     else:
#         t = fastest_lap
#     return t


def speedy_fella2(data):
    house_id = int(data[0]) - 1
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[house_id])
    column = df['Time(s)']
    speedy = min(column)
    fastest_lap[house_id] = float(speedy)
    return fastest_lap    

###############################################################
####################     SERIAL CODE       ####################
###############################################################




while True:
    try:
        #ser_bytes = ser.readline()
        #decoded_bytes = str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        #x = decoded_bytes.split(",")
        x=[7,1234567]
        for i in range(len(x)):
            x[i] = int(x[i])
        print(x)
        
        if x[0] in range(8):
            

            write_to_csv_RAW(x)
            
            
            
            write_to_csv_processed(x,["name_here", timing_calcs(x),str(datetime.timedelta(seconds=timing_calcs(x)))[2:10]])
            
            fastest_lap_val = min(speedy_fella2(x))
            laps_count = add_laps(x)
            print(laps_count)
        

            textstr_fl_sec = 'Time to beat = %.2f sec'%(fastest_lap_val)
            textstr_fl_min = str(datetime.timedelta(seconds=fastest_lap_val))[2:10]
            
        
        
            plt.figure().add_axes([0, 0, 1, 1])
        
            
            plt.bar(houses,laps, label = houses,color=house_cols)
            plt.suptitle('Time to beat = {} min'.format(textstr_fl_min), y=1.2)
            plt.yticks(list(range(0, max(laps)+1)))
            plt.title('Total Laps', fontsize = 22, weight = 'bold')
            plt.xlabel('Team', fontsize = 16)
            plt.ylabel('No. of Laps', fontsize = 16)
        

            plt.savefig('dark_sky_data/graph.jpg',bbox_inches='tight', dpi=150)

            plt.show()
            
            break
        
        else:
            void_lap(x)
            


    except:
        print("Keyboard Interrupt")
        #ser.close()
        break

