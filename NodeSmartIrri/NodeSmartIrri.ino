#define BLYNK_TEMPLATE_ID "TMPL3Rt1mWAGw"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "feykyD1drNnTnYZfi1dsqiOgEiOUWVuI"

//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display
char auth[] = "feykyD1drNnTnYZfi1dsqiOgEiOUWVuI";//Enter your Auth token
char ssid[] = "vanshwifi";//Enter your WIFI name
char pass[] = "12345678";//Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;

//Define component pins
#define sensor A0 
#define Rain D1
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
 
  }
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;
  Serial.println(value);

  Blynk.virtualWrite(V6, value);

}
void rain(){
  int m = analogRead(Rain);
  m = map(m, 0, 1024, 0, 100);
  m = (m - 100) * -1;
 Serial.print("");
 Serial.println(m);
  Blynk.virtualWrite(V2, m);

}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
  rain();
  delay(1000);
}