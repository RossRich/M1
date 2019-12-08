#include <Arduino.h>
#include <PCF8574T.h>
#include <HD44780.h>
#include <Encoder.h>
#include "M1.h"

HD44780 display(PCF_ADDRESS_FIXED + PCF_ADDRESS_HARDWARE);
Encoder e1(ENCODER_S1, ENCODER_S2, ENCODER_BUTTON);

void encoderRotation() { e1.listenRotation(); }
void clickOnEncoderButton() {
  if (e1.isButtonClick()) {
    Serial.println("Clicked En but.");
  }
}
void encodeSpin() {
  if (e1.isSpinPressure()) {
    int8_t dd = e1.getDiraction();
    if (dd == ENCODER_CCW_ROTATION)
      Serial.println("Click and rotation <-");
    else if (dd == ENCODER_CW_ROTATION)
      Serial.println("Click and rotation ->");
  }
}
void encoderRotationn() {
  int8_t d = e1.getDiraction();
  if (d == ENCODER_CCW_ROTATION)
    Serial.println("<-");
  else if (d == ENCODER_CW_ROTATION)
    Serial.println("->");
}

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  Serial.begin(57600);
  display.init();
  if (display.isError())
    errorBlink();
  e1.setInterruptRotationListener(encoderRotation);
  e1.addToListener(clickOnEncoderButton);
  e1.addToListener(encodeSpin);
  e1.addToListener(encoderRotationn);
  // e1.setLongClickListener(longClickOnEncoder);
}

void loop() {

  while (1) {
    e1.listen();

    /* if (e1.isButtonClick())
      Serial.println("Click button");

    if (e1.isButtonKeep())
      Serial.println("Keep encoder button");

    if (e1.isButtonDown())
      Serial.println("Down but");

    if (e1.isButtonUp())
      Serial.println("Up but"); */

    // if(e1.spinPressure_) {
    //   int8_t d = e1.getDiraction();
    //   if (d == ENCODER_CCW_ROTATION)
    //     Serial.println("<- and press");
    //   else if (d == ENCODER_CW_ROTATION)
    //     Serial.println("press and ->");
    // }

    // if(e1.isButtonLongPress())
    //   Serial.println("Long press");
  }

  char ch = ' ';
  const char *cst = "Hello World!";
  uint32_t t = millis();
  display.print(cst, 12);
  // Serial.println(millis() - t);
  Serial.print("CursorIndex: ");
  Serial.println(display.getCursorIndex());

  // t = millis();
  display.printBeginPosition(0x40, cst, 12);
  Serial.println(millis() - t);
  Serial.print("CursorIndex: ");
  Serial.println(display.getCursorIndex());

  if (display.isError())
    errorBlink();

  do {

    while (Serial.available()) {
      Serial.readBytes(&ch, 1);
      if (ch == '\n' || ch == '\r')
        continue;
      Serial.print("Char for write: ");
      Serial.println(ch);
      if (ch == '!') {
        display.clear();
        break;
      }
      if (ch == '~') {
        display.clear(false);
        display.isBusy();
        display.home();
        break;
      }

      if (ch == 0x8) {
        display.backspace();
        break;
      }

      display.command(HD_WRITE_DATA, ch, true);
      display.isBusy();

      Serial.println(display.getCursorIndex());
    }
    if (display.isError())
      errorBlink();

  } while (ch != '!');
  Serial.println("Exit");
  while (1)
    ;
}

void errorBlink() {
  pinMode(LED_BUILTIN, OUTPUT);
  uint8_t ledStatus = LOW;
  while (1) {
    for (uint8_t i = 0; i < 10; i++) {
      if (ledStatus == LOW)
        ledStatus = HIGH;
      else
        ledStatus = LOW;
      digitalWrite(LED_BUILTIN, ledStatus);
      delay(100);
    }
    delay(1500);
  }
}
