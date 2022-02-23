#if !defined(DRONE_JOYSTICK_H)
#define DRONE_JOYSTICK_H

#include "VJoystick.h"
#include <Joystick.h>

class DroneJoystick : public VJoystick, public InputSubject {
private:
  Joystick *_mJ = nullptr;
  InputObserver *_mObs = nullptr;
  JoyData _jData;

  DroneJoystick() {}

public:
  DroneJoystick(uint8_t xPin, uint8_t yPin, uint8_t keyPin)
      : _mJ(new Joystick(xPin, yPin, keyPin)) {
    init();
  }

  DroneJoystick(uint8_t xPin, uint8_t yPin, uint8_t keyPin, InputObserver *obs)
      : _mJ(new Joystick(xPin, yPin, keyPin)), _mObs(obs) {
    init();
  }

  ~DroneJoystick() {
    if (_mJ != nullptr)
      delete _mJ;
  }

  void init() {
    _jData.x = _mJ->x_p();
    _jData.y = _mJ->y_p();
    _jData.sw = _mJ->butState_p();
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

  JoyData *getData_p() override { return &_jData; }

  void subscribe(InputObserver *o) { _mObs = o; }
  void unsubscrube(InputObserver *o) {}
  void notify(IEv e) {
    if (_mObs != nullptr)
      _mObs->update(this, e);
  }
};

#endif // DRONE_JOYSTICK_H
