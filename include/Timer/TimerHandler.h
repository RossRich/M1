#if !defined(M1_TIMER_HANDLER_H)
#define M1_TIMER_HANDLER_H

#include <Arduino.h>
#include "ITimer.h"
#include <Vector.h>

class TimerHandler {
private:
  Vector<ITimer *> _mTimers;
  ITimer *_mTimersArray[10];

public:
  TimerHandler() { _mTimers.setStorage(_mTimersArray); }
  ~TimerHandler() {}
  void addTimer(ITimer *t) {
    _mTimers.push_back(t);
    Serial.println(_mTimers.size());
  }
  void check() {
    if (_mTimers.size() != 0) {
      uint32_t time = millis();
      if (time >= _mTimers.at(0)->getTimeout() && !_mTimers.at(0)->done())
        _mTimers.at(0)->execute();
      // Таймеры не должны включаться если сработали
      // удаление сработавших таймеров
    }
  }
};

extern TimerHandler gTimerHandler;

#endif // M1_TIMER_HANDLER_H