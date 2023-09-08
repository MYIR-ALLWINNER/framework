使用方法：
确保adb 正常，然后执行dTest.bat
2560x1440_dcvideo.yuv会被push到机器中，然后经过拆分成4份图片
最后Pull回来，得到1280x720_dvideo0~3.yuv

C:\Windows>adb shell G2dDemo 2
arc=2  testid=2
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb65ff000
fopen /tmp/dcvideo.yuv OK
IonFlushCachefd!
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb64ad000
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb635b000
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb6209000
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb60b7000
start trans 1x [2560x1440]  to 4x [1280x720] to decompose
end trans 1x 2560x1440  to 4x 1280x720   time =9781000
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/dvideo0.yuv OK
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/dvideo1.yuv OK
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/dvideo2.yuv OK
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/dvideo3.yuv OK
ion_alloc_free failed, do not find virtual address: 0xb6209000