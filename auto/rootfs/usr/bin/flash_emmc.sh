#!/bin/sh

#BLUE置低是亮
#gpio -s PD22 1 0 0 0
#Green置低是亮
#gpio -s PH10 1 0 0 0
#buzzer置低是响
#gpio -s PH8 1 0 0 0
#正常烧录过程中：green秒闪，blue常亮，buzzer无声
#烧录出错时：green灭，blue狂闪，buzzer有声
#正常烧录完：green亮，blue亮，buzzer无声

imagedir=/root/mfgimages
. ${imagedir}/Manifest
fslfile=${imagedir}/${fslfile}
bootresourcefile=${imagedir}/${bootresourcefile}
envfile=${imagedir}/${envfile}
bootfile=${imagedir}/${bootfile}
rootfsfile=${imagedir}/${rootfsfile}

echo "Update file list:"
echo "fslfile file: ${fslfile}"
echo "bootresourcefile file: ${bootresourcefile}"
echo "envfile file: ${envfile}"
echo "ubootfile file: ${ubootfile}"
echo "rootfsfile file: ${rootfsfile}"
echo "LED name: ${ledname}"

bootpart=""
vendorpart=""
rootpart=""
userpart=""

led_blue()
{
	if [ "$1" == "on" ];
	then
		gpio -s PD22 1 0 0 0
	else
		gpio -s PD22 1 1 0 0
	fi
}

led_green()
{
	if [ "$1" == "on" ];
	then
		gpio -s PH10 1 0 0 0
	else
		gpio -s PH10 1 1 0 0
	fi
}

buzzer_onoff()
{
	if [ "$1" == "on" ];
	then
		gpio -s PH8 1 0 0 0
	else
		gpio -s PH8 1 1 0 0
	fi

}

update_start()
{
	echo "Update starting..."
	#echo heartbeat > /sys/class/leds/user/trigger
	#while true;do
	#	echo "Updating..."
	#	sleep 1
	#	echo "Updating..."
	#	sleep 1
	#done
}

update_success()
{
	kill $PID_START
    #echo 1 > /sys/class/leds/heartbeat/brightness
    #echo 0 > /sys/class/leds/heartbeat/brightness   
	led_blue on
	led_green on
	buzzer_onoff off
    echo "Update complete..."
    echo "************************************************"
    echo "********** System update successfully **********"
    echo "*****************系统成功烧录完成 **************"
    echo
}

update_fail()
{
	kill $PID_START
	#echo 1 > /sys/class/leds/heartbeat/brightness 	
	echo $'>>>[86]{\"step\":\"firmware\",\"result\":{\"bootloader\":\"2\",\"kernel\":\"2\",\"rootfs\":\"2\",\"data\":\"2\"}}\r\n'
	sleep 1
	while true;do
		echo "Update failed..."
		buzzer_onoff on
		sleep 1
		echo "Update failed..."
		buzzer_onoff off
		sleep 1
	done
}

cmd_check()
{
	if [ $1 -ne 0 ];then
		echo "$2 failed!"
		echo
		update_fail
	fi
}

check_file()
{
	if [ ! -s $1 ];then
		echo "invalid imagefile $1"
		echo
		update_fail
	fi
}

if grep "root" /proc/cmdline > /dev/null;then
	echo
	echo "***********************************************"
	echo "*************    SYSTEM UPDATE    *************"
	echo "***********************************************"
	echo
else
	echo "Normal boot"
	exit 0
fi

update_start &
LED_PID=$!
# if echo ${ledname} | egrep -q '^[0-9]+$'; then
	# update_start_gpioled &
	# LED_PID=$!
# else
	# update_start_nameled &
	# LED_PID=$!
# fi


STEP=1
TOTAL_STEPS=8
if [ -s $datafile ];then
    TOTAL_STEPS=8
fi

echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Check image files in $imagedir ... "
check_file $fslfile
check_file $bootresourcefile
check_file $envfile
check_file $bootfile
check_file $rootfsfile
echo "OK"
echo

let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Checking Rootfs device: "
DRIVE="/dev/mmcblk0"
echo OK
echo

# 刷写fsl文件
let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Write fslfile ..."
#echo 0 > /sys/class/block/mmcblk1boot0/force_ro
#echo 0 > /sys/class/block/mmcblk1boot1/force_ro
#cmd_check $? "Write tf-a to eMMC"
#dd if=${tfafile} of=/dev/mmcblk1boot0 bs=1M conv=fsync > /dev/null 2>&1
#dd if=${tfafile} of=/dev/mmcblk1boot1 bs=1M conv=fsync > /dev/null 2>&1
#cmd_check $? "Update tf-a"
#echo 1 > /sys/class/block/mmcblk1boot0/force_ro
#echo 1 > /sys/class/block/mmcblk1boot1/force_ro
dd if=${fslfile} of=/dev/mmcblk0 bs=1M conv=fsync > /dev/null 2>&1
cmd_check $? "Update fsl boot"
sleep 1
sync
echo OK
echo

#刷写bootresourcefile
let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Write bootresourcefile ..."
cmd_check $? "Write bootresourcefile to eMMC"
dd if=${bootresourcefile} of=/dev/mmcblk0p1 bs=1M conv=fsync > /dev/null 2>&1
cmd_check $? "Update bootresourcefile"
sleep 1
sync
echo OK
echo

#刷写envfile
let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Write envfile ..."
cmd_check $? "Write envfile to eMMC"
dd if=${envfile} of=/dev/mmcblk0p2 bs=1M conv=fsync > /dev/null 2>&1
cmd_check $? "Update envfile"
sleep 1
sync
echo OK
echo $'>>>[92]{\"step\":\"firmware\",\"result\":{\"bootloader\":\"0\",\"kernel\":\"255\",\"rootfs\":\"255\",\"data\":\"255\"}}\r\n'
echo

mmc bootpart enable 1 1 /dev/mmcblk0
#cmd_check $? "Enable boot partion 1 to boot"
sleep 1


#刷写 kernel
let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Write  kernel ..."
cmd_check $? "Write  kernel to eMMC"
dd if=${bootfile} of=/dev/mmcblk0p3 bs=10M conv=fsync > /dev/null 2>&1
cmd_check $? "Update  kernel"
sleep 1
sync
echo OK
echo $'>>>[90]{\"step\":\"firmware\",\"result\":{\"bootloader\":\"0\",\"kernel\":\"0\",\"rootfs\":\"255\",\"data\":\"255\"}}\r\n'
echo

let STEP=STEP+1
#umount /dev/${rootpart}
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Copy rootfs files ... "
mkfs.ext4 -F -L "rootfs" /dev/mmcblk0p4 > /dev/null 2>&1
cmd_check $? "Write  rootfs to eMMC"
dd if=${rootfsfile} of=/dev/mmcblk0p4 bs=10M conv=fsync > /dev/null 2>&1
cmd_check $? "Write  rootfs to eMMC"
sync
echo OK
echo $'>>>[88]{\"step\":\"firmware\",\"result\":{\"bootloader\":\"0\",\"kernel\":\"0\",\"rootfs\":\"0\",\"data\":\"255\"}}\r\n'
echo


let STEP=STEP+1
echo -n "[ ${STEP} / ${TOTAL_STEPS} ] Copy userfs files ... "
#mkfs.ext4 -F -L "userfs" /dev/mmcblk1p5 > /dev/null 2>&1
#mkdir -p /run/media/${userpart}
#mount -t ext4 -o rw,noatime,nodiratime /dev/${userpart} /run/media/${userpart}
#dd if=${userfsfile} of=/dev/mmcblk1p5 bs=10M conv=fsync > /dev/null 2>&1
sleep 1
sync
echo OK
echo $'>>>[86]{\"step\":\"firmware\",\"result\":{\"bootloader\":\"0\",\"kernel\":\"0\",\"rootfs\":\"0\",\"data\":\"0\"}}\r\n'
echo

update_success

