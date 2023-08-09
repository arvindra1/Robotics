#include<Servo.h>
Servo servo;
#define cm5 A0


void setup() {
  // put your setup code here, to run once:
  pinMode(cm5,INPUT);
  servo.attach(9);


}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(cm5)>1500 && analogRead(cm5)<=2000 )
  {
    servo.write(90);
  }
  else{
    servo.write(0);
  }

}
