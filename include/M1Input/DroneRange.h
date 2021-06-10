#if !defined(DRONE_RANGE_H)
#define DRONE_RANGE_H

#include "VRange.h"
#include <Potentiometer.h>
#include "InputSubject.h"

class DroneRange : public VRange, InputSubject {
private:
  Potentiometer *_mP = nullptr;
  InputObserver *_mObs = nullptr;

public:
  DroneRange(uint8_t rangePin, int16_t minPos, int16_t maxPos)
      : _mP(new Potentiometer(rangePin, minPos, maxPos)) {}
  ~DroneRange() {}

  void check() override {
    _mP->listen();
    
    if (_mP->difVal() != 0)
      notify(INPUT_EVENTS::MOVE);
  }
  int16_t getValue() override { return _mP->value(); }

  void subscribe(InputObserver *o) override { _mObs = o; }
  void unsubscrube(InputObserver *o) override { _mObs = nullptr; }
  void notify(IEv e) override {
    if (_mObs != nullptr)
      _mObs->update(this, e);
  }
};

#endif // DRONE_RANGE_H
