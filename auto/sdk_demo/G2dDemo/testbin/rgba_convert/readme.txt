使用方法：
确保adb 正常，然后执行 conv_test.bat
本地的1024x600.rgba会被push到机器中
机器执行后会吧图片进行翻转，然后pull回到本地名为1024x600_conv.rgba
对比输入输出即可。





C:\Windows>adb shell G2dDemo 8
arc=2  testid=8
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb68dd000
fopen /tmp/1024x600.rgba OK
IonFlushCachefd!
alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=4
WritePicFileContent size=2457600
IonFlushCachefd!
fopen /tmp/ck.yuv OK
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb6685000
alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=5
start g2dflip:RGBA v flip
RGBA v flip use time =2945000
WritePicFileContent size=2457600
IonFlushCachefd!
fopen /tmp/outPic.rgba OK

C:\Windows>adb shell sync