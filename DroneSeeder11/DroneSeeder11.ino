
#include <dht.h>
#include<Servo.h>

dht DHT11;
Servo servo;

#define CH5 10

int ch5Value;
const int ldrPin = A0;
const int dhtPin = 2;


int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void rain(int DhtPin, int ldrpin){
int chk = DHT11.read(DhtPin);

int ldrValue = analogRead(ldrPin); // Read LDR value
if (ldrValue < 500 && DHT11.humidity > 70) {
  Serial.println("");

   }
   else{

   }

}

void setup() {
  // put your setup code here, to run once:
  pinMode(CH5,INPUT);
  servo.attach(9);
  Serial.begin(115200);
  pinMode(ldrPin, INPUT); // Set LDR pin as input



}

void loop() {
  // put your main code here, to run repeatedly:
   ch5Value = readChannel(CH5, 100, -100, 0);
   Serial.println(ch5Value);

  //  rain detection
   rain(dhtPin, ldrPin);

  if(ch5Value>80)
  {
    servo.write(0);
    delay(500);
    servo.write(90);
    delay(500);
  }
  else{
    servo.write(0);
  }
delay(500);
}
