#if !defined(ENCODER_H_)
#define ENCODER_H_

#define ENCODER_CW_ROTATION 1
#define ENCODER_CCW_ROTATION -1
#define ENCODER_BUTTON_PRESS 0
#define ENCODER_BUTTON_UNPRESS 1
#define ENCODER_BUTTON_LISTEN_PERIOD 150u // 150 ms
#define ENCODER_BUTTON_LONG_PRESS ((ENCODER_BUTTON_LISTEN_PERIOD) + 850u) // long press = listen_period or MORE

class Encoder {
private:
  uint8_t s1_;
  uint8_t s2_;
  uint8_t button_;
  uint8_t buttonState_;
  uint8_t prewButtonState_;
  uint32_t buttonListenPeriod_;
  uint32_t internalTime_;
  bool flRead_;
  bool butChangeState_;
  bool butDown_;
  bool butUp_;
  bool butClick_;
  bool butLongPress_;
  uint32_t butLongPressTimer_;
  volatile int8_t rotationDiraction_;
  void (*uClkFunc_)();
  void (*uLngClkFunc_)();
  void (*uSpinFunc_)();
  // void (*uRotFunc_)();
  void buttonListenerHendler();

public:
  Encoder();
  Encoder(uint8_t, uint8_t, uint8_t);
  void setClickListener(void (*)());
  void setLongClickListener(void (*)());
  void setRotationListener(void (*)());
  void setSpinListener(void (*)());
  void listenRotation();
  void listenButton();
  bool isButtonKeep() const;
  bool isButtonUp();
  bool isButtonDown();
  bool isButtonClick();
  bool isButtonLongPress();

  inline int8_t getDiraction() {
    noInterrupts();
    int8_t tDiractions = rotationDiraction_;
    rotationDiraction_ = 0;
    interrupts();
    return tDiractions;
  };
};

#endif // ENCODER_H_
