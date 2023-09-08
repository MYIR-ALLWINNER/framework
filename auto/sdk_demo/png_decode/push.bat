adb push %~dp0png2bmptest /
adb push %~dp0test.png /
adb shell chmod 777 /png2bmptest
adb shell /png2bmptest test.png test.bmp
adb pull /test.bmp %~dp0
pause