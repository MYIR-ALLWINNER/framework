adb push %~dp0../../sdk_lib/libs/libsdk_gifdecoder.so /usr/lib

adb push %~dp0test\. /tmp/

adb shell killall gif2rgb
adb push %~dp0gif2rgb /usr/bin
adb shell chmod 777 /usr/bin/gif2rgb

adb shell gif2rgb /tmp

adb pull /tmp/rainbow-0.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-1.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-2.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-3.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-4.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-5.rgb %~dp0\tmp\.
adb pull /tmp/rainbow-6.rgb %~dp0\tmp\.
pause
