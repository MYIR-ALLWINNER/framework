export PATH=/t113_devkit/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf/bin:$PATH


arm-linux-gnueabihf-gcc -static uart_fortest.c -o uart_fortest
arm-linux-gnueabihf-strip  --strip-all --remove-section=.comment --remove-section=.note ./uart_fortest

