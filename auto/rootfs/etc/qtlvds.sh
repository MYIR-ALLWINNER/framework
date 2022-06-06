
export  QTDIR=/usr/local/Qt_5.12.5
if [ -d $QTDIR ];then

	export  QT_ROOT=$QTDIR
	export  PATH=$QTDIR/bin:$PATH
	export  LD_LIBRARY_PATH=$QTDIR/lib:/usr/lib/cedarx/:$LD_LIBRARY_PATH

	export QT_QPA_PLATFORM_PLUGIN_PATH=$QT_ROOT/plugins
	export QT_QPA_PLATFORM=linuxfb:tty=/dev/fb1
	export QT_QPA_FONTDIR=$QT_ROOT/fonts

	export QML_IMPORT_PATH=$QTDIR/qml
	export QML2_IMPORT_PATH=$QTDIR/qml

	TouchDevice=ft5x_ts

	for InputDevices in /sys/class/input/input*
	do
		DeviceName=`cat $InputDevices/name`
		if [ $DeviceName == $TouchDevice ];then
		   TouchDeviceNum=${InputDevices##*input}
		   export TSLIB_CONSOLEDEVICE=none
		   export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/event$TouchDeviceNum
		   echo "add "/dev/input/event$TouchDeviceNum "to Qt Application."
		   break
		fi
	done
	if [ ! -n "$TouchDeviceNum" ]; then
	 echo "Error:Input device $TouchDevice can not be found,plz check it!"
	fi

	export QT_QPA_PLATFORM=eglfs
	export QT_QPA_GENERIC_PLUGINS=evdevtouch
	export QT_QPA_EGLFS_INTEGRATION=eglfs_mali
	#export QT_QPA_FB_HIDECURSOR=1
	#export QT_QPA_EGLFS_HIDECURSOR=1
	#export QT_QPA_EGLFS_ROTATION=90

	export QWS_MOUSE_PROTO=IntelliMouse:/dev/input/mouse0
	export DBUS_SESSION_BUS_ADDRESS=`cat /tmp/dbusaddr`
	mkdir -p /dev/shm	
	ulimit -c unlimited
	debug Launcher &
	#hellogles3 &
	echo "find qt5 installed done"                                     
fi

sleep 3
echo -ne "\033[?25h"
