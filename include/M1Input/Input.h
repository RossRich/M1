#if !defined(M1_INPUT_H)
#define M1_INPUT_H

#define JOYSTICK_LEFT_X A1
#define JOYSTICK_LEFT_Y A0
#define JOYSTICK_LEFT_KEY 8

#define JOYSTICK_RIGHT_X A3
#define JOYSTICK_RIGHT_Y A2
#define JOYSTICK_RIGHT_KEY 7

#define ANALOG_BUTTON_PIN A6
#define ANALOG_BUTTON_TOP 683u
#define ANALOG_BUTTON_DOWN 291u
#define ANALOG_BUTTON_LEFT 879u
#define ANALOG_BUTTON_RIGHT 517u
#define ANALOG_BUTTON_ENC 1020u

#define RANGE_POWER A7
#define RANGE_MIN_POS 0
#define RANGE_MAX_POS 255

#include "DroneButton.h"
#include "DroneEncoder.h"
#include "DroneJoystick.h"
#include "DroneRange.h"
#include "IInputActions.h"

class Input : public InputObserver {
private:
  IInputActions *_mAction;

  DroneButton *_mTopBut;
  DroneButton *_mBottomBut;
  DroneButton *_mLeftBut;
  DroneButton *_mRightBut;

  DroneButton *_mEncBut;

  DroneJoystick *_mLeftJoy;
  DroneJoystick *_mRightJoy;

  DroneRange *_mRange;

  DroneEncoder *_mEnc;

  void checkBut();
  void checkJoy();
  void checkRange();
  void checkEnc();

public:
  Input();
  ~Input();

  void check();
  void subscribe(InputObserver *o);
  void addListener(IInputActions *a) { _mAction = a; }

  inline int16_t *getRangeValue_p() { return _mRange->getValue_p(); }
  inline JoyData *getJoyLeftData_p() { return _mLeftJoy->getData_p(); }
  inline JoyData *getJoyRightData_p() { return _mRightJoy->getData_p(); }

  // InputObserver
  void update(VButton *b, IEv e) override;
  void update(VJoystick *j, IEv e) override;
  void update(VRange *r, IEv e) override;
  void update(VEncoder *en, INPUT_EVENTS ev) override;
};

#endif // M1_INPUT_H
