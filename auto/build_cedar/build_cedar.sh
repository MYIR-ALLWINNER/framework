#!/bin/sh

if [ -d "$LICHEE_PLATFORM_DIR/framework/libcedarc" ]; then
	cp -f $LICHEE_PLATFORM_DIR/framework/auto/build_cedar/libcedarc/* $LICHEE_PLATFORM_DIR/framework/libcedarc/
	cd $LICHEE_PLATFORM_DIR/framework/libcedarc/
	for i in `find . -name "*.patch"` ;  
	do  
	echo "patch -t -p2 < $i ";
	patch -t -p2 < $i ;
	done
	./build_t5cdc.sh
fi

if [ -d "$LICHEE_PLATFORM_DIR/framework/cedarx" ]; then

	cp -f $LICHEE_PLATFORM_DIR/framework/auto/build_cedar/cedarx/* $LICHEE_PLATFORM_DIR/framework/cedarx/
	cd $LICHEE_PLATFORM_DIR/framework/cedarx/
	for i in `find . -name "*.patch"` ;  
	do  
	echo "patch -t -p1 < $i ";
	patch -t -p1 < $i ;
	done
	./build_t5cdx.sh
fi
