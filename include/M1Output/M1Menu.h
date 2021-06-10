#if !defined(DRON_INTERFACE_H)
#define DRON_INTERFACE_H

#include <ArduMenu.h>
#include "Display.h"

class DronInterface {
private:
  Display *_mDisplay;

  StartView *_mStartView;
  MenuManager *_mMenuManager;

  Menu *_mMainMenu;
  Menu *_mSubMenu;

  EditView *_mOneEdit;
  EditView *_mTwoEdit;
  EditView *_mThreeEdit;
  EditView *_mFourEdit;

public:
  DronInterface(Display *display) : _mDisplay(display) {}
  ~DronInterface() {}

  MenuManager *init() {
    _mStartView = new StartView;
    _mMenuManager = new MenuManager(_mStartView, _mDisplay);

    _mMainMenu = new Menu("Mainmenu", _mStartView);
    _mSubMenu = new Menu("Sub menu", _mMainMenu);

    _mOneEdit = new EditView("Oneedit", _mMainMenu);
    _mTwoEdit = new EditView("Twoedit", _mMainMenu);
    _mThreeEdit = new EditView("Threeedi", _mSubMenu);
    _mFourEdit = new EditView("Fouredit", _mMainMenu);

    return _mMenuManager;
  }
};

#endif // DRON_INTERFACE_H
