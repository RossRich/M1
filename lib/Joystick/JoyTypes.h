#if !defined(_JOY_TYPES_H)
#define _JOY_TYPES_H

#include <inttypes.h>

struct JoyData {
  int16_t *x;
  int16_t *y;
  bool *sw;
};

#endif // _JOY_TYPES_H
