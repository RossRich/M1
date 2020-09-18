#if !defined(M1_VIEW_FACTORY_H)
#define M1_VIEW_FACTORY_H

#define ANALOG_BUTTON_TOP 683u
#define ANALOG_BUTTON_DOWN 291u
#define ANALOG_BUTTON_LEFT 879u
#define ANALOG_BUTTON_RIGHT 517u
#define ANALOG_BUTTON_ENC 1020u

#define JOYSTICK1_X A1
#define JOYSTICK1_Y A0
#define JOYSTICK1_KEY 8

#define JOYSTICK2_X A3
#define JOYSTICK2_Y A2
#define JOYSTICK2_KEY 7

#define RANGE_POWER A7

#include "M1Configuration.h"
#include <AnalogButton.h>
#include <Joystick.h>
#include <Potentiometer.h>
#include <PCF8574T.h>
#include <HD44780.h>

class VButton {
private:
public:
  VButton() {}
  virtual ~VButton() {}
  virtual bool isPressed() = 0;
  virtual bool isClicked() = 0;
  virtual void check() = 0;
};

class VJoystick {
private:
  // VButton *jButton;

public:
  // VJoystick(VButton *jb) : jButton(jb) {}
  VJoystick() {}
  virtual ~VJoystick() {}
  virtual void check() = 0;
  virtual int getX() = 0;
  virtual int getY() = 0;
};

class VRange {
private:
public:
  VRange() {}
  virtual ~VRange() {}
  void check() {}
  int getValue() { return 0; }
};

class M1ViewPowRange : public VRange {
private:
  Potentiometer *powerRange;

public:
  M1ViewPowRange() { powerRange = new Potentiometer(RANGE_POWER, 0, 255); }
  ~M1ViewPowRange() {}
  void check() { powerRange->listen(); }
  int getValue() { return powerRange->value(); }
};

class M1ViewButtonTop : public VButton {
private:
  AnalogButtons *top;

public:
  M1ViewButtonTop() { top = new AnalogButtons(A6, ANALOG_BUTTON_TOP); }
  ~M1ViewButtonTop() {}

  bool isPressed() override { return top->getVal(); };
  bool isClicked() override { return top->getVal(); };
  void check() override { top->listen(); };
};

class M1ViewButtonBottom : public VButton {
private:
  AnalogButtons *bottom;

public:
  M1ViewButtonBottom() { bottom = new AnalogButtons(A6, ANALOG_BUTTON_DOWN); }
  ~M1ViewButtonBottom() {}

  bool isPressed() override { return bottom->getVal(); };
  bool isClicked() override { return bottom->getVal(); };
  void check() override { bottom->listen(); };
};

class M1ViewButtonLeft : public VButton {
private:
  AnalogButtons *left;

public:
  M1ViewButtonLeft() { left = new AnalogButtons(A6, ANALOG_BUTTON_LEFT); }
  ~M1ViewButtonLeft() {}

  bool isPressed() override { return left->getVal(); };
  bool isClicked() override { return left->getVal(); };
  void check() override { left->listen(); };
};

class M1ViewButtonRight : public VButton {
private:
  AnalogButtons *right;

public:
  M1ViewButtonRight() { right = new AnalogButtons(A6, ANALOG_BUTTON_RIGHT); }
  ~M1ViewButtonRight() {}

  bool isPressed() override { return right->getVal(); };
  bool isClicked() override { return right->getVal(); };
  void check() override { right->listen(); };
};

class M1ViewButtonEnc : public VButton {
private:
  AnalogButtons *enc;

public:
  M1ViewButtonEnc() { enc = new AnalogButtons(A6, ANALOG_BUTTON_ENC); }
  ~M1ViewButtonEnc() {}

  bool isPressed() override { return enc->getVal(); };
  bool isClicked() override { return enc->getVal(); };
  void check() override { enc->listen(); };
};

class M1ViewLJ : public VJoystick {
private:
  Joystick *leftJoystick;

public:
  M1ViewLJ() {
    leftJoystick = new Joystick(JOYSTICK1_X, JOYSTICK1_Y, JOYSTICK1_KEY);
  }
  ~M1ViewLJ() {}

  void check() override { leftJoystick->listen(); }
  int getX() override { return leftJoystick->x(); }
  int getY() override { return leftJoystick->y(); }
};

class M1ViewRJ : public VJoystick {
private:
  Joystick *rightJoystick;

public:
  M1ViewRJ() {
    rightJoystick = new Joystick(JOYSTICK2_X, JOYSTICK2_Y, JOYSTICK2_KEY);
  }
  ~M1ViewRJ() {}

  void check() override { rightJoystick->listen(); }
  int getX() override { return rightJoystick->x(); }
  int getY() override { return rightJoystick->y(); }
};

class M1ViewFactory {
private:
public:
  M1ViewFactory() {}
  ~M1ViewFactory() {}

  VJoystick *createLeftJoystick() { return new M1ViewLJ; }
  VJoystick *createRightJoystick() { return new M1ViewRJ; }
  VButton *createTopButton() { return new M1ViewButtonTop; }
  VButton *createBottomButton() { return new M1ViewButtonBottom; }
  VButton *createLeftButton() { return new M1ViewButtonLeft; }
  VButton *createRightButton() { return new M1ViewButtonRight; }
  VButton *createEncButton() { return new M1ViewButtonEnc; }
  VRange *createRangePower() { return new M1ViewPowRange; }
  HD44780 *createDispaly() { return new HD44780(new PCF8574T); }
};

#endif // M1_VIEW_FACTORY_H
