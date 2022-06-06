#!/bin/sh

# for adbd compatibilities
if  [ ! -d /system ];  then
    mkdir -p /system/bin
    ln -s /bin/sh /system/bin/sh
fi

# config adb function
KER_CONF="`grep '/sys/kernel/config' /proc/mounts`"
if  [ -z "$KER_CONF" ];  then
    mount -t configfs none /sys/kernel/config
fi

if  [ ! -d /sys/kernel/config/usb_gadget/g1 ];  then
    mkdir /sys/kernel/config/usb_gadget/g1
    mkdir /sys/kernel/config/usb_gadget/g1/strings/0x409
    mkdir /sys/kernel/config/usb_gadget/g1/functions/ffs.adb
    mkdir /sys/kernel/config/usb_gadget/g1/configs/c.1
    mkdir /sys/kernel/config/usb_gadget/g1/configs/c.1/strings/0x409
fi

echo "0x18d1" > /sys/kernel/config/usb_gadget/g1/idVendor
echo "0x0002" > /sys/kernel/config/usb_gadget/g1/idProduct

echo "0402101560" > /sys/kernel/config/usb_gadget/g1/strings/0x409/serialnumber
echo "Google.Inc" > /sys/kernel/config/usb_gadget/g1/strings/0x409/manufacturer
echo "Configfs ffs gadget" > /sys/kernel/config/usb_gadget/g1/strings/0x409/product

echo 0xc0 > /sys/kernel/config/usb_gadget/g1/configs/c.1/bmAttributes
echo 500 > /sys/kernel/config/usb_gadget/g1/configs/c.1/MaxPower

if  [ ! -L /sys/kernel/config/usb_gadget/g1/configs/c.1/ffs.adb ];  then
    ln -s /sys/kernel/config/usb_gadget/g1/functions/ffs.adb/ /sys/kernel/config/usb_gadget/g1/configs/c.1/ffs.adb
fi

if  [ ! -d /dev/usb-ffs ];  then
    mkdir /dev/usb-ffs
    mkdir /dev/usb-ffs/adb
fi

USB_FFS="`grep '/dev/usb-ffs/adb' /proc/mounts`"
if [ -z "$USB_FFS" ]; then
    mount -o uid=2000,gid=2000 -t functionfs adb /dev/usb-ffs/adb/
fi

# start adbd daemon
killall adbd
adbd &

# enable udc
cat /sys/bus/platform/drivers/otg\ manager/usbc0/usb_device
udc=`ls /sys/class/udc`
echo $udc > /sys/kernel/config/usb_gadget/g1/UDC
