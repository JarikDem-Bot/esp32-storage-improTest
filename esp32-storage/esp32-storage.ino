#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <SPI.h>
#include <SD.h>
#include <FastBot.h>
#include <HttpsOTAUpdate.h>
#include <Preferences.h>
#include <Ticker.h>

#include "index.h"
#include "notFound.h"
#include "password.h"

FastBot bot(BOT_TOKEN);
WebServer server(80);
Preferences preferences;

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

void connect_wifi() {
  WiFiManager wifiManager;

  bool res;

  res = wifiManager.autoConnect("ESP32 Storage");
  wifiManager.setDarkMode(true);

  if (!res) {
    Serial.println("Failed to connect. Restarting board");
    ESP.restart();
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  preferences.begin("my-app", false);

  SD_init();

  connect_wifi();

  github_ota_init();

  server_route();
  server.begin();
  Serial.println("HTTP server started");

  tg_init();
}

void loop() {
  github_ota_tick();
  server.handleClient();
  bot.tick();
  delay(2);
}
