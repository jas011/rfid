/* Read RFID Tag with RC522 RFID Reader
    Made by miliohm.com
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 20 chars and 4 line display

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);
   Wire.begin(D2, D1); // Set SDA to D2 (GPIO 4), SCL to D1 (GPIO 5) for ESP8266
  lcd.init();         // Initialize the lcd
  lcd.backlight(); 
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
     lcd.setCursor(0, 0);
    lcd.print(tag);
    Serial.println(tag);
    if (tag == "37464218") {
      Serial.println("japjeet");
      lcd.setCursor(0, 1);
      lcd.print("japjeet singh");
      Serial.println("Access Granted!");
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
    } else {
      Serial.println("Access Denied!");
      lcd.setCursor(0, 1);
      lcd.print("Access Denied!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    delay(6000);
    lcd.clear();
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}