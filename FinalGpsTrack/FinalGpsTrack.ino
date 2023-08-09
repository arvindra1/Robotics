/*
  Upload the distance on the firebase realtime database
*/

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>




// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
// tx =D2 rx=D1
// Insert your network credentials
#define WIFI_SSID "Kon Ho"
#define WIFI_PASSWORD "kumar7654"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBRYit-KekfOeeT4qrdU9HBSUM3ZkWybNI"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "kumararvindra228@gmail.com"
#define USER_PASSWORD "123Node123##"

// Gps variables
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

// Insert RTDB URLefine the RTDB URL
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
// Timer variables (send new readings every three minutes)
// unsigned long sendDataPrevMillis = 0;
// unsigned long timerDelay = 18000;


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Write float values to the database
void sendFloat(String path, String value){
  if (Firebase.RTDB.setString(&fbdo, path.c_str(), value)){
    Serial.print("Writing value: ");
    Serial.print (value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}

void setup(){
  Serial.begin(115200);
  ss.begin(115200);

  initWiFi();

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
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
  latpath = databasePath + "/Latitute"; // --> UsersData/<user_uid>/temperature
  lonpath = databasePath + "/Longitute";
  datepath = databasePath + "/Date";
  timepath = databasePath + "/Time";
}

void loop(){
// Gps   
 while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
      }
      if (gps.date.isValid()) //check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (date < 10)
          date_str = '0';
        date_str += String(date);// values of date,month and year are stored in a string
        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month); // values of date,month and year are stored in a string
        date_str += " / ";
        if (year < 10)
          date_str += '0';
        date_str += String(year); // values of date,month and year are stored in a string
      }
      if (gps.time.isValid())  //check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        minute = (minute + 30); // converting to IST
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;   // converting to IST
        if (hour >= 12)  // checking whether AM or PM
          pm = 1;
        else
          pm = 0;
        hour = hour % 12;
        if (hour < 10)
          time_str = '0';
        time_str += String(hour); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (minute < 10)
          time_str += '0';
        time_str += String(minute); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (second < 10)
          time_str += '0';
        time_str += String(second); //values of hour,minute and time are stored in a string
        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
      }
    }

  // Send new readings to database

  if (Firebase.ready()){
    // Send readings to database:
    

    sendFloat(latpath, lat_str);
    sendFloat(lonpath, lng_str);
    sendFloat(datepath, date_str);
    sendFloat(timepath, time_str);
  }
  delay(5000);
}