./csi_test_mplane_de_64bit 5 0 1280 720 ./ 1 10000 25

直接在此目录执行make可以进行全部编译，也可以进入到子目录去执行make,编译成功后会默认拷贝到此目录的bin/下
(bin/下的东西不会自动拷贝到out，需要执行上一层的build.sh，或者到根目录执行./build.sh)

执行make clean执行清除生成文件和过程文件的命令。

此sdk_demo大部分的demo都依赖于../sdk_lib/lib64和../sdk_lib/cedarx/lib目录下的so。

每个子demo都有对应的readme.txt以及用adb执行的脚本，如果不会使用，请先参考这两个文件。


