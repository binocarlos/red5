#!/usr/bin/env bash

sudo apt-get install -y samba samba-common-bin

cat<<EOF > /etc/samba/smb.conf
[global]
  workgroup = red5
  server string = red5
  wins support = yes

[pi]
  path = /home/pi
  writeable = yes
	comment = PIDrive
	valid users = pi 
	writeable = yes 
	browseable = yes
EOF

#smbpasswd -a -n pi

service samba restart