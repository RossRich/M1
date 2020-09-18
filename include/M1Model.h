#if !defined(M1_MEDEL_H)
#define M1_MEDEL_H

#define RF24_CE 9u   // MI - MISO(12)
#define RF24_CSN 10u // MO - MOSI(11)
#define TX_NRF "TNode"
#define RX_NRF "RNode"
#define OBSERVERS_COUNT 5u

#include <RF24.h>

class Observer {
private:
public:
  Observer() {}
  virtual ~Observer() {}

  virtual void update() = 0;
};

struct M1JoystickData {
  int x;
  int y;
  bool sw;
};

struct M1Data {
  M1JoystickData j1;
  M1JoystickData j2;
  bool bT;
  bool bB;
  bool bL;
  bool bR;
  bool bE;
  int range;
};

class M1Model {
private:
  RF24 *radio = nullptr;
  Observer **observers = nullptr;
  M1Data data;
  int observerCount = 0;

public:
  M1Model() {
    radio = new RF24(RF24_CE, RF24_CSN);
    observers = new Observer *[OBSERVERS_COUNT];
  }
  ~M1Model() {}

  void init() {
    radio->begin();
    radio->setPALevel(RF24_PA_MIN);
    // radio->openWritingPipe(reinterpret_cast<const uint8_t *>(TX_NRF));
    // radio->maskIRQ(1, 1, 1);
    // attachInterrupt(digitalPinToInterrupt(3), nrfInterrupt, LOW);
  }

  void setJoystick1(int x, int y, int sw) {
    data.j1.x = x;
    data.j1.y = y;
    data.j1.sw = sw;
    notifyObservers();
  }
  inline M1JoystickData *getJoystick1() { return &data.j1; }

  void setJoystick2(int x, int y, int sw) {
    data.j2.x = x;
    data.j2.y = y;
    data.j2.sw = sw;
    notifyObservers();
  }
  inline M1JoystickData *getJoystick2() { return &data.j2; }

  void setButTop(bool state) {
    data.bT = state;
    notifyObservers();
  }
  inline bool getButTop() { return data.bT; }

  void setButBottom(bool state) {
    data.bB = state;
    notifyObservers();
  }
  inline bool getButBottom() { return data.bB; }

  void setButLeft(bool state) {
    data.bL = state;
    notifyObservers();
  }
  inline bool getButLeft() { return data.bL; }

  void setButRight(bool state) {
    data.bR = state;
    notifyObservers();
  }
  inline bool getButRight() { return data.bR; }

  void setButEnc(bool state) {
    data.bE = state;
    notifyObservers();
  }
  inline bool getButEnc() { return data.bE; }

  void setRange(int range) {
    data.range = range;
    notifyObservers();
  }
  inline int getRange() { return data.range; }

  void registerObserver(Observer *observer) {
    if (observerCount == OBSERVERS_COUNT)
      return;

    observers[observerCount] = observer;
    ++observerCount;
  }

  inline void removeObserver(Observer *observer) { return; }

  void notifyObservers() {
    for (int i = 0; i < observerCount; i++) {
      observers[i]->update();
    }
  }
};

#endif // M1_MEDEL_H
