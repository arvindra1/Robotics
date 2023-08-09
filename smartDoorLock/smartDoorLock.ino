#include <Servo.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include "Keypad.h"

Servo servo;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
#define SERVO_PIN  A0
#define led1 D8 
#define led2 D9 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {16, 5, 4, 0}; 
byte colPins[COLS] = {2, 14, 12, 13}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char* ssid = "Kon Ho";
const char* password = "kumar7654";

String phoneNumber = "+917651853228";
String apiKey = "8997839";

const String password_1 = "ABC1234"; // change your password here
const String password_2 = "5642B";   // change your password here
const String password_3 = "9765";    // change your password here
String input_password;

int angle = 0; // the current angle of servo motor
unsigned long lastTime;

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(D4,INPUT);
  servo.attach(SERVO_PIN);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Send Message to WhatsAPP
  sendMessage("Hello from ESP8266!");
}

void loop() {

  char key = keypad.getKey();

  if (key){
    Serial.println(key);
    
    if (key == '*') {
      Serial.print("enter the password");
      input_password = ""; // reset the input password
    } else if (key == '#') {
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        Serial.println("The password is correct, rotating Servo Motor to 90°");
        angle = 90;
        servo.write(angle);
        sendMessage("Warning!Your locker is opened.....");
        digitalWrite(led1,HIGH);
         digitalWrite(led2,LOW);
        lastTime = millis();
      } else {
        Serial.println("The password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }

  if (angle == 90 && (millis() - lastTime) > 5000) { // 5 seconds
    angle = 0;
    servo.write(angle);
    Serial.println("Rotating Servo Motor to 0°");
    digitalWrite(led1,LOW);
         digitalWrite(led2,HIGH);
  }
  }
  
