#!/bin/sh
set -e

if [ -d ./CameraUI ];then
	cd ./CameraUI
	make distclean 
	cd ../
fi

if [ -d ./Launcher ];then
	cd ./Launcher
	make distclean 
	cd ../
fi

if [ -d ./painting ];then
	cd ./painting
	make distclean 
	cd ../
fi

if [ -d ./MediaUI ];then
	cd ./MediaUI
	make distclean 
	cd ../
fi

if [ -d ./ui_qt_simple ];then
	echo "=====clean ui_qt_simple success!!!======"
	#cd ./ui_qt_simple
	#make distclean 
	#cd ../
fi

if [ -d ./MXAPP ];then
        cd ./MXAPP
        make distclean
        cd ../
fi

echo "clean done!"
