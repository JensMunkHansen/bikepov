#include <Arduino.h>

// Connect 5V and GND
// Signal to digital pin 2

int hallSensorPin = 9;
int ledPin = 7;
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(hallSensorPin, INPUT);
}

void loop() {
  state = digitalRead(hallSensorPin);
  if (state == LOW) {
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, HIGH);
  }
}
