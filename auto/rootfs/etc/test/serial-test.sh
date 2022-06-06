#!/bin/sh
echo ""
echo "please connect uart5 RX and TX pin"
echo "3s"
sleep 1
echo "2s"
sleep 1
echo "1s"
sleep 1
echo "start"
/etc/uart/uart.out /dev/ttyS5
