adb shell killall Launcher
adb push %~dp0bin/Launcher /usr/bin/
adb shell chmod 777 /usr/bin/Launcher
pause