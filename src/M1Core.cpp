#include <Arduino.h>
#include <M1Controller.h>
#include "M1Core.h"

// Encoder e1(ENCODER_S1, ENCODER_S2)

M1Model *m;
M1Controller *m1Controller;
void setup() {
  Serial.begin(57600);
  Serial.println(F("Start"));
  m = new M1Model;
  Serial.println(F("Model ok"));
  m1Controller = new M1Controller(m);
  Serial.println(F("Controller ok"));
}

void loop() { m1Controller->listenChange(); }
