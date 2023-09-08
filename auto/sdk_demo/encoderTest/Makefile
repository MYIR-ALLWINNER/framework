Target = encoderTest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib

CXXFLAGS = -I$(SDK_PATH)/cedarx/include/libcedarc/include
CXXFLAGS += -I$(SDK_PATH)/include

LDFLAGS = -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib
LIBS = -lMemAdapter -lvencoder -lVE -lcdc_base -lvenc_jpeg -lvenc_common -lvenc_h264 -lvenc_h265  -lvenc_base
LIBS += -lsdk_encoder -lsdk_memory

all: $(Target) 

$(Target) : encoderTest.cpp
	$(CPP) encoderTest.cpp -o $(Target) $(LIBS) $(LDFLAGS) -lpthread $(CXXFLAGS) -g
	@echo "generate $(Target) success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall install distclean

install:
	-cp $(Target) $(INSTATLL_PATH)
#清除所有目标文件以及生成的最终目标文仿
clean:
	-rm -f $(CDEF) $(CPPDEF)
	-rm -f $(Target) $(COBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 
	
