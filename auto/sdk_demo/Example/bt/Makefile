include ../env.mk
TARGET = brcm_patchram_plus
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
