#if !defined(JOYSTICK_H_)
#define JOYSTICK_H_

#include <Arduino.h>
#include <Vector.h>

#define VRX A0
#define VRY A1
#define KEY 11
#define J_KEY_PRESS 0
#define J_KEY_UNPRESS 1
#define J_LISTEN_PERIOD 20u
#define J_DEFAULT_POT_MAX 1023u
#define J_DEFAULT_POT_MIN 0u

struct JPosition {
  int16_t x = 0;
  int16_t y = 0;
  int16_t pX = 0;
  int16_t pY = 0;
};

struct JState {
  bool but;
  bool pBut;
};

class Joystick {
private:
  JPosition _jPos;
  JState _jState;
  uint8_t vrxPin_;
  uint8_t vryPin_;
  uint8_t keyPin_;
  int16_t xVal_;
  int16_t yVal_;
  uint16_t maxPos_;
  int16_t minPos_;
  uint32_t listenPeriod_;
  bool keyStatus_;
  bool prewKeyStatus_;
  bool keyClick_;
  void init();
  void events();

public:
  Joystick();
  Joystick(uint8_t vrx, uint8_t vry, uint8_t key);
  Joystick(
      uint8_t vrx, uint8_t vry, uint16_t minPosition, uint16_t maxPosition);
  void listen();
  bool isKeyClick();
  inline int16_t x() { return _jPos.x; }
  inline int16_t y() { return _jPos.y; }
  inline bool isKeyPress() {
    return (_jState.but == J_KEY_PRESS) ? true : false;
  }

  inline int16_t difX() { return _jPos.x - _jPos.pX; }

  inline int16_t difY() { return _jPos.y - _jPos.pY; }

  
};

#endif // JOYSTICK_H_
