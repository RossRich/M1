#include "ArduMenu.h"

void StartView::print(MenuDisplay *dispaly) {
  Serial.println(getName());
  dispaly->clear();
  dispaly->setCursor(0, 0);
  dispaly->print(getName());
  // cout << getName() << endl;
  // cout << getName() << endl;
}

void StartView::scroll(int dir) {}
void StartView::select() {
  if (_mNext != nullptr)
    _mMenuManager->setVisible(_mNext);
}
void StartView::add(MenuComponent *next) {
  next->setParent(this);
  next->setManager(_mMenuManager);
  _mNext = next;
}
void StartView::sweep(int dir) {}