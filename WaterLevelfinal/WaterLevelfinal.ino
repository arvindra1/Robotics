#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct"; //Enter your Auth token
char ssid[] = "Kon Ho"; //Enter your WIFI name
char pass[] = "kumar7654"; //Enter your WIFI password

#define trigPin D1
#define echoPin D2
#define led1 D3
#define led2 D4
#define led3 D5
#define water D6

long duration;
float distance;
long level;
const int fixdis=3;


void sendWaterLevelToBlynk()
{
  Blynk.virtualWrite(V0, distance); // Send the water level to Virtual Pin V0
}

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(water, OUTPUT);


}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance>fixdis && distance<20)
  {
    digitalWrite(water, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
  }
  else
  {
    digitalWrite(water, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  Blynk.run();
  timer.run();
}
