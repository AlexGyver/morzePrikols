// скетч принимает данные по родному сериалу
// и отправляет через софт

#define BT_RX 12
#define BT_TX 11
#include <SoftwareSerial.h>
SoftwareSerial BTserial(BT_RX, BT_TX);
void setup() {
  Serial.begin(900);
  Serial.setTimeout(40);
  BTserial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    BTserial.println(Serial.readString());
  }  
}
