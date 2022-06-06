include ../env.mk
TARGET = $(notdir $(CURDIR))
objs := $(patsubst %c, %o, $(shell ls *.c))
$(TARGET)_test:$(objs)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c -o $@ $<
clean:
	rm -f  $(TARGET)_test *.all *.o
