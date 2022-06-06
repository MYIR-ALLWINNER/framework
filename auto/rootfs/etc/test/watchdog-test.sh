#!/bin/sh
echo "sstart watchdog test"
echo "press keyboard ctrl+c"
echo "press keyboard ctrl+c"
echo "press keyboard ctrl+c"
/etc/watchdogd/watchdogd.out 1 10 
sleep 1
echo "stop test"
sync
exit
