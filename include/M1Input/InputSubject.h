#if !defined(INPUT_SUBJECT_H)
#define INPUT_SUBJECT_H

#include "InputObserver.h"

class InputSubject {
public:
  virtual ~InputSubject() {}
  virtual void subscribe(InputObserver *o) = 0;
  virtual void unsubscrube(InputObserver *o) = 0;
  virtual void notify(IEv e) = 0;
};

#endif // INPUT_SUBJECT_H
