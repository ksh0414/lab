#define LED_PWM_R 12
#define LED_PWM_G 13
#define LED_PWM_B 14

uint8_t ledCH = 0;
uint32_t freq = 500;
uint8_t resolution_bits = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PWM_R, OUTPUT);
  digitalWrite(LED_PWM_R, LOW);
  pinMode(LED_PWM_G, OUTPUT);
  digitalWrite(LED_PWM_G, LOW);
  pinMode(LED_PWM_B, OUTPUT);
  digitalWrite(LED_PWM_B, LOW);

  ledcSetup(ledCH, freq, resolution_bits);
  //ledcAttachPin(LED_PWM_G, ledCH);
  //ledcAttachPin(LED_PWM_B, ledCH);
}

void blinkPWMLED(uint8_t led_count);

void loop() {
  // put your main code here, to run repeatedly:
  blinkPWMLED();
}

void blinkPWMLED()
{
  static uint32_t led_count = 0;
  ledcAttachPin(LED_PWM_R+led_count, ledCH);
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    // Duty Cycle 값이 0~255까지 순차적으로 증가(LED 밝기 증가)
    ledcWrite(ledCH, dutyCycle);
    delay(7);
  }
  for (int dutyCycle = 255; dutyCycle > 0; dutyCycle--) {
    // Duty Cycle 값이 0~255까지 순차적으로 증가(LED 밝기 감소)
    ledcWrite(ledCH, dutyCycle);
    delay(7);
  }
  ledcDetachPin(LED_PWM_R+led_count);
  led_count = (led_count == 2) ? 0 : led_count+1;
}