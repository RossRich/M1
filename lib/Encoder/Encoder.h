#if !defined(ENCODER_H_)
#define ENCODER_H_

#include <Arduino.h>

#define ENCODER_CW_ROTATION 1
#define ENCODER_CCW_ROTATION -1
#define ENCODER_BUTTON_PRESS 0
#define ENCODER_BUTTON_UNPRESS 1
#define ENCODER_BUTTON_LISTEN_PERIOD 150u // 150 ms
#define ENCODER_BUTTON_LONG_PRESS                                              \
  ((ENCODER_BUTTON_LISTEN_PERIOD) + 850u) // long press = listen_period or MORE
#define MAX_NUM_LISTENER 4u

class Encoder {
private:
  uint8_t s1_;
  uint8_t s2_;
  uint8_t button_;
  uint8_t buttonState_;
  uint8_t prewButtonState_;
  uint32_t buttonListenPeriod_;
  uint32_t internalTime_;
  bool isReadedLongPress_;

  // bool butChangeState_;
  bool butDown_;
  bool butUp_;
  bool butClick_;
  bool butLongPress_;

  bool isReady_;
  uint32_t butLongPressTimer_;
  volatile int8_t rotationDiraction_;
  volatile bool spinPressure_;
  void (*uClkFunc_)();
  void (*uLngClkFunc_)();
  void (*uSpinFunc_)();
  void buttonListenerHendler();
  void spinPressureHendler(void (*)());
  uint8_t listenerBufferIndex_;
  void (*listenerArray[MAX_NUM_LISTENER])();
  volatile uint32_t debounce_;

public:
  Encoder();
  Encoder(uint8_t, uint8_t, uint8_t);
  Encoder(uint8_t, uint8_t);
  // Encoder(uint8_t, uint8_t, uint8_t, void (*)());
  void setClickListener(void (*)());
  void setLongClickListener(void (*)());
  void setInterruptRotationListener(void (*)());
  void setSpinPressureListener(void (*)());
  void setLongClickTime(); // todo
  // void listenRotation();
  void listen();
  bool isButtonKeep() const;
  bool isButtonUp();
  bool isButtonDown();
  bool isButtonClick();
  bool isButtonLongPress();
  bool isSpinPressure();
  int8_t getDiraction();
  void listenRotation();
  void addToListener(void (*)());
};

#endif // ENCODER_H_
