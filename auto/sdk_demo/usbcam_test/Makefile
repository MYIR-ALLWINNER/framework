TARGET := usbcam_test

include ../makefile_cfg

ARCH_DIR=$(LICHEE_KERN_DIR)/arch/arm64/include/
CFLAGS := -I $(ARCH_DIR)


.PHONY: all clean

all: $(TARGET)

$(TARGET): csi_test_mplane.c
	$(CC) $(CFLAGS) -static  $^  -o  $@
	@echo "generate usbcam_test success!!!"
	@cp -f $(TARGET) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(TARGET) $(INSTATLL_PATH) \e[0m'

clean:
	rm -rf $(TARGET) usbcam_test *.o

install:
	-cp $(Target) $(INSTATLL_PATH) 
