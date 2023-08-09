#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define the RX and TX pins for the GPS module
#define GPS_RX_PIN 10
#define GPS_TX_PIN 11

// Create a SoftwareSerial object to communicate with the GPS module
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);      // Initialize the serial communication
  gpsSerial.begin(9600);   // Initialize the software serial for GPS module
}

void loop() {
  // Read the GPS data if available
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Check if GPS data is valid
      if (gps.location.isValid()) {
        // Retrieve latitude and longitude
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Print latitude and longitude
        Serial.print("Latitude: ");
        Serial.println(latitude, 6);
        Serial.print("Longitude: ");
        Serial.println(longitude, 6);
    
  }
}
}
}