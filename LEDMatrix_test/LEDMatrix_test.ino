#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#define ISSI_ADDR_DEFAULT 0x74

const char text[4]={'A','J','O','U'}; // 출력을 위한 6개의 문자 배열 선언
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
void setup() {
// I2C주소값 선언
  //Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
  matrix.begin(); 
}


void loop() {
  matrix.setTextSize(1); // Text 크기
  matrix.setTextColor(100); // Text 밝기
  for(int pos = 28; pos >= -24; pos--){ // text[ ] 배열에 대한 반복문 선언
    matrix.clear(); // LED Matrix 화면 초기화
    matrix.setCursor(pos, 1); //함수
    matrix.printf("%s", text); //함수
    delay(100);
}
}