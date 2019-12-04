#if !defined(ENCODER_H_)
#define ENCODER_H_

#define ENCODER_CW_ROTATION 1
#define ENCODER_CCW_ROTATION -1

class Encoder {
private:
  uint8_t s1_;
  uint8_t s2_;
  uint8_t button_;
  uint32_t time;
  volatile int8_t rotationDiraction_;
  volatile uint8_t ccw;
  volatile uint8_t cw;
  void (*uClkFunc)();
  void (*uRotFunc)();

public:
  Encoder(uint8_t, uint8_t, uint8_t);
  void setClickListener(void (*)());
  void setRotationListener(void (*)());
  void listenRotation();
  inline int8_t getDiraction() {
    noInterrupts();
    int8_t tDiractions = rotationDiraction_;
    rotationDiraction_ = 0;
    interrupts();
    return tDiractions;
  };
};

#endif // ENCODER_H_
