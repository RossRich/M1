#if !defined(M1_H)
#define M1_H

#include <Arduino.h>

#define BUTTON1 8
#define ENCODER_S1 2
#define ENCODER_S2 7
#define ENCODER_BUTTON 10

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_KEY 11

void errorBlink();
void clickOnEncoderButton();
void turnEncoder(int8_t);
void encoderRotation();

#endif // M1_H
