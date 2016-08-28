#!/bin/sh
# This shell script should enable the device tree overlay
#for EL-100-020-001 DIN-Rail-controller
# strasys.at
# Johannes Strasser
# August 25th 2016

slots="/sys/devices/bone_capemgr.9/slots"
echo strasys-wistcon >$slots

/usr/lib/cgi-bin/firmware

