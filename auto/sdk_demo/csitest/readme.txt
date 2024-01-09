./csitestT113_ptr 0 0 1280 720 ./ 4 10000 25
3   	/dev/video3
0   	sel
w   	1280
h   	720
./  	path_name
4   	mode
100  	test_cnt
25		fps

csi_test_mplane_webcam.c ：适用于 uvc 设备的调试
csi_test_mplane_usrptr.c ：  适用于常规 csi 设备的调试，使用的内存为用户空间申请
csi_test_mplane.c： 适用于常规 csi 设备的调试，使用的内存为 mmap

这里使用的 Makefile 默认是编译 csi_test_mplane_usrptr.c ，如果需要编译或者情况 mmap 版本的，使用如下命令：
make -f Makefile_mmap 
make -f Makefile_mmap clean

4# cat /sys/class/disp/disp/attr/sys
screen 0:
de_rate 300000000 hz, ref_fps:61
mgr0: 1024x600 fmt[rgb] cs[0x204] range[full] eotf[0x4] bits[8bits] err[0] force_sync[0] unblank direct_show[false] iommu[1]
dmabuf: cache[0] cache max[0] umap skip[0] overflow[3]
        lcd output      backlight( 50)  fps:60.6        1024x 600
        err:0   skip:378        irq:347000      vsync:343336    vsync_skip:588
   BUF    enable ch[0] lyr[0] z[1] prem[N] a[globl 255] fmt[ 77] fb[1280, 720; 640, 360; 640, 360] crop[   0,   0,1280, 720] frame[   0,   0,1024, 600] addr[  b00000,       0,       0] flags[0x       0] trd[0,0]
depth[ 0]    BUF    enable ch[1] lyr[0] z[16] prem[N] a[pixel 255] fmt[  0] fb[1024, 600;1024, 600;1024, 600] crop[   0,   0,1024, 600] frame[   0,   0,1024, 600] addr[       0,       0,       0] flags[0x       0] trd[0,0]


 