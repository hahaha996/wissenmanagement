### Buy list

- 1x lora with antenne, exp: https://www.amazon.de/-/en/gp/product/B084NWDFH1/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
- 2x usb mini cable 
- 1x e-ink, suggestion:
    - with colour: https://www.amazon.de/Waveshare-12-48inch-Resolution-Three-Color-Communicating/dp/B081NG6N21
- 1x usb c hub with ethernet 
- 1x ethernet cable
- 2x breadboard 
- 2x esp 32, due lack of documention and example, suggession new one:
https://www.amazon.de/-/en/gp/product/B071P98VTG/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1
- resistance cable
- battery modul (li-on or LiFePO4) for esp 32 board

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