#!/bin/sh
# This script copies the service file enables and starts it
#Johannes Strasser
# 15.04.2015
# www.strasys.at
#

cp init_privateplc.service /lib/systemd/system/
cp strasys-homectrl-00A0.dtbo /lib/firmware/
cp init_privateplc.sh /usr/lib/cgi-bin/

cd /lib/systemd/system/
systemctl enable init_privateplc.service
systemctl start init_privateplc.service

echo "System - programs installation ready!\n"
echo "Please reboot your device!\n"