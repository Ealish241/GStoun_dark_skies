#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

#define SS_PIN 5
#define RST_PIN 9
#define LED_BUILTIN 4



MFRC522 rfid(SS_PIN, RST_PIN);

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


File myFile;






void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  //SD.begin(10);

  //Serial.println("Tap RFID/NFC Tag on reader");
}






void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      String dataString = "";
      dataString += String(checkUID(rfid.uid.uidByte));
      dataString += String(",");
      dataString += String(millis());
      Serial.println(dataString);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType));
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(1000);                      
      digitalWrite(LED_BUILTIN, LOW);    
      delay(700);

      

      // print NUID in Serial Monitor in the hex format
      //Serial.print("UID:");
     // for (int i = 0; i < rfid.uid.size; i++) {
       // Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(rfid.uid.uidByte[i], HEX);
      //}
      
      //Serial.print(checkUID(rfid.uid.uidByte));
      //Serial.print(",");
      //Serial.print(millis());
      //Serial.println();
      
      

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD

      //logCard(); 
    }
  }
}




void logCard() {
  // Enables SD card chip select pin
  digitalWrite(10,LOW);
  
  // Open file
  myFile=SD.open("/dark_skies.txt", FILE_WRITE);

  // If the file opened ok, write to it
  if (myFile) {
    Serial.println("File open");
    myFile.print("Hello World");
    
    Serial.println("sucessfully written on SD card");
    myFile.close();
  }
  else {
    Serial.println("error opening ");  
  }
  // Disables SD card chip select pin  
  digitalWrite(10,HIGH);
}


// Function to check if the scanned UID matches the known UID
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
    return 15;
  }
  else if (uid[0] == Tag16[0] && uid[1]== Tag16[1]) {
    return 16;
  }
}
