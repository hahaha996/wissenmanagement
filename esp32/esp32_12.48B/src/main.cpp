#include <esp_system.h>
#include "BluetoothSerial.h"
#include <time.h>
#include "DEV_Config.h"
#include "utility/EPD_12in48b.h"
// #include "EPD_12in48b.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include "helpers.h"
#include <stdlib.h>

#define LED_PIN 15 // GPIO pin for LED

int Version = 1; // Software version
/* Check if Bluetooth configurations are enabled in the SDK (Software Development Kit)*/
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// #if !defined(MAX_STR_BUFF)
// #define MAX_STR_BUFF 128
// #endif

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 30       /* Time ESP32 will go to sleep (in seconds) */

// #define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex
#define BUTTON_PIN_BITMASK (2ULL << 35)
RTC_DATA_ATTR int bootCount = 0;

void start_deepsleep()
{
    // Configures and enables deep sleep mode with specific wake-up sources
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 1); // 1 = High, 0 = Low
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("### *** Setup ESP32 to deep sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
    Serial.println("### *** Going to sleep now");
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    esp_deep_sleep_start();
}

void setup()
{
    // Setup function runs once at boot
    Serial.begin(115200); // Start serial communication
    pinMode(LED_PIN, OUTPUT); // Set LED pin as output
    BluetoothSerial SerialBT; // Create BluetoothSerial object

    struct payload pl; // Create payload struct for storing received data

    // Determine the cause of wake-up from deep sleep
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    digitalWrite(LED_PIN, HIGH); // Turn on LED

    // Handle wake-up due to external signal (button press)
    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0)
    {
        Serial.println("### *** Wakeup caused by external signal using RTC_IO"); 
        Serial.println("### *** Printing wake button message!");
        draw_wakeup_button_msg(); // Display message for wake-up button
        start_deepsleep(); // Go back to deep sleep
    }
    else
    {
        // Handle wake-up due to timer
        if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER)
        {
            Serial.println("### *** Wakeup caused by timer ...");
        }
        for (int tries = 0; tries < 5; tries++)
        {
            // sourcecode: https://que0le.github.io/posts/pi-bluetooth/
            uint8_t mac[6];
            esp_read_mac(mac, ESP_MAC_BT);

            // Print the Bluetooth address
            Serial.printf("### *** Bluetooth Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            /* If no name is given, default 'ESP32' is applied */
            /* If you want to give your own name to ESP32 Bluetooth device, then */
            /* specify the name as an argument SerialBT.begin("myESP32Bluetooth"); */
            SerialBT.begin();
            Serial.println("### *** Bluetooth Started! Ready to pair...");

            if (SerialBT.available())
            {
                // Read data into the buffer
                int bytesRead = SerialBT.readBytes((char *)&pl, sizeof(struct payload));

                // Process the received data
                if (bytesRead > 0)
                {
                    // we got some usable data
                    Serial.printf("### *** Read: %d counter: %d. Received message: ", bytesRead, pl.count);
                    Serial.write(pl.message, 100);
                    Serial.println();
                    // Print data for debugging purpose
                    for (int i = 0; i < 10; i++)
                    {
                        time_t unixTime = pl.last_updates[i];
                        struct tm *timeInfo;
                        char t_buffer[80];
                        timeInfo = localtime(&unixTime);
                        strftime(t_buffer, sizeof(t_buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
                        Serial.printf("Humid: %f, Temp: %f, Heat: %f, letzte Aktualisierung: %s ",
                                      pl.humids[i], pl.temps[i], pl.heats[i], t_buffer);
                        Serial.println();
                    }
                    Serial.println();
                    // Plotting to eink by passing the payload to this function
                    draw_normal_message(pl);
                    // Done drawing. Setup button to wake up from deepsleep
                    esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 1); // 1 = High, 0 = Low
                    // ... and sleep timeout. 
                    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
                    Serial.println("### *** Deep sleep " + String(TIME_TO_SLEEP) + " Seconds");
                    Serial.println("### *** Going to sleep now.");
                    delay(1000);
                    // Turn off the LED.
                    digitalWrite(LED_PIN, LOW);
                    // All done. We can sleep.
                    esp_deep_sleep_start();
                }
                // delay(5000);
            }
            delay(5000);
        }
    }
    digitalWrite(LED_PIN, LOW);
}

void loop()
{
}
