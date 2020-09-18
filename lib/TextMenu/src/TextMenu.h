/* #if !defined(TEST_MANU_H)
#define TEST_MANU_H

// #define TEXT_MENU_DEBUG

#if defined(TEXT_MENU_DEBUG)

#include <vector>
#include <iostream>
using std::cout;

inline DEBUG(const char *text) { cout << text << std::endl; }

#pragma message "DEBUG MODE\n"

#else

#include <Arduino.h>
#include <HD44780.h>
#include <Vector.h>

const char START_SCREEN[] PROGMEM = " DRONEiNTERFACE ";

#endif // DEBUG

class TextMenu;

#if defined(TEXT_MENU_DEBUG)
using vector = std::vector<TextMenu *>;
#else
using vector = Vector<TextMenu *>;
#endif // TEXT_MENU_DEBUG

class TextMenu {
private:
  bool m_isActive = false;
public:                                   
  TextMenu();
  virtual ~TextMenu();
  virtual void print() = 0;
  virtual const char *getName() = 0;
  virtual inline void activate();
  virtual inline void deactivate();
  inline bool isActive();

protected:
  virtual vector *getChildren() = 0;
  virtual void remove(TextMenu *textMenu) = 0;
  virtual void add(TextMenu *textMenu) = 0;
};

class MenuItem : public TextMenu {
private:
  const char *m_title;

public:
  MenuItem(const char *title);
  ~MenuItem();

  void remove(TextMenu *textMenu);
  virtual vector *getChildren() override;
  void print();
  const char *getName();
  void add(TextMenu *textMenu);
};

class Menu : public TextMenu {
private:
  vector m_menuItems;
  int m_itemsCount = 0;
  const char *m_title;
  int index = 0;

public:
  Menu(const char *title);
  ~Menu();
  const char *getName();
  virtual vector *getChildren() override;
  void remove(TextMenu *textMenu);
  void print();
  void add(TextMenu *textMenu);
  void scroll(bool upDown); 
};

#endif // TEST_MANU_H */