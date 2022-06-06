#!/bin/sh
insmod /lib/modules/4.9.170/bcmdhd.ko 
insmod /lib/modules/4.9.170/bcm_btlpm.ko

sleep 2 

#for wifi station function
wpa_supplicant -i wlan0 -Dnl80211 -c /etc/wpa_supplicant.conf -B
udhcpc -i wlan0  2>/dev/null &
#udhcpc -i wlan0 -n -q -t 6 &

#for wifi ap function
#hostapd /etc/hostapd.conf -B
#ifconfig wlan0 192.168.1.1
#touch /var/lib/dhcp/dhcpd.leases
#dhcpd
