#include<Servo.h>
Servo servo1;
Servo servo2;


void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
  servo2.attach(3);
  pinMode(6,OUTPUT);
servo2.write(100);
  for(int a=1;a<=8;a++)
  {
   digitalWrite(6,HIGH);
  delay(200); 
   digitalWrite(6,LOW);
  delay(200); 
  }


}

void loop() {
	
  
servo1.write(120);

servo2.write(0);
delay(2000);
  servo1.write(0);
servo2.write(100);
delay(2000);



}
