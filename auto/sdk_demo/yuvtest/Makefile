Target = yuvtest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib

CXXFLAGS += -I$(SDK_PATH)/
CXXFLAGS += -L$(SDK_PATH)/lib64
CXXFLAGS += -I$(SDK_PATH)/include/
CXXFLAGS += -I$(SDK_PATH)/include/disp2
CXXFLAGS += -I$(SDK_PATH)/memory
CXXFLAGS += -I$(SDK_PATH)/cedarx/include/libcedarc/include

LDFLAGS = -L$(SDK_PATH) -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 

	
CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0 

LIBS += -lMemAdapter  -lVE -lcdc_base -lvideoengine -lcdx_common -lcdx_base -lsdk_memory -lsdk_disp -lsdk_log -lcdx_ion

all: $(Target)

$(Target):yuvtest.cpp
	$(CPP) yuvtest.cpp -o $(Target) $(CXXFLAGS) $(LIBS) $(LDFLAGS) 
	@echo "generate encoder success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall

clean: 
	@rm -f $(Target)
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)	
