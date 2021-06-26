#include <HD44780.h>
#include <ArduMenu.h>

class Display : public MenuDisplay {
private:
  PCF8574T *_i2cDriver;
  HD44780 *_mDriver;
  uint8_t _dispWidth = 16;
  uint8_t _dispHeight = 2;

public:
  Display() {
    _i2cDriver = new PCF8574T;
    _mDriver = new HD44780(_i2cDriver, _dispWidth, _dispHeight);
  }
  ~Display() {}

  void print(const char *chVal) override { _mDriver->print(chVal); }
  void print(uint8_t val) override { _mDriver->print(val); }
  void print(uint8_t *val) override { _mDriver->print(*val); }
  void print(const __FlashStringHelper *st) override { _mDriver->print(st); }

  void print(char ch) { _mDriver->print(ch); }

  void print(int16_t intVal) { _mDriver->print(intVal); }
  void print(int *intVal) { _mDriver->print(*intVal); }

  void setCursor(uint8_t x, uint8_t y) override { _mDriver->setCursor(x, y); }

  void setCursor(Point2 &position) override {
    _mDriver->setCursor(position.x, position.y);
  }

  void setCursor(Point2 *position) override {
    _mDriver->setCursor(position->x, position->y);
  }

  void clear() override { _mDriver->clear(); }

  uint8_t getWidth() const override { return _dispWidth; }

  uint8_t getHeight() const override { return _dispHeight; }

  void draw() {
    if (_mDriver->isError()) {
      Serial.print(F("Display error: "));
      Serial.println(_mDriver->isError());
      _mDriver->qClean();
      _mDriver->clearError();
    } else {
      if (_mDriver->queueSize() != 0 && !_mDriver->isBusy())
        _mDriver->checkQueue();
    }
  }
};