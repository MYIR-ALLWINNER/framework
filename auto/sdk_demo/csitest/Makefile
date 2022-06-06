#CC:=/home/licy/t507/out/t507/myir/longan/buildroot/host/bin/aarch64-linux-gnu-gcc
CC:=/home/lcy/t507/out/t507/myir/longan/buildroot/host/bin/aarch64-linux-gnu-gcc
#ARCH_DIR=/home/linux01/t5longan06/kernel/linux-4.9/arch/arm64/include/
ARCH_DIR=$(LICHEE_KERN_DIR)/arch/arm64/include/
CFLAGS := -I $(ARCH_DIR)
TARGET := csitestT5

.PHONY: all clean

all: $(TARGET)

$(TARGET): csi_test_mplane.c
	$(CC) $(CFLAGS) -static  $^  -o  $@

clean:
	rm -rf $(TARGET) csitestT5_ptr *.o

install:
	-cp $(Target) $(INSTATLL_PATH) 
