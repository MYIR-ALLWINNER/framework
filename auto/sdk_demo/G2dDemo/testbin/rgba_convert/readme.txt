#adb shell G2dDemo 8
arc=2  testid=8
****alloc_buffer->phy = 0xfe800000,alloc_buffer->vir = 0x7f860e8000
fopen /tmp/1024x600.rgba OK
alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=5
WritePicFileContent size=2457600
fopen /tmp/ck.yuv OK
****alloc_buffer->phy = 0xfe400000,alloc_buffer->vir = 0x7f85e90000
alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=6
start g2dflip:RGBA v flip
RGBA v flip use time =2914000  
WritePicFileContent size=2457600
fopen /tmp/outPic.rgba OK