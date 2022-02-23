#if !defined(POTENTIOMETR_H_)
#define POTENTIOMETR_H_

#include <Arduino.h>
#include <GyverFilters.h>

#define MIN_ADC 0u
#define MAX_ADC 1023u
#define DEFAULT_LISTEN_PERIOD 20u

/**
 * A simple potentiometr class
 **/
class Potentiometer {
private:
  int16_t _minADC;
  int16_t _maxADC;
  uint8_t _potPin;
  int16_t _signalOut;
  int16_t _penSignalOut;
  bool _isFilterEnable;
  uint32_t _listenPeriod;
  int16_t _maxOut;
  int16_t _minOut;
  GMedian3<int16_t> *filter = nullptr;

public:
  /**
   * Main constructor for create object
   **/
  Potentiometer();

  /**
   * Extended constructor
   * @param potPin - analog pin
   * @param isFilterEnable - flag for enableing filter
   **/
  Potentiometer(uint8_t potPin, bool isFilterEnable = true);

  /**
   * @param potPin - analog pin
   * @param minOut - min value for converting from raw value
   * @param maxOut - max value for converting from raw value
   * @param isFilterEnable - flag for enableing filter
   *
   * @note max and min range is -32000 to 32000
   **/
  Potentiometer(
      uint8_t potPin, int16_t minOut, int16_t maxOut,
      bool isFilterEnable = true);

  /**
   * Listen changes on pin of board
   *
   * @note need calling in main loop
   **/
  void listen();

  /**
   * @return pot value
   **/
  inline int16_t value() { return _signalOut; }

  /**
   * @return pot value pointer
   **/
  inline int16_t* value_p() { return &_signalOut; }

  /**
   * Set minOut and maxOut value for converting to out range
   *
   * @param minOut - min value for converting from raw value
   * @param maxOut - max value for converting from raw value
   *
   * @note max and min range is -32000 to 32000
   **/
  void setRange(int16_t minOut, int16_t maxOut);
  void setRange(int16_t *minOut, int16_t *maxOut);

  /**
   * Set raw ADC value range
   * @param minADC - min value for ADC range
   * @param maxADC - max value for ADC range
   **/
  void setADCrange(int16_t minADC, int16_t maxADC);
  void setADCrange(int16_t *minADC, int16_t *maxADC);
  
  /**
   * Manual setup work ADC range
   **/
  void setupADC();


  inline int16_t difVal() {
    return _signalOut - _penSignalOut;
  }
};

#endif // POTENTIOMETR_H_