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
File uploadFile;


void handleRoot() {
  String html = HTML_HOME_PAGE;
  server.send(200, "text/html", html);
}

String get_directory_list(File root) {
  String result = "{\"files\": [";

  if (!root) {
    Serial.println("Failed to open directory");
    result += "]}";
    return result;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      if ((String)file.name() != "/System Volume Information")result += get_directory_list(file);
    } else {
      result += "\n{\"name\": \"";
      result += file.name();
      result += "\",\n\"size\": ";
      result += file.size();
      result += "},";
    }
    file = root.openNextFile();
  }
  if (result.endsWith(",")) {
    result.remove(result.length() - 1);
  }
  result += "]}";
  return result;
}

void handleList() {
  String response = get_directory_list(SD.open("/"));
  server.send(200, "application/json", response);
}

void handleDelete() {
  if (server.uri() != "/delete") {
    return;
  }

  String filename = server.arg(0);
  if (!filename.startsWith("/")) filename = "/" + filename;

  SD.remove(filename);

  String response = get_directory_list(SD.open("/"));
  server.send(200, "application/json", response);
}

void handleDownload() {
  if (server.uri() != "/download") {
    return;
  }
  String filename = server.arg(0);
  if (!filename.startsWith("/")) filename = "/" + filename;

  File file = SD.open(filename);
  if (file) {
    server.streamFile(file, "form-data");
  }
  file.close();
}

void handleUpload() {
  if (server.uri() != "/upload") {
    return;
  }

  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    Serial.print("Upload File Name: "); Serial.println(filename);
    SD.remove(filename);
    uploadFile = SD.open(filename, FILE_WRITE);
    //filename = String();
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    if (uploadFile) {
      uploadFile.write(upload.buf, upload.currentSize);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (uploadFile)
    {
      uploadFile.close();
      Serial.print("Upload Size: "); Serial.println(upload.totalSize);
      String response = get_directory_list(SD.open("/"));
      server.send(200, "application/json", response);
    }
    else
    {
      Serial.println("Unable to close file");
    }
  }
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

void serverRoute() {
  server.on("/", handleRoot);
  server.on("/list", HTTP_GET, handleList);
  server.on("/delete", HTTP_DELETE, handleDelete);
  server.on("/download", HTTP_POST, handleDownload);
  server.on("/upload", HTTP_POST, []() {
    server.send(200);
  }, handleUpload);
  server.onNotFound(handleNotFound);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

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

  serverRoute();
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);
}
