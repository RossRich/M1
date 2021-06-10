#include <PCF8574T.h>
#include <HD44780.h>
#include <ArduMenu.h>

class Display : public MenuDisplay {
private:
  PCF8574T *_i2cDriver;
  HD44780 *_mDriver;

public:
  Display() {
    _i2cDriver = new PCF8574T;
    _mDriver = new HD44780(_i2cDriver, 16, 2);
  }
  ~Display() {}

  void print(const char *chVal) override { _mDriver->print(chVal); }
  void print(uint8_t val) override { _mDriver->print(val); }

  void print(char ch) { _mDriver->print(ch); }

  void print(int16_t intVal) { _mDriver->print(intVal); }

  void setCursor(uint8_t x, uint8_t y) { _mDriver->setCursor(x, y); }

  void setCursor(Point2 &position) {
    _mDriver->setCursor(position.x, position.y);
  }

  void setCursor(Point2 *position) {
    _mDriver->setCursor(position->x, position->y);
  }

  void clear() { _mDriver->clear(); }

  uint8_t getWidth() const { return _mDriver->getWidth(); }

  uint8_t getHeight() const { return _mDriver->getHeight(); }

  void draw() {
    if (_mDriver->queueSize() != 0 && !_mDriver->isBusy())
      _mDriver->checkQueue();
  }
};