#include <Adafruit_Sensor.h>
#include <Wire.h>    
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include<Arduino.h>

#define DHTTYPE    DHT11     // DHT 11
#define DHT11_PIN D7

DHT dht(DHT11_PIN, DHTTYPE);


 LiquidCrystal_I2C lcd(0x3F,16,2); 

#define MQ4_PIN A0
#define BUZZER_PIN D3
#define GREEN_LED_PIN D4
#define RED_LED_PIN D5

const int thresholdValue = 50;  // Change this value as per your requirements

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Detecting");
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  pinMode(DHT11_PIN, INPUT); // Corrected the pin mode for DHT11 sensor data pin
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  int gasValue = (100.00 - ((analogRead(MQ4_PIN) / 1023.00) * 100.00));
  Serial.print("Temperature = ");
  Serial.println(dht.readTemperature() );
 

  Serial.print("Analog Value: ");
  Serial.println(gasValue);

  if (gasValue >= thresholdValue || (dht.readTemperature() > 0 && dht.readTemperature() < 10)) { // Check for safe temperature range
    Serial.println("Spoiled food detected!");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Spoiled Food");
    lcd.setCursor(2, 1);
    lcd.print("Detected");
    Serial.println("Detected");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(2000);  // Sound the alarm for 2 seconds
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Consumable");
    lcd.setCursor(0, 1);
    lcd.print("Enjoy it.");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  }

  delay(1000);  // Adjust the delay time based on your application.
}
