#!/bin/sh
ifconfig eth0 192.168.1.11 netmask 255.255.255.0
ifconfig eth1 192.168.1.12 netmask 255.255.255.0
echo "ping eth1"
echo "if you want to stop , press ctrl + c"
ping 192.168.1.12

