#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder(uint8_t s1Pin, uint8_t s2Pin, uint8_t buttonPin) {
  s1_ = s1Pin;
  s2_ = s2Pin;
  button_ = buttonPin;

  pinMode(s1Pin, INPUT_PULLUP);
  pinMode(s2Pin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}

void Encoder::setClickListener(void (*ucfun)()) { this->uClkFunc = ucfun; }

void Encoder::setRotationListener(void (*urfun)()) {
  if (digitalPinToInterrupt(s1_) != NOT_AN_INTERRUPT)
    attachInterrupt(digitalPinToInterrupt(s1_), urfun, FALLING);
}

void Encoder::listenRotation() {

  if (digitalRead(s2_))
    rotationDiraction_ = ENCODER_CW_ROTATION;
  else
    rotationDiraction_ = ENCODER_CCW_ROTATION;
}