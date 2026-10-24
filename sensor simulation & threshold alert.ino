#include <DHT.h>

#define DHTPIN 2        // Digital pin connected to the DHT22 sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)
#define ALERT_LED 13    // Digital pin for the threshold alert LED

DHT dht(DHTPIN, DHTTYPE);

const float TEMPERATURE_THRESHOLD = 30.0; // 30 degrees Celsius threshold

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 Sensor Simulation - Threshold Alert"));
  
  pinMode(ALERT_LED, OUTPUT);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements (DHT22 needs ~2 seconds)
  delay(2000);

  // Read temperature as Celsius
  float tempCelsius = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(tempCelsius)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the current temperature to the Serial Monitor
  Serial.print(F("Temperature: "));
  Serial.print(tempCelsius);
  Serial.println(F("°C"));

  // Check if temperature exceeds the 30°C threshold
  if (tempCelsius >= TEMPERATURE_THRESHOLD) {
    digitalWrite(ALERT_LED, HIGH);  // Turn on alert LED
    Serial.println(F("[ALERT] Temperature threshold exceeded! (> 30°C)"));
  } else {
    digitalWrite(ALERT_LED, LOW);   // Turn off alert LED
  }
}
