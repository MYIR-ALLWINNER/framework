#!/bin/sh
#  LICHEE_TOP_DIR   =/home/yuanguochao/other/t5_bak/longan
#  LICHEE_BR_OUT    =/home/yuanguochao/other/t5_bak/longan/out/t507/demo2.0/longan/buildroot
#  GPU include      =$LICHEE_TOP_DIR/platform/core/graphics/gpu_um_pub/mali-bifrost/include
#  GPU lib			=$LICHEE_TOP_DIR/platform/core/graphics/gpu_um_pub/mali-bifrost/fbdev/mali-g31/aarch64-linux-gnu/lib/
#  SYSROOT  		=$LICHEE_BR_OUT/out/t507/demo2.0/longan/buildroot/host/usr/aarch64-buildroot-linux-gnu/sysroot/



PWD=`pwd`
export QT_SRC_DIR=$PWD
source $PWD/bin/export_gcc484.sh

#export QT_GPU_LIB=$LICHEE_TOP_DIR/platform/core/graphics/gpu_um_pub/mali-bifrost/fbdev/mali-g31/aarch64-linux-gnu/lib
#export QT_GPU_INC=$LICHEE_TOP_DIR/platform/core/graphics/gpu_um_pub/mali-bifrost/include

#export SYSROOT=$LICHEE_TOP_DIR/out/t507/demo2.0/longan/buildroot/host/usr/aarch64-buildroot-linux-gnu/sysroot
export SYSROOT=$LICHEE_TOP_DIR/out/${LICHEE_IC}/evb1_auto/longan/buildroot/host/arm-buildroot-linux-gnueabi/sysroot
export PATH=$LICHEE_BR_OUT/host/bin/:$PATH
#export CROSS_COMPILE=$LICHEE_TOP_DIR/out/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu
#./${LICHEE_IC}/${LICHEE_BOARD}/ICHEE_LINUX_DEV/buildroot/host/opt/ext-toolchain/bin/arm-linux-gnueabi-gcc
export CROSS_COMPILE_DIR=$LICHEE_TOP_DIR/out/${LICHEE_IC}/${LICHEE_BOARD}/${ICHEE_LINUX_DEV}/buildroot/host/opt/ext-toolchain/bin/
export CROSS_COMPILE=$CROSS_COMPILE_DIR/arm-linux-gnueabi-

export CPLUS_INCLUDE_PATH=$PWD/qtbase/src/3rdparty/angle/include:$CPLUS_INCLUDE_PATH

QT_ENV_CFG=qtenv.sh
QT_ENV_TARGET_DIR=$LICHEE_PLATFORM_DIR/framework/auto/rootfs/etc

sed -i '/^export  QTDIR*/d' $QT_ENV_CFG
sed -i '1 a \export  QTDIR='$QT_RUN_DIR'' $QT_ENV_CFG

HOST=arm-linux-gnueabi

OUT_GCC=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-gcc'`
OUT_CPP=`find ${LICHEE_BR_OUT} -perm /a+x -a -regex '.*-g\+\+'`

export CC=$OUT_GCC
export CXX=$OUT_GCC

cpu_cores=`cat /proc/cpuinfo | grep "processor" | wc -l`
if [ ${cpu_cores} -le 8 ] ; then
	LICHEE_JLEVEL=${cpu_cores}
else
	LICHEE_JLEVEL=${cpu_cores}
fi

#env

function cdqtroot
{
cd $QT_SRC_DIR
}
#-no-c++11
function qtmakeconfig
{
	#cp $QT_GPU_LIB/* $SYSROOT/lib/ -rf
	mkdir -p $QT_INSTALL_DIR

	$QT_SRC_DIR/configure \
		-opensource \
		-confirm-license \
		-extprefix $QT_INSTALL_DIR \
		-sysroot $SYSROOT \
		-xplatform arm-linux-gnueabi-g++ \
		-device-option CROSS_COMPILE=$CROSS_COMPILE \
		-R /usr/lib \
		-no-strip \
		-c++std c++11 \
		-shared \
		-nomake examples \
		-accessibility \
		-no-sql-db2 -no-sql-ibase -no-sql-mysql -no-sql-oci \
		-no-sql-odbc -no-sql-psql -no-sql-sqlite2  -no-sql-tds \
 		-no-sql-sqlite -plugin-sql-sqlite \
		-no-qml-debug \
		-no-sse2 \
		-no-sse3 \
		-no-ssse3 \
		-no-sse4.1 \
		-no-sse4.2 \
		-no-avx \
		-no-avx2 \
		-no-mips_dsp \
		-no-mips_dspr2 \
		-qt-zlib \
		-no-journald \
		-qt-libpng \
		-qt-libjpeg \
		-qt-freetype \
		-qt-harfbuzz \
		-no-openssl \
		-no-xcb-xlib \
		-no-glib \
		-no-pulseaudio \
		-alsa \
		-gui \
		-widgets \
		-v \
		-optimized-qmake \
		-no-cups \
		-no-iconv \
		-evdev \
		-no-icu \
		-no-fontconfig \
		-no-strip \
		-pch \
		-dbus \
		-no-use-gold-linker \
		-no-directfb \
		-eglfs \
		-qpa eglfs \
		-linuxfb \
		-no-kms \
		-opengl es2 \
		-no-system-proxies \
		-no-slog2 \
		-no-pps \
		-no-imf \
		-no-lgmon \
		-no-tslib 
}

function qtmakeall
{
	make  -j${LICHEE_JLEVEL} -C $QT_SRC_DIR
}

function qtmakeinstall
{
	make  -j${LICHEE_JLEVEL} -C $QT_SRC_DIR install
	mkdir -p $QT_TARGET_DIR

	#cp libs to target
	cp -rf \
	$QT_INSTALL_DIR/lib $QT_INSTALL_DIR/plugins $QT_INSTALL_DIR/qml \
	 $QT_TARGET_DIR
	#cp fonts to target
	cp -rf fonts $QT_TARGET_DIR 
	#Remove redundant files
	rm -rf $QT_TARGET_DIR/lib/cmake
	rm -rf $QT_TARGET_DIR/lib/pkgconfig
	rm -rf $QT_TARGET_DIR/lib/*.a
	rm -rf $QT_TARGET_DIR/lib/*.prl
	rm -rf $QT_TARGET_DIR/lib/*.la
	
	#cp $QT_GPU_LIB/* $LICHEE_BR_OUT/target/usr/lib/ -rf
	
	cp $QT_ENV_CFG $QT_ENV_TARGET_DIR
}

function qtmakecleanall
{
	cd $QT_SRC_DIR
	make distclean -j${LICHEE_JLEVEL}
	make -C $QT_SRC_DIR clean -j${LICHEE_JLEVEL}
	rm -rf $QT_INSTALL_DIR
	rm -rf $QT_TARGET_DIR
	
}

echo "  "
echo "********************** useage ***************************"
echo "        please use:"
echo "        qtmakeconfig:         config qt env."
echo "        qtmakeall:            build qt"
echo "        qtmakeinstall:        install qt-lib and cp to target dir."
echo "        qtmakecleanall:       clean qt and rm all target."
echo "        QT_INSTALL_DIR:       " $QT_INSTALL_DIR
echo "        QT_TARGET_DIR:       " $QT_TARGET_DIR
echo "        qtmakecleanall:       clean qt and rm all target."
echo "  "
