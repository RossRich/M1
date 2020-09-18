#include "TextMenu.h"

int main(int argc, char const *argv[]) {
  MenuItem item("Item1");
  // item.print();

  MenuItem item2("Item2");
  // item2.print();

  MenuItem item3("Item3");

  Menu sItem2("SubItem2");
  MenuItem si21("item");
  MenuItem si22("item2");
  sItem2.add(&si21);
  sItem2.add(&si22);

  Menu dMenu("DroneMenu");
  dMenu.add(&item);
  dMenu.add(&item2);
  dMenu.add(&item3);
  dMenu.add(&sItem2);

  dMenu.print();

  char ch;
  while (!(std::cin >> ch).fail() && ch != 'q') {
    if (ch == '\n') {
      std::cin.get();
      continue;
    }

    if (ch == '1')
      dMenu.scroll(1);
    else if (ch == '2')
      dMenu.scroll(0);

    dMenu.print();
  }
  return 0;
}
