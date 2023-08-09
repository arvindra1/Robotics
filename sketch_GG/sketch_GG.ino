 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("shivansh is a student of class 9A./n");
  pinMode(5,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Aamir is a student of class 9A");
  digitalWrite(5,HIGH);
  delay(1);
  digitalWrite(5,LOW);
  delay(2);


}
