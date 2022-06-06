#G2dDemo 5
arc=2  testid=5
****alloc_buffer->phy = 0xfe200000,alloc_buffer->vir = 0x7f9f0f3000
fopen /tmp/video0.yuv OK
alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=5
WritePicFileContent size=1382400
fopen /tmp/ck.yuv OK
****alloc_buffer->phy = 0xfe000000,alloc_buffer->vir = 0x7f9efa1000
alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=6
start g2dClipByFd rotate
g2dClipByFd rotate use time =1831000
WritePicFileContent size=1382400
fopen /tmp/out.yuv OK


要注意的是如果是旋转90，输出的长宽就不是1280x720，而是720*1280