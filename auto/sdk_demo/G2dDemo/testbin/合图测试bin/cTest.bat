adb shell rm /tmp/*.yuv
adb push %~dp01280x720_video0.yuv /tmp/video0.yuv
adb push %~dp01280x720_video1.yuv /tmp/video1.yuv
adb push %~dp01280x720_video2.yuv /tmp/video2.yuv
adb push %~dp01280x720_video3.yuv /tmp/video3.yuv
adb push %~dp0../../G2dDemo /usr/bin
adb shell chmod 777 /usr/bin/G2dDemo
adb shell G2dDemo 3

adb pull /tmp/cvideo.yuv %~dp02560x1440_cvideo.yuv


pause