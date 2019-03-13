/*  -*- coding: utf-8; mode: c; indent-tabs-mode: nil -*- */

#include <Arduino.h>

// micros() wraps around after 70 min, resolution is 4 microseconds

// rev/s = km/h * 1000.0 m/km / 3600.0 s/h / 2m
// 60 km/h => 8.3 rev/s
//  4 km/h => 0.55 rev/s

// unsigned long

#if 0
unsigned long prev = 0;
void bla() {
  // It is very unlikely that we hit micros() == 0 (after 71 min)
  unsigned long cur = micros();
  unsigned long diff;
  if (cur > prev) {
    diff = cur - prev;
  } else {
    diff = cur + ( (1 << 32) - prev);
  }
  if ( (diff > 120000) && (diff < 1800000)) {
    // Time to sleep - round up every other time
    // minimum lines is 64, 1800000 / 64 < 2^15
    tts = (diff / nLines) - (elapsed + 900);
  } else {
    tts = 0; // We always spent elapsed + 900
  }
  prev = cur;
}
#endif

// Connect 5V and GND
// Signal to digital pin 2

int hallSensorPin = 2; // Digital pin 2 triggers interrupt 0 on pro5v328
int ledPin = 7;
int state = 0;

volatile byte bstate = HIGH;

volatile byte revolutions = 0;
void magnet_detect()
{
  Serial.println("detect");
  bstate = !bstate;
  revolutions++;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  // Do not set a mode for the IRQ pin
  Serial.begin(9600);
  Serial.println("start");
  attachInterrupt(0, magnet_detect, RISING);
}

void loop() {
  digitalWrite(ledPin, bstate);
  if (revolutions >= 5) {
    detachInterrupt(0);
    Serial.println("low");
    revolutions = 0;
    attachInterrupt(0, magnet_detect, RISING);
  }
}
