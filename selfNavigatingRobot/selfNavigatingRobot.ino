

#define BLYNK_TEMPLATE_ID "TMPLx4kze-lL"
#define BLYNK_TEMPLATE_NAME "wificontrol"
#define BLYNK_AUTH_TOKEN "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct"
//Include the library files
#define BLYNK_PRINT Serial
#include<Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Servo servo1;
// Servo servo2;

// #define trig1 D0
// #define echo1 D8

//Initialize the LCD display
char auth[] = "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct";//Enter your Auth token
char ssid[] = "Kon Ho";//Enter your WIFI name
char pass[] = "kumar7654";//Enter your WIFI password
 
// bool Rel = 0;

//Define component pins
// #define in1 D1 
// #define in2 D2
// #define trig2 D3
// #define echo2 D4
// #define trig3 D5
// #define echo3 D6

void setup() {
  Serial.begin(9600);
   servo1.attach(D7);
  //  servo2.attach(D7);
  // pinMode(trig1,OUTPUT);
  // pinMode(echo1,INPUT);
  // pinMode(trig2,OUTPUT);
  // pinMode(echo2,INPUT);
  // pinMode(trig3,OUTPUT);
  // pinMode(echo3,INPUT);

  // pinMode(in1, OUTPUT);
  // pinMode(in2, OUTPUT);
 
 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the function
 
}

// //Get the button value

// BLYNK_WRITE(V0) {
//   Rel = param.asInt();

//   if (Rel == 1) {
//     digitalWrite(in1, LOW);
//       digitalWrite(in2, HIGH);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, HIGH);
//   } else {
//     digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, LOW);
//   }
// }

// BLYNK_WRITE(V1) {
//   Rel = param.asInt();

//   if (Rel == 1) {
//     digitalWrite(in1, HIGH);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, HIGH);
//           digitalWrite(in4, LOW);
//   } else {
//     digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, LOW);
//   }
// }

// BLYNK_WRITE(V2) {
//   Rel = param.asInt();

//   if (Rel == 1) {
//     digitalWrite(in1, HIGH);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, HIGH);
//   } else {
//     digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, LOW);
//   }
// }

// //
// BLYNK_WRITE(V3) {
//   Rel = param.asInt();

//   if (Rel == 1) {
//     digitalWrite(in1, LOW );
//       digitalWrite(in2, HIGH);
//         digitalWrite(in3, HIGH);
//           digitalWrite(in4, LOW);
//   } else {
//     digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//         digitalWrite(in3, LOW);
//           digitalWrite(in4, LOW);
//   }
// }
// BLYNK_WRITE(V4) {
//   Rel = param.asInt();

//   if (Rel == 1) {
 
//           digitalWrite(Relay, HIGH);
//   } else {
   
//           digitalWrite(Relay, LOW);
//   }
// }
   BLYNK_WRITE(V6){
   servo1.write(param.asInt());
 }


void loop() {
  Blynk.run();
  // long duration1, distance1;
  // long duration2, distance2;
  // long duration3, distance3;
 
  // // Trigger ultrasonic sensor
  // digitalWrite(trigPin1, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin1, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin1, LOW);

  // // Measure the response2
  // duration1 = pulseIn(echoPin1, HIGH);
  // // Calculate the distance (in cm)
  // distance1 = duration1 *0.034/2;
  //  digitalWrite(trigPin2, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin2, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin2, LOW);

  // // Measure the response3
  // duration2 = pulseIn(echoPin2, HIGH);
  // distance2 = duration2 *0.034/2;
  


  //  digitalWrite(trigPin3, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin3, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin3, LOW);

  // // Measure the response
  // duration3 = pulseIn(echoPin3, HIGH);

  // // Calculate the distance (in cm)
  // distance3 = duration3 *0.034/2;
  // Serial.print(distance);

  // if((distance1<200 && distance1>50)&&(distance2>50)&&(distance3<200 && distance3>50))
  // {
  //   digitalWrite(in1, HIGH);
  //     digitalWrite(in2, LOW);
  //       digitalWrite(in3, HIGH);
  //         digitalWrite(in4, LOW);
  // }
  // else if(())
  

}