adb shell killall phoneMachineConnect
adb push %~dp0phoneMachineConnect /usr/bin
adb shell chmod 777 /usr/bin/phoneMachineConnect
pause