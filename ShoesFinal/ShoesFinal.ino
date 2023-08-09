
//Created by Arvindra Ahirwar

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Create a TinyGPS++ object
TinyGPSPlus gps;

// GPS module connection
#define RXPin D2
#define TXPin D3

// Define the GSM module pins
#define GSM_TX_PIN D4
#define GSM_RX_PIN D5

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
// Create a software serial port called "gsmSerial"
SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);

// Define the latitude and longitude range for the location
const float targetLatitude = 37.12345; // Change this to your desired latitude
const float targetLongitude = -122.67890; // Change this to your desired longitude
const float tolerance = 0.001; // Change this tolerance value as needed

void setup() {
  // put your setup code here, to run once:
  gpsSerial.begin(9600);  // Setting the baud rate for GPS Module
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)

  // Set the baud rate for the serial communication with the GSM module
  gsmSerial.begin(9600);

  // Initialize the GSM module by sending AT commands
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read()))
      displayInfo();
  }
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS detected");
    while (true);
  }
  delay(2000);
}

void displayInfo() {
  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng(); 
    Serial.print("Latitude: "); 
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

    // Check if the current location is within the target range
    // if (abs(latitude - targetLatitude) < tolerance && abs(longitude - targetLongitude) < tolerance) {
     
     if ((latitude<28.643800 && latitude>28.643600)&&(longitude>77.294300 && longitude < 77.294600) ) {
      Serial.print("Safe");
       sendSMS("+919267969899", "Hello, Safe!");
    }
  }
  else {
    Serial.println("Location:danger");
    sendSMS("+919267969899", "Hello, Child is not in safe!");
  }
}

void sendSMS(const char* phoneNumber, const char* message) {
  // AT command to set the phone number
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);

  // Send the message
  gsmSerial.print(message);
  delay(100);
  gsmSerial.write(26); // End of message character (Ctrl+Z)
  delay(1000);
}
