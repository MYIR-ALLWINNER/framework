adb shell killall MediaUI
adb push %~dp0bin/MediaUI /usr/bin/
adb shell chmod 777 /usr/bin/MediaUI
adb shell MediaUI
pause