#if !defined(V_JOYSTICK_H)
#define V_JOYSTICK_H

#include <inttypes.h>

class VJoystick {
public:
  virtual ~VJoystick() {}
  virtual void check() = 0;
  virtual int16_t getX() = 0;
  virtual int16_t getY() = 0;
};

#endif // V_JOYSTICK_H
