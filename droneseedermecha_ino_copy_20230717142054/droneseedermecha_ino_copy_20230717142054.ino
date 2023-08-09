#include <SoftwareSerial.h>

#include<Servo.h>

Servo servo;
#define CH5 10
int ch5Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CH5,INPUT);
  servo.attach(9);
  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
   ch5Value = readChannel(CH5, 100, -100, 0);
   Serial.println(ch5Value);


   
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
