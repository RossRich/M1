#if !defined(M1_VIEW_H)
#define M1_VIEW_H

// #include "DronInterface.h"
#include "ObsSubj/Observer.h"
#include "Display.h"
#include "MenuManager.h"
#include "StartView.h"
#include "Menu.h"
#include "EditView.h"
#include "TestView.h"

#define JOYS_COUNT 2
#define BUTS_COUNT 5
#define RANGES_COUNT 2

class M1Controller;

class M1View : public Observer {
private:
  M1Controller *_mController;
  // M1Model *model;
  // DronInterface *_mDi;
  Display *_mDisplay;
  // StartView *_mStartView;
  TestView *_tt;
  MenuManager *_mMenuManager;

  MenuComponent *joysticks[JOYS_COUNT] = {0};
  MenuComponent *buttons[BUTS_COUNT] = {0};
  MenuComponent *ranges[RANGES_COUNT] = {0};

  // Menu *_mMainMenu;
  // Menu *_mSubMenu;

  // EditView *_mOneEdit;
  // EditView *_mTwoEdit;
  // EditView *_mThreeEdit;
  // EditView *_mFourEdit;
  // EditView *_mFiveEdit;

public:
  M1View() {}
  explicit M1View(M1Controller *c);
  virtual ~M1View() {}

  /* MenuManager *init() {

    // _mStartView = new StartView("StartView");

    // _tt->setVal(val);
    // _mMenuManager = new MenuManager(_tt, _mDisplay);
    // _mMenuManager->print();

    _mMainMenu = new Menu("Mainmenu", _mStartView);
    _mSubMenu = new Menu("Sub menu", _mMainMenu);

    _mOneEdit = new EditView("Oneedit", _mMainMenu);
    _mTwoEdit = new EditView("Twoedit", _mMainMenu);
    _mThreeEdit = new EditView("Threeedi", _mMainMenu);
    _mFourEdit = new EditView("Fouredit", _mSubMenu);
    _mFiveEdit = new EditView("Fiveedit", _mSubMenu);
    return _mMenuManager;
  } */

  inline void print() { _mMenuManager->print(); }
  inline void listen() { _mDisplay->draw(); }

  void select() { _mMenuManager->select(); }
  void scroll(int dir) { _mMenuManager->scroll(dir); }
  void sweep(int dir) { _mMenuManager->sweep(dir); }

  void updateRange();
  void updateJoy();
  void updateBut();

  // Observer
  void update() override { _mMenuManager->update(); };
};

#include "M1Controller.h"

#endif // M1_VIEW_H