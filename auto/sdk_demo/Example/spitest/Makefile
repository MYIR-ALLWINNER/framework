include ../env.mk
TARGET = $(notdir $(CURDIR))

objs := $(patsubst %c, %o, $(shell ls *.c))

all: spidev_test

spidev_test:
	$(CC) spidev_test.c -o spidev_test

clean:
	rm -f spidev_test *.o *~
