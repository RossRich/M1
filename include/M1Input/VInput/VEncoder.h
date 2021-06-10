#if !defined(V_ENCODER_H)
#define V_ENCODER_H

class VEncoder {
private:
public:
  virtual ~VEncoder() {}
  virtual bool isRotation() = 0;
  virtual bool isClicked() = 0;
  virtual void check() = 0;
  virtual int8_t getDiraction() = 0;
};

#endif // V_ENCODER_H
