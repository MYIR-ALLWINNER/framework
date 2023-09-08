adb shell rm -f /usr/bin/audioenc_test
adb push %~dp0audioenc_test /usr/bin/
adb shell chmod 777 /usr/bin/audioenc_test
pause