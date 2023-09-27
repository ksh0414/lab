#define BZ_CTRL 2
#define BZ_PWM 25
#define INIT_FREQ 261.6256

uint8_t PWMCH = 0;
uint8_t resolution_bits = 8;
uint32_t MAX_DUTY = (resolution_bits == 0) ? 0 : (1 << (resolution_bits-1))-1;

inline void BUZZ_ON() {digitalWrite(BZ_CTRL, HIGH); ledcWriteTone(PWMCH, INIT_FREQ);}
inline void BUZZ_OFF() {digitalWrite(BZ_CTRL, LOW);}

void setup() {
  // put your setup code here, to run once:
  pinMode(BZ_CTRL, OUTPUT);
  digitalWrite(BZ_CTRL, LOW);
  
  ledcSetup(PWMCH, INIT_FREQ, resolution_bits);
  ledcAttachPin(BZ_PWM, PWMCH);
}

void loop() {
  // put your main code here, to run repeatedly:
  BUZZ_ON();
  for(int i=0; i<1; i++)
  {
    for(int freq = INIT_FREQ; freq <= 1000; freq+=1)
    {
      ledcWriteTone(PWMCH, freq);
      delay(20);
    }
    delay(100);
  }

  BUZZ_OFF();
  delay(100000);
}
