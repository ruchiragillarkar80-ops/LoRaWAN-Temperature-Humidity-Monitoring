#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa failed!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String data = "";

    while (LoRa.available()) {
      data += (char)LoRa.read();
    }

    int commaIndex = data.indexOf(',');

    String temp = data.substring(0, commaIndex);
    String hum = data.substring(commaIndex + 1);

    display.clearDisplay();

    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.setCursor(0, 30);
    display.print("Hum: ");
    display.print(hum);
    display.println(" %");

    display.display();
  }
}