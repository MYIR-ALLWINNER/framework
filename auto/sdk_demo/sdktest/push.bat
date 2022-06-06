adb shell rm -f /usr/bin/sdktest
adb push %~dp0sdktest /usr/bin
adb shell chmod 777 /usr/bin/sdktest 

pause