/*
 * ---- Reference ----
 * https://raw.githubusercontent.com/RuiSantosdotme/Random-Nerd-Tutorials/master/Projects/ESP32/ESP32_HC_SR04.ino
*/

#include <Arduino.h>

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
}

void loop() {

  double distance = readSR();  // Get distance in cm from the HC-SR04

  Serial.println("Distance: " + + String(distance) + "cm");

  delay(500);
}
