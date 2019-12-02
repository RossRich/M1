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

void Encoder::onPressListener(void (*ufunc)(const char *)) {
  this->userfunction = ufunc;
}

void Encoder::listen() {

  if (!digitalRead(this->button)) {
    this->userfunction("pressed");
  }

  uint8_t s1Statuss = digitalRead(this->s1);
  uint8_t s2Statuss = digitalRead(this->s2);
  uint8_t val =
      uint8_t(digitalRead(this->s1)) | (uint8_t(digitalRead(this->s2)) << 1);

  if (!s1Statuss && !s2Statuss) {

    if (val == 0x2)
      this->userfunction("->");
    else if (val == 0x1)
      this->userfunction("<-");

  } else if (s1Statuss && s2Statuss) {

    if (val == 0x2)
      this->userfunction("<-");
    else if (val == 0x1)
      this->userfunction("->");
  }
}