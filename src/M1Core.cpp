#include <Arduino.h>
#include <M1Controller.h>
#include "M1Core.h"

// Encoder e1(ENCODER_S1, ENCODER_S2);
// Joystick j1(JOYSTICK1_X, JOYSTICK1_Y, JOYSTICK1_KEY); // left
// Joystick j2(JOYSTICK2_X, JOYSTICK2_Y, JOYSTICK2_KEY); // right
// Potentiometer p1(A7, 0, 255);
// AnalogButtons keyGroup(A6, 5);

M1Controller *m1Controller;

void setup() {
  Serial.begin(9600);
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
