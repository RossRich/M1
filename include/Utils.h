#if !defined(UTILS_H_)
#define UTILS_H_

#include <inttypes.h>

inline uint8_t lowBits(uint8_t byte) { return byte & 0xF; }
inline uint8_t highBits(uint8_t byte) { return byte >> 4; }

#endif // UTILS_H_
