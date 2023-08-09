#include <SoftwareSerial.h>

// Pins for motor control
#define m1  2
#define m2  3
#define m3  4
#define m4  5


// SoftwareSerial object to communicate with the voice module
SoftwareSerial voiceModule(10, 11); // RX, TX

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  voiceModule.begin(9600);
  
  // Set motor control pins as outputs
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  
}

void loop() {
  // Check for voice commands
  if (voiceModule.available()) {
    char command = voiceModule.read();
    Serial.println(command);
    
    
    // Move forward
    if (command == 'F') {
      digitalWrite(m1,HIGH);
      digitalWrite(m2,LOW);
      digitalWrite(m3,HIGH);
      digitalWrite(m4,LOW);
    }
    // Move backward
    else if (command == 'B') {
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    }
    // Turn left
    else if (command == 'L') {
      digitalWrite(m1,LOW);
      digitalWrite(m2,HIGH);
      digitalWrite(m3,HIGH);
      digitalWrite(m4,LOW);
    }
    // Turn right
    else if (command == 'R') {
      digitalWrite(m1,HIGH);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,HIGH);
    }
    // Stop
    else if (command == 'S') {
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
}
}
}