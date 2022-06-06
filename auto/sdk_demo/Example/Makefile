# make all demoes at one time

#CROSS_COMPILE = arm-linux-gnueabihf-
#CC=$(CROSS_COMPILE)gcc
#CC = arm-linux-gnueabihf-gcc
#CC = arm-openstlinux_eglfs-linux-gnueabi-gcc

all: 
	make -C ./framebuffer
	make -C ./i2c
	make -C ./gpio_key
	make -C ./network
	make -C ./rtc
	make -C ./spiflash
	make -C ./gpio_led
	make -C ./rs485
	make -C ./can
	make -C ./uart
	make -C ./bt

.Phony: clean

clean:
	make clean -C ./framebuffer
	make clean -C ./i2c
	make clean -C ./gpio_key
	make clean -C ./network
	make clean -C ./rtc
	make clean -C ./spiflash
	make clean -C ./gpio_led
	make clean -C ./rs485
	make clean -C ./can
	make clean -C ./uart
	make clean -C ./bt


