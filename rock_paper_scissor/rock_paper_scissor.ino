#include <Servo.h>

 

const int trigPin = 3;  // Ultrasonic sensor trigger pin
const int echoPin = 2;  // Ultrasonic sensor echo pin
const int ledPin = 8;   // LED pin

 

Servo servo1;  // Servo for 2-finger gesture
Servo servo2;  // Servo for palm gesture
Servo servo3;  // Servo for punch gesture

 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

 

  servo1.attach(10);   // Servo 1 pin
  servo2.attach(9);   // Servo 2 pin
  servo3.attach(6);   // Servo 3 pin

 

  servo1.write(0);   // Set initial position for servo 1
  servo2.write(0);   // Set initial position for servo 2
  servo3.write(0);   // Set initial position for servo 3
}

 

void loop() {
 long duration, distance;
 
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in cm)
  distance = duration *0.034/2;
  Serial.print(distance);

 

  // Detect hand gestures
  if (distance >= 2 && distance <= 10) {    // 2-finger gesture
    servo1.write(90);
    servo2.write(0);
    servo3.write(0);
    digitalWrite(ledPin, HIGH);
  } else if (distance > 10 && distance <= 20) {   // Palm gesture
    servo1.write(0);
    servo2.write(90);
    servo3.write(0);
    digitalWrite(ledPin, HIGH);
  } else if (distance > 20 && distance <= 30) {   // Punch gesture
    servo1.write(0);
    servo2.write(0);
    servo3.write(90);
    digitalWrite(ledPin, HIGH);
  } else {   // No gesture detected
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    digitalWrite(ledPin, LOW);
  }

  delay(100);  // Adjust delay as needed
}