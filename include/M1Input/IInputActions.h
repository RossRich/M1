#if !defined(I_VIEW_ACTIONS)
#define I_VIEW_ACTIONS

#include "InputEvents.h"
#include <inttypes.h>

class IInputActions {
public:
  virtual ~IInputActions() {}

  virtual void leftBut(INPUT_EVENTS e) = 0;
  virtual void rightBut(INPUT_EVENTS e) = 0;
  virtual void bottomBut(INPUT_EVENTS e) = 0;
  virtual void topBut(INPUT_EVENTS e) = 0;
  virtual void encBut(INPUT_EVENTS e) = 0;

  virtual void joyLeft(INPUT_EVENTS e, JoyData *jd) = 0;
  virtual void joyRight(INPUT_EVENTS e, JoyData *jd) = 0;

  virtual void joyLeftButton(INPUT_EVENTS e) = 0;
  virtual void joyRightButton(INPUT_EVENTS e) = 0;

  virtual void range(INPUT_EVENTS e, int16_t *val) = 0;

  virtual void encoderRot(INPUT_EVENTS e, int8_t dir) = 0;
};

#endif // I_VIEW_ACTIONS
