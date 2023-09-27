#define BZ_CTRL 2
#define BZ_PWM 25
#define INIT_FREQ 261.6256

uint8_t PWMCH = 0;
uint32_t freq = 500;
uint8_t resolution_bits = 8;
const uint32_t MAX_DUTY = (resolution_bits == 0) ? 0 : (1 << (resolution_bits))-1;

inline void BUZZ_ON() {digitalWrite(BZ_CTRL, HIGH); 
                       ledcWrite(PWMCH, MAX_DUTY/2);
                       ledcWriteTone(PWMCH, INIT_FREQ);}
inline void BUZZ_OFF() {digitalWrite(BZ_CTRL, LOW);}

void setup() {
  // put your setup code here, to run once:
  pinMode(BZ_CTRL, OUTPUT);
  digitalWrite(BZ_CTRL, LOW);
  
  ledcSetup(PWMCH, freq, resolution_bits);
  ledcAttachPin(BZ_PWM, PWMCH);
}

void loop() {
  // put your main code here, to run repeatedly:
  BUZZ_ON();
  for(int i=0; i<1; i++)
  {
    for(int duty = 0; duty <= MAX_DUTY; duty+=1)
    {
      ledcWrite(PWMCH, duty);
      delay(100);
    }
    delay(1000);
  }

  BUZZ_OFF();
  delay(100000);
}
