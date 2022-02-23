#if !defined(DRON_INTERFACE_H)
#define DRON_INTERFACE_H

#include "M1View.h"


class DronInterface : public M1View {
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
  explicit DronInterface(M1Controller *controller, Display *display)
      : M1View(controller), _mDisplay(display) {}

  DronInterface(M1Controller *controller) : M1View(controller) {
   
    // _mMenuManager = _mDi->init();
    // _mMenuManager->print();
    init();
  }
  ~DronInterface() {}

  MenuManager *init() {

    // _mStartView = new StartView("StartView");

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

  inline void print() { _mMenuManager->print(); }
  inline void listen() { _mDisplay->draw(); }
  inline void update() { _mMenuManager->update(); }

  void select() { _mMenuManager->select(); }
  void scroll(int dir) { _mMenuManager->scroll(dir); }
  void sweep(int dir) { _mMenuManager->sweep(dir); }

  // setup testview
  void setupTestView() {
    _tt = new TestView("_TEst_");
    _tt->setLabel("Label1");
    _tt->setVal();
  }
};

#endif // DRON_INTERFACE_H
