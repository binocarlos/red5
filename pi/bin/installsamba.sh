#!/usr/bin/env bash

sudo apt-get install -y samba

cat<<EOF > /etc/samba/smb.conf
[global]
	guest account = nfsnobody
	map to guest = bad user

[pi]
  path = /home/pi
  writable = yes
  guest ok = yes
  public = yes
  force user = pi
  force group = pi
  create mask = 666
  directory mask = 666
  security mask = 666
  force create mode = 666
EOF

service samba restart