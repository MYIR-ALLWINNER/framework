Target = memTest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib

CXXFLAGS += -I$(SDK_PATH)/include/

LDFLAGS = -L$(SDK_PATH)/libs -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 

CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0 

LIBS += -lsdk_memory -lcdx_ion -lMemAdapter -lVE -lcdc_base

all: $(Target)
	@echo -e '\e[1;33m if you want to test memtestDE,you should type:\nmake -f MakefileDE \e[0m'

$(Target): MemTest.cpp
	$(CPP) MemTest.cpp -o $(Target) $(CXXFLAGS) $(LIBS) $(LDFLAGS) 
	@echo "generate encoder success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'
	

	
.PHONY:clean cleanall

clean: 
	@rm -f $(Target) memTestDE
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 
	
distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)	
