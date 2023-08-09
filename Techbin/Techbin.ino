#include <Servo.h>

#include <LiquidCrystal_I2C.h>

Servo servo1;
Servo servo2;
Servo servo3;

#include <MFRC522.h>

LiquidCrystal_I2C lcd(0x27,16,2);


 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  lcd.init();
  lcd.backlight();
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  pinMode(4,OUTPUT);
  for(int i=0;i<16;i++){
  lcd.setCursor(0, 0);
  lcd.print("Starting");
  lcd.setCursor(i, 1);
  lcd.print(".");
  delay(500);
  }
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kindly scan....");

  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "43 5D E1 F5" || content.substring(1) == "43 5D E1 F5") //change here the UID of the card/cards that you want to give access
  {
    servo1.write(80);
    delay(3000);
    servo2.write(60);
    servo3.write(-60);
    delay(3000);
    servo2.write(0);
    servo3.write(0);
    servo1.write(0);

  }
 
 else   {
    Serial.println(" Access denied");
    servo1.write(-80);
    delay(3000);
    servo2.write(-60);
    servo3.write(60);
    delay(3000);
    servo2.write(0);
    servo3.write(0);
    servo1.write(0);
  }
} 