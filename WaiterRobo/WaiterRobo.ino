
// defines pins numbers
#define trigPin 11  
#define echoPin 10

#define motor1 2
#define motor2 3
#define motor3 4
#define motor4 5


// defines variables
long duration;
float distance;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   pinMode(motor1,OUTPUT);
   pinMode(motor2,OUTPUT);
   pinMode(motor3,OUTPUT);
   pinMode(motor4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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

  if(distance>10 && distance<200)
  {
   digitalWrite(motor1,HIGH);
   digitalWrite(motor2,LOW);
   digitalWrite(motor3,HIGH);
   digitalWrite(motor4,LOW);
  }
  else if(distance)

}
