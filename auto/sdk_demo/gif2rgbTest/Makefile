Target = gif2rgb

include ../makefile_cfg



PWD=$(shell pwd)
LICHEE_DIR=$(PWD)/../../../../..
LICHEE_OUT_SYS= $(LICHEE_DIR)/out/${MISC_CHIP}/linux/common/buildroot
SDK_PATH = $(PWD)/../../sdk_lib




LDFLAGS = -L$(SDK_PATH)/libs/
LIBS += -lsdk_gifdecoder

all: 
	$(CPP)  gif2rgb.c  -o gif2rgb $(LIBS) $(LDFLAGS) -lpthread $(CXXFLAGS)
	@echo "generate  $(Target) success!!!"

.PHONY:clean cleanall

clean:            
	@rm -f  $(Target)

