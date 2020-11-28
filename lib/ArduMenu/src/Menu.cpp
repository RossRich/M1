#include "ArduMenu.h"

void Menu::add(MenuComponent *item) {
  item->setParent(this);
  item->setManager(_mMenuManager);
  _mItems.push_back(item);
  _mNumItems = _mItems.size();
}

void Menu::select() {
  if (_mIndex >= 0 && _mIndex <= _mNumItems - 1)
    _mMenuManager->setVisible(_mItems.at(_mIndex));
  else if (_mIndex == -1 || _mIndex == _mNumItems)
    if (_parent != nullptr) // ??
      _mMenuManager->setVisible(_parent);
}

/** TODO
 * hide cursor
 **/
void Menu::print(MenuDisplay *display) {
  Serial.print(getName());
  Serial.print(" ");
  Serial.print(_mCursor);
  Serial.print(" ");
  Serial.println(_mIndex);

  // out mode[return to parent] of start list
  if (_mIndex < 0) {
    display->setCursor(0, 1);
    display->print(" ");
    return;
  }

  // out mode [return to parent] of end list
  if (_mIndex == _mNumItems) {
    if (_mNumItems > display->getHeight()) {
      display->setCursor(0, display->getHeight());
      display->print(" ");
    } else {
      display->setCursor(0, _mNumItems);
      display->print(" ");
    }
    return;
  }

  display->clear();

  uint8_t printIndex = _mIndex;

  if (_mNumItems > display->getHeight()) {
    if (display->getHeight() + printIndex > _mNumItems)
      printIndex = _mNumItems - display->getHeight();
  }

  for (int i = 0; i < display->getHeight(); ++i) {
    if (printIndex + i > _mNumItems - 1)
      break;

    display->setCursor(0, i + 1);
    display->print(" ");
    Serial.println(_mItems.at(printIndex + i)->getName());
    display->print(_mItems.at(printIndex + i)->getName());
  }
  printPointer(display);
}

void Menu::printPointer(MenuDisplay *display) {
  uint8_t printingItems = _mNumItems - _mIndex + 1;
  if (printingItems > 0 && printingItems > display->getHeight()) {
    display->setCursor(0, 1);
    display->print("*");
  } else {
    if (_mNumItems > display->getHeight()) {
      uint8_t ii = _mNumItems - display->getHeight(); // if _mNumItems > dispHe
      display->setCursor(0, _mIndex + 1 - ii);
    } else
    {
       display->setCursor(0, _mIndex + 1);
    }
    
    display->print("*");
  }
}

void Menu::scroll(int dir) {
  _mCursor = _mIndex;
  if (dir == SCROLL_BOTTOM && _mIndex < _mNumItems) {
    ++_mIndex;
  } else if (dir == SCROLL_TOP && _mIndex != -1) {
    --_mIndex;
  } else if (_mIndex < 0)
    _mIndex = _mNumItems - 1;
  else if (_mIndex == _mNumItems)
    _mIndex = 0;

  // cout << "Index = " << _mIndex << endl;
}

void Menu::sweep(int dir) {}
