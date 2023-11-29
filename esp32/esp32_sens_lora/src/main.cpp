
#include <SPI.h>
#include <LoRa.h>
#include <SPI.h>
#include "DHT.h"

// LORA: define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2
// SENSOR:
#define DHTPIN 25     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

int counter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  Serial.println("Setup done");
  counter = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  char resultString[100];
  sprintf(resultString, "%d: Humidity: %.2f%%, Temp: %.2fC, Heat index: %.2fC", counter, h, t, hic);
  Serial.println(resultString);


  LoRa.setPins(ss, rst, dio0);
  Serial.println("initing lora ... ");
  while (!LoRa.begin(866E6))
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  delay(500);
  Serial.println("Sending msg: ...");
  Serial.println(resultString);
  LoRa.beginPacket();
  LoRa.printf(resultString);
  LoRa.endPacket();
  counter = counter + 1;
  Serial.println("Sent. Sleep.");
  delay(10000);

}