
export  QTDIR=/usr/local/Qt_5.12.5
if [ -d $QTDIR ];then

	export  QT_ROOT=$QTDIR
	export  PATH=$QTDIR/bin:$PATH
	export  LD_LIBRARY_PATH=$QTDIR/lib:/usr/lib/cedarx/:$LD_LIBRARY_PATH

	export QT_QPA_PLATFORM_PLUGIN_PATH=$QT_ROOT/plugins
	export QT_QPA_PLATFORM=linuxfb:tty=/dev/fb0
	export QT_QPA_FONTDIR=$QT_ROOT/fonts
	
	export QML_IMPORT_PATH=$QTDIR/qml
	export QML2_IMPORT_PATH=$QTDIR/qml

	TouchDevice="generic ft5x06 (79)"
	for InputDevices in /sys/class/input/input*
	do
		DeviceName=`cat $InputDevices/name`
		if [[ $DeviceName == $TouchDevice ]];then
		   TouchDeviceNum=${InputDevices##*input}
		   export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/event$TouchDeviceNum
		   echo "add "/dev/input/event$TouchDeviceNum "to Qt Application."
		   break
		fi
	done
	if [ ! -n "$TouchDeviceNum" ]; then
	 echo "Error:Input device $TouchDevice can not be found,plz check it!"
	fi

	export QT_QPA_PLATFORM=linuxfb
	export set TSLIB_TSDEVICE=/dev/input/dev/input/event$TouchDeviceNum
	export set TSLIB_CONFFILE=/etc/ts.conf
	export set TSLIB_PLUGINDIR=/usr/lib/ts
	export set TSLIB_CALIBFILE=/etc/pointercal
	export set TSLIB_CONSOLEDEVICE=none
	export set TSLIB_FBDEVICE=/dev/fb0
	export QT_QPA_GENERIC_PLUGINS=evdevtouch,evdevmouse:/dev/input/event6
	#export QT_QPA_EGLFS_INTEGRATION=eglfs_mali
	#export QT_QPA_FB_HIDECURSOR=1
	#export QT_QPA_EGLFS_HIDECURSOR=1
	#export QT_QPA_EGLFS_ROTATION=90
	
	#export QWS_MOUSE_PROTO=Intellimouse:/dev/input/event6
	
	#export DBUS_SESSION_BUS_ADDRESS=`cat /tmp/dbusaddr`
	mkdir -p /dev/shm	
	ulimit -c unlimited
	mxapp2 &
	echo "find qt5 installed done"                                     
fi

