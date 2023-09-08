Target = libsdk_encoder.so
include ../makefile_cfg

#INC = -I$(SDK_PATH)/cedarx/include/libcedarc/include

LDFLAGS = -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 
CXXFLAGS =  -I$(SDK_PATH)/cedarx/include/libcedarc/include
CXXFLAGS +=  -I$(SDK_PATH)/include

LIBS = -lMemAdapter -lvencoder -lVE -lcdc_base

all: CHECK __LIB

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)
	
__LIB:
	$(CPP) AWVidoeEncoder.cpp -o $(Target) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -shared -fPIC 	 
	@cp -f $(Target) $(Target).nostrip
	$(STRIP) $(Target)
	@cp $(Target) $(SDK_LIBS)
	@echo "generate $(Target) success!!!"
	@echo -e '\e[1;33m cp $(Target) $(SDK_LIBS) \e[0m'
	mv $(Target).nostrip $(Target)
	
.PHONY:clean 

.PHONY:clean cleanall distclean

clean:
	-rm -f $(Target) 
cleanall:distclean
distclean:
	-rm -f $(Target) 
	-rm $(SDK_LIBS)/$(Target)

