#if !defined(ENCODER_H_)
#define ENCODER_H_

#define ENCODER_CW_ROTATION 1
#define ENCODER_CCW_ROTATION -1
#define ENCODER_BUTTON_PRESS 0
#define ENCODER_BUTTON_UNPRESS 1
#define ENCODER_BUTTON_LISTEN_PERIOD 150

class Encoder {
private:
  uint8_t s1_;
  uint8_t s2_;
  uint8_t button_;
  uint32_t buttonListenPeriod_;
  bool butChangeState_;
  bool butDown_;
  bool butUp_;
  bool butClick_;
  volatile int8_t rotationDiraction_;
  uint8_t buttonState_;
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
  inline int8_t getDiraction() {
    noInterrupts();
    int8_t tDiractions = rotationDiraction_;
    rotationDiraction_ = 0;
    interrupts();
    return tDiractions;
  };
};

#endif // ENCODER_H_
