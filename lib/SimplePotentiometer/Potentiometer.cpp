#include "Potentiometer.h"

Potentiometer::Potentiometer() {
  _potPin = 8;
  setADCrange(MIN_ADC, MAX_ADC);
  setRange(MIN_ADC, MAX_ADC);
}
Potentiometer::Potentiometer(uint8_t potPin, bool isFilterEnable)
    : Potentiometer() {
  _potPin = potPin;
  _isFilterEnable = isFilterEnable;
  if (isFilterEnable)
    filter = new GMedian3<int16_t>();
}

Potentiometer::Potentiometer(
    uint8_t potPin, int16_t minOut, int16_t maxOut, bool isFilterEnable)
    : Potentiometer(potPin, isFilterEnable) {
  setRange(minOut, maxOut);
}

void Potentiometer::listen() {
  if (millis() - _listenPeriod >= DEFAULT_LISTEN_PERIOD) {
    _signalOut =
        constrain(static_cast<uint16_t>(analogRead(_potPin)), _minADC, _maxADC);
    _signalOut = map(_signalOut, _minADC, _maxADC, _minOut, _maxOut);
    if (_isFilterEnable)
      _signalOut = filter->filtered(_signalOut);

    _listenPeriod = millis();
  }
}

void Potentiometer::setRange(int16_t minOut, int16_t maxOut) {
  _minOut = minOut;
  _maxOut = maxOut;
}

void Potentiometer::setRange(int16_t *minOut, int16_t *maxOut) {
  minOut = &_minOut;
  maxOut = &_maxOut;
}

void Potentiometer::setADCrange(uint16_t minADC, uint16_t maxADC) {
  _minADC = minADC;
  _maxADC = maxADC;
}

void Potentiometer::setADCrange(uint16_t *minADC, uint16_t *maxADC) {
  minADC = &_minADC;
  maxADC = &_maxADC;
}

void Potentiometer::setupADC() {
    Serial.flush();
    
    while (!Serial.available()) {
      Serial.println(analogRead(_potPin));
      delay(500);
    }

    int16_t vals[2] = {};
    char buf[36] = {};
    byte i = 0;

    Serial.readBytes(buf, 35);

    char *command = strtok(buf, ";");
    while (command != 0) {
      vals[i] = atoi(command);
      ++i;
      command = strtok(0, ";");
    }

    setADCrange(vals[0], vals[1]);
  }

