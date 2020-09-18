#include "Joystick.h"

Joystick::Joystick() {
  vrxPin_ = VRX;
  vryPin_ = VRY;
  keyPin_ = KEY;

  keyStatus_ = keyClick_ = prewKeyStatus_ = false;

  maxPos_ = 255;
  minPos_ = 0;

  init();
}

Joystick::Joystick(uint8_t vrx, uint8_t vry, uint8_t key) {
  vrxPin_ = vrx;
  vryPin_ = vry;
  keyPin_ = key;

  maxPos_ = 255;
  minPos_ = 0;

  init();
}

Joystick::Joystick(
    uint8_t vrx, uint8_t vry, uint16_t minPosition, uint16_t maxPosition)
    : Joystick(vrx, vry, 0) {
  minPos_ = minPosition;
  maxPos_ = maxPosition;

  init();
}

void Joystick::init() {
  pinMode(keyPin_, INPUT_PULLUP);
  pinMode(vrxPin_, INPUT);
  pinMode(vryPin_, INPUT);
}

void Joystick::listen() {
  if (millis() - listenPeriod_ >= J_LISTEN_PERIOD) {

    keyStatus_ = digitalRead(keyPin_);
    bool changeKeyStatus = keyStatus_ != prewKeyStatus_;

    xVal_ =
        map(analogRead(vrxPin_), J_DEFAULT_POT_MIN, J_DEFAULT_POT_MAX, minPos_,
            maxPos_);
    yVal_ =
        map(analogRead(vryPin_), J_DEFAULT_POT_MIN, J_DEFAULT_POT_MAX, minPos_,
            maxPos_);

    if (keyStatus_ == J_KEY_PRESS && changeKeyStatus) {

    } else if (keyStatus_ == J_KEY_UNPRESS && changeKeyStatus) {
      keyClick_ = true;
    } else {
      keyClick_ = false;
    }

    prewKeyStatus_ = keyStatus_;
    listenPeriod_ = millis();
  }
}

bool Joystick::isKeyClick() {
  if (keyClick_) {
    keyClick_ = !keyClick_;
    return true;
  }
  return false;
}
