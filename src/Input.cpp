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


// InputObserver
void Input::update(VButton *b, IEv e) {
  if (b == _mTopBut) {
    _mAction->topBut(e);
  }

  if (b == _mBottomBut) {
    _mAction->bottomBut(e);
  }

  if (b == _mLeftBut) {
    _mAction->leftBut(e);
  }

  if (b == _mRightBut) {
    _mAction->rightBut(e);
  }

  if (b == _mEncBut) {
    _mAction->encBut(e);
  }
}

void Input::update(VJoystick *j, IEv e) {
  if (j == _mLeftJoy && e == INPUT_EVENTS::MOVE)
    _mAction->joyLeft(e, j->getData_p());

  if (j == _mRightJoy && e == INPUT_EVENTS::MOVE)
    _mAction->joyRight(e, j->getData_p());

 /*  if (j == _mLeftJoy && e == INPUT_EVENTS::CLICK)
    _mAction->joyLeftButton(e);

  if (j == _mRightJoy && e == INPUT_EVENTS::CLICK)
    _mAction->joyRightButton(e);

  if (j == _mLeftJoy && e == INPUT_EVENTS::PRESS)
    _mAction->joyLeftButton(e);

  if (j == _mRightJoy && e == INPUT_EVENTS::PRESS)
    _mAction->joyRightButton(e); */
}

void Input::update(VRange *r, IEv e) {
  _mAction->range(e, _mRange->getValue_p());
}

void Input::update(VEncoder *en, IEv e) {
  // _mAction->encoderRot(e, en->getDiraction());
}