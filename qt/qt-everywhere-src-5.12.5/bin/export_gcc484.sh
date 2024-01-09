#!/bin/sh
PWD=`pwd`
echo $PWD
export PATH=$PWD/bin/:$PATH
gcc -v
