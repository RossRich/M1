#include "M1Controller.h"

M1Controller::M1Controller(M1Model *m1Model) : _mModel(m1Model) {
  Serial.println(F("M1Controller constructor"));

  _mView = new M1View(this);
  Serial.println(F("M1View ok"));

  _mModel->addObserver(_mView);

  _mInput = new Input();
  _mInput->addListener(this);

  _inputTimer = millis() + 5000;
  _viewTimer = _inputTimer;
}

M1Controller::~M1Controller() {}

// inputaction

void M1Controller::leftBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("Left:Click");

  if (e == INPUT_EVENTS::PRESS)
    Serial.println("Left:Press");
}

void M1Controller::rightBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("Right:Click");

  if (e == INPUT_EVENTS::PRESS)
    Serial.println("Right:Press");
}

void M1Controller::bottomBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK) {
    Serial.println("bottomBut");
    // _mView->scroll(SCROLL_BOTTOM);
    // _mView->print();
  }
}

void M1Controller::topBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK) {
    Serial.println("topBut:CLICK");
    // _mView->scroll(SCROLL_TOP);
    // _mView->print();
  }
}

void M1Controller::encBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK) {
    Serial.println("encBut:Click");
    // _mView->select();
    // _mView->print();
  }
}

void M1Controller::joyLeft(INPUT_EVENTS e, int16_t x, int16_t y) {
  Serial.print("Joy:Left: ");
  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);
  // _mController->changeLeftJValue(x, y);
}

void M1Controller::joyRight(INPUT_EVENTS e, int16_t x, int16_t y) {
  Serial.print("Joy:Right: ");
  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);
  // _mController->changeRightJValue(x, y);
}

void M1Controller::joyLeftButton(INPUT_EVENTS e) {
  Serial.print("JBut: ");
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("CLICK");
  else
    Serial.println("PRESS");
}

void M1Controller::joyRightButton(INPUT_EVENTS e) {
  Serial.print("JBut: ");
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("CLICK");
  else
    Serial.println("PRESS");
}

void M1Controller::range(INPUT_EVENTS e, int16_t val) {
  Serial.print("Range: ");
  Serial.println(val);
  _mModel->setRange(val);
}

void M1Controller::encoderRot(INPUT_EVENTS e, int8_t dir) {
  Serial.print("Enc: ");
  if (dir == ENCODER_CCW_ROTATION)
    Serial.println("DOWN");
  else
    Serial.println("TOP");
}

int *M1Controller::getRange() { return _mModel->getRange(); }

JoyData *M1Controller::getJoy() { return nullptr; }

void M1Controller::listen() {
  uint32_t ms = millis();

  if (ms - _inputTimer >= 150) {
    _mInput->check();
    _inputTimer = millis();
  }

  if (ms - _viewTimer >= 100) {
    _mView->listen();
    _viewTimer = millis();
  }
}