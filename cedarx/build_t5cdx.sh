#!/bin/bash
set -x
set -e

CDX_TOP=`pwd`
CDC_TOP=$(cd $CDX_TOP/../libcedarc;pwd )

#see libcedarc/library/ dir to conform
CDC_LIB=toolchain-sunxi-aarch64-glibc
CDX_LIB=openwrt-aarch64-glibc

CDX_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx
CDC_INSTALL_DIR=$LICHEE_TOP_DIR/platform/framework/auto/sdk_lib/cedarx

HOST=aarch64-linux-gnu

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


OUT_GCC=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-gcc'`
OUT_CPP=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-g\+\+'`

export CC=$OUT_GCC
export CXX=$OUT_GCC
export PATH=$LICHEE_BR_OUT/host/bin/:$PATH

cd $CDX_TOP

autoreconf -ivf
./bootstrap 

./configure --prefix=$CDX_INSTALL_DIR --host=$HOST --enable-ssl CFLAGS="-D__ENABLE_ZLIB__ -g" CPPFLAGS="-D__ENABLE_ZLIB__ -g" LDFLAGS="-lcrypto -lz -L$CDX_TOP/external/lib64/$CDX_LIB -L$CDX_TOP/external/lib32/$CDX_LIB  -L$CDC_INSTALL_DIR/lib" 
make -j32
make install -j32
cd -
echo "compile cedarx finish!!!\npls check the update file in \n$CDX_INSTALL_DIR"

