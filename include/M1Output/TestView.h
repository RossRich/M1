#if !defined(_TEST_VIEW_H)
#define _TEST_VIEW_H

#include <ArduMenu.h>
#include <MenuComponent.h>
#include <M1Input/Input.h>

class TestView : public MenuComponent {
  int16_t *_range = nullptr;
  JoyData *_leftJData = nullptr;
  JoyData *_rightJData = nullptr;
  const char *_rangeLabel = "Throttle: ";
  const char *_leftJoyLabel = "JLx: ";
  const char *_rightJoyLabel = "JRx: ";

public:
  explicit TestView(const char *name) : MenuComponent(name){};
  virtual ~TestView(){};

  void select() override {}

  void add(MenuComponent *item) override {}

  void print(MenuDisplay *display) override {
    display->print(_rangeLabel);
    display->print(_range);
    display->setCursor(0, 2);
    display->print(_leftJoyLabel);
    display->print(_leftJData->x);
    display->setCursor(9, 2);
    display->print(_rightJoyLabel);
    // display->print(_rightJData->x);
  }

  void scroll(int dir) override {}

  void sweep(int dir) override {}

  inline void setRange(int16_t *v) { _range = v; }
  inline void setLeftJoy(JoyData *jd) { _leftJData = jd; }
  inline void setRightJoy(JoyData *jd) { _rightJData = jd; }

  void update(MenuDisplay *display) {
    // display->setCursor(10, 1);
    // display->print(_range);
    // display->print(" ");
    display->setCursor(5, 2);
    display->print(_leftJData->x);
    display->print(" ");
  }
};

#endif // _TEST_VIEW_H
