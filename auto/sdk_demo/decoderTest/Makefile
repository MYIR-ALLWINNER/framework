Target = decoderTest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib

CXXFLAGS = -I$(SDK_PATH)/cedarx/include/libcedarc/include
CXXFLAGS += -I$(SDK_PATH)/include

LDFLAGS = -L$(SDK_PATH)/lib64/ -L$(SDK_PATH)/cedarx/lib/ 
LIBS = -lMemAdapter -lvdecoder -lVE -lcdc_base -lvideoengine -lcdx_common -lcdx_base
LIBS += -lsdk_decoder

all: $(Target) 

$(Target) : decoderTest.cpp
	$(CPP) decoderTest.cpp -o $(Target)  $(LIBS) $(LDFLAGS) -lpthread $(CXXFLAGS)
	@echo "generate $(Target) success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall install distclean

#清除所有目标文件以及生成的最终目标文仿
clean:
	-rm -f $(Target) $(COBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)