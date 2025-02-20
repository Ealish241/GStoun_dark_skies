First off, appologies for the ugly coding - it works, but please feel free to add/edit to make it more elegant and functional.

The repository contains three main codes: The Arduino code for the RFID reader and LED, the Python code to save and interpret lap data, and the HTML code, for uploading data to a local web server.
Throughout the code, it has assumed the Arduino is using COM6 and operating at baud rate 9600.

Arduino Code:
The wiring used for the Arduino is as follows:
RFID:   SS=10, RST = 9, SPI = 13, MISO = 12, MOSI = 11. This is standard wiring as used in many of the MFRC522 Library.
Note - you must download the correct library into the Arduino IDE for the code to run.
The LED is a simple circuit: Pin 4 > LED > 220ohm res > grd

Python Code:
The python code save raw data to csv, as well as processed lap data. The serial monitor in the Arduino IDE must be cl
