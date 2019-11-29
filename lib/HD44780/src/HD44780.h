#if !defined(HD44780_H)
#define HD44780_H

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

#define HD_SET_CHAR 0x80U

const uint8_t MAX_BUF_SUZE = 32;

inline uint8_t lowBits(uint8_t byte) { return byte & 0xF; }
inline uint8_t highBits(uint8_t byte) { return byte >> 4; }

class HD44780 {
private:
  PCF8574T *pcf = NULL;
  uint8_t chars;
  uint8_t rows;
  uint8_t backLight;
  uint8_t address;
  uint8_t cursorIndex;
  uint8_t dBufferCounter;
  uint8_t dBuffer[MAX_BUF_SUZE];
  int8_t errorStatus;

  inline void WRITE_COMMAND(uint8_t code, bool isEnd = true) {
    command(HD_WRITE_COMMAND, code, isEnd);
  };

  inline void WRITE_DATA(uint8_t data, bool isEnd = true) {
    command(HD_WRITE_DATA, data, isEnd);
  };

public:
  HD44780();
  HD44780(uint8_t, uint8_t = 16, uint8_t = 2);
  int8_t init();
  template <typename T>
  void print(const T[], uint8_t);
  void command(uint8_t, uint8_t, bool);
  bool isBusy();
  uint8_t getCursorIndex();

  inline void clear(bool isEnd = true) {
    command(HD_WRITE_COMMAND, HD_CLEAR, isEnd);
  };

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

  inline bool isError() { return bool(this->errorStatus); }
  inline void setError(uint8_t err = 1) { this->errorStatus = err; };
  // inline void clearError() { this->errorStatus = 0; };
};

template <typename T>
void HD44780::print(const T cst[], uint8_t lenght) {
  for (uint8_t i = 0; i < lenght; i++) {
    WRITE_DATA(cst[i], false);
    isBusy();
  }
}

#endif // HD44780_H
