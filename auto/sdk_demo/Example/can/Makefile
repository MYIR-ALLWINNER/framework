include ../env.mk
TARGET = $(notdir $(CURDIR))

objs := $(patsubst %c, %o, $(shell ls *.c))

all: can_send can_receive

can_send:
	$(CC) can_send.c -o can_send
can_receive:
	$(CC) can_receive.c -o can_receive

clean:
	rm -f can_send can_receive *.o *~
