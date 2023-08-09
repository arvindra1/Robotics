/* Upload the distance on the Firebase Realtime Database */
//created by Arvindra Ahirwar...........

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <FirebaseESP8266.h>
#include <Wire.h>
#include <TinyGPS++.h>  // Library for GPS module
#include <SoftwareSerial.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

TinyGPSPlus gps;          // The TinyGPS++ object
SoftwareSerial ss(4, 5);  // The serial connection to the GPS device

// Insert your network credentials
#define WIFI_SSID "Kon Ho"
#define WIFI_PASSWORD "kumar7654"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBRYit-KekfOeeT4qrdU9HBSUM3ZkWybNI"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "kumararvindra7691@gmail.com"
#define USER_PASSWORD "Arvindra123#"

// Gps variables
float latitude, longitude;
int year, month, date, hour, minute, second;
String date_str, time_str, lat_str, lng_str;
int pm;

// Insert RTDB URL
#define DATABASE_URL "https://getstarted-8f9b1-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;
String latpath;
String lonpath;
String datepath;
String timepath;

String databasePath;
// D8 pulled gnd
#define button 15 

const int led=D6;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Write string values to the database
void sendString(String path, String value) {
  if (Firebase.setString(fbdo, path.c_str(), value.c_str())) {
    Serial.print("Writing value: ");
    Serial.print(value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}

void setup() {
  Serial.begin(115200);
  ss.begin(115200);

  initWiFi();
  pinMode(button,INPUT);
  // Assign the API key (required)
  config.api_key = API_KEY;

  // Assign the user sign-in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Initialize the Firebase ESP8266 library
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid;

  // Update database path for sensor readings
  latpath = databasePath + "/Latitude";
  lonpath = databasePath + "/Longitude";
  datepath = databasePath + "/Date";
  timepath = databasePath + "/Time";
}

void loop() {
  int valB=digitalRead(button);
  // Send new readings to the database
  if (Firebase.ready()) {
    // GPS
    while (ss.available() > 0) {
      if (gps.encode(ss.read())) {
        if (gps.location.isValid()) {
          latitude = gps.location.lat();
          lat_str = String(latitude, 6);
          longitude = gps.location.lng();
          lng_str = String(longitude, 6);
        }
        if (gps.date.isValid()) {
          date_str = "";
          date = gps.date.day();
          month = gps.date.month();
          year = gps.date.year();
          if (date < 10)
            date_str = '0';
          date_str += String(date);
          date_str += " / ";
          if (month < 10)
            date_str += '0';
          date_str += String(month);
          date_str += " / ";
          if (year < 10)
            date_str += '0';
          date_str += String(year);
        }
        if (gps.time.isValid()) {
          time_str = "";
          hour = gps.time.hour();
          minute = gps.time.minute();
          second = gps.time.second();
          minute = (minute + 30);
          if (minute > 59) {
            minute = minute - 60;
            hour = hour + 1;
          }
          hour = (hour + 5);
          if (hour > 23)
            hour = hour - 24;
          if (hour >= 12)
            pm = 1;
          else
            pm = 0;
          hour = hour % 12;
          if (hour < 10)
            time_str = '0';
          time_str += String(hour);
          time_str += " : ";
          if (minute < 10)
            time_str += '0';
          time_str += String(minute);
          time_str += " : ";
          if (second < 10)
            time_str += '0';
          time_str += String(second);
          if (pm == 1)
            time_str += " PM ";
          else
            time_str += " AM ";
        }
      }
    }
    if ( valB == HIGH) {
      Serial.print(" ");
      Serial.println(valB);
      for(int i=5;i<10;i++)
      {
        digitalWrite(led,HIGH);
        delay(500);
        digitalWrite(led,LOW);
        delay(500);
      }

      if (latitude != 0.0 && longitude != 0.0) {
        sendString(latpath, lat_str);
        sendString(lonpath, lng_str);

      }
    }
    else{
      Serial.println("Failed to update");
    }
  }

  delay(500);
}
