#!/bin/sh
# Set the correct uid and gid of files
# Johannes Strasser
# 1.1.2016
# www.strasys.at
#


#
#Add later the chowner process where needed
#

read -p "Would you like to continue with disabeling of services? (y/n)? " RESP
if [ "$RESP" != "y" ]; then
  exit 1
fi

