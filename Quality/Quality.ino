#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0X27, 16, 2);

#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;
#define SMOKE_SENSOR_PIN A1
#define Soil A0

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(3, 0);
    lcd.print("Detecting..");
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(500);
  }
}

void loop() {
  Serial.println();
  float mois = (100.00 - ((analogRead(Soil) / 1023.00) * 100.00));

  int chk = DHT11.read(DHT11PIN);
  int smokeValue = analogRead(SMOKE_SENSOR_PIN);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  Serial.print("Smoke Value");
  Serial.println(smokeValue);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(14,0);
  lcd.print((float)DHT11.temperature, 2);
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.setCursor(14,1);
  lcd.print((float)DHT11.temperature, 2);
  delay(3000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Air Quality:");
  lcd.setCursor(4,1);
  lcd.print(smokeValue);
  delay(3000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(4,1);
  lcd.print(mois);
  delay(3000);
}