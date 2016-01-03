#!/bin/sh
# Installation of server components
# Johannes Strasser
# 3.1.2016
# www.strasys.at
#

#Installation of Server components
#
echo "installation of php5 \n"
apt-get install php5
wait
echo "Installation of php5 completed \n"
echo "restart apache2 \n"
/etc/init.d/apache2 restart
wait
echo "apache got restarted \n"

read -p "Would you like to reboot? (y/n)? " RESP
if [ "$RESP" = "y" ]; then
reboot
else
echo "End of installation process!\"
exit 1
fi
