#include "PCF8574T.h"

/**
 *
 * MAX clock - 100kHz
 * Total package sink current - 80mA
 *
 **/

PCF8574T::PCF8574T() {
  Serial.println(F("PCF constuructor"));
  _address = PCF_ADDRESS_FIXED + PCF_ADDRESS_HARDWARE;
  errorStatus = 0;
  init();
}

PCF8574T::PCF8574T(uint8_t address) : PCF8574T() { _address = address; }

void PCF8574T::init() {
  Serial.println(F("PCF init "));
  Wire.begin();
  Wire.setClock(PCF_MAX_SPEED);
  Serial.println(F("PCF init ok"));
}

/**
 * Before recieve data pcf must have hight logical level on readeble pins
 * ret readed bytes
 */
int8_t PCF8574T::receive(uint8_t length, bool isEnd, bool clear) {
  if (clear)
    send(0xFFU, false);
  uint8_t res = Wire.requestFrom(_address, length, (uint8_t)isEnd);
  if (res) {
    return Wire.read();
  } else {
    setError(TWI_ERR_RECEIVE);
    return 0;
  }
}

/**
 *
 */
void PCF8574T::send(uint8_t data, bool isEnd) {

  send();

  if (!Wire.write(data)) {
    setError(TWI_ERR_WRITE);
  } else {
    setError(Wire.endTransmission((uint8_t)isEnd));
  }
}

void PCF8574T::send(const uint8_t data[], uint8_t length, bool isEnd) {

  send();

  Wire.write(data, length);
  if (Wire.getWriteError()) {
    setError(TWI_ERR_WRITE);
  } else {
    setError(Wire.endTransmission((uint8_t)isEnd));
  }
}

void PCF8574T::send() {
  if (isError())
    return;

  Wire.beginTransmission(_address);
}

uint8_t PCF8574T::addToSend(uint8_t item) {
  if (isError())
    return isError();

  Wire.write(item);
  setError(Wire.getWriteError());

  return isError();
}

uint8_t PCF8574T::addToSend(const uint8_t array[], uint8_t length) {
  if (isError())
    return isError();

  Wire.write(array, length);
  setError(Wire.getWriteError());

  return isError();
}

uint8_t PCF8574T::commit(bool isEnd) {
  if (isError())
    return isError();

  uint8_t res = Wire.endTransmission((uint8_t)isEnd);

  if (res > 0)
    setError(res);

  return res;
}
