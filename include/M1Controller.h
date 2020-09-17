#if !defined(M1_CONTROLLER_H)
#define M1_CONTROLLER_H

#include "M1View.h"

class M1Controller {
private:
  M1View *m_m1View = nullptr;
  M1Model *m_m1Model = nullptr;

public:
  M1Controller(M1Model *m1Model);
  ~M1Controller();

  void clickTopButton(bool state);

  void clickDownBotton(bool state);

  void clickLeftBotton(bool state);

  void clickRightButton(bool state);

  void clickEncoderButton(bool state);

  void changePotValue();

  void changeRightJValue(int x, int y);

  void changeLeftJValue(int x, int y);

  void listenChange();
};

#endif // M1_CONTROLLER_H
