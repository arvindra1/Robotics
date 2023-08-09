#define BLYNK_TEMPLATE_ID "TMPLx4kze-lL"
#define BLYNK_TEMPLATE_NAME "wificontrol"
#define BLYNK_AUTH_TOKEN "Oh6MCgsMwMpzR0pp1Qs_YWTYpQqLWGct"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 //Enter your blynk auth token
bool In=0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Abhishek.S";//Enter your WIFI name
char pass[] = "gopikishan ";//Enter your WIFI password

//Get the button value
BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
}