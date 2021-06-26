#if !defined(_SUBJECT_H_)
#define _SUBJECT_H_

#include <Arduino.h>
#include <inttypes.h>

#include "Observer.h"

class Subject {
protected:
  Observer **observers = nullptr;
  uint8_t observersCount = 0;

public:
  Subject();
  virtual ~Subject() {}
  virtual void addObserver(Observer *obs) = 0;
  virtual void delObserver(Observer *obs) = 0;
  virtual void notifyObservers() = 0;
};

#endif // _SUBJECT_H_
