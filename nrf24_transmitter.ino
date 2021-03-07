#include <SPI.h>
#include "RF24.h"

RF24 radio(A3, A5);

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    while(true) {
      Serial.println("init failed");
      delay(1000);
    }
  }
  Serial.println("init ready");
  radio.setChannel(90); // Дефолтный 76-й у меня забит.
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(0x7676767676);
  radio.stopListening(); // Неочевидная магия
}

uint32_t iteration = 0;

void loop() {
  Serial.print("result: ");
  Serial.println(radio.write(&iteration, 4));
  delay(100);
}
