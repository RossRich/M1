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
#include "M1Input/Input.h"
#include "M1Output/M1Menu.h"

class M1Controller;

class M1View : public Observer, IInputActions {
private:
  M1Controller *_mController;
  M1Model *model;
  Display *_mDisplayDriver;
  DronInterface *_mDi;
  MenuManager *viewManager;
  Input *_mI;
  JoyData _mLeftJoy;
  JoyData _mRightJoy;
  uint32_t timer;
  uint32_t timer1;

  void init();

public:
  M1View(M1Controller *c, M1Model *m);
  ~M1View();

  void update() {}
  void listen();

  void leftBut(INPUT_EVENTS e) override;
  void rightBut(INPUT_EVENTS e) override;
  void bottomBut(INPUT_EVENTS e) override;
  void topBut(INPUT_EVENTS e) override;
  void encBut(INPUT_EVENTS e) override;

  void joyLeft(INPUT_EVENTS e, int16_t x, int16_t y) override;
  void joyRight(INPUT_EVENTS e, int16_t x, int16_t y) override;

  void joyLeftButton(INPUT_EVENTS e) override;
  void joyRightButton(INPUT_EVENTS e) override;

  void range(INPUT_EVENTS e, int16_t val) override;

  void encoderRot(INPUT_EVENTS e, int8_t dir) override;
};

#include "M1Controller.h"

#endif // M1_VIEW_H