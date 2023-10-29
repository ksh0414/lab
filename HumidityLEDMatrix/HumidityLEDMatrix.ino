#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <SparkFunBME280.h> 
#define ISSI_ADDR_DEFAULT 0x74
#define BME280_ADDR 0x77

#define TEMP_LIMIT 28.0
#define HUMIDITY_LIMIT 58.0

BME280 myBME280;

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

static const uint8_t PROGMEM
sad_bmp[] = // 이모티콘 배열 선언(생성 사이트 참고)
{
B00000000,
B10100101,
B01000010,
B00000000,
B00111100,
B01000010,
B00000000,
B00000000
};

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
void setup() {
// I2C주소값 선언
  matrix.begin(); 
  Serial.begin(115200);
  myBME280.setI2CAddress(BME280_ADDR);
  myBME280.setReferencePressure(101990);
  myBME280.beginI2C();
}

int check_temp(float temp)
{
  if(temp > TEMP_LIMIT)
    return 1;
  else
    return 0;
}

int check_humidity(float humidity)
{
  if(humidity > HUMIDITY_LIMIT)
    return 1;
  else
   return 0;
}

void loop() {
  matrix.setRotation(0); // 디스플레이 위치 값
  matrix.clear(); // LED Matirx 화면 초기화
  

  float temp = myBME280.readTempC();
  float humidity = myBME280.readFloatHumidity();

  Serial.print(" Temperature(℃): ");
  Serial.print(temp, 2);
  Serial.println(" degrees C");
    // 상대습도(%)
  Serial.print(" Humidity: ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  int temp_over = check_temp(temp);
  int humidity_over = check_humidity(humidity);

  if(temp_over && humidity_over)
    matrix.drawBitmap(0, 0, sad_bmp, 8, 8, 100);
  else
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, 100);

  delay(100);
}
