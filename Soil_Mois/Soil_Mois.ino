#include <LiquidCrystal.h>

int soil_sensor ;

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

void setup() {
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  lcd.print("Soil Moisture:");
}

void loop() {
  float mois=(100.00-((analogRead(A0)/1023.00)*100.00));
  lcd.setCursor(0,1);
  lcd.print(mois);
  delay(1000);
  lcd.print(" ");
delay(100);
}