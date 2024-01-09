
del /s /q %~dp0720x1280video0_rote90.yuv
adb shell rm -r /tmp/out.yuv
adb push %~dp01280x720_video0.yuv /tmp/video0.yuv

::adb push %~dp0../../G2dDemo /usr/bin
::adb shell chmod 777 /usr/bin/G2dDemo

adb shell sync
adb shell G2dDemo 5
adb shell sync

adb pull /tmp/out.yuv %~dp0720x1280video0_rote90.yuv
pause

