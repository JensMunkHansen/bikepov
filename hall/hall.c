#include <Arduino.h>

// Connect 5V and GND
// Signal to digital pin 2

int hallSensorPin = 2;
int ledPin = 13;
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(hallSensorPin, INPUT);
}

int loop() {
  state = digitalRead(hallSensorPin);
  if (state == LOW) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
