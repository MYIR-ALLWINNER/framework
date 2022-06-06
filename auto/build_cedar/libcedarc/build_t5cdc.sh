#!/bin/bash
set -x
set -e

CDC_TOP=`pwd`

#see libcedarc/library/ dir to conform
CDC_LIB=toolchain-sunxi-aarch64-glibc

CDC_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx

HOST=aarch64-linux-gnu

OUT_GCC=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-gcc'`
OUT_CPP=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-g\+\+'`

export CC=$OUT_GCC
export CXX=$OUT_GCC
export PATH=$LICHEE_BR_OUT/host/bin/:$PATH

#echo Compile Cedarc
cd $CDC_TOP
#if [ -f "Makefile" ]; then
#    make distclean
#fi
autoreconf -ivf
./bootstrap
./configure --prefix=$CDC_INSTALL_DIR --host=$HOST CFLAGS="-DCONF_KERNEL_VERSION_4_9 -g" CPPFLAGS="-DCONF_KERNEL_VERSION_4_9 -g" LDFLAGS="-L$CDC_TOP/library/$CDC_LIB" 
make -j32
make install -j32
cd -

echo "compile libcedarc finish"
