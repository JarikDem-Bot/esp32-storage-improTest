static HttpsOTAStatus_t otastatus;
String newETag;
bool abortOta = false;

Ticker otaTicker;

void github_ota_init() {
  HttpsOTA.onHttpEvent(HttpEvent);
  otaTicker.attach(1800, startOta);
}

void startOta() {
  Serial.println("Starting OTA");
  HttpsOTA.begin(otaUrl, server_certificate);
}

void github_ota_tick() {
  otastatus = HttpsOTA.status();
  if (otastatus == HTTPS_OTA_SUCCESS && !abortOta) {
    preferences.putString("ETag", newETag);
    Serial.println("Firmware written successfully. To reboot device, call API ESP.restart() or PUSH restart button on device");
    ESP.restart();
  } else if (otastatus == HTTPS_OTA_FAIL) {
  }
}

void HttpEvent(HttpEvent_t *event)
{
  switch (event->event_id) {
    case HTTP_EVENT_ERROR:
      Serial.println("Http Event Error");
      break;
    case HTTP_EVENT_ON_CONNECTED:
      Serial.println("Http Event On Connected");
      break;
    case HTTP_EVENT_HEADER_SENT:
      Serial.println("Http Event Header Sent");
      abortOta = false;
      break;
    case HTTP_EVENT_ON_HEADER:
      Serial.printf("Http Event On Header, key=%s, value=%s\n", event->header_key, event->header_value);
      if (strcasecmp(event->header_key, "ETag") == 0) {
        String ETag = preferences.getString("ETag", "");
        if(ETag == event->header_value) {
          abortOta = true;
          Serial.println("Firmware is up to date. OTA upload abort.");
        } else {
          newETag = event->header_value;
        }
      }
      break;
    case HTTP_EVENT_ON_DATA:
      if(abortOta) {
        Serial.println("OTA update aborted");
        break;
      }
      break;
    case HTTP_EVENT_ON_FINISH:
      Serial.println("Http Event On Finish");
      break;
    case HTTP_EVENT_DISCONNECTED:
      Serial.println("Http Event Disconnected");
      break;
  }
}
