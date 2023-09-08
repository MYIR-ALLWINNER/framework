adb shell rm -f /usr/bin/xplayerdemo
adb push %~dp0xplayerdemo /usr/bin/
adb shell chmod 777 /usr/bin/xplayerdemo
pause