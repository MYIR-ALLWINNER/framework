#!/bin/sh

echo "/dev/mmcblk1p1" > /sys/class/android_usb/android0/f_mass_storage/lun/file
echo 0 > /sys/class/android_usb/android0/enable
echo 1f3a > /sys/class/android_usb/android0/idVendor
echo 100D > /sys/class/android_usb/android0/idProduct
echo mass_storage > /sys/class/android_usb/android0/functions
echo 1 > /sys/class/android_usb/android0/enable