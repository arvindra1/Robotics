
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display
char auth[] = "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct";//Enter your Auth token
char ssid[] = "Kon Ho";//Enter your WIFI name
char pass[] = "kumar7654";//Enter your WIFI password


// defines pins numbers
#define trigPin D1  
#define echoPin D2  
#define led1 D3
#define led2 D4
#define led3 D5
#define water D6

// defines variables
long duration;
float distance;
long level;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
   pinMode(led3,OUTPUT);
   pinMode(water ,OUTPUT);

  Blynk.begin(auth, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("distance:");
  Serial.print(distance);

  if(distance> 3 )
  {
    digitalWrite(water,HIGH);
    digitalWrite(led1,LOW);
     digitalWrite(led2,HIGH);
     digitalWrite(led3,HIGH);
     delay(500);
     digitalWrite(led2,LOW);
      delay(500);
  }
  else{
    digitalWrite(water,LOW);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
  }
 Blynk.run();
}
