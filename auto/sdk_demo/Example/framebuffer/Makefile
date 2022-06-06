include ../env.mk
EXEC = framebuffer_test
OBJS = lcd_test.o
SRC  = lcd_test.c

#CC=gcc

all:$(EXEC)

$(EXEC):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -pthread

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ -pthread

clean:
	@rm -vf $(EXEC) *.o *~
