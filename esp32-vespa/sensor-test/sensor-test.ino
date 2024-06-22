/*
 * ---- References ----
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient/examples/ReuseConnection
 * https://raw.githubusercontent.com/RuiSantosdotme/Random-Nerd-Tutorials/master/Projects/ESP32/ESP32_HC_SR04.ino
 * https://www.robocore.net/placa-robocore/vespa
*/

#include <Arduino.h>

/* --- HC-SR04 --- */
const int trigPin = 19;
const int echoPin = 23;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

/* --- LEDS --- */
const int redLedPin = 5;
const int yellowLedPin = 18;
const int greenLedPin = 21;

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

  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(redLedPin, LOW);     // turn off the red LED
  digitalWrite(yellowLedPin, LOW);  // turn off the yellow LED
  digitalWrite(greenLedPin, LOW);   // turn off the green LED

}

void loop() {

  double distance = readSR();  // Get distance in cm from the HC-SR04

  // 0 <= D < 10, red
  // 10 <= D < 30, yellow
  // 30 <= D, green

  if (distance >= 30.0) {
    digitalWrite(greenLedPin, HIGH);

    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
  } else if (distance >= 10.0) {
    digitalWrite(yellowLedPin, HIGH);

    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  } else {
    digitalWrite(redLedPin, HIGH);

    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
  }
    String jsonData = "{\"distance\": " + String(distance) + "}";  // Create JSON with distance
    Serial.println(jsonData);

  delay(500);
}
