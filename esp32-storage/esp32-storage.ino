#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

#include "index.h"
#include "password.h"

WebServer server(80);
StaticJsonDocument<250> jsonDocument;



void handleRoot() {
  String html = HTML_HOME_PAGE;
  server.send(200, "text/html", html);
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void listDir() {
  printDirectory(SD.open("/"), 0);
}

void handleUpload() {
  Serial.println("Inside upload");
  if (server.hasArg("plain") == false) {
  }

  String body = server.arg("plain");

  if (server.uri() != "/upload") {
    Serial.println("Return");
    return;
  }
  File uploadFile;
  HTTPUpload& upload = server.upload();
  listDir();
  Serial.print("Status: "); Serial.println(upload.status);
  Serial.println("Before if");
  uploadFile = SD.open((String("/") + upload.filename).c_str(), FILE_WRITE);
  if (upload.status == UPLOAD_FILE_START) {
    Serial.println("if status upload");
    if (SD.exists((char *)upload.filename.c_str())) {
      Serial.println("remove file");
      SD.remove((char *)upload.filename.c_str());
    }
    Serial.println("before opening");
    
    Serial.print("Upload: START, filename: "); Serial.println(upload.filename);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Serial.println("if write");
    if (uploadFile) {
      Serial.println("writing");
      uploadFile.write(upload.buf, upload.currentSize);
    }
    Serial.print("Upload: WRITE, Bytes: "); Serial.println(upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.println("upload file end");
    if (uploadFile) {
      Serial.println("closing");
      uploadFile.write(upload.buf, upload.currentSize);
      uploadFile.close();
    }
    Serial.print("Upload: END, Size: "); Serial.println(upload.totalSize);
  }

  Serial.println(body);
  Serial.println(server.arg(0));
  listDir();
  String response = "{\"state\": \"Is it works?\"}";
  server.send(200, "application/json", response);
}

void handleNotFound() {
  server.send(404, "text/html", "<h1>404 Not found</h1><a href=\"/\">Return to main page</a>");
}

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

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(2, OUTPUT);
  SD_init();

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

  server.on("/", handleRoot);
  server.on("/upload", HTTP_POST, handleUpload);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);
}
