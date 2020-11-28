#include "ArduMenu.h"

  void EditView::print(MenuDisplay *dispaly) {
    Serial.println(getName());
    Serial.println(label);
    // cout << getName() << endl;
    // cout << label << val << endl;
  }
  void EditView::scroll(int dir) {}
  void EditView::select() { _mMenuManager->setVisible(_parent); }

  void EditView::sweep(int dir) {
    if (dir == SWEEP_LEFT)
      val -= 1;
    else
      val += 1;
  }