#include <Arduino.h>
#include <Wire.h>
#include "PCF8574T.h"

/**
 *
 * MAX clock - 100kHz
 * Total package sink current - 80mA
 *
 **/

PCF8574T::PCF8574T() {
  this->address = PCF_ADDRESS_FIXED + PCF_ADDRESS_HARDWARE;
  this->errorStatus = 0;
  init();
}

PCF8574T::PCF8574T(uint8_t address) : PCF8574T() { this->address = address; }

void PCF8574T::init() {
  Wire.begin();
  Wire.setClock(PCF_MAX_SPEED);
}

/**
 * Before recieve data pcf must have hight logical level on readeble pins
 * ret readed bytes
 **/
int8_t PCF8574T::receive(uint8_t length, bool isEnd) {
  uint8_t res = Wire.requestFrom(this->address, length, (uint8_t)isEnd);
  if (res) {
    return Wire.read();
  } else {
    setError(TWI_ERR_RECEIVE);
    return 0;
  }
}

/**
 * 
 **/
int8_t PCF8574T::send(uint8_t data, bool isEnd) {
  Wire.beginTransmission(this->address);
  if (!Wire.write(data)) {
    setError(TWI_ERR_WRITE);
    return 0;
  } else {
    setError(Wire.endTransmission((uint8_t)isEnd));
    return isError();
  }
}

int8_t PCF8574T::send(const uint8_t data[], uint8_t length, bool isEnd) {
  Wire.beginTransmission(this->address);
  Wire.write(data, length);
  if (Wire.getWriteError()) {
    setError(TWI_ERR_WRITE);
    return 0;
  } else {
    setError(Wire.endTransmission((uint8_t)isEnd));
    return isError();
  }
}