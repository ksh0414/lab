#define _A0_LIGHT_ADC_36 36 // A0핀 센서에 해당하는 GPIO 핀 매크로지정
void setup(){
  Serial.begin(115200);
}
void loop() {
  Serial.print("Light Sensor Value = ");
  Serial.println(analogRead(_A0_LIGHT_ADC_36)); // 센서값 출력
  Serial.print(" ");
  delay(100);
}