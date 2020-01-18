// передаём hello через UART

void setup() {
  Serial.begin(1200);
}

void loop() {
  static int count = 0;
  Serial.print("hello #");
  Serial.print(++count);
  delay(800);
}
