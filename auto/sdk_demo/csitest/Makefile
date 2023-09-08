ARCH_DIR=$(LICHEE_KERN_DIR)/arch/arm64/include/
CFLAGS := -I $(ARCH_DIR)
TARGET := csitestT113_ptr

include ../makefile_cfg

SDK_PATH =../../sdk_lib

LDFLAGS = -L$(SDK_PATH)/libs -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/

INC = -I$(SDK_PATH)/include \
	-I$(SDK_PATH)/include/disp2

LIBS += -lsdk_memory -lMemAdapter -lVE -lcdc_base -lsdk_disp

.PHONY: all clean

all: $(TARGET)

$(TARGET): csi_test_mplane_usrptr.cpp
	$(CPP) csi_test_mplane_usrptr.cpp -o $(TARGET) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) -g

clean:
	rm -rf $(TARGET) csitestT113_ptr *.o

install:
	-cp $(Target) $(INSTATLL_PATH) 
