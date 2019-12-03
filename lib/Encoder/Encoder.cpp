#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder(uint8_t s1Pin, uint8_t s2Pin, uint8_t buttonPin) {
  this->s1 = s1Pin;
  this->s2 = s2Pin;
  this->button = buttonPin;

  pinMode(s1Pin, INPUT_PULLUP);
  pinMode(s2Pin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}

void Encoder::setClickListener(void (*ufunc)()) {
  this->userfunction = ufunc;
}

void Encoder::listen() {

  uint8_t s2Statuss = digitalRead(this->s2);

  if (s2Statuss) {
    this->userfunction("->");
  } else {
    this->userfunction("<-");
  }
}