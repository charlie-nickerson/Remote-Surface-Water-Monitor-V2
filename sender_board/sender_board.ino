#include <OneWire.h>
#include <DallasTemperature.h>
#include <LoRa.h>
#include <ArduinoLowPower.h>

// Data wire is connected to pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  // Setup DS18B20 sensor
  sensors.begin();

  // Initialize LoRa with the appropriate frequency
  if (!LoRa.begin(915E6)) {
    // Blink an LED rapidly if LoRa fails to start (for debugging)
    pinMode(LED_BUILTIN, OUTPUT);
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }

  // Set the transmission power (can range from 2 to 20)
  LoRa.setTxPower(20);

  // Set the spread factor to increase reliability
  LoRa.setSpreadingFactor(8);

  // Set bandwidth. Higher bandwidth increases reliability but also increases required signal strength
  LoRa.setSignalBandwidth(250E3);
  
  // Indicate LoRa startup success by blinking LED slowly
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Request temperature from DS18B20 sensor
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // Indicate that data is being sent by blinking LED
  digitalWrite(LED_BUILTIN, HIGH);
  
  // Send temperature data over LoRa
  LoRa.beginPacket();
  LoRa.print("Temperature: ");
  LoRa.print(temperatureC);
  LoRa.print(" °C");
  LoRa.endPacket();
  
  digitalWrite(LED_BUILTIN, LOW);

  // Enter sleep mode for 5 minutes
  for (int i = 0; i < 30; i++) {
    LowPower.sleep(10000); // Sleep for 10 seconds (30 times = 300 seconds)
  }
}
