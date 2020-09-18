/* #include "TextMenu.h"

TextMenu::TextMenu() {

#if defined(TEXT_MENU_DEBUG)
  DEBUG("This is BaseClass");
#endif // TEXT_MENU_DEBUG
}

TextMenu::~TextMenu() {

#if defined(TEXT_MENU_DEBUG)
  DEBUG("Deleting base class");
#endif // TEXT_MENU_DEBUG
}

void TextMenu::add(TextMenu *i) { return; }
void TextMenu::remove(TextMenu *i) { return; }
vector *TextMenu::getChildren() { return nullptr; }
inline void TextMenu::activate() { m_isActive = true; }
inline void TextMenu::deactivate() { m_isActive = false; }
bool TextMenu::isActive() { return m_isActive; }

MenuItem::MenuItem(const char *title) : m_title(title) {}
MenuItem::~MenuItem() {}
void MenuItem::remove(TextMenu *textMenu) { TextMenu::remove(nullptr); }
vector *MenuItem::getChildren() { return TextMenu::getChildren(); }
void MenuItem::print() {
#if defined(TEXT_MENU_DEBUG)

  cout << m_title << std::endl;

#endif // TEXT_MENU_DEBUG
};
const char *MenuItem::getName() { return m_title; };
void MenuItem::add(TextMenu *textMenu) { TextMenu::add(nullptr); }

Menu::Menu(const char *title) : m_title(title) {}
Menu::~Menu() {}
const char *Menu::getName() { return m_title; }
vector *Menu::getChildren() { return &m_menuItems; }
void Menu::remove(TextMenu *textMenu) { TextMenu::remove(nullptr); }
void Menu::print() {

  if (m_itemsCount > 0) {
    vector::iterator itemsIt = m_menuItems.begin();
    while (itemsIt != m_menuItems.end()) {
      if ((*itemsIt)->isActive())

#if defined(TEXT_MENU_DEBUG)

        cout << "* ";

#endif // TEXT_MENU_DEBUG
      (*itemsIt)->print();
      ++itemsIt;
    }
  }
}
void Menu::add(TextMenu *textMenu) {
  m_menuItems.push_back(textMenu);
  ++m_itemsCount;
}

void Menu::scroll(bool upDown) {
  if (upDown) {
    if (index < m_itemsCount - 1)
      index++;
  } else {
    if (index != 0)
      index--;
  }

  vector::iterator itemsIt = m_menuItems.begin();
  while (itemsIt != m_menuItems.end()) {
    if ((*itemsIt)->isActive())
      (*itemsIt)->deactivate();
    ++itemsIt;
  }

  m_menuItems.at(index)->activate();
} */