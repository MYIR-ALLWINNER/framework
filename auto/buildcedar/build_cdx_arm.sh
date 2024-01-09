#!/bin/bash
set -x
set -e

CDX_TOP=`pwd`
CDC_TOP=$(cd $CDX_TOP/../libcedarc;pwd )

#see libcedarc/library/ dir to conform
CDC_LIB=${LICHEE_CROSS_COMPILER}
CDX_LIB=${LICHEE_CROSS_COMPILER}
HOST=${LICHEE_CROSS_COMPILER}

CDX_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx
CDC_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx

if [ "x" = "x$LICHEE_BR_OUT" ]; then
    echo "cdx build.sh:error LICHEE_BR_OUT string is empty"
	echo -e "\033[31mpls source .buildconfig first\033[0m"
	echo "or you need to point out where to search gcc"
	exit
fi

if [ $# -eq 1 ]; then
	if [ "$1" = "-f" ]; then
		echo "make distclean"
		make distclean
	elif [ "$1" = "clean" ]; then
		echo "make distclean then exit"
		make distclean
		exit 
	fi 	
fi 

OUT_GCC=${LICHEE_TOOLCHAIN_PATH}/bin/${LICHEE_CROSS_COMPILER}-gcc
OUT_CPP=${LICHEE_TOOLCHAIN_PATH}/bin/${LICHEE_CROSS_COMPILER}-g++

export CC=$OUT_GCC
export CXX=$OUT_GCC
export PATH=$LICHEE_BR_OUT/host/bin/:$PATH

cd $CDX_TOP

autoreconf -ivf
./bootstrap 

./configure --prefix=$CDX_INSTALL_DIR --host=$HOST CFLAGS="-D__ENABLE_ZLIB__  -DFILE_STREAM_ENABLE -g" CPPFLAGS="-D__ENABLE_ZLIB__  -DCONF_KERNEL_VERSION_5_4 -g" LDFLAGS="-lcrypto -lz -L$CDX_TOP/external/lib32/$CDX_LIB -L$CDX_TOP/external/lib32/$CDX_LIB  -L$CDC_INSTALL_DIR/lib" 
make -j32
make install -j32
cd -
echo "compile cedarx finish!!!"
echo "pls check the update file in"
echo "$CDX_INSTALL_DIR"