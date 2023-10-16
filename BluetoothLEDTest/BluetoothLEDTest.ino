#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string.h>

// The remote service we wish to connect to.
#define SERVER_UUID"eb33a17e-6bc4-11ee-b962-0242ac120002"
// The characteristic of the remote service we are interested in.
#define CHARACTERISTIC_UUID "fbc92da6-6bc4-11ee-b962-0242ac120002"
#define LED_PIN 13

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("New value: ");
      char buf[11] = {0, };
      for (int i = 0; i < value.length(); i++)
      {
        Serial.print(value[i]);
        if(i < 10)
          buf[i] = value[i];
      }
      Serial.println();
      

      if(strcmp(buf, "LED ON") == 0)
      {
        Serial.println("LED ON");
        digitalWrite(LED_PIN, HIGH);
      }
      else if(strcmp(buf, "LED OFF") == 0)
      {
        Serial.println("LED OFF");
        digitalWrite(LED_PIN, LOW);
      }
      else
      {
        Serial.println("invalid command");
      }
      Serial.println("*********");
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");
  Serial.println("Starting Arduino BLE Client application...");

  BLEDevice::init("MyESP32_6");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVER_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
