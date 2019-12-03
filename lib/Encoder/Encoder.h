#if !defined(ENCODER_H_)
#define ENCODER_H_

#define ENCODER_CW_ROTATION 0x1
#define ENCODER_CCW_ROTATION 0x2

class Encoder {
private:
  uint8_t s1;
  uint8_t s2;
  uint8_t button;
  uint32_t time;
  volatile uint8_t rotationDiraction;
  volatile uint8_t ccw;
  volatile uint8_t cw;
  void (*userfunction)(const char *);

public:
  Encoder(uint8_t, uint8_t, uint8_t);
  void setClickListener(void (*)(bool));
  void setRotationListener(void (*)(int8_t));
  void listen();
};

#endif // ENCODER_H_
