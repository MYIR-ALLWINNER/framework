adb shell killall CameraUI
adb push %~dp0CameraUI /usr/bin/
adb shell chmod 777 /usr/bin/CameraUI
pause