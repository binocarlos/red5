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

echo "now do:"
echo ""
echo "$ sudo smbpasswd -a -n pi"
echo ""
echo "then type password"
echo ""
echo "$ sudo service samba restart"