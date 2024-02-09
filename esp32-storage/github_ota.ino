static HttpsOTAStatus_t otastatus;

void github_ota_init() {
  HttpsOTA.onHttpEvent(HttpEvent);
  Serial.println("Starting OTA");
  HttpsOTA.begin(otaUrl, redirect_certificate);
}

void github_ota_tick() {
  otastatus = HttpsOTA.status();
  if (otastatus == HTTPS_OTA_SUCCESS) {
    Serial.println("Firmware written successfully. To reboot device, call API ESP.restart() or PUSH restart button on device");
  } else if (otastatus == HTTPS_OTA_FAIL) {
    //Serial.println("Firmware Upgrade Fail");
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
      break;
    case HTTP_EVENT_ON_HEADER:
      Serial.printf("Http Event On Header, key=%s, value=%s\n", event->header_key, event->header_value);
      //if (strcasecmp(event->header_key, "Location") == 0) {
        //Serial.printf("Redirecting to: %s\n", event->header_value);

        // Set the new OTA URL and initiate a new connection
        //HttpsOTA.begin(event->header_value, redirect_certificate);
      //}
      break;
    case HTTP_EVENT_ON_DATA:
      break;
    case HTTP_EVENT_ON_FINISH:
      Serial.println("Http Event On Finish");
      break;
    case HTTP_EVENT_DISCONNECTED:
      Serial.println("Http Event Disconnected");
      break;
  }
}