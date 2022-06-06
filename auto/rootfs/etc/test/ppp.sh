#!/bin/sh

#4G ec20
sleep 30 
if [ ! -d /dev/ttyUSB3 ];then
#pppd call quectel-ppp &
. /etc/ppp/peers/quectel-pppd.sh
fi
