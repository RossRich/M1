#include "M1Input/DroneButton.h"

DroneButton::DroneButton(uint8_t analogPin, uint16_t analogValue)
    : _mB(new AnalogButtons(analogPin, analogValue)) {}

DroneButton::~DroneButton() {
  if (_mB != nullptr)
    delete _mB;
}

bool DroneButton::isPressed() { return _mB->isPress(); }
bool DroneButton::isClicked() { return _mB->isClick(); }
void DroneButton::check() {
  _mB->listen();

  if (isPressed())
    notify(INPUT_EVENTS::PRESS);

  if (isClicked())
    notify(INPUT_EVENTS::CLICK);
}

void DroneButton::subscribe(InputObserver *o) { _mIObs = o; }
void DroneButton::unsubscrube(InputObserver *o) {}
void DroneButton::notify(IEv e) {
  if (_mIObs != nullptr)
    _mIObs->update(this, e);
}
