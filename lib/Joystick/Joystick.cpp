#include "Joystick.h"

Joystick::Joystick() {
  vrxPin_ = VRX;
  vryPin_ = VRY;
  keyPin_ = KEY;

  keyStatus_ = keyClick_ = prewKeyStatus_ = false;

  maxPos_ = 1023;
  minPos_ = 0;
  listenPeriod_ = millis() + J_LISTEN_PERIOD;

  init();
}

Joystick::Joystick(uint8_t vrx, uint8_t vry, uint8_t key) : Joystick() {
  vrxPin_ = vrx;
  vryPin_ = vry;
  keyPin_ = key;

  init();
}

Joystick::Joystick(
    uint8_t vrx, uint8_t vry, uint8_t key, uint16_t minPosition,
    uint16_t maxPosition)
    : Joystick(vrx, vry, key) {
  minPos_ = minPosition;
  maxPos_ = maxPosition;

  init();
}

void Joystick::init() { pinMode(keyPin_, INPUT_PULLUP); }

void Joystick::listen() {
  internalTime_ = millis();

  if (listenPeriod_ <= internalTime_) {
    listenPeriod_ += J_LISTEN_PERIOD;

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
  }
}

bool Joystick::isKeyClick() {
  if (keyClick_) {
    keyClick_ = !keyClick_;
    return true;
  }
  return false;
}
