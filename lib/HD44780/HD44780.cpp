#include "HD44780.h"

/** TODO
 * without PCF module
 **/
/* HD44780::HD44780(byte chars, byte rows) {
  _chars = chars;
  _rows = rows;
} */

/**
 * Begin with PCF8574T
 * @param address
 * @param chars = 16
 * @param rows = 2
 **/
HD44780::HD44780(PCF8574T *pcfInstance, byte chars, byte rows) {

  _rows = rows;
  _chars = chars;

  _dBufferIndex = 0;
  _dBufferStart = 0;
  _dBufferEnd = 0;

  errorStatus = 0;

  if (pcfInstance != nullptr) {
    _pcf = pcfInstance;
    setup();
  } else
    setError(11);
  Serial.println(F("HD44780 constructor ok"));
}

void HD44780::setup() {
  Serial.println(F("HD44780 setup"));
  delayMicroseconds(50);

  WRITE_COMMAND(0x30, false);

  delayMicroseconds(4500);

  WRITE_COMMAND(0x30, false);
  delayMicroseconds(4500);

  WRITE_COMMAND(0x30, false);
  delayMicroseconds(150);

  WRITE_COMMAND(0x20, false);

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
  Serial.println(isError());
  Serial.println(F("HD44780 setup ok"));
}

bool HD44780::isBusy() {
  // Serial.println("------ isBusy -");
  bool busyFlag = true;
  uint8_t receive = 0;
  if (errorStatus)
    return 0;

  _pcf->send(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E, false);

  while (busyFlag && !_pcf->isError()) {
    receive = uint8_t(_pcf->receive(1, false)) & 0xF0;

    if (_pcf->isError())
      break;

    _pcf->send();
    _pcf->addToSend(HD_READ_STATUS | HD_BACK_LIGHT);
    _pcf->addToSend(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
    _pcf->commit(false);

    if (_pcf->isError())
      break;

    receive |= uint8_t(_pcf->receive(1, false)) >> 4;

    if (_pcf->isError())
      break;

    busyFlag = bool(bitRead(receive, 7));

    if (busyFlag) {
      _pcf->send();
      _pcf->addToSend(HD_READ_STATUS | HD_BACK_LIGHT);
      _pcf->addToSend(
          PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT | HD_E);
      _pcf->commit(false);
    } else {
      _pcf->send(PCF_BEFORE_RECEIVE | HD_READ_STATUS | HD_BACK_LIGHT, true);
    }

    if (_pcf->isError())
      break;

    // Serial.print("Received: ");
    // Serial.println(receive, HEX);
  }

  if (_pcf->isError()) {
    setError(_pcf->isError());
    return 0;
  } else
    this->cursorIndex = receive;

  // Serial.println("------ end -");
  return busyFlag;
}

void HD44780::command(uint8_t cmnd, uint8_t dataWord, bool isEnd) {
  if (errorStatus)
    return;

  uint8_t bitsHight = (highBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;
  uint8_t bitsLow = (lowBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;

  // Serial.print("Command: ");
  // Serial.println(bitsHight, HEX);
  // Serial.println(bitsLow, HEX);

  _pcf->send();
  _pcf->addToSend(bitsHight);
  _pcf->addToSend(HD_BACK_LIGHT | cmnd);
  _pcf->addToSend(bitsLow);
  _pcf->addToSend(HD_BACK_LIGHT | HD_READ_STATUS);

  setError(_pcf->commit(isEnd));
}

void HD44780::command(uint8_t cmnd, uint8_t dataWord) {
  if (errorStatus)
    return;

  uint8_t bitsHight = (highBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;
  uint8_t bitsLow = (lowBits(dataWord) << 4) | HD_E | HD_BACK_LIGHT | cmnd;

  // Serial.print("Command: ");
  // Serial.println(bitsHight, HEX);
  // Serial.println(bitsLow, HEX);

  // _pcf->send();
  _pcf->addToSend(bitsHight);
  _pcf->addToSend(HD_BACK_LIGHT | cmnd);
  _pcf->addToSend(bitsLow);
  _pcf->addToSend(HD_BACK_LIGHT | HD_READ_STATUS);
  setError(_pcf->isError());
}

size_t HD44780::write(byte data) {
  _pcf->send();
  command(HD_WRITE_DATA, data);
  return _pcf->commit();
}

size_t HD44780::write(const uint8_t data[], size_t len) {
  _pcf->send();
  for (size_t i = 0; i < len; ++i) {
    command(HD_WRITE_DATA, data[i]);
  }
  return _pcf->commit();
}

void HD44780::printBeginPosition(
    uint8_t position, const char cst[], uint8_t len) {
  WRITE_TO_POSOTION(position, false);
  isBusy();
  _pcf->send();
  for (uint8_t i = 0; i < len; i++)
    command(HD_WRITE_DATA, cst[i]);
  setError(_pcf->commit());
}

void HD44780::setCursor(uint8_t col, uint8_t row) {
  // row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row >= 2) {
    WRITE_TO_POSOTION(col + 64, false);
  } else {
    WRITE_TO_POSOTION(col, false);
  }

  isBusy();
}

/* byte HD44780::buf(const byte *str, byte len) {

  if (len > HD_BUF_SIZE)
    return 1;
  else if (_dBufferIndex + len > HD_BUF_SIZE)
    return 1;

  for (byte i = 0; i < len; i++)
    _dBuffer[_dBufferIndex++] = str[i];
  _dBufferEnd = _dBufferIndex;
  return 0;
}

byte HD44780::buf() {

  _pcf->send();
  byte len = _dBufferEnd - _dBufferStart;
  if(len > 8) {
    len = 8;
  }
  for (byte i = _dBufferStart; i < len; i++)
  {
    command(HD_WRITE_DATA, _dBuffer[i]);
    _dBufferStart = i;
  }
  _dBufferIndex = 0;
} */
