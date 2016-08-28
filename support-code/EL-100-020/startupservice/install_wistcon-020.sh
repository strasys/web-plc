#!/bin/sh
# Installation script to start the initial installation process!
# Johannes Strasser
# 25.08.2016
# www.strasys.at
#
#Installation description:
#cd /tmp
#wget -nH -r -np --cut-dirs=3 http://HP-Max/wistcon/EL-100-020/vers1_0/startupservice/install_wistcon-020.sh
#chmod o+x install_privateplc.sh
#./install_wistcon-020.sh
#
#Fetch programm components from version server
#
echo "Fetch files from software version server!\n"
wget --no-host-directories --directory-prefix=/tmp/wistcon-020 --cut-dirs=3 --recursive --no-parent http://HP-Max/wistcon/EL-100-020/wistcon-020_vers_1_0.tar
wait
echo "generate folder to extract"
mkdir /tmp/wistcon-020/extract
wait
echo "extracting ..."
cd /tmp/wistcon-020/
tar -xvf wistcon-020_vers_1_0.tar -C /tmp/wistcon-020/extract 
wait
echo "Copy webcontent to /var/www"
cp -rT /tmp/wistcon-020/extract/vers1_0/webcontent/ /var/www/
wait
echo "Copy firmware files to /usr/lib/cgi-bin"
cp -rT /tmp/wistcon-020/extract/vers1_0/firmware/ /usr/lib/cgi-bin/
wait


#Ask user what's next
read -p "Would you like to continue with change of uid gid of files? (y/n)? " RESP
if [ "$RESP" = "y" ]; then
	echo "change uid of install_setuidgid.sh"
	cd /tmp/wistcon-020/extract/vers1_0/startupservice/
	wait
	chmod o+x install_setuidgid.sh
	wait
	./install_setuidgid.sh
else
	echo "Installation stopped after copy of components from version server.\n"
	exit 1
fi
