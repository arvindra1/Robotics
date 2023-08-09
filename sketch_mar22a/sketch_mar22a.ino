
void setup(){
  Serial.begin(9600);
Serial.print("It is setup block.");
pinMode(13,OUTPUT);
  
}   

void loop(){ 
  Serial.print("It is Loop block.\n");
  Serial.print("Uday");
  delay(1000);   

  digitalWrite(13,HIGH); 
  delay(100);
  digitalWrite(13,LOW); 
  delay(100);

}