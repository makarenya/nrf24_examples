#include <SPI.h>
#include "RF24.h"

// 13-я нога используется для SPI, BUILTIN_LED не работает
#define LED 2

RF24 radio(8, 9); // Куда хочу, туда и подключаю
uint32_t timestamp = 0;

void setup() {
  if (!radio.begin()) {
    while(true) {
      // Сигнализируем о проблемме.
      pinMode(LED, OUTPUT);
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
    }
  }
  // Забит у меня дефолтный 76 канал
  radio.setChannel(90);
  // Либо LOW - либо отдельное питание/большой кондёр на входе.
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, 0x7676767676);
  radio.startListening();
  
  timestamp = millis();
}

void loop() {
  uint32_t now = millis();
  uint32_t payload;
  if (radio.available()) {
    radio.read(&payload, 4);
    timestamp = now;
    // Посылка пришла - всё ок
    digitalWrite(LED, HIGH);
  }
  if (now - timestamp > 120) {
    // Слишком долго нет посылки - ошибка
    digitalWrite(LED, LOW);
    delay(100);
  }
}
