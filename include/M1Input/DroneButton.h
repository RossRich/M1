#if !defined(DRONE_BOTTON_H)
#define DRONE_BOTTON_H

#include <AnalogButton.h>
#include "InputSubject.h"

class DroneButton : public VButton, public InputSubject {
private:
  AnalogButtons *_mB = nullptr;
  InputObserver *_mIObs = nullptr;

public:
  DroneButton(uint8_t analogPin, uint16_t analogValue);
  ~DroneButton();

  bool isPressed() override;
  bool isClicked() override;
  void check() override;

  void subscribe(InputObserver *o) override;
  void unsubscrube(InputObserver *o) override;
  void notify(IEv e) override;
};

#endif // DRONE_BOTTON_H
