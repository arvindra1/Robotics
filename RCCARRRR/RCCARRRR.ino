#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3;  // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

String readvoice;  // Initialize t to a default value
char t;

// Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  for (int i = 1; i < 10; i++) {
    digitalWrite(5, HIGH);
    delay(100 * i);
    digitalWrite(5, LOW);
    delay(100 * i);
  }
  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    player.playMp3Folder(3);
    delay(4000);
    player.playMp3Folder(1);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // put your main code here, to run repeatedly:
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);


  if (Serial.available() > 0) {
    delay(3);
    t = Serial.read();
    readvoice += t;
  }
  if (readvoice.length() > 0 || t > 0) {

    Serial.println(readvoice);

    if ((readvoice == 'Forward' || t == 'F') && distance > 100) {
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
    } else if ((readvoice == 'Backward' || t == 'B') && distance > 100) {
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
    }
    // else if(readvoice == 'Right' || t=='R'){
    //   digitalWrite(9, HIGH);
    //   digitalWrite(10, LOW);
    //   digitalWrite(11, LOW);
    //   digitalWrite(12, HIGH);
    // }
    //   else if(readvoice == 'Left' || t=='L'){
    //   digitalWrite(9, LOW);
    //   digitalWrite(10, HIGH);
    //   digitalWrite(11, HIGH);
    //   digitalWrite(12, LOW);
    // }
    else if ((readvoice == 'Stop' || t == 'S') && distance <= 100) {
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);

      if (player.begin(softwareSerial)) {
        Serial.println("Hello Sir");

        // Set volume to maximum (0 to 30).
        player.volume(30);
        // Play the "0001.mp3" in the "mp3" folder on the SD card
        player.playMp3Folder(2);  //please take a glass water

        delay(10000);
        // player.playMp3Folder(3);//thank you sir,Have a great day

      } else {
        Serial.println("Connecting to DFPlayer Mini failed!");
      }
    }
  }
  readvoice = "";
}
