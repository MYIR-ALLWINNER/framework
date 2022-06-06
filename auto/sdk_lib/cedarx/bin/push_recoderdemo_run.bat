adb push %~dp0recorderdemo /tmp
adb push %~dp0720p.yuv /tmp
adb push %~dp0lss.wav /tmp
adb shell chmod 777 /tmp/recorderdemo
adb shell source /qt5.9.sh 
adb shell /tmp/recorderdemo /tmp/720p.yuv /tmp/lss.wav
adb pull /tmp/save.mp4 %~dp0save.mp4
pause

