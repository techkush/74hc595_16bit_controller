int latchPin = 5;
int clockPin = 6;
int dataPin = 4;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}
void loop() {
  digitalWrite(latchPin, LOW);
  //2nd IC Binary 
  shiftOut(dataPin, clockPin, MSBFIRST, 67);
  //1st IC Binary
  shiftOut(dataPin, clockPin, MSBFIRST, 4);

  digitalWrite(latchPin, HIGH);
}
