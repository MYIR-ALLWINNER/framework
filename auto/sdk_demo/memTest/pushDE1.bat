adb push %~dp0memTestDE /usr/bin
adb shell chmod 777 /usr/bin/memTestDE
adb shell /usr/bin/memTestDE 20 200
sleep 2
pause
