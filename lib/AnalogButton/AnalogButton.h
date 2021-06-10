#if !defined(ANALOG_BUTTONS_H)
#define ANALOG_BUTTONS_H

#include <Arduino.h>

#define A_OFFSET 5u

class AnalogButtons {

private:
  const uint16_t _POLLING_RATE = 200; // in ms
  uint8_t _pin;
  uint16_t _analogValue = 1024;
  uint32_t _prev_time;
  uint16_t _lastVal = 0;
  bool _state = false;
  inline uint16_t GET_MAX_OFFSET(uint16_t value) { return value + (A_OFFSET); }
  inline uint16_t GET_MIN_OFFSET(uint16_t value) { return value - (A_OFFSET); }
  uint32_t clickMillis = 0;

public:
  AnalogButtons(uint8_t analogPin, uint16_t analogValue);

  bool getState();
  bool isClick();
  inline bool isPress() { return _state; }

  void listen();
};

#endif // ANALOG_BUTTONS_H
