import numpy as np
import serial
import csv
import matplotlib.pyplot as plt
import datetime
import pandas as pd
from colorama import Fore, Back, Style
import time



###############################################################
####################       SET UP       #######################
###############################################################

ser = serial.Serial('COM6', 9600) ##check that COM port and Baud rate correspond to selected board and baud rate in Arduino code/IDE
ser.flushInput()
#if there is an error at this point, check Serial Monitor in Arduino IDE is closed


print(Fore.WHITE +Back.GREEN + 'CONNECTION SUCCESSFUL!')
print(Style.RESET_ALL)


houses = ["Bruce","Cumming", "Duffus","Round Square","Hopeman","Plewlands","Windmill"]
house_cols =  ['#008000', '#ffbf00', '#000000', '#ff0000', '#0000ff', '#ff00ff', '#ffff00']
laps = [0,0,0,0,0,0,0]
fastest_lap = [0,0,0,0,0,0,0]

###############################################################
########################   FILE NAMES #########################
## Makes sure to change the file paths to the correct folder ##
###############################################################

file_names_arr = np.array(["Documents/Dark Skies/dark_sky_data/B_data.csv",
                      "Documents/Dark Skies/dark_sky_data/C_data.csv",
                      "Documents/Dark Skies/dark_sky_data/D_data.csv",
                      "Documents/Dark Skies/dark_sky_data/R_data.csv",
                      "Documents/Dark Skies/dark_sky_data/H_data.csv",
                      "Documents/Dark Skies/dark_sky_data/P_data.csv",
                      "Documents/Dark Skies/dark_sky_data/W_data.csv"])

file_names_processed_arr = np.array(["Documents/Dark Skies/dark_sky_data/B_data_processed.csv", 
                                 "Documents/Dark Skies/dark_sky_data/C_data_processed.csv",
                                 "Documents/Dark Skies/dark_sky_data/D_data_processed.csv",
                                 "Documents/Dark Skies/dark_sky_data/R_data_processed.csv",
                                 "Documents/Dark Skies/dark_sky_data/H_data_processed.csv",
                                 "Documents/Dark Skies/dark_sky_data/P_data_processed.csv",
                                 "Documents/Dark Skies/dark_sky_data/W_data_processed.csv"
                                 ])


## Generate csv files ##

for i in range(len(file_names_arr)):
    with open(file_names_arr[i], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow([1,0])
        
for i in range(len(file_names_processed_arr)):
    with open(file_names_processed_arr[i], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(['Runner','Time(s)', 'Time(mm:ss)', 'RTC'])
        

        


###############################################################
#################       FUNCTIONS       #######################
###############################################################


## selects house using integer[0] from arduino array, saves house number (int[0]) and millisecond data (int[1]) to csv
def write_to_csv_RAW(data):
    house_id = int(data[0])
    file_names = file_names_arr
    with open(file_names[house_id-1], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(data)
       
## selects house using integer[0] from arduino array, saves lap time and RTC to csv
def write_to_csv_processed(data, time):
    house_id = int(data[0])
    file_names = file_names_processed_arr
    with open(file_names[house_id-1], "a", newline="") as f:
        writer = csv.writer(f, delimiter=",")
        writer.writerow(time)
 
## selects house using integer[0] from arduino array, deletes last row in relevant 'processed' csv file. Raw data csv is unaltered
def void_lap(data):
    void_id = int(data[0])-7
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[void_id -1])
    df = df[:-1]
    df.to_csv(file_names[void_id -1], header=['Runner','Time(s)', 'Time(mm:ss)','RTC'], index=False)


## selects house using integer[0] from arduino array, calculates lap time by computing difference in millisec count between last two entries in raw data csv
## True time calc by dividing by 1000 to get time in sec rather than millis.
def timing_calcs(data):
    house_id = int(data[0]) - 1
    with open(str(file_names_arr[house_id]), "r") as f:
        lines = f.readlines()
        last_line = lines[-2].strip()
    last_val = last_line[2:len(last_line)+1]
    true_time = (float(data[1])-float(last_val))/1000
    return true_time


## selects house using integer[0] from arduino array, calculates lap tally for that house by reading how many entries are in the relevant 'processed' csv file
## edits the pre defined laps array with new lap count for that house     
def add_laps(data):
    house_id = int(data[0]) - 1
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[house_id])
    column = df['Time(s)']
    lapcount = len(column)
    laps[house_id] = int(lapcount)
    return laps
    

## selects house using integer[0] from arduino array, calculates fastest laps by reading the min lap time from relevant 'processed' csv file
## edits the pre defined laps array with new fastest lap for that house.
def speedy_fella2(data):
    house_id = int(data[0]) - 1
    file_names = file_names_processed_arr
    df = pd.read_csv(file_names[house_id])
    column = df['Time(s)']
    speedy = min(column)
    pretty_speedy = str(datetime.timedelta(seconds=float(speedy)))[2:9]
    fastest_lap[house_id] = pretty_speedy
    return fastest_lap    


## for lap counts over 15, graph produces ticks every 5 laps, otherwise every lap
def lap_scale(lap_ct):
    lap_mag = 1 
    if lap_ct[0] > 15:
        lap_mag = 5
    else:
        lap_mag = 1 
    return lap_mag 

###############################################################
####################     SERIAL CODE       ####################
###############################################################




while True:
    try:
        ## read the bytes from arduino, decode to produce an integer array x of the form [a,b] where a is the house id (1-7, or 8-14 for void laps) and b is the millisec count since code started
        ser_bytes = ser.readline()
        decoded_bytes = str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        x = decoded_bytes.split(",")
        for i in range(len(x)):
            x[i] = int(x[i])
        print(Style.RESET_ALL)
        print(x) 
        
        if x[0] in range(8): ## ie, the first element in the array x, the house id, is 1-7, corresponding to a normal dib with the relevant house tag
            
           
            current_time = time.strftime("%H:%M:%S", time.localtime()) #RTC when data recieved
            epoch_time = round(time.time(),2) #time count, not currently used in the code

            write_to_csv_RAW(x) #write the raw arduino data to csv
            
            
            
            write_to_csv_processed(x,["name_here", timing_calcs(x),str(datetime.timedelta(seconds=timing_calcs(x)))[2:10],current_time]) #write processed data to csv: lap time in sec, lap time in min:sec, RTC
            
            fastest_lap = speedy_fella2(x) #update fastest lap array
            
            laps_count = add_laps(x) #update lap count array
            
    
            
            
            print(Fore.BLUE +Back.WHITE + 'LAP RECORDED')
            print(Style.RESET_ALL)
            
            print("{}, Lap Time: {}, Current Time: {}".format(houses[int(x[0]) - 1],str(datetime.timedelta(seconds=timing_calcs(x)))[2:10],current_time))
            print('Fastest Lap Times: {}'.format(fastest_lap))
            
            ###########################
            #######   GRAPH   #########
            ###########################
        
            y_ticks = list(range(0, max(laps)+1,lap_scale(laps_count))) #set y ticks using the lap scale
            y_ticks_minor = list(range(0, max(laps)+1,1)) #minor ticks force gridlines every lap even when axis is counting up in 5s
            


            ax = plt.figure().add_axes([0, 0, 1, 1])
           
            ax.bar(houses,laps, label = houses,color=house_cols) #set bars
            ax.set_yticks(y_ticks) #set y ticks
            ax.set_yticks(y_ticks_minor,minor=True) #set minor y ticks
            ax.grid(which='minor', axis='y', alpha=0.3) # set gridlines for minor y ticks
            ax.grid(which='major', axis='y', alpha=0.7) #set gridlines for major y ticks
            plt.title('Total Laps', fontsize = 22, weight = 'bold') # Plot titles
            plt.xlabel('Team', fontsize = 16) #x axis lable
            plt.ylabel('No. of Laps', fontsize = 16) #y axis lable
        

            plt.savefig('Documents/Dark Skies/dark_sky_data/graph.jpg',bbox_inches='tight', dpi=150) #save fig to folder
            plt.savefig('OneDrive/Dark_Skies/graph.jpg',bbox_inches='tight', dpi=150) #I also have it saving to a one drive folder for the htlm code to access- this is only necessary if you want to run the html code that pulls from one drive

            plt.show() #this shows the plot in the plot pane 
            
        
        elif x[0] in range(8,15): #x[0] 8-14 corresponds to the 'void tags' - see tag UID in Arduino code
            void_lap(x)
            print('LAP VOIDED')
            


    except:
        print(Fore.WHITE +Back.RED + 'THE CODE HAS STOPPED!')
        print(Style.RESET_ALL)
        ser.close()
        break

