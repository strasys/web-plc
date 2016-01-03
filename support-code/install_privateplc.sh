#!/bin/sh
# Installation script to start the initial installation process!
# Johannes Strasser
# 3.1.2016
# www.strasys.at
#

#
#Fetch programm components from version server
#
echo "Fetch files from software version server!\n"
wget --no-host-directories --directory-prefix=/tmp/privateplc --cut-dirs=2 --recursive --no-parent http://HP1-strasser/privateplc/privateplc_vers_1_0.tar
wait
echo "generate folder to extract\n"
mkdir /tmp/privateplc/extract
wait
echo "extracting ...\n"
tar -xvf privateplc_vers_1_0.tar -C /tmp/privateplc/extract 
wait
echo "Copy webcontent to /var/www\n"
cp -rT /tmp/privateplc/extract/vers1_0/webcontent/ /var/www/
wait
echo "Copy firmware files to /usr/lib/cgi-bin\n"
cp -rT /tmp/privateplc/extract/vers1_0/firmware/ /usr/lib/cgi-bin/
wait

read -p "Would you like to continue with change of uid gid of files? (y/n)? " RESP
if [ "$RESP" = "y" ]; then
install_setuidgid.sh
else
echo "Installation stopped after copy of components from version server.\n"
exit 1
fi
