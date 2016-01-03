#!/bin/sh
# Installation of *.services
# Installation of device tree *.dtbo 
# Johannes Strasser
# 3.1.2016
# www.strasys.at
#
#
# copy and enabeling of system related components
#
echo "copy: init_privateplc.service to /lib/systemd/system/\n"
cp init_privateplc.service /lib/systemd/system/
echo "copy: strasys-homectrl-00A0.dtbo to /lib/firmware/\n"
cp strasys-homectrl-00A0.dtbo to /lib/firmware/
echo "copy: init_privateplc.sh /usr/lib/cgi-bin/\n"
cp init_privateplc.sh /usr/lib/cgi-bin/

cd /lib/systemd/system/
echo "enable init_privateplc.service \n"
systemctl enable init_privateplc.service
echo "start init_privateplc.service \n"
systemctl start init_privateplc.service

echo "System - programs installation ready!\n"
echo "Please reboot your device!\n"
