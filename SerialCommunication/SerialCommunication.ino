void setup() {
    Serial.begin(115200);

    Serial.println("serial strart\n");
}

int count = 0;

void loop() {
  Serial.println(count++, DEC); 
  delay(1000);
}
