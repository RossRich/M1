#include "M1Controller.h"

M1Controller::M1Controller(M1Model *m1Model) : _mModel(m1Model) {
  Serial.println(F("M1Controller constructor"));

  _mInput = new Input();

  bindModelData();
  // BUG: If first initialize M1View before Input or bindModelData(), MC not
  // works correctly, becouse in M1View use getRangeVal_p() func from Input;
  _mView = new M1View(this);
  Serial.println(F("M1View ok"));

  _mModel->addObserver(_mView);
  _mInput->addListener(this);
  _inputTimer = millis();
  _viewTimer = _inputTimer;
}

M1Controller::~M1Controller() {}

void M1Controller::bindModelData() {
  _mModel->setJoyLeft_p(_mInput->getJoyLeftData_p());
  _mModel->setJoyRight_p(_mInput->getJoyRightData_p());
  _mModel->setRange_p(_mInput->getRangeValue_p());
}

int16_t *M1Controller::getRangeVal_p() { return _mModel->getRange_p(); }
JoyData *M1Controller::getLeftJData_p() { return _mModel->getJoyLeft_p(); }
JoyData *M1Controller::getRightJData_p() { return _mModel->getJoyRight_p(); }

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

void M1Controller::joyLeft(INPUT_EVENTS e, JoyData *jd) {
#if defined(_DEBUG_)

  Serial.print("Joy:Left: ");
  Serial.print(*jd->x);
  Serial.print('\t');
  Serial.println(*jd->y);

#endif // _DEBUG_

  _mView->updateJoy();
}

void M1Controller::joyRight(INPUT_EVENTS e, JoyData *jd) {
#if defined(_DEBUG_)

  Serial.print("Joy:Right: ");
  Serial.print(*jd->x);
  Serial.print('\t');
  Serial.println(*jd->y);

#endif // _DEBUG_

  // _mView->updateJoy();
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

void M1Controller::range(INPUT_EVENTS e, int16_t *val) {
#if defined(_DEBUG_)

  Serial.print("Range: ");
  Serial.println(*val);

#endif // _DEBUG_

  _mView->updateRange();
}

void M1Controller::encoderRot(INPUT_EVENTS e, int8_t dir) {
  Serial.print("Enc: ");
  if (dir == ENCODER_CCW_ROTATION)
    Serial.println("DOWN");
  else
    Serial.println("TOP");
}

void M1Controller::listen() {
  uint32_t ms = millis();

  if (ms - _inputTimer >= 150) {
    _mInput->check();
    _inputTimer = millis();
  }

  if (ms - _viewTimer >= 500) {
    _mView->listen();
    _viewTimer = millis();
  }
}