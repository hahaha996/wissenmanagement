### create OS SD for Raspberry Pi

https://www.raspberrypi.com/software/

do it as follows: wifi username and password must be included


### Get IP of Pi
Go to Wifi router, then go to website with your IP adresse and look up the ip of raspberry pi

### Setup SSH on workstation

```bash
# We can access the Pi as follow:
ssh pi@192.168.1.24 -i ~/.ssh/pi
## For better workflow, config ssh config:
nano ~/.ssh/config
######
Host pi
        HostName 192.168.1.24
        User pi
        IdentityFile ~/.ssh/pi
######
# From now, SSH into the Pi by
ssh pi
```

### Set static IP for Pi
SSH into the Pi, and:
```bash
# Edit this file
sudo nano /etc/dhcpcd.conf
########### with the following content
interface eth0
static ip_address=192.168.1.24/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.1.1
static domain_name_servers=192.168.1.1
###########
sudo reboot
``````