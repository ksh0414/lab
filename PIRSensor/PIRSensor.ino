#define _D0_PIR_GPIO_2 33 // D0핀 입력장치(PIR센서)에 해당하는 GPIO 핀 매크로지정
#define _D1_PIR_GPIO_15 15 // D1핀 출력장치(PIR센서)에 해당하는 GPIO 핀 매크로지정

void setup() { pinMode(_D0_PIR_GPIO_2, INPUT); // D0핀 입력설정
  pinMode(_D0_PIR_GPIO_2, INPUT);
  pinMode(_D1_PIR_GPIO_15, OUTPUT); // D0핀 출력설정
  Serial.begin(115200);
}

void loop() {
  int motionState = digitalRead(_D0_PIR_GPIO_2); // D0핀 입력상태 저장
  Serial.print("PIR value: ");
  Serial.println(motionState);
  if (motionState == HIGH) // 입력상태에 따른 조건문
    digitalWrite(_D1_PIR_GPIO_15, HIGH); // D1핀(GPIO15) LED ON
  else 
    digitalWrite(_D1_PIR_GPIO_15, LOW); // D1핀(GPIO15) LED OFF }
  
  motionState = 0;
  delay(100);
}