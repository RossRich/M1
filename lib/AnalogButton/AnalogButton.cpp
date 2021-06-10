#include "AnalogButton.h"

AnalogButtons::AnalogButtons(uint8_t analogPin, uint16_t analogValue) {
  _pin = analogPin;
  _analogValue = analogValue;
  _prev_time = millis();
}

bool AnalogButtons::getState() {
  if (_lastVal >= GET_MIN_OFFSET(_analogValue) &&
      _lastVal <= GET_MAX_OFFSET(_analogValue))
    return true;
  else
    return false;
}

void AnalogButtons::listen() {
  if (_prev_time <= millis()) {
    _prev_time += _POLLING_RATE;
    _lastVal = analogRead(_pin);

    _state = getState();
  }
}

bool AnalogButtons::isClick() {
  if (clickMillis + 350 >= millis() && !_state) {
    clickMillis = 0;
    return true;
  }

  if (!_state && clickMillis != 0)
    clickMillis = 0;
  else if (_state && clickMillis == 0)
    clickMillis = millis();

  return false;
}
