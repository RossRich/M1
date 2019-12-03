#if !defined(M1_H)
#define M1_H

#define BUTTON1 10
#define ENCODER_S1 2
#define ENCODER_S2 7
#define ENCODER_BUTTON 9

void errorBlink();
void serialPrint(const char*);
void encoderInterrupt();

#endif // M1_H
