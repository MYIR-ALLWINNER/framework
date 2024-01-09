adb shell rm /mnt/sdcard/mmcblk1p1/frontVideo0/*
adb shell ls /mnt/sdcard/mmcblk1p1/frontVideo0/

adb shell rm -f /recordTest
adb push %~dp0720p_recordTest.yuv /tmp/
adb push %~dp0recordTest /
adb shell chmod 777 /recordTest
adb shell /recordTest
adb shell ls /mnt/sdcard/mmcblk1p1/frontVideo0/
adb pull /tmp/recode_out.h264 %~dp0recode_out.h264
pause