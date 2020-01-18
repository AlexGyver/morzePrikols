// Раскодировщик Морзянки с кнопки
// алфавит с Вики https://ru.wikipedia.org/wiki/%D0%90%D0%B7%D0%B1%D1%83%D0%BA%D0%B0_%D0%9C%D0%BE%D1%80%D0%B7%D0%B5
// AlexGyver, 2020

#define BTN 3         // пин кнопки
#define MIN_DASH 200  // мин. время тире (и макс. точки)
#define TIMEOUT 900   // таймаут

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // адрес дисплея м.б. 0x3f или 0x27
#define DEBUG(x) Serial.print(x)
#define RETURN() Serial.println()

bool btnFlag, receiveFlag;
uint32_t myTimer, timeoutTimer, debounceTimer = 0;
String decodeStr = "";

// я знаю, что можно и в PROGMEM
const char *codeTable[] = {
  "01",
  "1000",
  "011",
  "110",
  "100",
  "0",
  "0001",
  "1100",
  "00",
  "0111",
  "101",
  "0100",
  "11",
  "10",
  "111",
  "0110",
  "010",
  "000",
  "1",
  "001",
  "0010",
  "0000",
  "1010",
  "1101",
  "1011",
  "1001",

  "01111",
  "00111",
  "00011",
  "00001",
  "00000",
  "10000",
  "11000",
  "11100",
  "11110",
  "11111",

  "010101",
  "101010",
  "10010",
  "100001",
  "10001",
};

const char decodeTable[] = "ABWGDEVZIJKLMNOPRSTUFHCQYX1234567890.,;- ";

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  bool btnState = !digitalRead(BTN);
  if (btnState && !btnFlag && millis() - debounceTimer > 30) {
    debounceTimer = millis();
    btnFlag = true;
    myTimer = millis();
  }
  if (!btnState && btnFlag && millis() - debounceTimer > 30) {
    debounceTimer = millis();
    btnFlag = false;
    int signal = millis() - myTimer;
    if (signal < MIN_DASH) {
      DEBUG(".");
      decodeStr += "0";
    } else {
      DEBUG("-");
      decodeStr += "1";
    }
    timeoutTimer = millis();
    receiveFlag = true;
  }
  if (receiveFlag && millis() - timeoutTimer > TIMEOUT) {
    RETURN();
    DEBUG("receive: ");
    char receive = NULL;
    for (byte i = 0; i < strlen(decodeTable); i++) {
      if (decodeStr == codeTable[i]) {
        receive = decodeTable[i];
        break;
      }
    }
    DEBUG(decodeStr);
    DEBUG(" as ");
    DEBUG(receive);
    RETURN();
    RETURN();
    decodeStr = "";
    receiveFlag = false;
    if (receive != NULL) lcd.print(receive);
  }
}
