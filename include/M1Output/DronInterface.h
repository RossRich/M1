#if !defined(DRON_INTERFACE_H)
#define DRON_INTERFACE_H

#include "Display.h"
#include "MenuManager.h"
#include "StartView.h"
#include "Menu.h"
#include "EditView.h"
#include "TestView.h"

class DronInterface {
private:
  Display *_mDisplay;
  TestView *_tt;
  // StartView *_mStartView;
  MenuManager *_mMenuManager;

  // Menu *_mMainMenu;
  // Menu *_mSubMenu;

  // EditView *_mOneEdit;
  // EditView *_mTwoEdit;
  // EditView *_mThreeEdit;
  // EditView *_mFourEdit;
  // EditView *_mFiveEdit;

public:
  explicit DronInterface(Display *display) : _mDisplay(display) {}
  DronInterface() {
    _mDisplay = new Display();
    // _mMenuManager = _mDi->init();
    // _mMenuManager->print();
    init();
  }
  ~DronInterface() {}

  MenuManager *init() {

    // _mStartView = new StartView("StartView");
    _tt = new TestView("_TEst_");
    _tt->setLabel("Label1");
    // _tt->setVal(val);
    _mMenuManager = new MenuManager(_tt, _mDisplay);
    _mMenuManager->print();

    /* _mMainMenu = new Menu("Mainmenu", _mStartView);
    _mSubMenu = new Menu("Sub menu", _mMainMenu);

    _mOneEdit = new EditView("Oneedit", _mMainMenu);
    _mTwoEdit = new EditView("Twoedit", _mMainMenu);
    _mThreeEdit = new EditView("Threeedi", _mMainMenu);
    _mFourEdit = new EditView("Fouredit", _mSubMenu);
    _mFiveEdit = new EditView("Fiveedit", _mSubMenu); */
    return _mMenuManager;
  }

  inline void select() { _mMenuManager->select(); }

  inline void print() { _mMenuManager->print(); }

  inline void scroll(int dir) { _mMenuManager->scroll(dir); }

  inline void sweep(int dir) { _mMenuManager->sweep(dir); }

  inline void listen() { _mDisplay->draw(); }

  inline void update() { _mMenuManager->update(); }

  inline void setVal(int *val) { _tt->setVal(val); }
};

#endif // DRON_INTERFACE_H
