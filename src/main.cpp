#include <Arduino.h>
#include <PCF8574T.h>
#include <HD44780.h>
#include <Encoder.h>
#include "M1.h"

HD44780 display(PCF_ADDRESS_FIXED + PCF_ADDRESS_HARDWARE);
Encoder e1(ENCODER_S1, ENCODER_S2, ENCODER_BUTTON);

void setup() {
  Serial.begin(57600);
  display.init();
  if (display.isError())
    errorBlink();
  pinMode(BUTTON1, INPUT_PULLUP);
  e1.setClickListener();
  attachInterrupt(0, e1.listen, RISING);
}

void loop() {
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

