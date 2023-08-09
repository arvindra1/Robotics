#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2);

#include <Servo.h>

#include <dht.h>

dht DHT;

#define DHT11_PIN 4 

Servo servo;

// Define Input Connections

#define CH5 10
#define CH6 11

// Integers to represent values from sticks and pots
 
int ch5Value;

// Boolean to represent switch value
bool ch6Value;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  servo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("starting drone");
  for(int i=0;i<16;i++){
    lcd.setCursor(i,1);
    lcd.print('.');
    delay(500);
  }
  lcd.clear();
  
  // Set all pins as inputs
  
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}


void loop() {

   // READ DATA
  int chk = DHT.read11(DHT11_PIN);
  Serial.println(DHT.humidity, 1);

  
  // Get values for each channel
  



if (DHT.humidity > 70) {
  Serial.println("High chance of rain");
  Serial.println(DHT.humidity);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("high chance ");
   lcd.setCursor(1,1);
   lcd.print("of rain ");
   lcd.print(DHT.humidity);
   delay(200);
   }
   else if (DHT.humidity > 60 && DHT.humidity<70 ) {

   Serial.println("medium chance of rain");
   Serial.println(DHT.humidity);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("medium chance ");
   lcd.setCursor(1,1);
   lcd.print("of rain ");
   lcd.print(DHT.humidity);

   delay(200);


   }

   else {  
   Serial.println("Clean Weather");
   Serial.println(DHT.humidity);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("low chance ");
   lcd.setCursor(1,1);
   lcd.print("of rain ");
   lcd.print(DHT.humidity);
   delay(200);

   }


  ch5Value = readChannel(CH5, 100, 0, -100);
  ch6Value = readSwitch(CH6, false); 
  
  // Print to Serial Monitor
 
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);

  delay(100);
  
  if(ch5Value<70)
  {
    servo.write(130);
    delay(500);
    servo.write(0);
    delay(500);
  }
  else{ 
    servo.write(0);
  }
  delay(100);
}
