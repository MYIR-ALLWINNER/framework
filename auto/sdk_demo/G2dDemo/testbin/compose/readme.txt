使用方法：
确保adb 正常，然后执行 cTest.bat

本地的4张720p的图片会被push到/tmp目录，然后合成之后会被pull回来，得到一张4合一的图片2560x1440_cvideo.yuv

C:\Windows>adb shell G2dDemo 3
arc=2  testid=3
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb690a000
fopen /tmp/video0.yuv OK
IonFlushCachefd!
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb67b8000
fopen /tmp/video1.yuv OK
IonFlushCachefd!
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb6666000
fopen /tmp/video2.yuv OK
IonFlushCachefd!
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb6514000
fopen /tmp/video3.yuv OK
IonFlushCachefd!
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/ck.yuv OK
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb5fce000
start trans 4x 720p to 1x 2560x1440 compose
end trans 4x 720p to 1x 2560x1440 compose time =9463000
WritePicFileContent size=5529600
IonFlushCachefd!
fopen /tmp/cvideo.yuv OK