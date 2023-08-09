#define BLYNK_TEMPLATE_ID "TMPLx4kze-lL"
#define BLYNK_DEVICE_NAME "wificontrol"
#define BLYNK_AUTH_TOKEN "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct"

//Include the library files
#define BLYNK_PRINT Serial
#include<Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Servo servo1;
Servo servo2;

//Initialize the LCD display
char auth[] = "";//Enter your Auth token
char ssid[] = "Kon Ho";//Enter your WIFI name
char pass[] = "kumar7654";//Enter your WIFI password

bool Rel = 0;

//Define component pins
#define in1 D2 
#define in2 D3
#define in3 D4
#define in4 D5
#define Relay D6

int speeed = 0;

void setup() {
  Serial.begin(9600);
   servo1.attach(D1);
   servo2.attach(D7);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Relay, OUTPUT);
 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the function
 
}

//Get the button value

BLYNK_WRITE(V0) {
  Rel = param.asInt();

  if (Rel == 1) {
    digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
          digitalWrite(in4, HIGH);
  } else {
    digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
          digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V1) {
  Rel = param.asInt();

  if (Rel == 1) {
    digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
          digitalWrite(in4, LOW);
  }
}

BLYNK_WRITE(V2) {
  Rel = param.asInt();

  if (Rel == 1) {
    digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
          digitalWrite(in4, LOW);
  }
}

//
BLYNK_WRITE(V3) {
  Rel = param.asInt();

  if (Rel == 1) {
    digitalWrite(in1, HIGH );
      digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
          digitalWrite(in4, HIGH);
  } else {
    digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
          digitalWrite(in4, LOW);
  }
}

//BUZZER

BLYNK_WRITE(V4) {
  Rel = param.asInt();

  if (Rel == 1) {
 
          digitalWrite(Relay, HIGH);
  } else {
   
          digitalWrite(Relay, LOW);
  }
}

  // horizontal move
  BLYNK_WRITE(V5){
  servo1.write(param.asInt());
}
  BLYNK_WRITE(V6){
  servo2.write(param.asInt());
}


void loop() {
  Blynk.run();//Run the Blynk library
}