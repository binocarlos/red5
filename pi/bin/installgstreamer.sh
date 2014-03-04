#!/usr/bin/env bash

if [ -z `cat /etc/apt/sources.list | grep vontaene.de` ]; then
	echo "deb http://vontaene.de/raspbian-updates/ . main" >> /etc/apt/sources.list
fi

apt-get update
apt-get install -y gstreamer1.0

gst-inspect-1.0 | grep OpenMAX