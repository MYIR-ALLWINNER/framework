#!/bin/sh
set -e

if [ -d ./CameraUI ];then
	cd ./CameraUI
	make distclean 
	./makeCameraUI
	echo "=====build CameraUI success!!!======"
	cd ../
fi

if [ -d ./Launcher ];then
	cd ./Launcher
	make distclean 
	./makeLauncher
	echo "=====build Launcher success!!!======"
	cd ../
fi

if [ -d ./MediaUI ];then
	cd ./MediaUI
	make distclean 
	./makeMediaUI
	echo "=====build MediaUI success!!!======"
	cd ../
fi

if [ -d ./MXAPP ];then
        cd ./MXAPP
        make distclean
        ./makeMXAPP
        echo "=====build MXAPP success!!!======"
        cd ../
fi

if [ -d ./hellogles3 ];then
	cd ./hellogles3
	make distclean
	./makegles3
	echo "=====build glfs2 success!!!======"
	cd ../
fi


if [ -d ./ui_qt_simple ];then
	cd ./ui_qt_simple
	make distclean 
	./makedvr
	echo "=====build ui_qt_simple success!!!======"
	cd ../
fi

echo "rebuildAll done!"
