adb push %~dp01024x600.rgba /tmp/
adb push %~dp0../../G2dDemo /usr/bin
adb shell chmod 777 /usr/bin/G2dDemo
adb shell G2dDemo 8
adb pull /tmp/outPic.rgba %~dp0outPic.rgba
adb shell rm -f /tmp/outPic.rgba
pause

pause
