#if !defined(ENCODER_H_)
#define ENCODER_H_

class Encoder {
private:
  uint8_t s1;
  uint8_t s2;
  uint8_t button;
  uint32_t time;
  
  void (*userfunction)(const char*);
public:
  Encoder(uint8_t, uint8_t, uint8_t);
  void onPressListener(void (*)(const char*));
  void listen();
};



#endif // ENCODER_H_
