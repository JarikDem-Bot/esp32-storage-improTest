#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>
#include <FastBot.h>

#include "index.h"
#include "notFound.h"
#include "password.h"

FastBot bot(BOT_TOKEN);

WebServer server(80);

void SD_init() {
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void connectWifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Web server at: ");
  Serial.print(WiFi.localIP()); Serial.println(":80");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  SD_init();

  connectWifi();

  serverRoute();
  server.begin();
  Serial.println("HTTP server started");

  tg_init(); 
}

void loop() {
  server.handleClient();
  bot.tick();
  delay(2);
}
