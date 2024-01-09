adb shell killall MediaUI
adb push %~dp0bin/MediaUI /
adb shell chmod 777 /MediaUI
adb shell /MediaUI
pause