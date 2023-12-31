

### Shopping List

- **1x LoRa with Antenna**
  - Example: [LoRa Module on Amazon](https://www.amazon.de/-/en/gp/product/B084NWDFH1/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  
- **2x USB Mini Cables**
  
- **1x E-Ink Display**
  - Suggested Option:
    - **Color E-Ink**: [Waveshare 12.48inch Color E-Ink Display](https://www.amazon.de/Waveshare-12-48inch-Resolution-Three-Color-Communicating/dp/B081NG6N21)
  
- **1x USB-C Hub with Ethernet**
  
- **1x Ethernet Cable**
  
- **2x Breadboards**
  
- **2x ESP32**
  - Due to lack of documentation and examples, consider this alternative:
    - [Alternative ESP32](https://www.amazon.de/-/en/gp/product/B071P98VTG/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
  
- **Resistance Cables** [Resistance Cables]
  (https://www.amazon.de/Assortment-Resistors-Electronic-Compliant-Tolerance/dp/B09TRQXZTB/ref=sr_1_3_sspa?keywords=Resistor&qid=1698917150&sr=8-3-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)

- **Battery Module (Li-Ion or LiFePO4) for ESP32 Board**

### Raspberry Pi OS SD Card Setup

- Visit [Raspberry Pi's Software Page](https://www.raspberrypi.com/software/)
- Ensure to include Wi-Fi username and password during the setup process.

### Obtaining Raspberry Pi's IP Address

- Access your WiFi router's settings to find the IP address.
- Locate the IP assigned to the Raspberry Pi within the connected devices list.

### SSH Configuration on Workstation

```bash
# Command to access the Pi
ssh pi@10.0.0.10 -i ~/.ssh/pi

# Configure SSH for better workflow
nano ~/.ssh/config
```

```bash
# SSH Config Content
Host pi
        HostName 10.0.0.10
        User pi
        IdentityFile ~/.ssh/pi
```

```bash
# SSH into the Pi
ssh pi
```

### Setting a Static IP for the Pi

- SSH into the Pi and execute the following:

```bash
sudo nano /etc/dhcpcd.conf
```

```bash
# dhcpcd.conf Content
interface eth0
static ip_address=10.0.0.10/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.0.0.1
static domain_name_servers=10.0.0.1
```

```bash
sudo reboot
```
### Run example Python Code
```bash
### ssh into pi
ssh pi
### cd to this Folder
cd /home/pi/12.48inch-e-paper/RaspberryPi/python/examples

### run example Code
sudo python3 epd_12in48B_test.py

### restart pi
sudo reboot 

### shutdown pi
sudo shutdown now
``````
#### Fotos

![image](media/IMG_3361_2.png)
![image](media/IMG_3361.png)
![image](media/IMG_3363.png)
![image](media/IMG_3365.png)

### How to cabling 

Die Kabel sollten so angeschlossen werden, wie es auf dem Bild des Herstellers gezeigt wird. Das rote Kabel-Label im Herstellerhinweis sollte genauso mit einem passenden Kabel-Label in E-Ink versehen werden. Der gelbe Bereich steht für das Kabel-Label des Raspberry Pi. Beide Labels müssen übereinstimmen. Um die Kabel-Labels besser zu ordnen, kommt auf dem Raspberry Pi eine Nummerierung hinzu. Da unser Eink mit 3V arbeitet, wird zum Beispiel RBI 3V3 (VCC) in E-Ink mit dem Platz 3V3 auf dem Raspberry Pi (der linkeste Platz) verbunden.

![image](12in48.png)



```bash
Enter Download/upload mode for esp32: hold boot button
```
### Note 26.11.23

**Issue: Incompatibility when combining LoRa and E-ink on Raspberry Pi GPIO**

**Problem Description:**

- While the LoRa module and E-ink display function independently, attempting to combine the two leads to failure. It seems that they are unable to share the GPIO (General Purpose Input/Output).

**To-Do:**

- Modify the `test_send_from_pi_over_lora.py` script to incorporate signal testing.
- Separate the GPIO configurations for the LoRa module and the Raspberry Pi to prevent conflicts.


#### Note 9.12.2023
Copy all code files from Waveshare's example `12.48inch-e-paper/esp32/esp32-epd-12in48/src` to `esp32/esp32_12.48B/src`. To run the code in platformio

All setup guide is here: https://www.waveshare.com/wiki/12.48inch_e-Paper_Module_(B)#Software_setup

#### Note 11.12.2023

##### Libraries install for pi

```bash
sudo apt-get install bluetooth bluez libbluetooth-dev
sudo python3 -m pip install pybluez
```
- The folder `esp32_12.48B` is the official folder that encompasses all functions, while `esp32_12.48B_draw` is specifically designed for drawing dummy data with the ESP32.

- After inspecting the sensor, we observed a very slow decrease in temperature. The indoor temperature is 26 degrees Celsius, and the outdoor temperature is around 5 degrees. However, after 1 minute, the temperature only dropped by 1 degree, indicating that we received data reporting a temperature of 25 degrees instead of the actual 5 degrees. Therefore, the conclusion is that the quality of this sensor appears to be subpar.


220ohm

```bash
sudo nano  /etc/systemd/system/pi_controller.service
sudo systemctl daemon-reload
sudo systemctl enable pi_controller.service
sudo systemctl start pi_controller.service

# see logs
journalctl -xefu pi_controller

# Debug
journalctl -u pi_controller.service -b

```