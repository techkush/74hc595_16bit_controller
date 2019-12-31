//16Bit Firebase Controlled Application

// Add Libarary and set internet connection
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "hasystem-b6df4.firebaseio.com"   
#define FIREBASE_AUTH "rmKKMaGyuC5Xx7qPjylKaX751ke3YNONSsWzKy2y"   
#define WIFI_SSID "SLT-ADSL-296A1"                                         
#define WIFI_PASSWORD "adsl1234"  

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

//16bit shift ic configurations
int latchPin = D3;
int clockPin = D1;
int dataPin = D2;

void setup() {
  Serial.begin(115200);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(D0, OUTPUT);

  //Connect with WIfi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //Connection Ok!
  digitalWrite(D0, HIGH);

  //Connect Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  //Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
void loop() {
  int sec_one = 0;
  int sec_two = 0;
  for (int i = 1; i < 9; i++){
    Firebase.getInt(firebaseData, "16bit-application/16bit00001/section-one/ch" + String(i));
    sec_one = sec_one + firebaseData.intData();
    Serial.print("sec-one : ");
    Serial.print(sec_one);
    Serial.println();
  }

  for (int j = 1; j < 9; j++){
    Firebase.getInt(firebaseData, "16bit-application/16bit00001/section-two/ch" + String(j));
    sec_two = sec_two + firebaseData.intData();
    Serial.print("sec-two : ");
    Serial.print(sec_two);
    Serial.println();
  }

  digitalWrite(latchPin, LOW);
  //2nd IC Binary 
  shiftOut(dataPin, clockPin, MSBFIRST, sec_two);
  //1st IC Binary
  shiftOut(dataPin, clockPin, MSBFIRST, sec_one);
  digitalWrite(latchPin, HIGH);
}
