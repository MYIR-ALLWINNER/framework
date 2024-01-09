使用方法：
确保adb 正常，然后执行rotateTest.bat
输入的是1280x720_video0.yuv，输出得到旋转90度的720x1280video0_rote90.yuv


C:\Windows>adb shell G2dDemo 5
arc=2  testid=5
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb69a9000
fopen /tmp/video0.yuv OK
IonFlushCachefd!
alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=4
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/ck.yuv OK
dbg1 sunxi_ion_alloc_palloc
****alloc_buffer->phy = 0x0,alloc_buffer->vir = 0xb6857000
alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=5
start g2dClipByFd rotate
g2dClipByFd rotate use time =2035000
WritePicFileContent size=1382400
IonFlushCachefd!
fopen /tmp/out.yuv OK

C:\Windows>adb shell sync


要注意的是如果是旋转90，输出的长宽就不是1280x720，而是720*1280