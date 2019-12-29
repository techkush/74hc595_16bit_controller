//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 4;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(19200);
}

void loop() {
  for (int currentValue = 0; currentValue < 65536; currentValue++) {
    //Mask counter with 1111111100000000 to select high order byte and divide by 256 to scale to a 8 bit output
    int ByteHigh = (currentValue & 65280)/256;
    //Mask counter with 0000000011111111 to select low order byte
    int ByteLow = currentValue & 255;

    // Disable the latch while we clock in data
    digitalWrite(latchPin, LOW);
   
    // Send the value as a binary sequence to the module
    shiftOut(dataPin, clockPin, MSBFIRST, ByteHigh);
    shiftOut(dataPin, clockPin, MSBFIRST, ByteLow);
    Serial.println(ByteHigh); 
    Serial.println(ByteLow);

    // Enable the latch again to set the output states
    digitalWrite(latchPin, HIGH);

    delay(100);
  }
}
