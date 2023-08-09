#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//Create a TinyGPS++ object
TinyGPSPlus gps;
// GPS module connection
#define RXPin 10
#define TXPin 9

// Define the GSM module pins
//#define GSM_TX_PIN D4
//#define GSM_RX_PIN D5

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
// Create a software serial port called "gsmSerial"
//SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);

void setup() {
  // put your setup code here, to run once:
    gpsSerial.begin(9600);  // Setting the baud rate for GPS Module
    Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
    // Set the baud rate for the serial communication with the GSM module
    //gsmSerial.begin(9600);
    // Initialize the GSM module by sending AT commands
  //gsmSerial.println("AT");
  //delay(1000);
  //gsmSerial.println("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (gpsSerial.available() > 0)
  {
     if (gps.encode(gpsSerial.read()))
      displayInfo(); 
  }
   // If 5000 milliseconds pass and there are no characters coming in
   // over the software serial port, show a "No GPS detected" error
   if (millis() > 5000 && gps.charsProcessed() < 10)
   {
     Serial.println("No GPS detected");
     while (true);
   }
   delay(2000);

}

void displayInfo()
{
  if (gps.location.isValid())
  {
    float latitude = (gps.location.lat());
    float longitude = (gps.location.lng()); 
    Serial.print("Latitude: "); 
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
// define the condition for particular location
  //if(true){
    ///sendSMS("+1234567890", "Hello, this is a test message from Arduino!");
  //}
  //else{

 // }


 // }
 // else

  ///{
    //Serial.println("Location: Not Available");
  //}


//void sendSMS(const char* phoneNumber, const char* message) {
  // AT command to set the phone number
  //gsmSerial.print("AT+CMGS=\"");
  //gsmSerial.print(phoneNumber);
  //gsmSerial.println("\"");
  //delay(1000);

  // Send the message
 // gsmSerial.print(message);
  //delay(100);
 //gsmSerial.write(26); // End of message character (Ctrl+Z)
  //delay(1000);
//}

