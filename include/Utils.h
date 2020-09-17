#if !defined(UTILS_H_)
#define UTILS_H_

#include <inttypes.h>
#include <Arduino.h>

// inline uint8_t lowBits(uint8_t byte) { return byte & 0xF; }
// inline uint8_t highBits(uint8_t byte) { return byte >> 4; }

void errorBlink() {
  pinMode(LED_BUILTIN, OUTPUT);
  uint8_t ledStatus = LOW;
  while (1) {
    for (uint8_t i = 0; i < 10; i++) {
      if (ledStatus == LOW)
        ledStatus = HIGH;
      else
        ledStatus = LOW;
      digitalWrite(LED_BUILTIN, ledStatus);
      delay(100);
    }
    delay(1500);
  }
}

#endif // UTILS_H_
