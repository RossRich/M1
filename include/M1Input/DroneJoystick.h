#if !defined(DRONE_JOYSTICK_H)
#define DRONE_JOYSTICK_H

#include "VJoystick.h"
#include <Joystick.h>

struct JoyData {
  int x;
  int y;
  bool sw;
};

class DroneJoystick : public VJoystick, public InputSubject {
private:
  Joystick *_mJ = nullptr;
  InputObserver *_mObs = nullptr;

public:
  DroneJoystick(uint8_t xPin, uint8_t yPin, uint8_t keyPin)
      : _mJ(new Joystick(xPin, yPin, keyPin)) {}

  DroneJoystick(uint8_t xPin, uint8_t yPin, uint8_t keyPin, InputObserver *obs)
      : _mJ(new Joystick(xPin, yPin, keyPin)), _mObs(obs) {}

  ~DroneJoystick() {
    if (_mJ != nullptr)
      delete _mJ;
  }

  void check() override {
    _mJ->listen();

    if (_mJ->difX() != 0 || _mJ->difY() != 0)
      notify(INPUT_EVENTS::MOVE);

    if (_mJ->isKeyPress())
      notify(INPUT_EVENTS::PRESS);

    if (_mJ->isKeyClick())
      notify(INPUT_EVENTS::CLICK);
  }

  int16_t getX() override { return _mJ->x(); }
  int16_t getY() override { return _mJ->y(); }

  void subscribe(InputObserver *o) { _mObs = o; }
  void unsubscrube(InputObserver *o) {}
  void notify(IEv e) { _mObs->update(this, e); }
};

#endif // DRONE_JOYSTICK_H
