#if !defined(V_JOYSTICK_H)
#define V_JOYSTICK_H

#include <inttypes.h>
#include "JoyTypes.h"

class VJoystick {
public:
  virtual ~VJoystick() {}
  virtual void check() = 0;
  virtual JoyData *getData_p() = 0;
};

#endif // V_JOYSTICK_H
