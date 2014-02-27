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

login = root / root

```
$ lsusb
```

You should see the wifi adaptor listed - mine says:

```
Bus 001 Device 004: ID 0bda:8176 Realtek Semiconductor Corp. RTL8188CUS 802.11n WLAN Adapter
```

## wifi config

setup the wifi card by creating a config file:

```
$ nano /etc/netctl/pifi
```

the file should be:

```
Description='PIFI'
Interface=wlan0
Connection=wireless
Security=wpa

IP=dhcp

ESSID='SSIDHERE'
Key='XXXXXXXXX'
```

lock down the wifi password file:

```
$ chmod 640 /etc/netctl/pifi
```

Then start the wifi:

```
$ netctl start pifi
```

Then make it start each time:

```
$ netctl enable pifi
```

## get IP address

```
$ ifconfig
```

This outputs the status of network cards on the machine - look for:

```
wlan0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.1.16  netmask 255.255.255.0  broadcast 192.168.1.255
        ether 64:70:02:29:63:35  txqueuelen 1000  (Ethernet)
```

From this we know the IP address of the PI on the wireless network (in this example 192.168.1.16)

## connect over Putty

Open Putty from windows - create a new server - the details are:

 * Host Name (or IP address) = 192.168.1.16 - or what your PI is on your wireless network above
 * Port = 22

Save the session.

Double click the PI session in putty - it will say 'I have not seen this before' - then a login:

username: root
password: root

## finito

the PI is installed - you can remove the HDMI cable and keyboard and mouse.

the next step is - installsoftware.md
