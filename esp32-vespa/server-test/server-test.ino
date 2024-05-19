/**
 * reuseConnection.ino
 *
 *  Created on: 22.11.2015
 *
 */


#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define STASSID "WIFI_SSID"
#define STAPSK "WIFI_PSWRD"
#define HOST "SERVER_IP"
#define PORT 3000

WiFiMulti wifiMulti;

HTTPClient http;

void setup() {

  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  wifiMulti.addAP(STASSID, STAPSK);

  // allow reuse (if server supports it)
  http.setReuse(true);
}

void loop() {
  // wait for WiFi connection
  Serial.println("Waiting for wifi connection ...");
  if ((wifiMulti.run() == WL_CONNECTED)) {

    String uri = "/test";
    http.begin(HOST, PORT, uri);

    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST("{\"distance\": 0.0}");
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        // http.writeToStream(&Serial); // Using stream
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(1000);
}
