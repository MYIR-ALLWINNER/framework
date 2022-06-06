#!/bin/sh

if [ "x" = "x$LICHEE_BR_OUT" ]; then
    echo "auto/build.sh:error LICHEE_BR_OUT string is empty"
	echo -e "\033[31mpls source .buildconfig first!\033[0m"
	exit
fi

cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/lib64/*                     $LICHEE_BR_OUT/target/usr/lib/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/cedarx/lib/*.so             $LICHEE_BR_OUT/target/usr/lib/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/cedarx/bin/*           	 $LICHEE_BR_OUT/target/usr/bin/
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo/bin/* 					 $LICHEE_BR_OUT/target/usr/bin/
cp -rf $LICHEE_PLATFORM_DIR/framework/auto/rootfs/*                          $LICHEE_BR_OUT/target/

cp -rf $LICHEE_PLATFORM_DIR/framework/auto/rootfs/etc/sshd_config                          $LICHEE_BR_OUT/target/etc/ssh/

make -C $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib 
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_lib/lib64/*                     $LICHEE_BR_OUT/target/usr/lib/

make -C $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo
cp -f $LICHEE_PLATFORM_DIR/framework/auto/sdk_demo/bin/* 					 $LICHEE_BR_OUT/target/usr/bin/

#we only use libtinyalsa.so in /usr/lib,not the /lib
if [ -e "$LICHEE_BR_OUT/target/lib/libtinyalsa.so" ]; then
	rm $LICHEE_BR_OUT/target/lib/libtinyalsa.so
fi

if [ "x" != "x$QT_INSTALL_DIR" ]; then
	if [ -e $QT_INSTALL_DIR/bin/qmake ];then
		cd $LICHEE_PLATFORM_DIR/framework/auto/qt_demo
		./build.sh
		cp -f ./CameraUI/CameraUI $LICHEE_BR_OUT/target/usr/bin/
		cp -f ./Launcher/bin/Launcher $LICHEE_BR_OUT/target/usr/bin/
		cp -f ./MediaUI/bin/MediaUI $LICHEE_BR_OUT/target/usr/bin/
		#HMI2.0
		cp -f ./MXAPP/mxapp2 $LICHEE_BR_OUT/target/usr/bin/
		mkdir $LICHEE_BR_OUT/target/usr/share/myir
		cp -r ./MXAPP/Music $LICHEE_BR_OUT/target/usr/share/myir/
		cp -r ./MXAPP/Video $LICHEE_BR_OUT/target/usr/share/myir/
		cp -r ./MXAPP/Capture $LICHEE_BR_OUT/target/usr/share/myir/
		mkdir $LICHEE_BR_OUT/target/usr/share/fonts/ttf/
		cp -r ./MXAPP/fonts/msyh.ttc $LICHEE_BR_OUT/target/usr/share/fonts/ttf/
		cp -r ./MXAPP/ecg $LICHEE_BR_OUT/target/usr/share/myir/
		cp -f ./hellogles3/hellogles3 $LICHEE_BR_OUT/target/usr/bin/


		cd -
		echo "build qt demo done."
	else
		echo "\033[33mWAR: there are no Qt libs, so skip to build qt_demo.  \033[0m"
	fi
fi
