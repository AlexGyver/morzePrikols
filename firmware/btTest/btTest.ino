// скетч отправляет битмап через блютус
// для проверки приложения

#define BT_RX 12
#define BT_TX 11

#include "bitmap1.h";
#include <SoftwareSerial.h>
SoftwareSerial BTserial(BT_RX, BT_TX);

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  for (uint16_t framenum = 0; framenum < 3; framenum++) {
    for (byte y = 0; y < 16; y++) {
      for (byte x = 0; x < 16; x++) {
        String outPacket = "";
        outPacket += x;
        outPacket += ' ';
        outPacket += y;
        outPacket += ' ';
        long color;
        switch (framenum) {
          case 0: color = expandColor(pgm_read_word(&(frame1[y * 16 + x])));
            break;
          case 1: color = expandColor(pgm_read_word(&(frame2[y * 16 + x])));
            break;
          case 2: color = expandColor(pgm_read_word(&(frame3[y * 16 + x])));
            break;
        }
        outPacket += (color >> 16) & 0xff;
        outPacket += ' ';
        outPacket += (color >> 8) & 0xff;
        outPacket += ' ';
        outPacket += color & 0xff;

        BTserial.println(outPacket);
        //Serial.println(outPacket);
        delay(20);
      }
    }
  }
}

// gamma correction для expandColor
static const uint8_t PROGMEM
gamma5[] = {
  0x00, 0x01, 0x02, 0x03, 0x05, 0x07, 0x09, 0x0b,
  0x0e, 0x11, 0x14, 0x18, 0x1d, 0x22, 0x28, 0x2e,
  0x36, 0x3d, 0x46, 0x4f, 0x59, 0x64, 0x6f, 0x7c,
  0x89, 0x97, 0xa6, 0xb6, 0xc7, 0xd9, 0xeb, 0xff
},
gamma6[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08,
  0x09, 0x0a, 0x0b, 0x0d, 0x0e, 0x10, 0x12, 0x13,
  0x15, 0x17, 0x19, 0x1b, 0x1d, 0x20, 0x22, 0x25,
  0x27, 0x2a, 0x2d, 0x30, 0x33, 0x37, 0x3a, 0x3e,
  0x41, 0x45, 0x49, 0x4d, 0x52, 0x56, 0x5b, 0x5f,
  0x64, 0x69, 0x6e, 0x74, 0x79, 0x7f, 0x85, 0x8b,
  0x91, 0x97, 0x9d, 0xa4, 0xab, 0xb2, 0xb9, 0xc0,
  0xc7, 0xcf, 0xd6, 0xde, 0xe6, 0xee, 0xf7, 0xff
};

// преобразовать цвет из 16 битного в 24 битный
static uint32_t expandColor(uint16_t color) {
  return ((uint32_t)pgm_read_byte(&gamma5[ color >> 11       ]) << 16) |
         ((uint32_t)pgm_read_byte(&gamma6[(color >> 5) & 0x3F]) <<  8) |
         pgm_read_byte(&gamma5[ color       & 0x1F]);
}
