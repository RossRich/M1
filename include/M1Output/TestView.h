#if !defined(_TEST_VIEW_H)
#define _TEST_VIEW_H

#include <ArduMenu.h>
#include <MenuComponent.h>

class TestView : public MenuComponent {
  int *_test;
  const char *_label;

public:
  TestView(const char *name) : MenuComponent(name){};
  ~TestView(){};

  void select() override {}

  void add(MenuComponent *item) override {}

  void print(MenuDisplay *display) override { 
    display->print(_label);
    display->print(F(": "));
    display->print(_test);
   }

  void scroll(int dir) override {}

  void sweep(int dir) override {}

  void setLabel(const char *l ) {
    _label = l;
  }

  void setVal(int *v) {
    _test = v;
  }

  void update(MenuDisplay *display) {
    // display->setCursor(8, 1);
    // display->print("   ");
    display->setCursor(8, 1);
    display->print((uint8_t)*_test);
  }
};

// TestView::TestView() : MenuComponent(_name) {}

// TestView::~TestView() {}

#endif // _TEST_VIEW_H
