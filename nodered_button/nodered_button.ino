#define LED_PIN 15

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  if(Serial.available())
  {
    char payload = Serial.read();
    if(payload == '1'){
      digitalWrite(LED_PIN, HIGH);
      Serial.println(1);
    }
    else if(payload == '0'){
      digitalWrite(LED_PIN, LOW);
      Serial.println(0);
    }
  }
  delay(100);
}
