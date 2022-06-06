adb shell rm -f /audioenc_test
adb push %~dp0audioenc_test /
adb shell chmod 777 /audioenc_test
pause