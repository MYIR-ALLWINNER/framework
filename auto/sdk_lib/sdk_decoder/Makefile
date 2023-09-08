Target = libsdk_decoder.so

include ../makefile_cfg


CXXFLAGS =  -I$(SDK_PATH)/cedarx/include/libcedarc/include
CXXFLAGS +=  -I$(SDK_PATH)/include

LDFLAGS = -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 
LIBS = -lMemAdapter -lvdecoder -lVE -lcdc_base -lvideoengine  -lcdx_common -lcdx_base  -lsdk_memory -lcdx_ion

	
all: CHECK __LIB

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)

__LIB:
	$(CPP) AWVideoDecoder.cpp -o $(Target) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -shared -fPIC 	  
	$(STRIP) $(Target)
	@cp $(Target) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(Target) $(SDK_LIBS) \e[0m'
	@echo "generate $(Target) success!!!"
	
	
.PHONY:clean 

.PHONY:clean cleanall distclean

clean:
	-rm -f  $(Target) 
cleanall:distclean
distclean:
	-rm -f  $(Target) 
	-rm -f $(SDK_LIBS)/$(Target)

