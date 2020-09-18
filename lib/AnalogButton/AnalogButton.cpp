#include "AnalogButton.h"

AnalogButtons::AnalogButtons(uint8_t analogPin, uint16_t analogValue) {
  _pin = analogPin;
  _analogValue = analogValue;
  _prev_time = millis();
  _lastVal = 0;
}

bool AnalogButtons::getVal() {
  if (_lastVal >= GET_MIN_OFFSET(_analogValue) &&
      _lastVal <= GET_MAX_OFFSET(_analogValue))
    return true;
  else
    return false;
}

void AnalogButtons::setup() {}

void AnalogButtons::listen() {
  if (_prev_time <= millis()) {
    _prev_time += _POLLING_RATE;
    _lastVal = analogRead(_pin);
  }
}