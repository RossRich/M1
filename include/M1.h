#if !defined(M1_H)
#define M1_H

#define BUTTON1 8
#define ENCODER_S1 2
#define ENCODER_S2 7
#define ENCODER_BUTTON 10

void errorBlink();
void clickOnEncoderButton();
void turnEncoder(int8_t);
void encoderRotation();

#endif // M1_H
