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

/* --- LEDS --- */
const int redLedPin = 5;
const int yellowLedPin = 18;
const int greenLedPin = 21;

// Coeficientes para cálculo do volume (polinômio de segundo grau)
const double A = 1.99;
const double B = -104.11;
const double C = 1274.84;

// Calculates the volume based on the height (distance) using the trend equation
double calculateVolume(double height) {
  double volume = A * height * height + B * height + C;
  if (volume < 0) {
    volume = 0; // Ensure volume is not negative
  }
  return volume;
}

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
    delay(500);
  }

  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(redLedPin, LOW);     // turn off the red LED
  digitalWrite(yellowLedPin, LOW);  // turn off the yellow LED
  digitalWrite(greenLedPin, LOW);   // turn off the green LED

  wifiMulti.addAP(STASSID, STAPSK);

  // allow reuse (if server supports it)
  http.setReuse(true);
}

void loop() {

  double distance = readSR();  // Get distance in cm from the HC-SR04
  double volume = calculateVolume(distance);
  // 0 <= D < 10, red
  // 10 <= D < 30, yellow
  // 30 <= D, green

  if (volume >= 800.0 || volume <= 100.0) {
    digitalWrite(redLedPin, HIGH);

    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
  } else if (volume >= 600.0 || volume <= 300.0) {
    digitalWrite(yellowLedPin, HIGH);

    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  } else {
    digitalWrite(greenLedPin, HIGH);

    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  }

  Serial.println("Waiting for wifi connection ...");
  // wait for WiFi connection
  if (wifiMulti.run() == WL_CONNECTED) {

    String jsonData = "{\"distance\": " + String(volume) + "}";  // Create JSON with distance
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

  delay(1000);
}
