
del shell rm -f /tmp/outPic.rgba
rd /s /q %~dp1024x600.rgba


adb push %~dp01024x600.rgba /tmp/

::adb push %~dp0../../G2dDemo /usr/bin
::adb shell chmod 777 /usr/bin/G2dDemo

adb shell sync
adb shell G2dDemo 8
adb shell sync

adb pull /tmp/outPic.rgba %~dp1024x600.rgba

pause

pause
