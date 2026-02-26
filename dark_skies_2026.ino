//Library Set-up
// Make sure to install MFRC522 Library via: Tools -> Manage Libraries -> Install MFRC522 Library

#include <SPI.h>
#include <MFRC522.h> 


// Pin Set-up. (See Git Repository for full pin wirings)
#define SS_PIN 10
#define RST_PIN 9



MFRC522 rfid(SS_PIN, RST_PIN);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Assign Tag UIDs to byte variables (You can read the tag UIDs using the example code found under File -> Examples -> MFRC522 -> ReadNUID)//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte Tag1[4] = {0xF3, 0x2B, 0x89, 0xA5};
byte Tag2[4] = {0xD3, 0x5F, 0x51, 0xA6};
byte Tag3[4] = {0x43, 0x63, 0xE2, 0xA5};
byte Tag4[4] = {0xB9, 0xB6, 0x31, 0x02};
byte Tag5[4] = {0x63, 0xFE, 0x91, 0xA5};
byte Tag6[4] = {0xE3, 0xC3, 0x7C, 0xA5};
byte Tag7[4] = {0xC3, 0x09, 0xD6, 0xA6};
byte Tag8[4] = {0x43, 0x0F, 0xAA, 0xA5};
byte Tag9[4] = {0x63, 0x1E, 0x9A, 0xA5};
byte Tag10[4] = {0xB3, 0x0A, 0xCC, 0xA6};
byte Tag11[4] = {0x43, 0x69, 0xFF, 0xA6};
byte Tag12[4] = {0xC3, 0xC3, 0x4C, 0xA6};
byte Tag13[4] = {0xB3, 0x25, 0xD6, 0xA5};
byte Tag14[4] = {0xE3, 0xF8, 0x75, 0xA5};
byte Tag15[4] = {0x83, 0xEE, 0x93, 0xA5};
byte Tag16[4] = {0x33, 0xCD, 0x99, 0xA5};
byte Tag17[4] = {0xD3, 0xFD, 0x91, 0xA5};
byte Tag18[4] = {0x93, 0x86, 0x54, 0xA6};
byte Tag19[4] = {0x73, 0x61, 0xBF, 0xA6};
byte Tag20[4] = {0x93, 0x2E, 0xC8, 0xA6};
byte Tag21[4] = {0x13, 0xBB, 0x83, 0xA5};

//////////////////////////////////
//SETUP - runs once at the start//
//////////////////////////////////

void setup() {
  Serial.begin(9600); // make sure this corresponds with baud rate in Python code
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  
  //Serial.println("Tap RFID/NFC Tag on reader");
}


/////////////////////////////////////////////
//MAIN CODE - runs on loop until interupted//
/////////////////////////////////////////////

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      String dataString = "";
      dataString += String(checkUID(rfid.uid.uidByte)); // checkUID function defined below, returns integer value rather than UID byte sequence
      dataString += String(",");
      dataString += String(millis()); //millis gives time in milliseconds since code began. In the event of code crashing, this resests upon restart, which disrupts lap time calcs for that period.
      Serial.println(dataString); //this string is what is read by the python code
      
      delay(1500); // Delay reduces the likelihood of the tag being read multiple times. This becomes redunant if including an LED script etc.

      

      
      
      

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD

       
    }
  }
}





///////////////////////////////////////////////////////////////
// Function to check if the scanned UID matches the known UID//
///////////////////////////////////////////////////////////////
// int 1-7 corresponds to new lap in python code            ///
// there are 2 tags that each return 1-7 - one is a spare   ///
// int 8-14 corresponds to void lap in python code          ///
///////////////////////////////////////////////////////////////

int checkUID(byte* uid) {

  if (uid[0] == Tag1[0] && uid[1]== Tag1[1]) {
    return 1;
  }
  else if (uid[0] == Tag2[0] && uid[1]== Tag2[1]) {
    return 2;
  }
  else if (uid[0] == Tag3[0] && uid[1]== Tag3[1]) {
    return 3;
  }
  else if (uid[0] == Tag4[0] && uid[1]== Tag4[1]) {
    return 4;
  }
  else if (uid[0] == Tag5[0] && uid[1]== Tag5[1]) {
    return 5;
  }
  else if (uid[0] == Tag6[0] && uid[1]== Tag6[1]) {
    return 6;
  }
  else if (uid[0] == Tag7[0] && uid[1]== Tag7[1]) {
    return 7;
  }
  else if (uid[0] == Tag8[0] && uid[1]== Tag8[1]) {
    return 8;
  }
  else if (uid[0] == Tag9[0] && uid[1]== Tag9[1]) {
    return 9;
  }
  else if (uid[0] == Tag10[0] && uid[1]== Tag10[1]) {
    return 10;
  }
  else if (uid[0] == Tag11[0] && uid[1]== Tag11[1]) {
    return 11;
  }
  else if (uid[0] == Tag12[0] && uid[1]== Tag12[1]) {
    return 12;
  }
  else if (uid[0] == Tag13[0] && uid[1]== Tag13[1]) {
    return 13;
  }
  else if (uid[0] == Tag14[0] && uid[1]== Tag14[1]) {
    return 14;
  }
  else if (uid[0] == Tag15[0] && uid[1]== Tag15[1]) {
    return 1;
  }
  else if (uid[0] == Tag16[0] && uid[1]== Tag16[1]) {
    return 2;
  }
  else if (uid[0] == Tag17[0] && uid[1]== Tag17[1]) {
    return 3;
  }
  else if (uid[0] == Tag18[0] && uid[1]== Tag18[1]) {
    return 4;
  }
  else if (uid[0] == Tag19[0] && uid[1]== Tag19[1]) {
    return 5;
  }
  else if (uid[0] == Tag20[0] && uid[1]== Tag20[1]) {
    return 6;
  }
  else if (uid[0] == Tag21[0] && uid[1]== Tag21[1]) {
    return 7;
  }
}
