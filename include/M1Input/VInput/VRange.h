#if !defined(V_RANGE_H)
#define V_RANGE_H

#include <inttypes.h>

class VRange {
public:
  virtual ~VRange() {}
  virtual void check() = 0;
  virtual int16_t getValue() = 0;
};

#endif // V_RANGE_H
