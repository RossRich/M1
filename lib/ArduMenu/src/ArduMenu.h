#if !defined(ARDU_MENU_H)
#define ARDU_MENU_H

#include <Arduino.h>
#include <WString.h>
#include <Vector.h>
#include "MenuDisplay.h"

#define SCROLL_TOP 1
#define SCROLL_BOTTOM 0
#define SWEEP_LEFT 2
#define SWEEP_RIGHT 3

#define MAX_ITEMS 7

class MenuManager;

class MenuComponent {
private:
  String _mName;

protected:
  MenuManager *_mMenuManager = nullptr;
  MenuComponent *_parent = nullptr;

public:
  MenuComponent(String name = "") : _mName(name) {}
  ~MenuComponent() {}

  inline const char *getName() const { return _mName.c_str(); }

  virtual void select() = 0;

  virtual void add(MenuComponent *item) = 0;

  virtual void print(MenuDisplay *display) = 0;

  virtual void scroll(int dir = SCROLL_BOTTOM) = 0;

  virtual void sweep(int dir = SWEEP_LEFT) = 0;

  inline void setParent(MenuComponent *item) { _parent = item; }

  inline void setManager(MenuManager *manager) { _mMenuManager = manager; }
};

class MenuManager {
private:
  MenuComponent *_mVisibleItem = nullptr;
  MenuDisplay *_mDispaly = nullptr;

public:
  MenuManager() { Serial.println(" ** MenuManager started"); }
  MenuManager(MenuComponent *startView, MenuDisplay *display) {
    setStarView(startView);
    _mDispaly = display;
    Serial.println(" ** MenuManager started");
  }
  ~MenuManager() {}

  inline void setStarView(MenuComponent *start) {
    start->setManager(this);
    _mVisibleItem = start;
  }

  inline void setVisible(MenuComponent *item) { _mVisibleItem = item; }

  inline void select() { _mVisibleItem->select(); }

  inline void print() { _mVisibleItem->print(_mDispaly); }

  inline void scroll(int dir) { _mVisibleItem->scroll(dir); }

  inline void sweep(int dir) { _mVisibleItem->sweep(dir); }
};

class Menu : public MenuComponent {
private:
  MenuComponent *vectorContainer[MAX_ITEMS];
  Vector<MenuComponent *> _mItems;
  int _mIndex = 0;
  int _mNumItems = 0;
  int _mCursor = 0;

public:
  Menu(String name) : MenuComponent(name) {}
  Menu(String name, MenuComponent *parent) : MenuComponent(name) {
    parent->add(this);
    _mItems.setStorage(vectorContainer);
  }
  ~Menu() {}

  void add(MenuComponent *item);

  void select();

  void print(MenuDisplay *display);

  void scroll(int dir);

  void sweep(int dir);

  void printPointer(MenuDisplay *display);
};

/*
class MenuItem : public MenuComponent {
private:
  MenuComponent *_mView = nullptr;

public:
  MenuItem(String name) : MenuComponent(name) {}
  MenuItem(String name, MenuComponent *parent) : MenuComponent(name) {
    parent->add(this);
  }
  ~MenuItem() {}

  void print(MenuDisplay *dispaly) { _mView->print(dispaly); }
  void scroll(int dir) {}
  void select() {
    if (_mView != nullptr)
      _mMenuManager->setVisible(_mView);
  }
  void add(MenuComponent *next) {
    _mView = next;
    next->setParent(_parent);
  }
  void sweep(int dir) {}
};
*/

class StartView : public MenuComponent {
private:
  MenuComponent *_mNext = nullptr;

public:
  StartView(String name = "Start") : MenuComponent(name) {}
  ~StartView() {}
  void print(MenuDisplay *dispaly);
  void scroll(int dir);
  void select();
  void add(MenuComponent *next);
  void sweep(int dir);
};

class EditView : public MenuComponent {
private:
  void add(MenuComponent *next) {}
  int val = 0;
  String label = "label: ";

public:
  EditView(String name) : MenuComponent(name) {}
  EditView(String name, MenuComponent *parent) : MenuComponent(name) {
    parent->add(this);
  }
  ~EditView() {}
  void print(MenuDisplay *dispaly);
  void scroll(int dir);
  void select();
  void sweep(int dir);
};
#endif // ARDU_MENU_H