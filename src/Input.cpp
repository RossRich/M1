#include "M1Input/Input.h"

// Encoder gEnc(ENCODER1_PIN, ENCODER2_PIN);

// void gEncoderHandler() { gEnc.listenRotation(); }

Input::Input() {

  _mLeftJoy =
      new DroneJoystick(JOYSTICK_LEFT_X, JOYSTICK_LEFT_Y, JOYSTICK_LEFT_KEY);

  _mRightJoy =
      new DroneJoystick(JOYSTICK_RIGHT_X, JOYSTICK_RIGHT_Y, JOYSTICK_RIGHT_KEY);

  _mTopBut = new DroneButton(ANALOG_BUTTON_PIN, ANALOG_BUTTON_TOP);

  _mBottomBut = new DroneButton(ANALOG_BUTTON_PIN, ANALOG_BUTTON_DOWN);

  _mLeftBut = new DroneButton(ANALOG_BUTTON_PIN, ANALOG_BUTTON_LEFT);

  _mRightBut = new DroneButton(ANALOG_BUTTON_PIN, ANALOG_BUTTON_RIGHT);

  _mEncBut = new DroneButton(ANALOG_BUTTON_PIN, ANALOG_BUTTON_ENC);

  _mRange = new DroneRange(RANGE_POWER, RANGE_MIN_POS, RANGE_MAX_POS);

  // _mEnc = new DroneEncoder(&gEnc);

  subscribe(this);
}

Input::~Input() {}

void Input::checkBut() {
  _mTopBut->check();
  _mBottomBut->check();
  _mLeftBut->check();
  _mRightBut->check();
  _mEncBut->check();
}

void Input::checkJoy() {
  _mLeftJoy->check();
  _mRightJoy->check();
}

void Input::checkRange() { _mRange->check(); }

void Input::checkEnc() { /*  _mEnc->check();  */
}

void Input::check() {
  checkBut();
  checkJoy();
  checkRange();
  // checkEnc();
}

void Input::subscribe(InputObserver *o) {
  _mTopBut->subscribe(o);
  _mBottomBut->subscribe(o);
  _mLeftBut->subscribe(o);
  _mRightBut->subscribe(o);
  _mEncBut->subscribe(o);

  _mLeftJoy->subscribe(o);
  _mRightJoy->subscribe(o);

  _mRange->subscribe(o);

  // _mEnc->subscribe(o);
}

void Input::update(VButton *b, IEv e) {
  if (b == _mTopBut) {
    _mActions->topBut(e);
  }

  if (b == _mBottomBut) {
    _mActions->bottomBut(e);
  }

  if (b == _mLeftBut) {
    _mActions->leftBut(e);
  }

  if (b == _mRightBut) {
    _mActions->rightBut(e);
  }

  if (b == _mEncBut) {
    _mActions->encBut(e);
  }
}

void Input::update(VJoystick *j, IEv e) {
  if (j == _mLeftJoy && e == INPUT_EVENTS::MOVE)
    _mActions->joyLeft(e, j->getX(), j->getY());

  if (j == _mRightJoy && e == INPUT_EVENTS::MOVE)
    _mActions->joyRight(e, j->getX(), j->getY());

  if (j == _mLeftJoy && e == INPUT_EVENTS::CLICK)
    _mActions->joyLeftButton(e);

  if (j == _mRightJoy && e == INPUT_EVENTS::CLICK)
    _mActions->joyRightButton(e);

  if (j == _mLeftJoy && e == INPUT_EVENTS::PRESS)
    _mActions->joyLeftButton(e);

  if (j == _mRightJoy && e == INPUT_EVENTS::PRESS)
    _mActions->joyRightButton(e);
}

void Input::update(VRange *r, IEv e) {
  _mActions->range(e, _mRange->getValue());
}

void Input::update(VEncoder *en, IEv e) {
  // _mActions->encoderRot(e, en->getDiraction());
}