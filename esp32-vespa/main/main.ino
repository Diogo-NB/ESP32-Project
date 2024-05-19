/*
 * ---- References ----
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient/examples/ReuseConnection
 * https://raw.githubusercontent.com/RuiSantosdotme/Random-Nerd-Tutorials/master/Projects/ESP32/ESP32_HC_SR04.ino
 * https://www.robocore.net/placa-robocore/vespa
*/

#include <Arduino.h>

/* --- Wifi & HTTP Client --- */
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define STASSID "WIFI_SSID"
#define STAPSK "WIFI_PSWRD"
#define HOST "SERVER_IP"
#define PORT 3000

WiFiMulti wifiMulti;

HTTPClient http;

/* --- HC-SR04 --- */
const int trigPin = 19;
const int echoPin = 23;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

// Returns the distance read in cm
double readSR() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(echoPin, HIGH);

  // Calculates and returns the distance
  return (double)duration * SOUND_SPEED / 2.0;
}

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

  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  wifiMulti.addAP(STASSID, STAPSK);

  // allow reuse (if server supports it)
  http.setReuse(true);
}

void loop() {

  Serial.println("Waiting for wifi connection ...");
  // wait for WiFi connection
  if (wifiMulti.run() == WL_CONNECTED) {
    double distance = readSR();  // Get distance in cm from the HC-SR04

    String jsonData = "{\"distance\": " + String(distance) + "}";  // Create JSON with distance
    Serial.println(jsonData);

    // http.begin() declaration: bool begin(String host, uint16_t port, String uri = "/");
    String uri = "/add-measurement";
    http.begin(HOST, PORT, uri);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(jsonData);

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

  delay(1500);
}
