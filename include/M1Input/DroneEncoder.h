#if !defined(DRONE_ENCODER_H)
#define DRONE_ENCODER_H

#define ENCODER1_PIN 2
#define ENCODER2_PIN 4

#include <Encoder.h>
#include "InputSubject.h"

void gEncoderHandler();

class DroneEncoder : public VEncoder, public InputSubject {
private:
  InputObserver *_mObs = nullptr;
  Encoder *_mE;
  int8_t dir = 0;

public:
  DroneEncoder(uint8_t s1Pin, uint8_t s2Pin) {
    _mE = new Encoder(s1Pin, s2Pin);
  }

  DroneEncoder(Encoder *gEnc) : _mE(gEnc) {
    _mE->setRotationListener(gEncoderHandler);
  }
  ~DroneEncoder() {}

  void check() {
    _mE->listen();

    if (isRotation())
      notify(INPUT_EVENTS::MOVE);
  }

  bool isRotation() {
    dir = _mE->getDiraction();
    if (dir == ENCODER_CCW_ROTATION || dir == ENCODER_CW_ROTATION)
      return true;
    else
      return false;
  }

  int8_t getDiraction() {
    int8_t rr = dir;
    dir = 0;
    return rr;
  }

  bool isClicked() { return false; }

  void subscribe(InputObserver *o) { _mObs = o; }
  void unsubscrube(InputObserver *o) { return; }
  void notify(INPUT_EVENTS e) {
    if (_mObs != nullptr)
      _mObs->update(this, e);
  }
};

#endif // DRONE_ENCODER_H
