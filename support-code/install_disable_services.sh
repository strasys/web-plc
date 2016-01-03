#!/bin/sh
# Services
# Johannes Strasser
# 3.1.2016
# www.strasys.at
#
#
#Disabeling of services
#
echo "Disabeling of not used services: \n"

echo "disabel cloud9.service \n"
systemctl disable cloud9.service
#systemctl disable gateone.service
echo "disable bonescript.service \n"
systemctl disable bonescript.service
echo "disable bonescript.socket \n"
systemctl disable bonescript.socket
echo "disable bonescript-autorun.service \n"
systemctl disable bonescript-autorun.service
echo "disable avahi-daemon.service \n"
systemctl disable avahi-daemon.service

#systemctl disable gdm.service
#systemctl disable mpd.service

wait
echo "Disabeling completed! \n"

read -p "Would you like to continue to install php5? (y/n)? " RESP
if [ "$RESP" != "y" ]; then
  exit 1
else
	
fi