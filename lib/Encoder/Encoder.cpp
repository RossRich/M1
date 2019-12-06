#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder() {
  s1_ = 2;
  s2_ = 7;
  button_ = 10;

  buttonState_ = ENCODER_BUTTON_UNPRESS;
  butChangeState_ = false;
  butDown_ = false;
  butUp_ = false;
  butClick_ = false;
}

Encoder::Encoder(uint8_t s1Pin, uint8_t s2Pin, uint8_t buttonPin) : Encoder() {
  s1_ = s1Pin;
  s2_ = s2Pin;
  button_ = buttonPin;

  pinMode(s1Pin, INPUT_PULLUP);
  pinMode(s2Pin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}

void Encoder::setClickListener(void (*uFuncClick)()) { uClkFunc_ = uFuncClick; }

void Encoder::setLongClickListener(void (*uFuncLongClick)()) {
  uLngClkFunc_ = uFuncLongClick;
}

void Encoder::setRotationListener(void (*urfun)()) {
  if ((digitalPinToInterrupt(s1_) != NOT_AN_INTERRUPT) && (urfun != NULL))
    attachInterrupt(digitalPinToInterrupt(s1_), urfun, FALLING);
}

void Encoder::setSpinListener(void (*uspifun)()) { uSpinFunc_ = uspifun; }

void Encoder::listenRotation() {
  if (digitalRead(s2_))
    rotationDiraction_ = ENCODER_CW_ROTATION;
  else
    rotationDiraction_ = ENCODER_CCW_ROTATION;
}

void Encoder::listenButton() {
  if (buttonListenPeriod_ <= millis()) {
    buttonListenPeriod_ += ENCODER_BUTTON_LISTEN_PERIOD;
    uint8_t bs = digitalRead(button_);
    if ((bs == ENCODER_BUTTON_PRESS) && (bs != buttonState_)) {
      butDown_ = true;
      butUp_ = butClick_ = false;
    } else if ((bs == ENCODER_BUTTON_UNPRESS) && (bs != buttonState_)) {
      butDown_ = false;
      butUp_ = butClick_ = true;
    }
    buttonState_ = bs;
  }
}

bool Encoder::isButtonKeep() const {
  return (buttonState_ == ENCODER_BUTTON_PRESS) ? true : false;
}

bool Encoder::isButtonDown() {
  if (butDown_ && (buttonState_ == ENCODER_BUTTON_PRESS)) {
    butDown_ = !butDown_;
    return true;
  }
  return false;
}

bool Encoder::isButtonUp() {
  if (butUp_ && (buttonState_ == ENCODER_BUTTON_UNPRESS)) {
    butUp_ = !butUp_;
    return true;
  }
  return false;
}

bool Encoder::isButtonClick() {
  if (butClick_ && (buttonState_ == ENCODER_BUTTON_UNPRESS)) {
    butClick_ = !butClick_;
    return true;
  }
  return false;
}