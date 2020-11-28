#if !defined(M1_VIEW_H)
#define M1_VIEW_H

/**
 *
 * M1Vewe
 * This is simple drone menu consist of:
 * 1. LCD display HD7780
 * 2. Potentiometr
 * 3. Two simple joysticks
 * 4. Encoder
 * 5. Five analog buttons
 *
 *           +-----------+
 *           |    LCD    |
 *           +-----------+
 *        -                  +
 *       ||                 + +  <- buttons
 *pot-> <_|                  +
 *enc->          () +
 *        {J1}         {J2}
 **/

#define VIEW_BUTTONS_COUNT 5
#define VIEW_JOYSTICKS_COUNT 2

#include "M1Model.h"
#include "DronInterface.h"

class M1Controller;

class M1View : public Observer {
private:
  M1Controller *controller;
  M1Model *model;
  VJoystick *leftJoystick;
  VJoystick *rightJoystick;
  VButton *topButton;
  VButton *bottomButton;
  VButton *leftButton;
  VButton *rightButton;
  VButton *encoderButton; // button for select
  M1ViewFactory componentFactory;
  VRange *rangePow;
  MenuManager *viewManager;
  DronInterface *di;

public:
  M1View(M1Controller *c, M1Model *m);
  ~M1View();

  void checkButons();
  void checkJoysticks();
  void checkRange();
  void openScreen();
  void update();
  void print(const char *msg, int size);
  void print(int val, int size);
};

#include "M1Controller.h"

#endif // M1_VIEW_H