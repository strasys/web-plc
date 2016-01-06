#!/bin/sh
# Set the correct uid and gid of files
# Johannes Strasser
# 1.1.2016
# www.strasys.at
#


#
#set uid, gid and access modes
#
cd /tmp/privateplc/extract/vers1_0/startupservice/
echo "change user mode of install_disable_services.sh"
chmod o+x install_disable_services.sh
echo "change user mode of install_service.sh"
chmod o+x install_service.sh
echo "change user mode of init_privateplc.sh"
cd /usr/lib/cgi-bin/
chmod o+x init_privateplc.sh
echo "change gid and uid of GPIOin.xml and GPIOout.xml to www-data."
cd /var/www/
chown www-data:www-data GPIOin.xml
chown www-data:www-data GPIOout.xml
echo "change gid und uid of user.txt"
chown www-data:www-data user.txt
echo "change user mode of pushButtonSensing\n"
cd /usr/lib/cgi-bin/
chown root:www-data pushButtonSensing
chmod 110 pushButtonSensing
echo "change user mode of init_privateplc.sh"
chmod 110 init_privateplc.sh
echo "change user mode of firmware"
chmod 110 firmware
echo "change user mode of RTChandler"
chown root:www-data RTChandler
chmod 4110 RTChandler
echo "change user mode of PT100handler"
chown root:www-data PT100handler
chmod 4110 PT100handler
echo "change user mode of GPIOhandler"
chown root:www-data GPIOhandler
chmod 4110 GPIOhandler
echo "change user mode of AINOUThandler"
chown root:www-data AINOUThandler
chmod 4110 AINOUThandler

read -p "Would you like to continue to install hardware related *.services? (y/n)? " RESP
if [ "$RESP" = "y" ]; then
	cd /tmp/privateplc/extract/vers1_0/startupservice/
	wait
	./install_service.sh
else
	echo "You stopped the installation after set of uid's and access modes.\n"	
	exit 1
fi

