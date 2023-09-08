adb shell killall decoderTest
adb push %~dp0decoderTest /usr/bin
adb shell chmod 777 /usr/bin/decoderTest
::adb push %~dp0decoderTest /usr/bin

rd /s /q %~dp0test_file\output\
adb shell rm -r /tmp/output/*
::adb push %~dp0test_file\input\. /tmp/
adb shell mkdir /tmp/output/

adb shell sync
adb shell decoderTest
adb shell sync

adb pull /tmp/output/ %~dp0test_file\output\

pause
