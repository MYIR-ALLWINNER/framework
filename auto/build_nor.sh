#!/bin/bash
AUTO_XLIBS="$LICHEE_PLATFORM_DIR/framework/auto/t5_sdk_xlibs"

if [ "x" = "x$LICHEE_BR_OUT" ]; then
    echo "auto/build.sh:error LICHEE_BR_OUT string is empty"
	echo -e "\033[31mpls source .buildconfig first!\033[0m"
	exit
fi



cp -rf $LICHEE_PLATFORM_DIR/framework/auto/rootfs/etc/*                          $LICHEE_BR_OUT/target/etc/
#cp -rf $LICHEE_PLATFORM_DIR/framework/auto/rootfs/usr/*                          $LICHEE_BR_OUT/target/usr/



