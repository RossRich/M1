#include "M1View.h"

M1View::M1View(M1Controller *c, M1Model *m) : controller(c), model(m) {
  Serial.println(F("M1View constructor"));
  model->registerObserver(this);
  model->init();
  Serial.println(F("Model inint"));
  pcfDriver = new PCF8574T;
  Serial.println(F("PCF ok"));
  display = new HD44780(pcfDriver);
  Serial.println(F("Display ok"));
  leftJoystick = componentFactory.createLeftJoystick();
  rightJoystick = componentFactory.createRightJoystick();
  Serial.println(F("Create joystick ok"));
  topButton = componentFactory.createRightButton();
  leftButton = componentFactory.createLeftButton();
  encoderButton = componentFactory.createEncButton();
  Serial.println(F("Create buttons ok"));

  Serial.println(F("M1View ok"));
}
M1View::~M1View() {}

void M1View::checkButons() {
  topButton->check();
  controller->clickTopButton(topButton->isClicked());

  leftButton->check();
  controller->clickLeftBotton(leftButton->isClicked());

  encoderButton->check();
  controller->clickEncoderButton(encoderButton->isClicked());
}

void M1View::checkJoysticks() {
  leftJoystick->check();
  rightJoystick->check();
  controller->changeLeftJValue(leftJoystick->getX(), leftJoystick->getY());
  controller->changeRightJValue(rightJoystick->getX(), rightJoystick->getY());
}

void M1View::print(int val, int size) { Serial.println(val); }

void M1View::print(const char *msg, int size) {
  Serial.println(msg);
  display->clear();
  display->printBeginPosition(0, msg, size);
  Serial.print(display->isError());
}

void M1View::checkPot() {}

void M1View::update() {
  M1JoystickData *j1 = model->getJoystick1();
  M1JoystickData *j2 = model->getJoystick2();

  String sj1(j1->x);
  sj1 += " ";
  sj1 += j1->y;
  sj1 += " ";

  // sj1 += j2->x;
  // sj1 += " ";
  // sj1 += j2->y;
  // sj1 += "\n";
  // Serial.println(sj1);
  print(sj1.c_str(), sj1.length());
}