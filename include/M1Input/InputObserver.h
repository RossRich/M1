#if !defined(INPUT_OBSERVER_H)
#define INPUT_OBSERVER_H

#include "VInput/VButton.h"
#include "VInput/VJoystick.h"
#include "VInput/VRange.h"
#include "VInput/VEncoder.h"

#include "InputEvents.h"

typedef INPUT_EVENTS IEv;

class InputObserver {
public:
  virtual ~InputObserver() {}
  virtual void update(VButton *b, IEv e) = 0;
  virtual void update(VJoystick *j, IEv e) = 0;
  virtual void update(VRange *r, IEv e) = 0;
  virtual void update(VEncoder *en, INPUT_EVENTS ev) = 0;
};

#endif // INPUT_OBSERVER_H
