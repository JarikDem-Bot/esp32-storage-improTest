#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#include "index.h"
#include "password.h"

WebServer server(80);
StaticJsonDocument<250> jsonDocument;

void handleRoot() {
  String html = HTML_HOME_PAGE;
  String led_state = "Off";
  if(digitalRead(2)) led_state = "On";
  html.replace("%LED_STATE%", led_state);
  server.send(200, "text/html", html);
}
  
void handleToggle() {
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  
  String foo = server.arg("foo");
  String blah = server.arg("blah");
  Serial.println(foo);
  Serial.println(blah);
  
  digitalWrite(2, !digitalRead(2));
  String led_state = "Off";
  if(digitalRead(2)) led_state = "On";
  
  String response = "{\"state\": \"%LED_STATE%\"}";
  response.replace("%LED_STATE%", led_state);
  server.send(200, "application/json", response);
}

void handleNotFound() {
  server.send(404, "text/html", "<h1>404 Not found</h1><a href=\"/\">Return to main page</a>");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(2, OUTPUT);
  
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
  server.on("/toggle-led", HTTP_POST, handleToggle);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);
}
