#!/bin/sh
echo "gpio up"
echo 1 > /proc/rp_gpio/gpiope12
echo 1 > /proc/rp_gpio/gpiope18
echo 1 > /proc/rp_gpio/gpiope19
echo 1 > /proc/rp_gpio/gpiope22

sleep 8

echo "gpio down"
echo 0 > /proc/rp_gpio/gpiope12
echo 0 > /proc/rp_gpio/gpiope18
echo 0 > /proc/rp_gpio/gpiope19
echo 0 > /proc/rp_gpio/gpiope22

echo "test over"
