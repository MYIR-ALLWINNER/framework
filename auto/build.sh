#!/bin/bash
AUTO_XLIBS="$LICHEE_PLATFORM_DIR/framework/auto/t5_sdk_xlibs"

if [ "x" = "x$LICHEE_BR_OUT" ]; then
    echo "auto/build.sh:error LICHEE_BR_OUT string is empty"
	echo -e "\033[31mpls source .buildconfig first!\033[0m"
	exit
fi



SDK_PATH=$LICHEE_PLATFORM_DIR/framework/auto/sdk_lib 
LOCAL_PATH=$LICHEE_PLATFORM_DIR/framework/
rm -f $SDK_PATH/cedarx/include/external/include/adecoder/*
rm -f $SDK_PATH/cedarx/include/external/include/aencoder/*
#rm -f $SDK_PATH/cedarx/include/external/include/alsa/sound/*
rm -f $SDK_PATH/cedarx/include/external/include/adecoder/*
#rm -f $SDK_PATH/cedarx/include/external/include/libxml/*
#rm -f $SDK_PATH/cedarx/include/external/include/live/*
rm -f $SDK_PATH/cedarx/include/external/include/openssl/*
rm -f $SDK_PATH/cedarx/include/external/include/sdecoder/*
rm -f $SDK_PATH/cedarx/include/external/include/zlib/*
rm -f $SDK_PATH/cedarx/include/libcore/base/include/*
rm -f $SDK_PATH/cedarx/include/libcore/muxer/include/*
rm -f $SDK_PATH/cedarx/include/libcore/parser/include/*
rm -f $SDK_PATH/cedarx/include/libcore/playback/include/*
rm -f $SDK_PATH/cedarx/include/libcore/stream/include/*
rm -f $SDK_PATH/cedarx/include/xmetadataretriever/include/*
rm -f $SDK_PATH/cedarx/include/xplayer/include/*  

#yangtingrui addd begin
cd ./buildcedar
echo "yangtingrui add==111==$PWD"
#cd  $LOCAL_PATH/buildcedar/
./T113_cedar_compile.sh
cd -
echo "yangtingrui add=2222===$PWD"
#yangtingrui add end

cp -f $LOCAL_PATH/cedarx/external/include/adecoder/*	$SDK_PATH/cedarx/include/external/include/adecoder/
cp -f $LOCAL_PATH/cedarx/external/include/aencoder/*	$SDK_PATH/cedarx/include/external/include/aencoder/
cp -f $LOCAL_PATH/cedarx/external/include/alsa/sound/*	$SDK_PATH/cedarx/include/external/include/alsa/sound/
cp -f $LOCAL_PATH/cedarx/external/include/adecoder/*	$SDK_PATH/cedarx/include/external/include/adecoder/
cp -f $LOCAL_PATH/cedarx/external/include/libxml/*		$SDK_PATH/cedarx/include/external/include/libxml/
cp -f $LOCAL_PATH/cedarx/external/include/live/*		$SDK_PATH/cedarx/include/external/include/live/
cp -f $LOCAL_PATH/cedarx/external/include/openssl/*		$SDK_PATH/cedarx/include/external/include/openssl/
cp -f $LOCAL_PATH/cedarx/external/include/sdecoder/*	$SDK_PATH/cedarx/include/external/include/sdecoder/
cp -f $LOCAL_PATH/cedarx/external/include/zlib/*		$SDK_PATH/cedarx/include/external/include/zlib/
cp -f $LOCAL_PATH/cedarx/libcore/base/include/*			$SDK_PATH/cedarx/include/libcore/base/include/
cp -f $LOCAL_PATH/cedarx/libcore/muxer/include/*		$SDK_PATH/cedarx/include/libcore/muxer/include/
cp -f $LOCAL_PATH/cedarx/libcore/parser/include/*		$SDK_PATH/cedarx/include/libcore/parser/include/
cp -f $LOCAL_PATH/cedarx/libcore/playback/include/*		$SDK_PATH/cedarx/include/libcore/playback/include/
cp -f $LOCAL_PATH/cedarx/libcore/stream/include/*		$SDK_PATH/cedarx/include/libcore/stream/include/
cp -f $LOCAL_PATH/cedarx/xmetadataretriever/include/*	$SDK_PATH/cedarx/include/xmetadataretriever/include/
cp -f $LOCAL_PATH/cedarx/xplayer/include/*				$SDK_PATH/cedarx/include/xplayer/include/ 

rm -rf $SDK_PATH/cedarx/include/libcedarc/include/*
cp -f $LOCAL_PATH/libcedarc/include/* $SDK_PATH/cedarx/include/libcedarc/include/


cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/libsdk.so             $LICHEE_BR_OUT/target/usr/lib/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/libs/*                     $LICHEE_BR_OUT/target/usr/lib/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/cedarx/lib/*.so             $LICHEE_BR_OUT/target/usr/lib/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/cedarx/bin/*           	 $LICHEE_BR_OUT/target/usr/bin/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo/bin/* 					 $LICHEE_BR_OUT/target/usr/bin/
cp -rf $LICHEE_PLATFORM_DIR/framework/auto/rootfs/*                          $LICHEE_BR_OUT/target/

#libopenssl-1.1.1 libcrypto.so.1.1
cp $LICHEE_BR_OUT/build/libopenssl-1.1.1a/libcrypto.so.1.1 $LICHEE_BR_OUT/target/usr/lib/
cp $LICHEE_BR_OUT/build/libopenssl-1.1.1a/libssl.so.1.1 $LICHEE_BR_OUT/target/usr/lib/

if [ -d "$AUTO_XLIBS" ]; then
	make -C $AUTO_XLIBS
fi

make -C $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib 
if [ $? -ne 0 ]; then
	echo  "compile sdk_lib fail .... "
	exit 1
else
	cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/libs/*                     $LICHEE_BR_OUT/target/usr/lib/
fi

echo "compile sdk_demo"
make -C $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo/

if [ $? -ne 0 ]; then
	echo  "compile sdk_demo fail"
	exit 1
else
	cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo/bin/* 					 $LICHEE_BR_OUT/target/usr/bin/
fi
cd ..

#we only use libtinyalsa.so in /usr/lib,not the /lib
if [ -e "$LICHEE_BR_OUT/target/lib/libtinyalsa.so" ]; then
	rm $LICHEE_BR_OUT/target/lib/libtinyalsa.so
fi

if [ "x" != "x$QT_INSTALL_DIR"  -a "$LICHEE_PLATFORM" != "3rd" ]; then
	if [ -e $QT_INSTALL_DIR/bin/qmake ];then
		cd $LICHEE_PLATFORM_DIR/framework/auto/qt_demo
		./build.sh
		cp -vf $LICHEE_PLATFORM_DIR/framework/auto/qt_demo/CameraUI/bin/CameraUI $LICHEE_BR_OUT/target/usr/bin/
		cp -vf $LICHEE_PLATFORM_DIR/framework/auto/qt_demo/Launcher/bin/Launcher $LICHEE_BR_OUT/target/usr/bin/
		cp -vf $LICHEE_PLATFORM_DIR/framework/auto/qt_demo/MediaUI/bin/MediaUI $LICHEE_BR_OUT/target/usr/bin/
		cp -vf $LICHEE_PLATFORM_DIR/framework/auto/qt_demo/painting/affine/affine $LICHEE_BR_OUT/target/usr/bin/
		#HMI2.0
		cp -f ./MXAPP/mxapp2 $LICHEE_BR_OUT/target/usr/bin/
		mkdir $LICHEE_BR_OUT/target/usr/share/myir
		cp -r ./MXAPP/Music $LICHEE_BR_OUT/target/usr/share/myir/
		cp -r ./MXAPP/Video $LICHEE_BR_OUT/target/usr/share/myir/
		cp -r ./MXAPP/Capture $LICHEE_BR_OUT/target/usr/share/myir/
		mkdir $LICHEE_BR_OUT/target/usr/share/fonts/ttf/
		cp -r ./MXAPP/fonts/msyh.ttc $LICHEE_BR_OUT/target/usr/share/fonts/ttf/
		cp ./MXAPP/ecg/* $LICHEE_BR_OUT/target/usr/share/myir/
		cp -f ./hellogles3/hellogles3 $LICHEE_BR_OUT/target/usr/bin/
		cd -
		echo "build qt demo done."
	else
		echo "\033[33mWAR: there are no Qt libs, so skip to build qt_demo.  \033[0m"
	fi
fi

# build extern kernel 
#echo "=================build extern xr829========================"

#cd $LICHEE_PLATFORM_DIR/framework/auto/kernel/xr829
#make
#cd $LICHEE_PLATFORM_DIR

#XR_PATH=`find $LICHEE_PLATFORM_DIR/../out/ -name "xr829.ko" | grep target`

#path=${XR_PATH%xr829.ko}
#mv $path/xr829.ko $path/xr829_wep.ko
#cp -vf $LICHEE_PLATFORM_DIR/framework/auto/kernel/xr829/xr829.ko $XR_PATH
