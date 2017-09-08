/**************************************************************************/
/*! 
    This example will attempt to connect to an ISO14443A
    card or tag and retrieve some basic information about it
    that can be used to determine what type of card it is.   
   
    Note that you need the baud rate to be 115200 because we need to print
    out the data and read from the card at the same time!

    To enable debug message, define DEBUG in PN532/PN532_debug.h
    
*/
/**************************************************************************/

#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"

PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);

void setup(void) {
  Serial.begin(115200);
  nfc.begin();
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT); 
  uint32_t versiondata = nfc.getFirmwareVersion();
  // Got ok data, print it out!
  /*Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);*/
  
  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0xFF);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
    
  //Serial.println("Waiting for an ISO14443A card");
}

void loop(void) {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  int a=digitalRead(2);
  int b=digitalRead(3);
  int c=digitalRead(4);
  int d=digitalRead(5);
  //Serial.println(a);
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    /*Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");*/
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX); 
       
    }
   Serial.print(" Button1:"+String(a)+" Button2:"+String(b)+" Button3:"+String(c)+" Button4:"+String(d));
    Serial.println("");
    // wait until the card is taken away
    //while (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength)) {}
  }else{
     Serial.println(" Button1:"+String(a)+" Button2:"+String(b)+" Button3:"+String(c)+" Button4:"+String(d));
   }

  if(a==1){
    digitalWrite(6,HIGH);
  }else{
    digitalWrite(6,LOW);
  }
  if(b==1){
    digitalWrite(7,HIGH);
  }else{
    digitalWrite(7,LOW);
  }
  if(c==1){
    digitalWrite(8,HIGH);
  }else{
    digitalWrite(8,LOW);
  }
  if(d==1){
    digitalWrite(9,HIGH);
  }else{
    digitalWrite(9,LOW);
  }
  delay(1000);
  
  /*else
  {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
  }*/
}
