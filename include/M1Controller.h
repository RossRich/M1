#if !defined(M1_CONTROLLER_H)
#define M1_CONTROLLER_H

#include "M1View.h"

class M1Controller {
private:
  M1View *_mView = nullptr;
  M1Model *_mModel = nullptr;
  bool _mArmedTimer = false;

  void init();

public:
  M1Controller(M1Model *m1Model);
  ~M1Controller();

  void clickTopButton(bool state);

  void clickBottomBotton(bool state);

  void clickLeftBotton(bool state);

  void clickRightButton(bool state);

  void clickEncoderButton(bool state);

  void changeRange(int val);

  void changeRightJValue(int x, int y);

  void changeLeftJValue(int x, int y);

  void listenChange();

  void openMenu() {}

  void closeMenu() {}

  void actionItem() {}

  /** TODO
   *  Common error handler
   **/
  void checkError() {}
};

#endif // M1_CONTROLLER_H
