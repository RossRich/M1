/**
 * M1Controller
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

#if !defined(M1_CONTROLLER_H)
#define M1_CONTROLLER_H

#include "M1Model.h"
#include "M1View.h"
#include "M1Input/Input.h"

class M1Controller : public IInputActions {
private:
  M1Model *_mModel = nullptr;
  M1View *_mView = nullptr;
  Input *_mInput = nullptr;
  uint32_t _inputTimer = 0;
  uint32_t _viewTimer = 0;

public:
  M1Controller(M1Model *m1Model);
  ~M1Controller();

  /* void clickTopButton(bool state);

  void clickBottomBotton(bool state);

  void clickLeftBotton(bool state);

  void clickRightButton(bool state);

  void clickEncoderButton(bool state);

  void changeRange(int val);

  void changeRightJValue(int x, int y);

  void changeLeftJValue(int x, int y);



  void openMenu() {}

  void closeMenu() {}

  void actionItem() {} */

  // InputActions
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

  void listen();

  int* getRange();
  JoyData* getJoy();

  /** TODO
   *  Common error handler
   **/
  void checkError() {}
};

#endif // M1_CONTROLLER_H
