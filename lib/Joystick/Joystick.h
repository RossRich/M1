#if !defined(JOYSTICK_H_)
#define JOYSTICK_H_

#include <Arduino.h>

#define VRX A0
#define VRY A1
#define KEY 11
#define J_KEY_PRESS 0
#define J_KEY_UNPRESS 1
#define J_LISTEN_PERIOD 50u
#define J_DEFAULT_POT_MAX 1023u
#define J_DEFAULT_POT_MIN 0u

class Joystick {
private:
  uint8_t vrxPin_;
  uint8_t vryPin_;
  uint8_t keyPin_;
  int16_t xVal_;
  int16_t yVal_;
  uint16_t maxPos_;
  int16_t minPos_;
  uint32_t internalTime_;
  uint32_t listenPeriod_;
  bool keyStatus_;
  bool prewKeyStatus_;
  bool keyClick_;
  void init();

public:
  Joystick();
  Joystick(uint8_t, uint8_t, uint8_t);
  Joystick(uint8_t, uint8_t, uint8_t, uint16_t, uint16_t);
  void listen();
  bool isKeyClick();
  inline int16_t x() { return xVal_; }
  inline int16_t y() { return yVal_; }
  inline bool isKeyPress() {
    return (keyStatus_ == J_KEY_PRESS) ? true : false;
  }
};

#endif // JOYSTICK_H_
