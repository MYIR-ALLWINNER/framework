include ../env.mk
TARGET = i2c_flash
objs := $(patsubst %c, %o, $(shell ls *.c))
$(TARGET):$(objs)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c -o $@ $<
clean:
	rm -f  $(TARGET) *.all *.o
