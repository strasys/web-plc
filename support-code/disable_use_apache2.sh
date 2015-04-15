#!/bin/sh

systemctl disable cloud9.service
systemctl disable gateone.service
systemctl disable bonescript.service
systemctl disable bonescript.socket
systemctl disable bonescript-autorun.service
systemctl disable avahi-daemon.service
systemctl disable gdm.service
systemctl disable mpd.service
