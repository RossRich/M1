#include "M1View.h"

M1View::M1View(M1Controller *c, M1Model *m) : controller(c), model(m) {
  Serial.println(F("M1View constructor"));
  model->registerObserver(this);
  model->init();
  Serial.println(F("Model inint"));
  
  display = componentFactory.createDispaly();
  Serial.println(F("Display ok"));

  leftJoystick = componentFactory.createLeftJoystick();
  rightJoystick = componentFactory.createRightJoystick();
  Serial.println(F("Create joystick ok"));

  topButton = componentFactory.createTopButton();
  leftButton = componentFactory.createLeftButton();
  bottomButton = componentFactory.createBottomButton();
  rightButton = componentFactory.createRightButton();
  encoderButton = componentFactory.createEncButton();
  Serial.println(F("Create buttons ok"));

  rangePow = componentFactory.createRangePower();
  Serial.println(F("RangePow ok"));

  Serial.println(F("M1View ok"));
}
M1View::~M1View() {}

void M1View::checkButons() {
  topButton->check();
  controller->clickTopButton(topButton->isClicked());

  bottomButton->check();
  controller->clickBottomBotton(bottomButton->isClicked());

  leftButton->check();
  controller->clickLeftBotton(leftButton->isClicked());

  rightButton->check();
  controller->clickRightButton(rightButton->isClicked());

  encoderButton->check();
  controller->clickEncoderButton(encoderButton->isClicked());
}

void M1View::checkJoysticks() {
  leftJoystick->check();
  controller->changeLeftJValue(leftJoystick->getX(), leftJoystick->getY());

  rightJoystick->check();
  controller->changeRightJValue(rightJoystick->getX(), rightJoystick->getY());
}

void M1View::checkRange() {
  rangePow->check();
  controller->changeRange(rangePow->getValue());
}

void M1View::print(int val, int size) { Serial.println(val); }

void M1View::print(const char *msg, int size) {
  Serial.println(msg);
  display->clear();
  display->printBeginPosition(0, msg, size);
  Serial.print(display->isError());
}

void M1View::update() {
  M1JoystickData *j1 = model->getJoystick1();
  M1JoystickData *j2 = model->getJoystick2();

  String j1m;
  j1m += "x: ";
  j1m += j1->x;
  j1m += " ";
  j1m += "y: ";
  j1m += j1->y;
  j1m += "  ";

  String j2m;
  j2m += "x: ";
  j2m += j2->x;
  j2m += " ";
  j2m += "y: ";
  j2m += j2->y;
  j2m += "  ";

  String bT("bT: ");
  bT += model->getButTop();
  bT += "  ";

  String bR("bR: ");
  bR += model->getButRight();
  bR += "  ";

  String bL("bL: ");
  bL += model->getButLeft();
  bL += "  ";

  String bB("bB: ");
  bB += model->getButBottom();
  bB += "  ";

  String bE("bE: ");
  bE += model->getButEnc();
  bE += "  ";

  Serial.println(j1m + j2m + bT + bB + bL + bR + bE);
}