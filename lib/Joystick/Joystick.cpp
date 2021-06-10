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

    _jState.but = static_cast<bool>(digitalRead(keyPin_));

    _jPos.pX = _jPos.x;
    _jPos.pY = _jPos.y;

    _jPos.x =
        map(analogRead(vrxPin_), J_DEFAULT_POT_MIN, J_DEFAULT_POT_MAX, minPos_,
            maxPos_);
    _jPos.y =
        map(analogRead(vryPin_), J_DEFAULT_POT_MIN, J_DEFAULT_POT_MAX, minPos_,
            maxPos_);

    events();
    listenPeriod_ = millis();
  }
}

void Joystick::events() {
  bool changedKeyStatus = _jState.but != _jState.pBut;

  if (_jState.but == J_KEY_PRESS && changedKeyStatus) {
    // ???
  } else if (_jState.but == J_KEY_UNPRESS && changedKeyStatus) {
    keyClick_ = true;
  } else {
    keyClick_ = false;
  }

  _jState.pBut = _jState.but;
}

bool Joystick::isKeyClick() {
  if (keyClick_) {
    keyClick_ = !keyClick_;
    return true;
  }
  return false;
}
