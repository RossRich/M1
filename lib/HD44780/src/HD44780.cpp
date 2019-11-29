#include <Arduino.h>
#include <PCF8574T.h>
#include "HD44780.h"

HD44780::HD44780() {}

/**
 * Begin with PCF8574T
 * @param address
 * @param chars = 16
 * @param rows = 2
 **/
HD44780::HD44780(uint8_t address, uint8_t chars, uint8_t rows) : HD44780() {
  this->dBufferCounter = 0;
  this->address = address;
  this->chars = chars;
  this->rows = rows;
  this->errorStatus = 0;
}

int8_t HD44780::init() {
  this->pcf = new PCF8574T(address);
  this->pcf->send(0xF8);

  delay(1000);
  this->pcf->send(0x30 | HD_WRITE_COMMAND, false);
  delayMicroseconds(4100);
  this->pcf->send(0x30 | HD_WRITE_COMMAND, false);
  delayMicroseconds(100);
  this->pcf->send(0x30 | HD_WRITE_COMMAND, false);

  this->pcf->send(0x20 | HD_WRITE_COMMAND, false);

  isBusy();

  WRITE_COMMAND(
      HD_SETTINGS | HD_S_BUS_INTERFACE_4 | HD_S_FONT_5X8 | HD_S_NUM_LINES_2,
      false);

  isBusy();

  WRITE_COMMAND(HD_CONTROL | HD_C_CURSOR_ON | HD_C_DSPL_ON, false);

  isBusy();

  clear(false);

  isBusy();

  WRITE_COMMAND(HD_ENTRY_MODE | HD_EM_INCREMENT_INDEX_CURSOR, false);

  isBusy();

  home();

  // isBusy();

  return 1;
}

bool HD44780::isBusy() {
  Serial.println("------ isBusy -");
  bool busyFlag = true;
  int8_t receive = 0;
  int8_t res = 0;
  setError(0);

  this->pcf->send(
      PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E, false);

  do {
    this->pcf->receive(1, false);

    if (!receive && pcf->isError())
      setError();

    res = uint8_t(receive) & 0xF0;

    pcf->send();
    pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT);
    pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
    pcf->commit(false);

    receive = this->pcf->receive(1, false);

    if (!receive && pcf->isError())
      setError();

    res |= (uint8_t(receive) >> 4);

    busyFlag = bool(bitRead(res, 7));

    if (busyFlag) {
      pcf->send();
      pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT);
      pcf->addToSend(
          PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
      pcf->commit(false);
    } else
      pcf->send(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT, true);

    Serial.print("Received: ");
    Serial.println(res, HEX);

  } while (busyFlag);

  this->cursorIndex = res;

  Serial.println("------ end -");
  return busyFlag;
}

void HD44780::command(uint8_t cmnd, uint8_t dataWord, bool isEnd) {
  uint8_t bitsHight = (highBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;
  uint8_t bitsLow = (lowBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;

  Serial.print("Command: ");
  Serial.println(bitsHight, HEX);
  Serial.println(bitsLow, HEX);

  pcf->send();
  pcf->addToSend(bitsHight);
  pcf->addToSend(PCF_BEFORE_RECEIVE | HD_BACK_LIGHT | cmnd);
  pcf->addToSend(bitsLow);
  pcf->addToSend(PCF_BEFORE_RECEIVE | HD_BACK_LIGHT | HD_READ_STATUS);
  pcf->commit(isEnd);

  setError(pcf->isError());
};

uint8_t HD44780::getCursorIndex() { return this->cursorIndex; }
