./csitestT5 3 0 1280 720 ./ 4 10000 25
./csitestT5_ptr 3 0 1280 720 ./ 4 10000 25
3   	/dev/video3
0   	sel
w   	1280
h   	720
./  	path_name
4   	mode
10000  	test_cnt
25		fps


csi_test_mplane_usrptr.c   和  csi_test_mplane.c的不同点在于：
csi_test_mplane_usrptr.c 中cam使用的内存是用户空间（用DmaIon.h的接口）申请的，
所以链接的时候也要把DmaIon.o编出来链接进去。


要编译/清空usrptr版本的话使用如下命令：
make -f Makefile_usrptr 
make -f Makefile_usrptr clean


csi_test_mplane_64bit  是编译好的对应64位软件，用的是mmp方式，和csitestT5一样
csi_test_mplane_32bit  编译好的对应32位软件，用的是mmp方式


