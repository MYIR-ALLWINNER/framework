memTest
可以只看打印，如果有sucess字样则表示成功
另外可以看memTest所在目录是否有a.out，这个a.out文件里内容应该全是0x5A

本应用只需链接 libsdk_memory.so 和 libcdx_ion.so 

需要用ion的地方可以是g2d,DE显示，VE编码等，
如果是编解码用，那么请使用memType=MEM_TYPE_CDX_NEW,因为编码器可能会需要用到ops参数
如果只是g2d或者显示，那么用MEM_TYPE_DMA即可。


如果要做DE显示的话，需要多链接一个libsdk_disp.so，参考MemTestDE.cpp和MakefileDE
也可以直接用如下命令编译带DE显示的版本：
make -f MakefileDE
生成的bin是memTestDE
测试方法：
直接不带参数运行memTest，正确执行的话显示屏上会输出纯色图片，对应的a.yuv图片也会存于memTest所在目录。

也可以带两个参数执行
memTestDE <y>  <c>
例如
memTestDE 20 200
memTestDE 20 20
不同的y c会显示不同颜色

也可以用pushDE.bat