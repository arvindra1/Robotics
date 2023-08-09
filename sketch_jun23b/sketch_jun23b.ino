#include <TinyGPS++.h>  // library for GPS module
#include <SoftwareSerial.h>

TinyGPSPlus gps;          // The TinyGPS++ object
SoftwareSerial ss(4, 5);  // The serial connection to the GPS device

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.println("GPS Test");
}

void loop() {
  while (ss.available() > 0)  //while data is available
  {
    if (gps.encode(ss.read()))  //read gps data
    {
      if (gps.location.isValid())  //check whether gps location is valid
      {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);  // print latitude with 6 decimal places
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);  // print longitude with 6 decimal places
    
      }
  
    }

  }
}