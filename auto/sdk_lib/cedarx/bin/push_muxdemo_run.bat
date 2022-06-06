adb push %~dp0muxdemo /usr/bin
adb push %~dp0720p.yuv /tmp
adb shell chmod 777 /usr/bin/muxdemo
adb shell muxdemo -i /tmp/720p.yuv -n 100 -f 0 -s 720 -d 720 -m /tmp/muxtest_720.H264.mp4
adb pull /tmp/muxtest_720.H264.mp4 %~dp0muxtest_720.H264.mp4
pause

