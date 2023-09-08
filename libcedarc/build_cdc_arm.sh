#!/bin/bash
set -x
set -e

CDC_TOP=`pwd`

GNUEABI=gnueabi

#see libcedarc/library/ dir to conform
CDC_LIB=${LICHEE_CROSS_COMPILER}
HOST=${LICHEE_CROSS_COMPILER}

CDC_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx

OUT_GCC=${LICHEE_TOOLCHAIN_PATH}/bin/${LICHEE_CROSS_COMPILER}-gcc
OUT_CPP=${LICHEE_TOOLCHAIN_PATH}/bin/${LICHEE_CROSS_COMPILER}-g++

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

./configure --prefix=$CDC_INSTALL_DIR --host=$HOST CFLAGS="-DCONF_KERNEL_VERSION_5_4 -g" CPPFLAGS="-DCONF_KERNEL_VERSION_5_4 -g" LDFLAGS="-L$CDC_TOP/library/$CDC_LIB" 

echo "dbg1 end"

make -j32
make install -j32

cp -f $CDC_TOP/library/$CDC_LIB/*   $CDC_INSTALL_DIR/lib

cd -

echo "compile libcedarc finish"
