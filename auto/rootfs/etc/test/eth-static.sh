#!/bin/sh

#udhcpc eth0 2>/dev/null &
#sleep 1

#udhcpc eth1 2>/dev/null &

#static ip
ifconfig eth0 up 192.168.1.11 netmask 255.255.255.0
ifconfig eth1 up 192.168.1.12 netmask 255.255.255.0
