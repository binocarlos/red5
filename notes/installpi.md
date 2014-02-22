# install raspberry PI

## prepare SD card

download the [sd card formatter](https://www.sdcard.org/downloads/formatter_4/eula_windows/)

run the SDFormatter program - format the SD card

download the [Arch Linux](http://downloads.raspberrypi.org/arch_latest) PI image

download [WinDiskImager](http://sourceforge.net/projects/win32diskimager/) - the green link

Unzip WinDiskImager to a folder where it will live (manual installation).

Unzip the ArchLinuxARMxxxx.img file from the zip.

Run WinDiskImager.exe.

Choose the Arch .img file you just unzipped.

Choose the SDCard drive (that was formatted just now).

Write the image to the SDCard (make a cuppa tea time).

## install PI

put the SD card into the PI

turn power on pi - keyboard and mouse via usb hub - mini usb - pi

hdmi cable into monitor

NOOBS boots - choose Raspbian and install (this takes a while make 2 cups of tea)

## install

The raspi-config program will launch first - using this:

 * set the password
 * enable boot to cli (default)
 * enable camera module
 * advanced -> enable ssh	

## network config

Power off PI - plug-in wifi usb directly into PI usb slot

Power on PI

Login as pi

Following [this guide](http://databoyz.wordpress.com/tag/how-to-setup-network-and-wpa_supplicant-conf-file-on-raspberry-pi/) - then setup the wifi card.

```
$ lsusb
```

You should see the wifi adaptor listed - mine says:

```
Bus 001 Device 004: ID 0bda:8176 Realtek Semiconductor Corp. RTL8188CUS 802.11n WLAN Adapter
```

## wifi config

first edit the interfaces:

```
$ sudo nano /etc/network/interfaces
```

the file should be:

```
auto lo
iface lo inet loopback

allow-hotplug eth0
iface eth0 inet dhcp

auto wlan0
allow-hotplug wlan0
iface wlan0 inet manual
wpa-roam /etc/wpa_supplicant/wpa_supplicant.conf
iface default inet dhcp
```

then edit the supplicant file:

```
$ sudo nano /etc/wpa_supplicant/wpa_supplicant.conf
```

the file should be:

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
        ssid="SSIDHERE"
        psk="PASSWORDHERE"
        proto=WPA
        key_mgmt=WPA-PSK
        pairwise=TKIP
        auth_alg=OPEN
}
```

if this does not work then perhaps it is the other wireless protocol:

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
        ssid="SSIDHERE"
        psk="PASSWORDHERE"
        proto=RSN
        key_mgmt=WPA-PSK
        pairwise=CCMP
        auth_alg=OPEN
}
```

then restart the wireless card:

```
$ sudo /etc/init.d/networking restart
```

wait 10 seconds then:

```
$ ifconfig
```

the crucial part is that wlan0 has an 'inet addr' - here is the relevant part of my ifconfig:

```
wlan0     Link encap:Ethernet  HWaddr 64:70:02:29:63:35
          inet addr:192.168.1.16  Bcast:192.168.1.255  Mask:255.255.255.0
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
```

From this we know the IP address of the PI on the wireless network.

## connect over Putty

Open Putty from windows - create a new server - the details are:

 * Host Name (or IP address) = 192.168.1.16 - or what your PI is on your wireless network above
 * Port = 22

Save the session.

Double click the PI session in putty - it will say 'I have not seen this before' - then a login:

username: pi
password: <thepassword you set when you installed the pi>

## finito

the PI is installed - you can remove the HDMI cable and keyboard and mouse.

the next step is - installsoftware.md

