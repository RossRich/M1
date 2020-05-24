#if !defined(M1_H)
#define M1_H

#include <Arduino.h>

#define ENCODER_S1 2 // interrupt pin
#define ENCODER_S2 4

#define JOYSTICK1_X A1
#define JOYSTICK1_Y A0
#define JOYSTICK1_KEY 8

#define JOYSTICK2_X A3
#define JOYSTICK2_Y A2
#define JOYSTICK2_KEY 7

#define RF24_CE 9
#define RF24_CSN 10
#define RF24_TX_ID ((const uint8_t *)"NODET")
#define RF24_RX_ID ((const uint8_t *)"NODER")

void errorBlink();
void clickOnEncoderButton();
void turnEncoder(int8_t);
void encoderRotationInterrupt();
void encoderRotation();
void encodeSpin();
void testDisplay();

#endif // M1_H
