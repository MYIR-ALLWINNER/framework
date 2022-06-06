#!/bin/sh
### BEGIN INIT INFO
# Provides: banner
# Required-Start:
# Required-Stop:
# Default-Start:     S
# Default-Stop:
### END INIT INFO

echo "System update start ..."
#echo  V > /dev/watchdog0
#find / -name "Manfest"
#if grep "update_emmc" /proc/cmdline > /dev/null;then
#    echo "Update for eMMC flash"
#	flash_emmc.sh
#elif grep "update_nand" /proc/cmdline > /dev/null;then
#    echo "Update for NAND flash"
#	flash_nand.sh
#else
#    echo "Update failed! Please restart and enter update process."
#    exit 0
#fi
#需要在此脚本里进行分区操作

do_paratition()
{
	echo "start paratition ..."
	parted -s /dev/mmcblk0 mklabel gpt &> /dev/null
	parted /dev/mmcblk0 mkpart boot-resource fat16 37.7M 71.3MB &> /dev/null
	parted /dev/mmcblk0 mkpart env fat16 71.3MB 88.1MB &> /dev/null
	parted /dev/mmcblk0 mkpart boot fat16 88.1MB 155MB &> /dev/null
	parted /dev/mmcblk0 mkpart rootfs ext4 155MB 2303MB &> /dev/null
	parted /dev/mmcblk0 mkpart rootfsbak ext4 2303MB 4450MB &> /dev/null
	parted /dev/mmcblk0 mkpart recovery fat16 4450MB 4568MB &> /dev/null
	parted /dev/mmcblk0 mkpart private fat16 4568MB 4585MB &> /dev/null
	parted /dev/mmcblk0 mkpart userfs ext4 4585MB 7085MB &> /dev/null
	sleep 1
	echo "start format paratition ..."
	if [ -b /dev/mmcblk0p4 ];then
		mkfs.ext4 /dev/mmcblk0p4 &> /dev/null
	fi
	if [ -b /dev/mmcblk0p5 ];then
		mkfs.ext4 /dev/mmcblk0p5 &> /dev/null
	fi
	if [ -b /dev/mmcblk0p8 ];then
		mkfs.ext4 /dev/mmcblk0p8 &> /dev/null
	fi
}

if [ $(dmesg | grep -c "nand: device found")  == 1 ]
then
        echo "Update for NAND flash"
        flash_nand.sh
else
        echo "Update for EMMC flash"
		do_paratition
		sleep 1
        flash_emmc.sh
fi
