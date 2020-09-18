#if !defined(M1_H)
#define M1_H



#include <Arduino.h>

void clickOnEncoderButton();
void turnEncoder(int8_t);
void encoderRotationInterrupt();
void encoderRotation();
void encodeSpin();
void testDisplay();
void nrfInterrupt();

#endif // M1_H
