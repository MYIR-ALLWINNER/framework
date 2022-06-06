编译cedarx & libcedarc
直接执行build_cedar.sh 就可以编译这两个多媒体库，先编libcedarc，后编cedarx
对应的编译脚本为
build_cedar/cedarx/build_t5cdx.sh
build_cedar/libcedarc/build_t5cdc.sh

对应t5linux平台的一些patch也会拷贝到相应目录然后自动打上。
这些patch有可能会被主分支采纳，有的不会。

执行过一次build_cedar.sh后，编译脚本和patch会被拷贝到相应目录，
所以也可以到相应的目录去单独执行编译：
cd platform/framework/libcedarc
./build_t5cdc.sh

cd platform/framework/cedarx
./build_t5cdx.sh