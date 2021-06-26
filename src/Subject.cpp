#include "ObsSubj/Subject.h"

Subject::Subject() {
  Serial.println("Subject");
  observers = new Observer *[OBSERVERS_MAX];

  for (size_t i = 0; i < OBSERVERS_MAX; i++)
    observers[i] = nullptr;
}

void Subject::addObserver(Observer *obs) {
  if (observersCount >= OBSERVERS_MAX || obs == nullptr)
    return;

  Serial.println("addObserver");

  observers[observersCount] = obs;
  ++observersCount;
}

void Subject::delObserver(Observer *obs) {}

void Subject::notifyObservers() {
  if (observersCount == 0)
    return;

  for (uint8_t i = 0; i < observersCount; i++) {
    if (observers[i] != nullptr)
      observers[i]->update();
  }
}