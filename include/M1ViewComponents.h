#if !defined(M1_VIEW_COMPONENTS_H)
#define M1_VIEW_COMPONENTS_H

#define MAX_DISPLAYS 5u
#define MAX_FRAMES 5u
#define DIR_LEFT 0u
#define DIR_RIGHT 1u

#include <inttypes.h>

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
public:
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

#endif // M1_VIEW_COMPONENTS_H
