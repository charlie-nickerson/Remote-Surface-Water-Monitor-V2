#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  // Initialize LoRa with a frequency of 915 MHz (adjust according to your region)
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: ");

    // Read packet
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print(received);
    }

    // Print RSSI (Received Signal Strength Indicator)
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}