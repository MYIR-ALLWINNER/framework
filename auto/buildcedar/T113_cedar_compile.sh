#!/bin/bash

BUILD_CEDAR=`pwd`
CDX_TOP=$(cd $BUILD_CEDAR/../../cedarx;pwd )
CDC_TOP=$(cd $BUILD_CEDAR/../../libcedarc;pwd )
AUTO_TOP=$(cd $BUILD_CEDAR/../;pwd )

cp ./build_cdx_arm.sh ../../cedarx/
cp ./build_cdc_arm.sh ../../libcedarc/

cd $CDC_TOP
./build_cdc_arm.sh
cd $CDX_TOP
./build_cdx_arm.sh
