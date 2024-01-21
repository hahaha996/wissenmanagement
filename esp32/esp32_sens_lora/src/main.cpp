
#include <SPI.h>
#include <LoRa.h>
#include <SPI.h>
#include "DHT.h"

// LORA: define the pins used by the transceiver module
#define ss 5 // Chip select pin for LoRa
#define rst 14 // Reset pin for LoRa
#define dio0 2 // Interrupt pin for LoRa
// DHT sensor configuration
#define DHTPIN 25     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // Type of DHT sensor DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE); // DHT sensor instance
// Array of locations
String locations[] = {"Lichtenberg", "Mitte", "Spandau", "Pankow"};


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
  // Humidity reading
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
  // sprintf(resultString, "%d,lichtenberg,Humidity: %.2f%%, Temp: %.2fC, Heat index: %.2fC", counter, h, t, hic);

  // Generate a random index to select a location
  int randomIndex = random(4); // Assuming 4 locations

  sprintf(resultString, "%d,%s,%.2f,%.2f,%.2f", counter, locations[randomIndex].c_str(), h+randomIndex*2, t+randomIndex*2, hic+randomIndex*2);

  // sprintf(resultString, "%d,Lichtenberg,%.2f,%.2f,%.2f", counter, h, t, hic);
  Serial.println(resultString); // Print the result string to the serial monitor.
  // The serial monitor allows for viewing output from the ESP32, that is also monitor function in platformio.

  LoRa.setPins(ss, rst, dio0); // Set LoRa module pins
  Serial.println("initing lora ... ");
  while (!LoRa.begin(866E6)) // Initialize LoRa at 866 MHz, a frequency suitable for LoRa communication in Europe.
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3); // Set synchronization word for LoRa communication
  delay(500);
  Serial.println("Sending msg: ...");
  Serial.println(resultString); // Print the message to be sent
  LoRa.beginPacket(); // Start a new LoRa packet
  LoRa.printf(resultString);  // Add data to the LoRa packet
  LoRa.endPacket(); // Finish and send the LoRa packet
  counter = counter + 1;
  Serial.println("Sent. Sleep.");
  delay(10000); // Delay for 10 seconds before the next loop iteration

}