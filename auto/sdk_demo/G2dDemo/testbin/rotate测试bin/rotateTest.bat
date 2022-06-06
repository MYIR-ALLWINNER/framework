adb push %~dp01280x720_video0.yuv /tmp/video0.yuv
adb shell sync
adb push %~dp0../../G2dDemo /usr/bin
adb shell chmod 777 /usr/bin/G2dDemo
adb shell G2dDemo 5

adb pull /tmp/out.yuv %~dp0out.yuv
pause

