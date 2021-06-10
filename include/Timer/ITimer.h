#if !defined(M1_ITIMER_H)
#define M1_ITIMER_H

#include <inttypes.h>

class ITimer {
private:
public:
  ITimer() {}
  virtual ~ITimer() {}

  virtual void execute() = 0;
  virtual uint32_t getTimeout() = 0;
  virtual bool done() = 0;
};

#endif // M1_ITIMER_H
