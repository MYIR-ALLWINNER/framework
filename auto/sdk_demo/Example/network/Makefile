include ../env.mk
TARGET = $(notdir $(CURDIR))

objs := $(patsubst %c, %o, $(shell ls *.c))

all: arm_client arm_server pc_client pc_server

arm_client:
	$(CC) client.c -o arm_client
arm_server:
	$(CC) server.c -o arm_server
pc_client:
	gcc client.c -o pc_client
pc_server:
	gcc server.c -o pc_server

clean:
	rm -f arm_client arm_server pc_client pc_server *.o *~
