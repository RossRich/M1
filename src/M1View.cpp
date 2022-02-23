#include "M1View.h"

M1View::M1View(M1Controller *c) : _mController(c) {
  Serial.println(F("M1View constructor"));
  _mDisplay = new Display();

  _tt = new TestView("_TEst_");
  _tt->setRange(_mController->getRangeVal_p());
  // _tt->setRightJoy(_mController->getRightJData_p());
  _tt->setLeftJoy(_mController->getLeftJData_p());
  // ranges[0] = _tt;
  // joysticks[0] = _tt;

  _mMenuManager = new MenuManager(_tt, _mDisplay);
  _mMenuManager->print();
}

void M1View::updateRange() {
  _mMenuManager->update();
  // Serial.print("R: ");Serial.println(*_mController->getRangeVal_p());
  /* for (uint8_t i = 0; i < RANGES_COUNT; i++) {
    if (ranges[i] != nullptr && ranges[i] == _mMenuManager->getVisible()) {
      _mMenuManager->update();
      break;
    }
  } */
}

void M1View::updateJoy() {
  _mMenuManager->update();
  // Serial.print("Jx: ");Serial.println(*_mController->getLeftJData_p()->x);
  // Serial.print("Jx: ");Serial.println(*_mController->getRightJData_p()->x);
  /* for (uint8_t i = 0; i < JOYS_COUNT; i++) {
    if (joysticks[i] != nullptr &&
        joysticks[i] == _mMenuManager->getVisible()) {
      _mMenuManager->update();
      break;
    }
  } */
}

void M1View::updateBut() {}