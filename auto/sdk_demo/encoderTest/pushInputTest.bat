::adb push %~dp0../../sdk_lib/libs_hf/libsdk_encoder.so /usr/lib

adb shell killall encoderTest

adb push %~dp0encoderTest /usr/bin
adb shell chmod 777 /usr/bin/encoderTest

rd /s /q %~dp0test_file\output\
adb shell rm -r /tmp/output/*
adb push %~dp0test_file/. /tmp/
adb shell mkdir /tmp/output/

adb shell sync
adb shell encoderTest -i /tmp/input/800x480x93_nv21.yuv -o /tmp/output/800x480x93_nv21  -p 1 -f 0 -w 0 -t 1 
adb shell sync

adb pull /tmp/output/ %~dp0test_file\output\

pause
