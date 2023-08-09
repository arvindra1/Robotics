#include <dht.h>


dht DHT;

#define sensorPin A0
void setup(){
  Serial.begin(9600);
  pinMode(D2,INPUT);
   pinMode(sensorPin,INPUT);
}

void loop(){

  int chk = DHT.read11(D2);
    Serial.print("Methane = ");
  Serial.println(analogRead(sensorPin));
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
}