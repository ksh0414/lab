#define MICS 36
#define LED_PWM_R 12
#define LED_PWM_B 14
#define SOUND_LIMIT 1500

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_PWM_R, OUTPUT);
  digitalWrite(LED_PWM_R, LOW);
  pinMode(LED_PWM_B, OUTPUT);
  digitalWrite(LED_PWM_B, LOW);
}

uint8_t state = 0;
void loop() {
  // put your main code here, to run repeatedly:
  uint16_t value = analogRead(MICS);

  if(value > SOUND_LIMIT)
  {
    Serial.println(value);
    if(!state)
    {
      digitalWrite(LED_PWM_R, HIGH);
      digitalWrite(LED_PWM_B, LOW);
      Serial.println("if");
    }
    else
    {
      digitalWrite(LED_PWM_B, HIGH);
      digitalWrite(LED_PWM_R, LOW);
      Serial.println("else");
    }
    state = !state;
  }

  delay(100);
}
