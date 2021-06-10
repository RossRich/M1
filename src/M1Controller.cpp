#include "M1Controller.h"

M1Controller::M1Controller(M1Model *m1Model) : _mModel(m1Model) {
  Serial.println(F("M1Controller constructor"));
  init();
}

M1Controller::~M1Controller() {}

void M1Controller::init() {
  _mView = new M1View(this, _mModel);
  Serial.println(F("M1View ok"));
}

void M1Controller::clickTopButton(bool state) {
  if (state != _mModel->getButTop())
    _mModel->setButTop(state);
}

void M1Controller::clickBottomBotton(bool state) {
  if (state != _mModel->getButBottom())
    _mModel->setButBottom(state);
}

void M1Controller::clickLeftBotton(bool state) {
  if (state != _mModel->getButLeft())
    _mModel->setButLeft(state);
}

void M1Controller::clickRightButton(bool state) {
  if (state != _mModel->getButRight())
    _mModel->setButRight(state);
}

void M1Controller::clickEncoderButton(bool state) {
  if (state != _mModel->getButEnc())
    _mModel->setButEnc(state);
}

void M1Controller::changeRange(int val) {
  if (val != _mModel->getRange())
    _mModel->setRange(val);
}

void M1Controller::changeLeftJValue(int x, int y) {
  _mModel->setJoystick1(x, y, 0);
}

void M1Controller::changeRightJValue(int x, int y) {
  _mModel->setJoystick2(x, y, 0);
}

void M1Controller::listenChange() {
  _mView->listen();
  // M1JoystickData *lJoy = _mModel->getJoystick1();
}