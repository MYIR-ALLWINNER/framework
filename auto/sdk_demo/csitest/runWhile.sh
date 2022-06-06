#!/bin/sh
i=1
sum=0
while [ $i -le 100 ]
do
  /csitestT5_ptr 3 0 1280 720 ./ 4 100 25 &
  sleep 6
  killall csitestT5_ptr
  echo "==================================================================================================="
done
