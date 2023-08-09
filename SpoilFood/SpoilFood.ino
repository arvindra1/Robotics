

#define METHANE_SENSOR A0   // Analog pin connected to the methane gas sensor
#define METHANE_THRESHOLD 100  // Methane gas concentration threshold for spoilage detection (adjust as needed)

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read methane gas concentration from the sensor
  float methaneConcentration = methaneMQTT.readCO2();

  // Check if the sensor reading is successful
  if (isnan(methaneConcentration)) {
    Serial.println("Failed to read from the methane gas sensor!");
    return;
  }

  // Print methane gas concentration on the serial monitor
  Serial.print("Methane (ppm): ");
  Serial.println(methaneConcentration);

  // Check for spoiled food conditions
  if (methaneConcentration > METHANE_THRESHOLD) {
    Serial.println("Spoiled food detected!");
    // You can add further actions here, like sending a notification or activating an alarm.
    // For simplicity, we are just printing a message on the serial monitor.
  }

  delay(5000); // Delay for 5 seconds before taking the next sensor reading
}
