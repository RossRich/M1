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
  this->dBuffer[MAX_BUF_SUZE] = {};
  this->screenArea[HD_LINE_LENGTH * 2] = {};
  for (uint8_t i = 0; i < 40; ++i) {
    this->screenArea[i] = i;
    this->screenArea[i + 40] = i + 64;
  }
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

  return 1;
}

bool HD44780::isBusy() {
  Serial.println("------ isBusy -");
  bool busyFlag = true;
  uint8_t receive = 0;
  setError(0);

  this->pcf->send(
      PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E, false);

  do {
    receive = uint8_t(this->pcf->receive(1, false)) & 0xF0;

    pcf->send();
    pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT);
    pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
    pcf->commit(false);

    receive |= uint8_t(this->pcf->receive(1, false)) >> 4;

    busyFlag = bool(bitRead(receive, 7));

    if (busyFlag) {
      pcf->send();
      pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT);
      pcf->addToSend(
          PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
      pcf->commit(false);
    } else {
      // pcf->send(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT, false);
      pcf->send(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT, true);
    }

    Serial.print("Received: ");
    Serial.println(receive, HEX);

  } while (busyFlag && !pcf->isError());

  if (pcf->isError())
    setError();
  else
    this->cursorIndex = receive;

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

  setError(uint8_t(pcf->isError()));
}

void HD44780::printBeginPosition(
    uint8_t position, const char cst[], uint8_t len) {

  WRITE_TO_POSOTION(position, false);
  isBusy();
  for (uint8_t i = 0; i < len; i++) {
    WRITE_DATA(cst[i], false);
    isBusy();
  }
}
