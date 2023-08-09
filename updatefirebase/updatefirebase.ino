#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "your-firebase-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-authentication-secret"
#define WIFI_SSID "your-wifi-ssid"
#define WIFI_PASSWORD "your-wifi-password"

#define GPS_RX_PIN D3
#define GPS_TX_PIN D4
#define BAUD_RATE 9600

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize GPS
  gpsSerial.begin(BAUD_RATE);
  
  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isUpdated()) {
        double latitude = gps.location.lat();
        double longitude = gps.location.lng();
        
        Serial.print("Latitude: ");
        Serial.println(latitude, 6);
        Serial.print("Longitude: ");
        Serial.println(longitude, 6);
        
        updateFirebase(latitude, longitude);
      }
    }
  }
}

void updateFirebase(double latitude, double longitude) {
  Firebase.setString(firebaseData, "/gps/latitude", String(latitude, 6));
  Firebase.setString(firebaseData, "/gps/longitude", String(longitude, 6));

  if (firebaseData.dataAvailable()) {
    if (firebaseData.success()) {
      Serial.println("Firebase update successful");
    } else {
      Serial.println("Firebase update failed");
      Serial.println(firebaseData.errorReason());
    }
  }
}
