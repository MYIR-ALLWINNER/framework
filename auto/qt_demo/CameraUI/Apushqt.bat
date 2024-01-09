adb shell killall CameraUI
adb push %~dp0CameraUI /
adb shell chmod 777 /CameraUI
pause