const int P34 = 34;       // GPIO34 for the soil moisture sensor
const int pumpPin = 5;    // GPIO5 for the water pump control (connected to the relay)

const int startThreshold = 30;  // Moisture percentage threshold to turn on the pump
const int stopThreshold = 60;   // Moisture percentage threshold to turn off the pump

void setup() {
  Serial.begin(9600);    // Set baud rate for serial communication
  pinMode(pumpPin, OUTPUT);  // Set GPIO5 as an output for the water pump

  // Set initial state of the relay (pump off)
  digitalWrite(pumpPin, HIGH); // Pump OFF (relay not active)
}

void loop() {
  float moisture_percentage;
  int sensor_analog;

  sensor_analog = analogRead(P34);  // Read the analog value from GPIO34

  // Calculate moisture percentage
  moisture_percentage = (100. - ((sensor_analog / 4095.00) * 100. ));

  // Print the moisture percentage to the Serial Monitor
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.println("%");

  // Control the water pump based on the moisture level
  if (moisture_percentage < startThreshold) {
    digitalWrite(pumpPin, LOW); // Turn on the water pump (relay active)
    Serial.println("Pump is ON");
  } else if (moisture_percentage >= stopThreshold) {
    digitalWrite(pumpPin, HIGH);  // Turn off the water pump (relay not active)
    Serial.println("Pump is OFF");
  }

  delay(1000);  // Wait for 1 second before the next reading
}
