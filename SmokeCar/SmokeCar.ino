#include <Servo.h>
Servo servo1;
Servo servo2;

#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;
#define MQ2pin (0)

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(9);
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  float smokeValue = analogRead(MQ2pin);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  Serial.print("Smoke Value");
  Serial.println(smokeValue);
  if (smokeValue > 100 || ((float)DHT11.temperature, 2) > 28 || ((float)DHT11.humidity, 2) > 65) {
    servo1.write(120);
    servo2.write(120);

  } else {
    servo1.write(0);
    servo2.write(0);
  }

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  delay(2000);
}