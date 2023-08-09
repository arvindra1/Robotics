

// Paste the  BLYNK_TEMPLATE_ID,BLYNK_TEMPLATE_NAME,BLYNK_AUTH_TOKEN

#define BLYNK_TEMPLATE_ID "TMPL3tUoZaK6A"
#define BLYNK_TEMPLATE_NAME "rob"
#define BLYNK_AUTH_TOKEN "c16Ayf7feObBCiLU2CPXGtnIJZ_53-6p"

//Include the library files
#include<Servo.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo servo;

#define in1 D1
#define in2 D2
#define in3 D3
#define in4 D3
int relay=0;

#define target D5

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Kon Ho";
char pass[] = "kumar7654";

void setup()
{
// Debug console
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);

servo.attach(7);
 Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

BLYNK_WRITE(V0)
{
relay=param.asInt();

if(relay==1)
{
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
}
else{
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);

}
}
BLYNK_WRITE(V1)
{
relay=param.asInt();
if(relay==1)
{
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
}
else{
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
}

}
BLYNK_WRITE(V2)
{
relay=param.asInt();

if(relay==1)
{
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
}
else{
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);

}
}
BLYNK_WRITE(V3)
{
relay=param.asInt();

if(relay==1)
{
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
}
else{
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);


}
}

BLYNK_WRITE(V4)
{
digitalWrite(target,param.asInt());
}

BLYNK_WRITE(V5)
{
relay=param.asInt();

if(relay==1)
{
servo.write(150);
}
else{
servo.write(0);
}
}

void loop()
{
Blynk.run();
}