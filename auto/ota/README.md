版本说明：
1、支持T113系列整包固件升级；
2、支持升级备份rootfs区的根文件系统；
3、增加了nand环境下烧写boot0及uboot；

使用步骤：
1、修改device/config/chips/t113/configs/evb1_auto/longan/sys_partition.fex，例如修改如下：
[partition]
    name         = rootfs
    size         = 2097152
    downloadfile = "rootfs.fex"
	user_type    = 0x8000

在private分区下增加：
[partition]
    name         = private
    size         = 32768
    ro           = 0
    user_type    = 0x8000
	
[partition]
    name         = rootfsbak
    size         = 2097152
    ;downloadfile = "rootfs1.fex"
    user_type    = 0x8000
	
2、将ota文件夹拷贝到platform/framework目录,并在该目录Make生成upgrade可执行文件；
3、将upgrade放在u盘或者SD卡或者直接推送到T113目标板根目录；
4、将out/t113_linux_evb1_auto_uart0.img放在与upgrade同级目录；
5、./upgrade t113_linux_evb1_auto_uart0.img mmcblk0p8 
6、当更新完毕，看到system OTA successfull!就表示更新成功；

说明：
目前的T113的rootfs在/dev/mmcblk0p5，分区，我们将新的固件更新到/dev/mmcblk0p8,在OTA成功后，在系统启动时，可以看到
RootDevice is "/dev/mmcblk0p8"
rootfsbak分区自定义，这里只是举例来说明！

