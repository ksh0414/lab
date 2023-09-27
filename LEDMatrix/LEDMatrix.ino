#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#define ISSI_ADDR_DEFAULT 0x74

const char text[5]={'A','J','O','U', 'N'}; // 출력을 위한 6개의 문자 배열 선언
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
void setup() {
// I2C주소값 선언
  //Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
  matrix.begin(); 
}


void loop() {
  matrix.setTextSize(1); // Text 크기
  matrix.setTextColor(100); // Text 밝기
  for(int i=0;i<=4;i++){ // text[ ] 배열에 대한 반복문 선언
    matrix.clear(); // LED Matrix 화면 초기화
    matrix.setCursor(0, i); //함수
    matrix.printf("%c", text[4]); //함수
    delay(1000);
  }
  matrix.clear();
  delay(2000);
}