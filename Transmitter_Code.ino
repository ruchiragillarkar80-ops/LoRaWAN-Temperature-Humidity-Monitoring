#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 4      // changed to D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println("LoRa Transmitter with DHT11");

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa failed!");
    while (1);
  }
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT!");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Hum: ");
  Serial.print(hum);
  Serial.println(" %");

  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.print(",");
  LoRa.print(hum);
  LoRa.endPacket();

  delay(2000);
}