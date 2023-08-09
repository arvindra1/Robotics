// NodeMCU Pin to which the raindrop sensor is connected
const int raindropSensorPin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(raindropSensorPin, INPUT);
}

void loop() {
  // Read the value from the raindrop sensor
   float sensorValue=(100.00-((analogRead(raindropSensorPin)/1023.00)*100.00));

  Serial.println(sensorValue);

  delay(1000); // You can adjust the delay as needed
}
