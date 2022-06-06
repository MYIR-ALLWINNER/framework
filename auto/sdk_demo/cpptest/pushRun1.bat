adb push %~dp0cpptest /usr/bin/
adb shell chmod 777 /usr/bin/cpptest
adb shell  cpptest

pause