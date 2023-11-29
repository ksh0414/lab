#define SECRET_SSID ""
#define SECRET_PASS ""
#define SECRET_CH_ID 
#define SECRET_WRITE_APIKEY ""


















#include <WiFi.h>
#include "ThingSpeak.h"
#include <SparkFunBME280.h> 

#define BME280_ADDR 0x77

BME280 myBME280;
// Use this file to store all of the private credentials and connection details
// replace MySSID with your WiFi network name
// replace MyPassword with your WiFi password
// replace 0000000 with your channel number
// replace XYZ with your channel write API Key
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password
WiFiClient client;
void setup() {
  Serial.begin(115200);
  delay(100);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  myBME280.setI2CAddress(BME280_ADDR);
  myBME280.setReferencePressure(101990);
  myBME280.beginI2C();
}

void loop() {
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("InConnected.");
  }
// temperatureC = bme.readTemperature();
  // 섭씨온도
  float temperatureC, pressure, humidity;
  temperatureC = myBME280.readTempC();
  Serial.print(" Temperature(℃): ");
  Serial.print(temperatureC, 2);
  Serial.println(" degrees C");

  // 상대습도(%)
  humidity = myBME280.readFloatHumidity();
  Serial.print(" Humidity: ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  // 기압(Pa) 1(atm) = 1013.25(hPa) = 101325(Pa)
  pressure = myBME280.readFloatPressure();
  Serial.print(" Pressure: ");
  Serial.print(pressure, 2);
  Serial.println(" Pa");

  // set the fields with the values
  ThingSpeak.setField(1, temperatureC);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, pressure);

// Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
// pieces of information in a channel. Here, we write to field 1.
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
// Wait 20 seconds to update the channel again
  delay(5000);
}
