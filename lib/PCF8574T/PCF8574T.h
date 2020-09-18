#if !defined(PCF8574T_H)
#define PCF8574T_H

#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>

#define PCF_MAX_SPEED 100000
#define PCF_ADDRESS_HARDWARE 0x7
#define PCF_ADDRESS_FIXED 0x20
#define PCF_READ 1
#define PCF_WRITE 0
#define PCF_BEFORE_RECEIVE 0xF0U

#define TWI_ERR_BUF_LEN 1   // length to long for buffer
#define TWI_ERR_ADDR_NACK 2 // address send, NACK received
#define TWI_ERR_DATA_NACK 3 // data send, NACK received
#define TWI_ERR_OTHER 4 // other twi error (lost bus arbitration, bus error, ..)
#define TWI_ERR_RECEIVE 5 // receive is empty
#define TWI_ERR_WRITE 6   // twi write error (check buffer length)

class PCF8574T {
private:
  uint8_t _address;
  int8_t errorStatus;
  void init();

public:
  PCF8574T();
  explicit PCF8574T(uint8_t);
  int8_t receive(uint8_t = 1, bool = true, bool = false);
  void send();
  void send(const uint8_t[], uint8_t, bool = true);
  void send(uint8_t, bool = true);
  uint8_t addToSend(uint8_t item);
  uint8_t addToSend(const uint8_t array[], uint8_t length);
  uint8_t commit(bool isEnd = true);
  inline void setError(int8_t err = 1) { errorStatus = err; };
  inline uint8_t isError() { return errorStatus; };
};

#endif // PCF8574T_H
