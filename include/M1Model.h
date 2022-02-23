#if !defined(M1_MEDEL_H)
#define M1_MEDEL_H

#define RF24_CE 9u   // MI - MISO(12)
#define RF24_CSN 10u // MO - MOSI(11)
#define TX_NRF "TNode"
#define RX_NRF "RNode"

#include <Arduino.h>
#include "ObsSubj/Subject.h"
#include "JoyTypes.h"

// #include <RF24.h>

class M1Model : public Subject {
private:
  JoyData *_joyLeft_p = nullptr;
  JoyData *_joyRight_p = nullptr;
  int16_t *_rangeValue_p = nullptr;
  bool *_topBut_p = nullptr;
  bool *_bottomBut_p = nullptr;
  bool *_leftBut_p = nullptr;
  bool *_rightBut_p = nullptr;
  bool *_encBut_p = nullptr;
  // RF24 *radio = nullptr;

public:
  M1Model() {
    // radio = new RF24(RF24_CE, RF24_CSN);
    init();
  }
  virtual ~M1Model() {}

  void init() {
    Serial.println(F("Model init"));
    // radio->begin();
    // radio->setPALevel(RF24_PA_MIN);
    // radio->openWritingPipe(reinterpret_cast<const uint8_t *>(TX_NRF));
    // radio->maskIRQ(1, 1, 1);
    // attachInterrupt(digitalPinToInterrupt(3), nrfInterrupt, LOW);
  }

  // Joystick left
  inline void setJoyLeft_p(JoyData *jd) { _joyLeft_p = jd; }
  inline JoyData *getJoyLeft_p() { return _joyLeft_p; }

  // Joystick right
  inline void setJoyRight_p(JoyData *jd) { _joyRight_p = jd; }
  inline JoyData *getJoyRight_p() { return _joyRight_p; }

  // Top but
  inline void setButTop_p(bool *but) { _topBut_p = but; }
  inline bool *getButTop_p() { return _topBut_p; }

  // Bottom button
  inline void setButBottom_p(bool *but) { _bottomBut_p = but; }
  inline bool *getButBottom_p() { return _bottomBut_p; }

  // Left button
  inline void setButLeft_p(bool *but) { _leftBut_p = but; }
  inline bool *getButLeft_p() { return _leftBut_p; }

  // Right button
  inline void setButRight_p(bool *but) { _rightBut_p = but; }
  inline bool *getButRight_p() { return _rightBut_p; }

  // Encoder button
  inline void setButEnc_p(bool *but) { _encBut_p = but; }
  inline bool *getButEnc_p() { return _encBut_p; }

  // Range
  inline void setRange_p(int16_t *rangePointer) { _rangeValue_p = rangePointer; }
  inline int16_t *getRange_p() { return _rangeValue_p; }

  // Subject
  void addObserver(Observer *obs) override { Subject::addObserver(obs); };
  void delObserver(Observer *obs) override { Subject::delObserver(obs); };
  void notifyObservers() override { Subject::notifyObservers(); };
};

#endif // M1_MEDEL_H
