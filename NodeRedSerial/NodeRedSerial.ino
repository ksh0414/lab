#include <SparkFunBME280.h>
#define BME280_ADDR 0x77

BME280 myBME280;

void setup(){
  Serial.begin(115200);
  myBME280.setI2CAddress(BME280_ADDR);
  myBME280.beginI2C(); // BME280 12C장치 호출
}
void loop()
{
  Serial.print(myBME280.readTempC(), 2);
  Serial.print("\n");
  delay(2000);
}