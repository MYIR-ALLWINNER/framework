
del /s /q %~dp01280x720_dvideo0.yuv
del /s /q %~dp01280x720_dvideo1.yuv
del /s /q %~dp01280x720_dvideo2.yuv
del /s /q %~dp01280x720_dvideo3.yuv
adb shell rm -r /tmp/dvideo0.yuv
adb shell rm -r /tmp/dvideo1.yuv
adb shell rm -r /tmp/dvideo2.yuv
adb shell rm -r /tmp/dvideo3.yuv

adb push %~dp02560x1440_dcvideo.yuv /tmp/dcvideo.yuv

::adb push %~dp0../../G2dDemo /usr/bin
::adb shell chmod 777 /usr/bin/G2dDemo

adb shell sync
adb shell G2dDemo 2
adb shell sync

adb pull /tmp/dvideo0.yuv %~dp01280x720_dvideo0.yuv
adb pull /tmp/dvideo1.yuv %~dp01280x720_dvideo1.yuv
adb pull /tmp/dvideo2.yuv %~dp01280x720_dvideo2.yuv
adb pull /tmp/dvideo3.yuv %~dp01280x720_dvideo3.yuv

pause
