adb shell rm -f /xplayerdemo
adb push %~dp0xplayerdemo /
adb shell chmod 777 /xplayerdemo
pause