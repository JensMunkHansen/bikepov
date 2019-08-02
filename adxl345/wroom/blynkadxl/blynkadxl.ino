/*  -*- coding: utf-8; mode: c; indent-tabs-mode: nil -*- */

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library

ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

float accX = 0;
float accY = 0;
float accZ = 0;

/************** DEFINED VARIABLES **************/
/*                                             */
#define offsetX     1        // OFFSET values
#define offsetY    -1
#define offsetZ   -18

#define gainX     263        // GAIN factors
#define gainY     257
#define gainZ     247

char auth[] = "7cFOFsV3Yj0_xTHDe9dQtX2U3p43IM8d";

char ssid[] = "little-bertha";
char pass[] = "hejnesgade13";

unsigned long nBursts = 2;

BlynkTimer timer;

const long updateTime = 60000; // Every minute

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(updateTime, sendStatus);


  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(2);

  adxl.setSpiBit(1);

  adxl.setActivityXYZ(0, 0, 1);

  adxl.setActivityThreshold(3);

  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(5);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

  adxl.setTapDetectionOnXYZ(1, 0, 0); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  adxl.setTapThreshold(10);           // 62.5 mg per increment
  adxl.setTapDuration(15);            // 625 μs per increment
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment

  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment

  // Setting all interupts to take place on INT1 pin
  //adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets "adxl.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);"
                                                        // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
                                                        // This library may have a problem using INT2 pin. Default to INT1 pin.

  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  adxl.InactivityINT(1);
  adxl.ActivityINT(1);
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
  adxl.singleTapINT(1);


}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V1) {
  nBursts = param.asInt();
}

void loop()
{
  Blynk.run();
  timer.run();

  // TODO: Use interupts instead
  
  int x,y,z;
  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in

  accX = float(x - offsetX) / gainX;         // Calculating New Values for X, Y and Z
  accY = float(y - offsetY) / gainY;
  accZ = float(z - offsetZ) / gainZ;

  // 24 l per mole at RTP
  // ethanol 46.07 g/mol

  // vol / (vol + water) = alc %

  // vol = volCO2  * (46.07 g/mol  / 24 l/mol)  /  (789 g / l)

#if 1
  if (fabs(accZ) > 1.035) {
    Serial.println("Bubble");
    Serial.println(fabs(accZ));
    nBursts = nBursts + 1;
  }
#else
  byte interrupts = adxl.getInterruptSource();

  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    Serial.println("*** ACTIVITY ***");
    nBursts = nBursts + 1;
  }
#endif
}

void sendStatus() {
  // Disable IRQ
  adxl.ActivityINT(0);


  BLYNK_PRINT.println("sending count");

  Blynk.virtualWrite(V1, nBursts);

  // Enable IRQ
  adxl.ActivityINT(1);
}
