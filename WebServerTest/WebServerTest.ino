#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define LED_PIN 15
#define LED_R_PIN 12
#define LED_G_PIN 13
#define LED_B_PIN 14

/* WiFi network name and password */
const char * ssid = "Ajou Univ";
const char * pwd = "";

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char * udpAddress = "172.21.55.149";
const int udpPort = 3333;

//create UDP instance
WiFiUDP udp;

void setup(){
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  digitalWrite(LED_R_PIN, LOW);
  digitalWrite(LED_G_PIN, LOW);
  digitalWrite(LED_B_PIN, HIGH);
  Serial.begin(115200);
  
  //Connect to the WiFi network
   WiFi.begin(ssid, pwd);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop(){
  //data will be sent to server
  uint8_t buffer[50] = "hello world";
  //send hello world to server
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if(udp.read(buffer, 50) <= 0)
  {
    delay(100);
    return;
  }
  if(strcmp((const char*)buffer, "ON") == 0)
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("recieve message: ON");
  }
  else if(strcmp((const char*)buffer, "OFF") == 0)
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("recieve message: OFF");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("recieve message: invalid");
  }
  
  delay(1000);
  
}