#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#define ISSI_ADDR_DEFAULT 0x74

static const uint8_t PROGMEM
smile_bmp[] = // 이모티콘 배열 선언(생성 사이트 참고)
{
B00000000,
B01000010,
B10100101,
B00000000,
B01000010,
B00111100,
B00000000,
B00000000
};

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
void setup() {
// I2C주소값 선언
  //Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
  matrix.begin(); 
}


void loop() {
  matrix.setRotation(0); // 디스플레이 위치 값
  matrix.clear(); // LED Matirx 화면 초기화
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, 100);
  delay(1000);
  matrix.clear();
  delay(2000);
}