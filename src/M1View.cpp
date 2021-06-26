#include "M1View.h"

M1View::M1View(M1Controller *c) : _mController(c) {
  Serial.println(F("M1View constructor"));

  _mDi = new DronInterface();
  _mDi->setVal(_mController->getRange());
}

void M1View::listen() { _mDi->listen(); }

void M1View::update() { _mDi->update(); }