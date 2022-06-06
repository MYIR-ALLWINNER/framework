include ../env.mk
TARGET = gpio_key
SRC =  $(TARGET).c
OBJS = $(patsubst %.c ,%.o ,$(SRC))
.PHONY: all
all: $(TARGET)
$(TARGET) : $(OBJS)
	$(CC) -o $@ $^
%.o : %.c
	$(CC) -c $< -o $@
clean:
	$(RM) *.o $(TARGET)
