#!/bin/sh
#set -e

if [ -d ./CameraUI ]; then
	cd ./CameraUI
	if [ -f ./Makefile ]; then
		make distclean
	fi
	./makeCameraUI
	result=$?
	if [ ${result} -eq 0 ]; then
		echo "=====build CameraUI success!!!======"
	else
		echo "=====build CameraUI failed!!!======"
	fi
	cd ../
fi

if [ -d ./Launcher ]; then
	cd ./Launcher
	if [ -f ./Makefile ]; then
		make distclean
	fi
	./makeLauncher
	result=$?
	if [ ${result} -eq 0 ]; then
		echo "=====build Launcher success!!!======"
	else
		echo "=====build Launcher failed!!!======"
	fi
	cd ../
fi

if [ -d ./MediaUI ]; then
	cd ./MediaUI
	if [ -f ./Makefile ]; then
		make distclean
	fi
	./makeMediaUI
	result=$?
	if [ ${result} -eq 0 ]; then
		echo "=====build MediaUI success!!!======"
	else
		echo "=====build MediaUI failed!!!======"
	fi
	cd ../
fi

if [ -d ./ui_qt_simple ]; then
	#cd ./ui_qt_simple
	#make  distclean
	#./makedvr
	echo "=====build ui_qt_simple success!!!======"
	#cd ../
fi

if [ -d ./painting ]; then
	cd ./painting
	if [ -f ./Makefile ]; then
		make distclean
	fi
	./makepainting
	result=$?
	if [ ${result} -eq 0 ]; then
		echo "=====build makepainting success!!!======"
	else
		echo "=====build makepainting failed!!!======"
	fi
	cd ../
fi

echo "rebuildAll done!"
