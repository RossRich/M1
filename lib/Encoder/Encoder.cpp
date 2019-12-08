#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder() {
  s1_ = 2;
  s2_ = 7;

  button_ = 10;
  butLongPressTimer_ = internalTime_ = millis() + ENCODER_BUTTON_LISTEN_PERIOD;
  buttonState_ = prewButtonState_ = ENCODER_BUTTON_UNPRESS;

  listenerBufferIndex_ = 0;

  // butChangeState_ = false;
  butDown_ = false;
  butUp_ = false;
  butClick_ = false;
  butLongPress_ = false;
  isReady_ = false;
}

Encoder::Encoder(uint8_t s1Pin, uint8_t s2Pin, uint8_t buttonPin) : Encoder() {
  s1_ = s1Pin;
  s2_ = s2Pin;
  button_ = buttonPin;

  pinMode(s1Pin, INPUT_PULLUP);
  pinMode(s2Pin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
}

/* Encoder::Encoder(
    uint8_t s1Pin, uint8_t s2Pin, uint8_t buttonPin,
    void (*interruptRotation)())
    : Encoder(s1Pin, s2Pin, buttonPin) {

  setInterruptRotationListener(interruptRotation);
} */

void Encoder::setInterruptRotationListener(void (*uFunc)()) {
  if ((uFunc != NULL) && (digitalPinToInterrupt(s1_) != NOT_AN_INTERRUPT)) {
    attachInterrupt(digitalPinToInterrupt(s1_), uFunc, FALLING);
  }
}

void Encoder::listenRotation() {
  rotationDiraction_ =
      (digitalRead(s2_)) ? ENCODER_CW_ROTATION : ENCODER_CCW_ROTATION;
  spinPressure_ = (digitalRead(button_) == ENCODER_BUTTON_PRESS) ? true : false;
}

void Encoder::listen() {
  internalTime_ = millis();
  if (buttonListenPeriod_ <= internalTime_) {
    buttonState_ = digitalRead(button_);
    buttonListenPeriod_ += ENCODER_BUTTON_LISTEN_PERIOD;
    bool butChangeState_ = buttonState_ != prewButtonState_;

    if ((buttonState_ == ENCODER_BUTTON_PRESS) && butChangeState_) {
      butDown_ = true;
      butUp_ = butClick_ = false;
      // butLongPressTimer_ = internalTime_ + ENCODER_BUTTON_LONG_PRESS;
      // isReadedLongPress_ = false;
      // isReady_ = true;
    } else if ((buttonState_ == ENCODER_BUTTON_UNPRESS) && butChangeState_) {
      butDown_ = butLongPress_ = isReadedLongPress_ = false;
      butUp_ = butClick_ = true;
      // isReady_ = true;
    } else
      butDown_ = butLongPress_ = butUp_ = butClick_ = isReady_ = false;

    if (listenerBufferIndex_ != 0)
      for (uint8_t i = 0; i < listenerBufferIndex_; i++)
        (*listenerArray[i])();

    prewButtonState_ = buttonState_;
  }

  /* if ((butLongPressTimer_ <= internalTime_) &&
      (buttonState_ == ENCODER_BUTTON_PRESS) && !isReadedLongPress_) {
    butLongPress_ = true;
    isReady_ = true;
  } */
}

bool Encoder::isButtonKeep() const {
  return (buttonState_ == ENCODER_BUTTON_PRESS) ? true : false;
}

bool Encoder::isButtonDown() {
  if (butDown_) {
    butDown_ = !butDown_;
    return true;
  }
  return false;
}

bool Encoder::isButtonUp() {
  if (butUp_) {
    butUp_ = !butUp_;
    return true;
  }
  return false;
}

bool Encoder::isButtonClick() {
  if (butClick_) {
    butClick_ = !butClick_;
    return true;
  }
  return false;
}

bool Encoder::isSpinPressure() {
  if(spinPressure_) {
    spinPressure_ = !spinPressure_;
    return true;
  }
  return false;
}

/* bool Encoder::isButtonLongPress() {
  if (butLongPress_ && !isReadedLongPress_) {
    isReadedLongPress_ = !isReadedLongPress_;
    butLongPress_ = !butLongPress_;
    return true;
  }
  return false;
} */

int8_t Encoder::getDiraction() {
  noInterrupts();
  int8_t tDiractions = rotationDiraction_;
  rotationDiraction_ = 0;
  interrupts();
  return tDiractions;
}

void Encoder::addToListener(void (*uFunc)()) {
  if (uFunc != NULL)
    listenerArray[listenerBufferIndex_++] = uFunc;
}

/* void Encoder::setLongClickListener(void (*uFunc)()) {
  listenItem[listenerBufferIndex_++] = {uFunc, &butLongPress_};
} */

/* void Encoder::setSpinPressureListener(void (*uFunc)()) {
  if (uFunc != NULL)
    listenItem[listenerBufferIndex_++] = {uFunc, &spinPressure_};
} */
