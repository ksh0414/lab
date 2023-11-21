#include <WiFi.h>
#include "PubSubClient.h"
const char* ssid = "sanghyun";
const char* password = "kim71228569";
const char* mqttServer = "broker.hivemq.com";
int port = 1883;
String stMac;
char mac[50];
char clientld[50];
WiFiClient espClient;
PubSubClient client(espClient);
const int ledPin = 15;

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}
void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection ... ");
    long r = random(1000);
    sprintf(clientld, "clientld-%ld", r);
    if (client.connect(clientld)) {
      Serial.print(clientld);
      Serial.println(" connected");
      client.subscribe("room/lamp_my123");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }

  Serial.println("reconnect complete");
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String stMessage;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }
  Serial.println();
  if (String(topic) == "room/lamp_my123") {
    Serial.print("Changing output to ");
    if(stMessage == "ON"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else{
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  wifiConnect();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  stMac = WiFi.macAddress();
  stMac.replace(":","_");
  Serial.println(stMac);
  client.setServer(mqttServer, port);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
  Serial.println("setup complete");
}

void loop() {
  delay(10);
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
}