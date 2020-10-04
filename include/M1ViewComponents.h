#if !defined(M1_VIEW_COMPONENTS_H)
#define M1_VIEW_COMPONENTS_H

#define MAX_DISPLAYS 5u
#define MAX_FRAMES 5u
#define DIR_LEFT 0u
#define DIR_RIGHT 1u

#include <inttypes.h>
#include <PCF8574T.h>
#include <HD44780.h>

class VButton {
private:
public:
  VButton() {}
  virtual ~VButton() {}
  virtual bool isPressed() = 0;
  virtual bool isClicked() = 0;
  virtual void check() = 0;
};

class VJoystick {
private:
public:
  VJoystick() {}
  virtual ~VJoystick() {}
  virtual void check() = 0;
  virtual int getX() = 0;
  virtual int getY() = 0;
};

class VRange {
private:
public:
  VRange() {}
  virtual ~VRange() {}
  void check() {}
  int getValue() { return 0; }
};

class Display {
private:
  PCF8574T *_mPCFDriver;
  HD44780 *_mLCDDriver;
  uint8_t _mWidth = 16;
  uint8_t _mHeight = 2;

public:
  Display() {
    _mPCFDriver = new PCF8574T;
    _mLCDDriver = new HD44780(_mPCFDriver);
  }
  ~Display() {}

  inline void print(const char *msg) { _mLCDDriver->print(msg); }
  inline void print(uint8_t *v) { _mLCDDriver->print(*v); }
  inline void print(uint32_t *v) { _mLCDDriver->print(*v); }
  inline void print(const __FlashStringHelper *ifsh) {
    Serial.println(_mLCDDriver->print(ifsh));
  }
  inline void setCursor(uint8_t x, uint8_t y) { _mLCDDriver->setCursor(x, y); }
  inline void clear() { _mLCDDriver->clear(); }
};

enum ScreensID { INFO_SCREEN = 0, MENU_SCREEN };

struct pointXY_t {
  uint8_t x;
  uint8_t y;
};

class VDisplayFrame {
private:
public:
  const char *test;
  uint8_t *testv;
  uint32_t *timeVal;
  pointXY_t pos;
  pointXY_t pos2;
  uint8_t one = 1;
  uint32_t time = millis();

  VDisplayFrame() { add("Hello2", {0, 0}, &time, {11, 0}); }
  ~VDisplayFrame() {}

  void add(const char *msg, pointXY_t pos, uint8_t *val, pointXY_t pos2) {
    test = msg;
    this->pos.x = pos.x;
    this->pos.y = pos.y;

    testv = val;
    this->pos2.x = pos2.x;
    this->pos2.y = pos2.y;
  }

  void add(const char *msg, pointXY_t pos, uint32_t *val, pointXY_t pos2) {
    test = msg;
    this->pos.x = pos.x;
    this->pos.y = pos.y;

    timeVal = val;
    this->pos2.x = pos2.x;
    this->pos2.y = pos2.y;
  }
};

class VDisplay {
private:
public:
  virtual ~VDisplay() {}
  virtual void print() = 0;
  virtual void start() = 0;
  virtual void reset() = 0;
  virtual void sweep(uint8_t dir = DIR_LEFT) = 0;
  virtual void scroll(uint8_t dir = DIR_LEFT) = 0;
  virtual void update() = 0;
};

class M1ViewDisplay : public VDisplay {
private:
  VDisplay *_mDisplays[MAX_DISPLAYS];
  uint8_t _mDisplayCurrent = 0;
  uint8_t _mDisplayNum = 0;
  Display *_mDisplay;

public:
  M1ViewDisplay(Display *driver) : _mDisplay(driver) {}
  ~M1ViewDisplay() {}

  void print() override { _mDisplays[_mDisplayCurrent]->start(); }

  void start() override { print(ScreensID::INFO_SCREEN); }

  void sweep(uint8_t dir) override {

    switch (dir) {
    case DIR_LEFT:
      if (_mDisplayCurrent < _mDisplayNum)
        ++_mDisplayCurrent;
      break;

    case DIR_RIGHT:
      if (_mDisplayCurrent != 0)
        --_mDisplayCurrent;
      break;

    default:
      break;
    }

    Serial.println(F("Next Display\n"));
  }

  void scroll(uint8_t dir) override {

    switch (dir) {
    case DIR_LEFT:
      break;

    case DIR_RIGHT:
      break;

    default:
      break;
    }

    Serial.println(F("Scroll Display\n"));
  }

  void reset() override {
    _mDisplayCurrent = 0;
    start();
  }

  void addDisplay(VDisplay *display) {
    if (_mDisplayNum < MAX_DISPLAYS) {
      _mDisplays[_mDisplayNum] = display;
      ++_mDisplayNum;
    }
  }

  void print(ScreensID id) {
    switch (id) {
    case ScreensID::INFO_SCREEN:
      _mDisplayCurrent = (uint8_t)ScreensID::INFO_SCREEN;
      break;
    case ScreensID::MENU_SCREEN:
      _mDisplayCurrent = ScreensID::MENU_SCREEN;
      break;
    default:
      _mDisplayCurrent = ScreensID::INFO_SCREEN;
      break;
    }
    print();
  }

  void update() override { _mDisplays[_mDisplayCurrent]->update(); }
};

class InfoScreen : public VDisplay {
private:
  Display *_mDisplay;

public:
  InfoScreen(Display *driver) : _mDisplay(driver) {}
  ~InfoScreen() {}

  void print() override {}

  void start() override {
    _mDisplay->clear();
    _mDisplay->setCursor(0, 1);
    _mDisplay->print("DRONE");
    _mDisplay->setCursor(5, 2);
    _mDisplay->print("iNTER");
    _mDisplay->print("FACE");
  }

  void update() override {
    VDisplayFrame f;
    _mDisplay->setCursor(f.pos2.x, f.pos2.y);
    _mDisplay->print(f.timeVal);
  }

private:
  void reset() override {}
  void sweep(uint8_t dir = DIR_LEFT) override {}
  void scroll(uint8_t dir = DIR_LEFT) override {}
};


class MenuDisplay
{
private:
  
public:
  MenuDisplay() {}
  ~MenuDisplay() {}
};
#endif // M1_VIEW_COMPONENTS_H
