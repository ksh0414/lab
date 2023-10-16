#define _TOUCH_LEFT_27 27 // LEFT TOUCH 장치 Pin번호 매크로 지정(GPIO27)
#define _TOUCH_RIGHT_4 4 // RIGHT TOUCH 장치 Pin번호 매크로 지정(GPIO4)
#define LED_R 12
#define LED_B 14
#define LIMIT_LEFT 10
#define LIMIT_RIGHT 11
#define LEFT 0
#define RIGHT 1


int touch_set[2][2] = {{_TOUCH_LEFT_27, LIMIT_LEFT},
                     {_TOUCH_RIGHT_4, LIMIT_RIGHT}};

void setup() {
  Serial.begin(115200); // Serial port baudrate 설정
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);
}

int touched(int pin);
void sensorPrint();

void loop() {
  if(touched(LEFT)) {Serial.print("RED LED ON\n"); digitalWrite(LED_R, HIGH);}
  else if(touched(RIGHT)) {Serial.print("BLUE LED ON\n"); digitalWrite(LED_B, HIGH);}
  else { digitalWrite(LED_R, LOW); digitalWrite(LED_B, LOW);}
  sensorPrint();
  delay(500);
}

int touched(int direction)
{
  if(touchRead(touch_set[direction][0]) <= touch_set[direction][1]) return 1;
  else                                                        return 0;
}

void sensorPrint()
{
  Serial.print("Left touch = ");
  Serial.print(touchRead(_TOUCH_LEFT_27)); // Left Touch Capacitor에 의한 전하량 Read
  Serial.print(" | ");
  Serial.print("Right Touch = ");
  Serial.println(touchRead(_TOUCH_RIGHT_4)); // Right Touch Capacitor에 의한 전하량 Read
}

