/*  -*- coding: utf-8; mode: c; indent-tabs-mode: nil -*- */
//PERSISTENCE OF VISION PROJECT
//AUTHOR: JES�S VICENTE PINPANPLOT@GMAIL.COM 2017
//Persistence of Vision Project by Jesús Vicente is licensed under a Creative Commons Reconocimiento 4.0 Internacional License.
/////////////////////////
//CONNECTIONS:
//////////////////////////
//HALL SENSOR IN D2 (RESISTOR 10K BETWEEN HALL SIGNAL AND HALL POSITIVE)
//ARDUINO NANO AND UNO: APA102 (or similar) 'DATA' TO MOSI (D11) AND 'CLOCK' TO SCK (D13) 
//ARDUINO MEGA: APA102 (or similar) 'DATA' TO MOSI (D51) AND 'CLOCK' TO SCK (D52)
//NOT CONNECT APA102 REVERSED!!! (POSIBLE DAMAGE)
//GND ARDUINO AND GND APA102 MUST BE CONNECTED
//POWER SUPPLY OF APA102 IS EXTERNAL FROM ARDUINO
//////////////////////////
//////////////////////////
const uint8_t chipled[] PROGMEM = {0};
const uint8_t numstrip[] PROGMEM = {1};
const uint8_t numradios[] PROGMEM = {1};
const uint8_t radio1directo[] PROGMEM = {1};
const uint8_t radio2directo[] PROGMEM = {1};
const uint8_t radio2180[] PROGMEM = {0};
const uint8_t offset1[] PROGMEM = {0};
const uint8_t offset2[] PROGMEM = {0};
const uint8_t brillo[] PROGMEM = {128};
const uint8_t animate[] PROGMEM = {0};
const uint8_t num_leds[] PROGMEM = {30};
const uint16_t numpasos[] PROGMEM = {46};
const uint16_t angreducido[] PROGMEM = {58};
const uint16_t sizePolarRedu[] PROGMEM = {264};
const uint8_t PolarRedu[264] PROGMEM = {0,1,5,0,2,5,0,3,5,0,4,5,0,5,5,0,6,5,0,7,5,0,8,5,0,9,5,0,10,5,0,11,5,0,12,5,0,13,5,0,14,5,0,15,5,0,16,5,0,17,5,0,18,5,0,19,5,0,20,5,0,21,5,0,22,5,0,23,5,0,24,5,0,25,5,0,26,5,0,27,5,0,28,0,0,29,0,0,30,0,17,15,0,18,14,0,18,16,0,18,17,0,19,13,0,19,18,0,21,12,0,21,19,0,23,20,0,25,11,0,28,21,0,33,10,0,38,21,5,45,20,5,50,19,5,53,10,5,53,18,5,56,17,5,58,16,5,59,11,5,60,15,5,61,12,5,62,13,5,62,14,5,98,20,0,99,18,0,99,19,0,100,17,0,6,17,5,7,18,5,7,19,5,8,20,5,46,12,0,46,13,0,47,11,0,47,14,0,48,15,0,50,16,0,51,10,0,52,17,0,55,18,0,58,19,0,63,20,0,64,9,0,68,9,5,72,21,0,78,21,5,80,10,5,83,20,5,84,11,5,86,19,5,87,12,5,88,18,5,89,13,5,89,17,5,90,14,5,90,15,5,90,16,5};
#include <avr/pgmspace.h>
#include "FastLED.h"
CRGB leds[141];
int angulo;
unsigned int numled;
unsigned int k = 0;
bool pasa = false;
bool cambiaLed = false;
long tiempoDibujo = 0;
long periodo = 0;
long periodoini = 0;
long previoustime = 0;
long tiempo = 0;
long contaseconds = 0;
unsigned int ang = 360;
long tvariable = 0;
int tiempoescritura = 700;
byte LedColour = 0;
byte vred = 0;
byte vgreen = 0;
byte vblue = 0;
int angAux = 0;
int anginicio = 360;
int kinicial = 0;
int contaang = 0;
long tiempoanimate = 0;
void setup() {
//Para resetear
pinMode(A2, INPUT);
digitalWrite(A2, LOW);
FastLED.addLeds<APA102>(leds, pgm_read_byte(num_leds + 0) + pgm_read_byte(offset1 + 0));
FastLED.setBrightness(pgm_read_byte(brillo + 0));
attachInterrupt(digitalPinToInterrupt(2), pasaIman, RISING);
memset(leds, 0, 141*3);
FastLED.show();
}
void loop() {
if (pasa == true) {
pasa = false;
tiempo = micros();
periodoini = tiempo - previoustime;
periodo = tiempo - previoustime - tvariable ;
//periodo teorico
tiempoDibujo = periodo / 360;
if (tiempoDibujo < 0) tiempoDibujo = 0;
previoustime = tiempo;
k = 0;
angulo = pgm_read_byte(PolarRedu + k);
if (k / 3 >= pgm_read_word_near(angreducido + 0)) {
angulo += 255;
};
contaang=0;
for (ang = 0; ang < 360 ; ang++) {
contaang++;
cambiaLed = false;
while (angulo == ang) {
cambiaLed = true;
if (pgm_read_byte(radio1directo + 0) == 1) {
numled = pgm_read_byte(PolarRedu + k+1) - 1 + pgm_read_byte(offset1 + 0);
} else {
//inverso es cero
numled = pgm_read_byte(num_leds + 0) - pgm_read_byte(PolarRedu + k+1) + pgm_read_byte(offset1 + 0);
}
LedColour = pgm_read_byte(PolarRedu + k+2);
//color option 0
vred = 0;
vgreen = 0;
vblue = 0;
if (LedColour == 4 || LedColour == 6 || LedColour == 7 || LedColour == 1) {
vblue = 255;
}
if (LedColour == 3 || LedColour == 5 || LedColour == 6 || LedColour == 1) {
vgreen = 255;
}
if (LedColour == 2 || LedColour == 5 || LedColour == 7 || LedColour == 1) {
vred = 255;
}
leds[numled].r = vred;
leds[numled].g = vgreen;
leds[numled].b = vblue;
k += 3;
if (k >= pgm_read_word_near(sizePolarRedu + 0)) {
angulo = 999;
}else{
angulo = pgm_read_byte(PolarRedu + k);
if (k / 3 >= pgm_read_word_near(angreducido + 0)) {
angulo += 255;
}
}
}
if (cambiaLed == true) {
FastLED.show();
if (tiempoDibujo > tiempoescritura) {
delayMicroseconds(tiempoDibujo - tiempoescritura);
}
} else {
if (tiempoDibujo > tiempoescritura) {
delayMicroseconds(tiempoDibujo + tiempoescritura * pgm_read_word_near(numpasos + 0) / (360 - pgm_read_word_near(numpasos + 0)));
} else {
delayMicroseconds(tiempoDibujo * 360 / (360 - pgm_read_word_near(numpasos + 0)));
}
}
if (pasa == true) {
//para que se sume a tvariable algo que se supone positivo
tvariable += (micros() - previoustime) * 360 /contaang - periodoini;
if (tvariable > 500000 || tvariable < -500000) {
tvariable = 0;
}
return;
}
}
//para que se sume a tvariable algo negativo
tvariable += (micros() - previoustime) - periodoini;
if (tvariable > 500000 || tvariable < -500000) {
tvariable = 0;
}
}
}
void pasaIman () {
pasa = true;
};
