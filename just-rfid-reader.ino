/*
 * This Arduino UNO R4 code was developed by newbiely.com
 *
 * This Arduino UNO R4 code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-rfid
 */

#include <SPI.h>
#include <MFRC522.h>


#include "Wire.h" 
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2); 


#define SS_PIN 10 // The Arduino UNO R4 pin connected to the SS pin of RC522 module
#define RST_PIN 5 // The Arduino UNO R4 pin connected to the RST pin of RC522 module

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  lcd.init(); 
  lcd.backlight();
  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType));

      // print NUID in Serial Monitor in the hex format
      Serial.print("UID:");
      lcd.clear();
lcd.setCursor(0, 0);
for (int i = 0; i < rfid.uid.size; i++) {
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
  Serial.print(rfid.uid.uidByte[i], HEX);

  if (rfid.uid.uidByte[i] < 0x10) lcd.print("0");
  lcd.print(rfid.uid.uidByte[i], HEX);
}
      Serial.println();
      lcd.setCursor(0, 1);
      lcd.print(rfid.PICC_GetTypeName(piccType));
      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }

}