#include "M1View.h"

M1View::M1View(M1Controller *c, M1Model *m) : _mController(c), model(m) {
  Serial.println(F("M1View constructor"));
  init();
}

void M1View::init() {
  model->registerObserver(this);
  _mDisplayDriver = new Display;
  _mDi = new DronInterface(_mDisplayDriver);

  _mI = new Input();
  _mI->subscribe(_mI);
  _mI->setActions(this);

  viewManager = _mDi->init();
  viewManager->print();

  timer = millis();
  timer1 = timer;
}

M1View::~M1View() {}

void M1View::listen() {
  uint32_t m = millis();

  if (m - timer >= 10) {
    _mDisplayDriver->draw();
    timer = millis();
  }

  if (m - timer1 >= 250) {
    _mI->check();
    timer1 = millis();
  }
}

void M1View::leftBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("Left:Click");

  if (e == INPUT_EVENTS::PRESS)
    Serial.println("Left:Press");
}

void M1View::rightBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("Right:Click");

  if (e == INPUT_EVENTS::PRESS)
    Serial.println("Right:Press");
}

void M1View::bottomBut(INPUT_EVENTS e) {
  Serial.println("bottomBut");
  if (e == INPUT_EVENTS::CLICK) {
    viewManager->scroll(SCROLL_BOTTOM);
    viewManager->print();
  }
}

void M1View::topBut(INPUT_EVENTS e) {
  Serial.println("topBut");
  if (e == INPUT_EVENTS::CLICK) {
    Serial.println("Right:Press");
    viewManager->scroll(SCROLL_TOP);
    viewManager->print();
  }
}

void M1View::encBut(INPUT_EVENTS e) {
  if (e == INPUT_EVENTS::CLICK) {
    Serial.println("encBut:Click");
    viewManager->select();
    viewManager->print();
  }
}

void M1View::joyLeft(INPUT_EVENTS e, int16_t x, int16_t y) {
  Serial.print("Joy:Left: ");
  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);
  _mController->changeLeftJValue(x, y);
}

void M1View::joyRight(INPUT_EVENTS e, int16_t x, int16_t y) {
  Serial.print("Joy:Right: ");
  Serial.print(x);
  Serial.print('\t');
  Serial.println(y);
  _mController->changeRightJValue(x, y);
}

void M1View::joyLeftButton(INPUT_EVENTS e) {
  Serial.print("JBut: ");
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("CLICK");
  else
    Serial.println("PRESS");
}

void M1View::joyRightButton(INPUT_EVENTS e) {
  Serial.print("JBut: ");
  if (e == INPUT_EVENTS::CLICK)
    Serial.println("CLICK");
  else
    Serial.println("PRESS");
}

void M1View::range(INPUT_EVENTS e, int16_t val) {
  Serial.print("Range: ");
  Serial.println(val);
}

void M1View::encoderRot(INPUT_EVENTS e, int8_t dir) {
  Serial.print("Enc: ");
  if (dir == ENCODER_CCW_ROTATION)
    Serial.println("DOWN");
  else
    Serial.println("TOP");
}