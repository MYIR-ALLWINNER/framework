adb push %~dp0dmesg_catch /usr/bin/
adb shell chmod 777 /usr/bin/dmesg_catch
adb shell  dmesg_catch &
pause
