

String readvoice;  // Initialize t to a default value
char t;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    delay(3);
    t = Serial.read();
    Serial.println(t);
    readvoice += t;
  }
  if (readvoice.length() > 0 || t > 0) {

    // Serial.println(readvoice);

    if (readvoice == 'Forward' || t == 'F') {
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
    } else if (readvoice == 'Backward' || t == 'B') {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
    }
    else if(readvoice == 'Right' || t=='R'){
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
    }
      else if(readvoice == 'Left' || t=='L'){
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
    }
    else if (readvoice == 'Stop' || t == 'S') {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
  }
  readvoice = "";
}
}
