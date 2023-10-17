#define BLYNK_TEMPLATE_ID "TMPL3qaTt8pGv"
#define BLYNK_TEMPLATE_NAME "IoT based liquid temperature monitoring"
#define BLYNK_AUTH_TOKEN "d63XTdTLRBdfgdf_R90G98_wtmQ34QSzCbR4k"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Data wire is connected to GPIO 13
#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "impulsetech";
char pass[] = "impulse567";
BlynkTimer timer;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  sensors.begin();

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  while (!Blynk.connected()) {
    Serial.println("Connecting to Blynk...");
    delay(1000);
  }
  Serial.println("Connected to Blynk");
}

void loop() {
  sensors.requestTemperatures(); // Request temperature readings
  
  // Replace 'YourSensorName' with a descriptive name for your sensor
  float temperatureC = sensors.getTempCByIndex(0); // Index 0 for the first sensor found
  
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature (°C): ");
    Serial.println(temperatureC, 2); // Print temperature with 2 decimal places
  } else {
    Serial.println("Error: Unable to read temperature.");
  }
  Blynk.virtualWrite(V0, temperatureC);
  delay(1000);

  // Run the Blynk loop
  Blynk.run();
}
