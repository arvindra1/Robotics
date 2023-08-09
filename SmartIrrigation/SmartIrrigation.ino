#include <Servo.h>
Servo servo1;
Servo servo2;


// Include library
#define moisture A0
// Defines pin number to which the sensor is connected

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(9);
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  float mois = (100.00 - ((analogRead(moisture) / 1023.00) * 100.00));
  Serial.println(mois);
  if (mois > 10) {
    Serial.print("Servo are started");
    servo1.write(90);
    servo2.write(90);

  } else {
    Serial.print("Servo are not started");
    servo1.write(90);
    servo2.write(90);
  }
}