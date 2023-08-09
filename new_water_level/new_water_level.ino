#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct"; //Enter your Auth token
char ssid[] = "Kon Ho"; //Enter your WIFI name
char pass[] = "kumar7654"; //Enter your WIFI password


const int trigPin = 12;
const int echoPin = 14;
BlynkTimer timer;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

#define water D2

long duration;
float distanceCm;
float distanceInch;

void sendWaterLevelToBlynk()
{
  Blynk.virtualWrite(V0, distanceCm); // Send the water level to Virtual Pin V0
}

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(water,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,sendWaterLevelToBlynk);
 
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);


  if (distanceCm>3 && distanceCm<20)
  {
    digitalWrite(water, HIGH);
    // digitalWrite(led1, LOW);
    // digitalWrite(led2, HIGH);
    // digitalWrite(led3, HIGH);
    // delay(500);
    // digitalWrite(led2, LOW);
    // delay(500);
  }
  else
  {
    digitalWrite(water, LOW);
    // digitalWrite(led1, HIGH);
    // digitalWrite(led2, HIGH);
    // digitalWrite(led3, HIGH);
  }

  Blynk.run();
  timer.run();
  
}