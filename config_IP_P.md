

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

```bash
Enter Download/upload mode for esp32: hold boot button
```