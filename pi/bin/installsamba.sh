#!/usr/bin/env bash

sudo apt-get install -y samba

cat<<EOF > /etc/samba/smb.conf
[pi]
comment = PI Share
path = /home/pi
read only = No
create mask = 0777
directory mask = 0777
guest only = Yes
guest ok = Yes
EOF
