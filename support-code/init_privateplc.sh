#!/bin/sh
# This shell script should enable the device tree overlay
# strasys.at
# Johannes Strasser
# Sep. 2nd 2014

slots="/sys/devices/bone_capemgr.9/slots"
echo strasys-homectrl >$slots

/usr/lib/cgi-bin/firmware












