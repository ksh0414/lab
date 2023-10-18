#define BZ_CTRL 2
#define BZ_PWM 25
#define _A0_ADC_36 36
#define MAX_FREQ 1300.0
#define MIN_VALUE 0
#define MAX_VALUE 4095.0

uint8_t PWMCH = 0;
uint8_t resolution_bits = 8;


void setup() {
  // put your setup code here, to run once:
  pinMode(BZ_CTRL, OUTPUT);
  digitalWrite(BZ_CTRL, HIGH);
  Serial.begin(115200);
  
  ledcSetup(PWMCH, 0, resolution_bits);
  ledcAttachPin(BZ_PWM, PWMCH);
}

double ratio(int level)
{
  return level / MAX_VALUE;
}
double get_freq(int level)
{
  return MAX_FREQ * (ratio(level));
}

void loop() {
  // put your main code here, to run repeatedly:
  int level = analogRead(_A0_ADC_36);
  
  Serial.println(ratio(level));
  ledcWriteTone(PWMCH, get_freq(level));

  delay(10);
}
