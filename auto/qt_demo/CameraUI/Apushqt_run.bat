adb shell killall CameraUI
adb push %~dp0CameraUI /
adb shell chmod 777 /CameraUI
adb shell echo 0,0 > /sys/class/disp/disp/attr/fb2ui
adb shell FRAMEBUFFER=/dev/fb0 /CameraUI 0 &
adb shell echo CameraUI, > /sys/inputFocus/write
pause