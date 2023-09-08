adb push %~dp0memTestDE /usr/bin
adb shell chmod 777 /usr/bin/memTestDE
adb shell /usr/bin/memTestDE 
sleep 2
adb shell /usr/bin/memTestDE 20 200
sleep 2
adb shell /usr/bin/memTestDE 20 250
sleep 2
adb shell /usr/bin/memTestDE 20 20
sleep 2
adb shell /usr/bin/memTestDE 70 20
pause
