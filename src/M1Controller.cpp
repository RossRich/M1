#include "M1Controller.h"

/**
 * TODO: Deligate methot fot chage state to VButton class
 **/

M1Controller::M1Controller(M1Model *m1Model) : m_m1Model(m1Model) {
  Serial.println(F("M1Controller constructor"));
  m_m1View = new M1View(this, m1Model);
  Serial.println(F("M1View ok"));
}
M1Controller::~M1Controller() {}

void M1Controller::clickTopButton(bool state) {
  if (state != m_m1Model->getButTop())
    m_m1Model->setButTop(state);
}

void M1Controller::clickBottomBotton(bool state) {
  if (state != m_m1Model->getButBottom())
    m_m1Model->setButBottom(state);
}

void M1Controller::clickLeftBotton(bool state) {
  if (state != m_m1Model->getButLeft())
    m_m1Model->setButLeft(state);
}

void M1Controller::clickRightButton(bool state) {
  if (state != m_m1Model->getButRight())
    m_m1Model->setButRight(state);
}

void M1Controller::clickEncoderButton(bool state) {
  if (state != m_m1Model->getButEnc())
    m_m1Model->setButEnc(state);
}

void M1Controller::changeRange(int val) {
  if (val != m_m1Model->getRange())
    m_m1Model->setRange(val);
}

void M1Controller::changeLeftJValue(int x, int y) {
  if ((m_m1Model->getJoystick1()->x != x) ||
      (m_m1Model->getJoystick1()->y != y))
    m_m1Model->setJoystick1(x, y, 0);
}

void M1Controller::changeRightJValue(int x, int y) {
  if ((m_m1Model->getJoystick2()->x != x) ||
      (m_m1Model->getJoystick2()->y != y))
    m_m1Model->setJoystick2(x, y, 0);
}

void M1Controller::listenChange() {
  m_m1View->checkButons();
  m_m1View->checkJoysticks();
  m_m1View->checkRange();
}