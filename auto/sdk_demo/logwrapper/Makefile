Target = logwrapper

include ../makefile_cfg


SDK_PATH = ../../sdk_lib

DEFINES += -DUSE_LOGCAT
LOGCAT = logcat

DEFINES += -DHAVE_PTHREADS -DSUPPORT_NEW_DRIVER -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX -D__ARM_HAVE_LDREXD \
				-D__ARM_HAVE_VFP -D__ARM_HAVE_NEON -DHAVE_POSIX_CLOCKS -DWATERMARK_ENABLE -DHAVE_PRCTL -DRTSP_SERVER -DWATERMARK -D_XOPEN_SOURCE -DADB_HOST=0 -DALLOW_ADBD_ROOT=1 -DADB_TRACE -DCDX_V27
			
 
LIBS = -L$(SDK_PATH)/lib64 -lsdk_log

INC += -I./include 
INC += -I$(SDK_PATH)/include
	
all: $(Target) 

$(Target): $(Target).cpp logwrap.cpp
	$(CPP) -c logwrap.cpp -o logwrap.o -g -fno-permissive $(INC) $(CEDAR_MACORS) $(DEFINES) -fpermissive
	$(CPP) -c klog.c -o klog.o -g -fno-permissive $(INC) $(CEDAR_MACORS) $(DEFINES)
	$(CPP) -c $(Target).cpp -o $(Target).o -g $(INC) $(CEDAR_MACORS) $(DEFINES)
	$(CPP) -o $(Target) $(Target).o logwrap.o klog.o $(LIBS) -L$(SDK_PATH)/ $(CEDAR_LINK_NEW) -lrt -lpthread -lz -lcrypto -lssl 
	@echo "generate $(Target) success!!!"

.PHONY:clean cleanall install distclean
 
clean:
	-rm -f $(Target).o $(Target) 
	
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 
	
distclean:cleanall 

install:
	-cp $(Target) $(INSTATLL_PATH)
