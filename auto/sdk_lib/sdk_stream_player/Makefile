Target = libsdk_stream_player.so

include ../makefile_cfg

INC += -I$(SDK_PATH)/include/disp2/
#INC = -I$(SDK_PATH)/cedarx/include/libcedarc/include
#INC += -I$(SDK_PATH)/include
#INC += -I$(SDK_PATH)/memory/
#INC += -I$(SDK_PATH)/cedarx/include/libcedarc/include/
#INC += -I$(SDK_PATH)/cedarx/include

LDFLAGS = -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 

all: CHECK __LIB

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)
	
__LIB:
	$(CPP) -g AWStreamPlayer.cpp -o $(Target) $(LIBS) $(LDFLAGS) $(INC) -shared -fPIC
	cp -f $(Target) $(Target).nostrip
	$(STRIP) $(Target)
	@cp $(Target) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(Target) $(SDK_LIBS) \e[0m'
	@echo "generate $(Target) success!!!"
	mv $(Target).nostrip $(Target)
	
.PHONY:clean cleanall distclean

clean:
	-rm -f $(Target) 
cleanall:distclean
distclean:
	-rm -f $(Target) 
	-rm -f $(SDK_LIBS)/$(Target)

