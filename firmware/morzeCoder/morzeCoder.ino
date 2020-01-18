// Кодировщик Морзянки
// алфавит с Вики https://ru.wikipedia.org/wiki/%D0%90%D0%B7%D0%B1%D1%83%D0%BA%D0%B0_%D0%9C%D0%BE%D1%80%D0%B7%D0%B5
// AlexGyver, 2020

#define OUT 2         // пин цифрового выхода
#define BUZ 4         // выход для динамика
#define PAUSE 20      // пауза между данными
#define FREQ 800      // частота писка
#define MIN_DOT 30    // время точки
#define MIN_DASH 50   // время тире
#define TIMEOUT 75    // таймаут

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
  "110011",
  "001100",
};

const char decodeTable[] = "ABWGDEVZIJKLMNOPRSTUFHCQYX1234567890.,;- !?";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(OUT, OUTPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String parsePacket = Serial.readString();
    Serial.println(parsePacket);
    Serial.println(parsePacket.length());
    for (byte i = 0; i < parsePacket.length(); i++) {
      for (byte j = 0; j < strlen(decodeTable); j++) {
        if (parsePacket[i] == decodeTable[j]) {
          Serial.println(codeTable[j]);
          for (byte k = 0; k < strlen(codeTable[j]); k++) {            
            if (codeTable[j][k] == '0') {
              digitalWrite(OUT, 1);
              digitalWrite(13, 1);
              tone(BUZ, FREQ);
              delay(MIN_DOT);
              digitalWrite(OUT, 0);
              digitalWrite(13, 0);
              noTone(BUZ);
            } else {
              digitalWrite(OUT, 1);
              digitalWrite(13, 1);
              tone(BUZ, FREQ);
              delay(MIN_DASH);
              digitalWrite(OUT, 0);
              digitalWrite(13, 0);
              noTone(BUZ);
            }           
            delay(PAUSE); 
          }
          delay(TIMEOUT);
          break;
        }
      }
    }
  }
}
