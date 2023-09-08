adb push %~dp0encoderTest /usr/bin
adb shell chmod 777 /usr/bin/encoderTest

rd /s /q %~dp0test_file\output\
adb shell rm -r /output/*
adb push %~dp0test_file/. /
adb shell mkdir /output/

adb shell sync
adb shell encoderTest -i /input/800x480.yuv -o /output/800x480.jpg -p 1 -f 1 -w 1 -t 1 
adb shell sync

adb pull /output/ %~dp0test_file\output\

pause
