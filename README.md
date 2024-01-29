### Kiezbox Project 

The project's goal is to implement a part of the Kiezbox's crisis functionalities. 

During the project, the objectives were slightly adjusted in consultation with the client. The updated goals include:

- Transmitting temperature data from a sensor via LoRa to the Raspberry Pi.
- The Pi should forward this data to the ESP32-E-Ink display.
- Display received data on the E-Ink screen.
- Store text messages directly in the ESP32.Display messages on the E-Ink screen by pressing an external button.
- Implement a power-saving mode in the ESP32 using a wake-on-timer.
- Gather ideas for further applications of the Kiezbox in both crisis and normal operations.

##### Libraries install for pi

```bash
sudo apt-get install bluetooth bluez libbluetooth-dev
sudo python3 -m pip install pybluez
```
- The folder `esp32_12.48B` is the official folder that encompasses all functions, while `esp32_12.48B_draw` is specifically designed for drawing dummy data with the ESP32.

- After inspecting the sensor, we observed a very slow decrease in temperature. The indoor temperature is 26 degrees Celsius, and the outdoor temperature is around 5 degrees. However, after 1 minute, the temperature only dropped by 1 degree, indicating that we received data reporting a temperature of 25 degrees instead of the actual 5 degrees. Therefore, the conclusion is that the quality of this sensor appears to be subpar.


## Make pi_controller start with system
```bash
# automaticly to start pi. paste from here:
# ./pi_controller.service
sudo nano  /etc/systemd/system/pi_controller.service
# Reload systemctl to update 
sudo systemctl daemon-reload

# Now, enable the service
sudo systemctl enable pi_controller.service
sudo systemctl start pi_controller.service
# Check if all green
sudo systemctl status pi_controller.service
# sometimes the data is not updated, should restart service
sudo systemctl restart pi_controller.service

# see logs
journalctl -xefu pi_controller

# Debug
journalctl -u pi_controller.service -b

```