#if !defined(HD44780_H)
#define HD44780_H

#include <PCF8574T.h>
#include <Print.h>

/**
 * Registers
 **/
#define HD_WRITE_COMMAND 0x0U
#define HD_WRITE_DATA 0x1U
#define HD_READ_STATUS 0x2U // read busy flag and index position
#define HD_READ_DATA 0x3U
#define HD_E 0x4U
#define HD_BACK_LIGHT 0x8U

/**
 * General commands
 **/
#define HD_CLEAR 0x1U
#define HD_HOME 0x2U
#define HD_SHIFT_RIGHT 0x1CU // Shift dispaly
#define HD_SHIFT_LEFT 0x18U
#define HD_MOVE_CURSOR_RIGHT 0x14U
#define HD_MOVE_CURSOR_LEFT 0x10U
#define HD_WRITE_TO_POSITION 0x80U

/**
 * Entry mode set
 * command = HD_ENTRY_MODE | HD_EM_INCREMENT_INDEX_CURSOR
 **/
#define HD_ENTRY_MODE 0x4U
#define HD_EM_INCREMENT_INDEX_CURSOR 0x2U
#define HD_EM_DECREMENT_INDEX_CURSOR 0x0U
#define HD_EM_SHIFT_DSPL_AND_CURSOR 0x1U
#define HD_EM_NSHIFT_DSPL_AND_CURSOR 0x0U

/**
 * Cursor and dispaly control
 * command = HD_CONTROL | HD_SHIFT
 **/
#define HD_CONTROL 0x8U
#define HD_C_DSPL_ON 0x4U
#define HD_C_CURSOR_ON 0x2U
#define HD_C_CURSOR_BLINK_ON 0x1U

/**
 * Function set
 * command = HD_CONTROL | HD_SHIFT
 **/
#define HD_SETTINGS 0x20U
#define HD_S_BUS_INTERFACE_8 0x10U
#define HD_S_BUS_INTERFACE_4 0x0U
#define HD_S_NUM_LINES_2 0x8U
#define HD_S_NUM_LINE_1 0x0U
#define HD_S_FONT_5X10 0x4U
#define HD_S_FONT_5X8 0x0U

// #define HD_LINE_LENGTH 40u // lenght of one line in two lines mode

#define HD_BUF_SIZE 64U

inline uint8_t lowBits(uint8_t byte) { return byte & 0xF; }
inline uint8_t highBits(uint8_t byte) { return byte >> 4; }

class HD44780 : public Print {
private:
  PCF8574T *_pcf = nullptr;
  uint8_t _chars;
  uint8_t _rows;
  uint8_t backLight;
  uint8_t _address;
  uint8_t cursorIndex;
  uint8_t _dBufferIndex;
  byte _dBufferEnd;
  byte _dBufferStart;
  uint8_t _dBuffer[HD_BUF_SIZE];
  int8_t errorStatus;
  void setup();

  inline void WRITE_COMMAND(uint8_t code, bool isEnd = true) {
    command(HD_WRITE_COMMAND, code, isEnd);
  };

  inline void WRITE_DATA(uint8_t data, bool isEnd = true) {
    command(HD_WRITE_DATA, data, isEnd);
  };

public:
  HD44780() {};
  explicit HD44780(PCF8574T * = nullptr, byte = 16, byte = 2);
  void command(uint8_t, uint8_t, bool);
  void command(uint8_t, uint8_t);
  bool isBusy();
  void printBeginPosition(uint8_t, const char[], uint8_t);
  void setCursor(uint8_t col, uint8_t row);

  virtual size_t write(byte) override;                               // from print
  virtual size_t write(const uint8_t *buffer, size_t size) override; // from print

  /* byte buf(const byte*, byte);
  byte buf(byte);
  byte buf(); */

  inline void clear(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_CLEAR, isEnd);
  };

  inline void on(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_C_DSPL_ON, isEnd);
  }

  inline void off(bool isEnd = true) {
    command(HD_WRITE_COMMAND, (~HD_C_DSPL_ON & HD_C_DSPL_ON), isEnd);
  }

  inline void home(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_HOME, isEnd);
  };

  inline void backspace(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_MOVE_CURSOR_LEFT, false);
    isBusy();
    command(HD_WRITE_DATA, ' ', false);
    isBusy();
    command(HD_WRITE_COMMAND, HD_MOVE_CURSOR_LEFT, isEnd);
  };

  inline void moveCursorRight(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_MOVE_CURSOR_RIGHT, isEnd);
  };

  inline void moveCursorLeft(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_MOVE_CURSOR_LEFT, isEnd);
  };

  inline void moveDisplayRight(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_SHIFT_RIGHT, isEnd);
  }

  inline void moveDisplayLeft(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_SHIFT_LEFT, isEnd);
  }

  inline void WRITE_TO_POSOTION(uint8_t posotion, bool isEnd = true) {
    command(HD_WRITE_COMMAND, posotion | HD_WRITE_TO_POSITION, isEnd);
  };

  inline uint8_t getCursorIndex() { return cursorIndex; };
  inline byte isError() { return errorStatus; }
  inline void setError(uint8_t err) { errorStatus = err; };
  // inline void clearError() { this->errorStatus = 0; };
};

#endif // HD44780_H
