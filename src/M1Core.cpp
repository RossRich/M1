#include <Arduino.h>
#include <M1Controller.h>
#include "M1Core.h"

// Encoder e1(ENCODER_S1, ENCODER_S2)


M1Controller *m1Controller;

void setup() {
  Serial.begin(57600);
  Serial.println(F("Start"));
  M1Model m;
  Serial.println(F("Model ok"));
  m1Controller = new M1Controller(&m);
  Serial.println(F("Controller ok"));
}

void loop() {
  m1Controller->listenChange();
  // Serial.println(F("Listen"));
}
