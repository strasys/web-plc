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
cd /tmp/privateplc/extract/vers1_0/startupservice/
echo "copy: init_privateplc.service to /lib/systemd/system/"
cp init_privateplc.service /lib/systemd/system/
echo "copy: strasys-homectrl-00A0.dtbo to /lib/firmware/"
cp strasys-homectrl-00A0.dtbo /lib/firmware/

cd /lib/systemd/system/
echo "enable init_privateplc.service"
systemctl enable init_privateplc.service
echo "start init_privateplc.service"
systemctl start init_privateplc.service

echo "The privateplc based software installation is done!"
