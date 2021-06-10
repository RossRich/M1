#if !defined(M1_TIMER_H)
#define M1_TIMER_H

#include "ITimer.h"

template <typename T>
class Timer : public ITimer {
private:
  uint32_t _mTimer = 0;
  void (T::*ufunc)();
  T *_mClass;
  bool _mIsDone = false;

public:
  Timer(uint32_t timeout, T *uClass, void (T::*func)()) {
    _mClass = uClass;
    ufunc = func;
    _mTimer = millis() + timeout;
  }
  ~Timer() {}

  void execute() override {
    Serial.println("execute");
    (_mClass->*ufunc)();
    _mIsDone = true;
  }
  uint32_t getTimeout() override { return _mTimer; }
  bool done() override { return _mIsDone; }
};

#endif // M1_TIMER_H