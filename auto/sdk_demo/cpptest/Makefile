Target = cpptest

include ../makefile_cfg

CFLAGS+=-Wall -W -D_REENTRANT -fPIC -std=c++11 -std=gnu++11 -std=gnu99 \
		-D_SUNXIW17_ -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX \
		-DHAVE_POSIX_CLOCKS -DHAVE_PRCTL -DWATERMARK -DCDX_V27 -DSUPPORT_NEW_DRIVER -DUSE_LOGCAT
		
		
		
GPUINC = 	-I $(SDK_PATH)/include/opengl/include \
		-I $(SDK_PATH)/include/opengl/include/khronos/original/

LIBS +=  $(LICHEE_BR_OUT)/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/libmali.so


LDFLAGS := -rdynamic -lpthread -fPIC 
MAKE = make
SUBDIRS = $(shell find . -maxdepth 3 -type d)
DEFINC = 	-I$(SDK_PATH)/include \
			-I$(SDK_PATH)/include/storage \
			-I$(SDK_PATH)/include/disp2 \
			-I$(SDK_PATH)/include/cutils \
			-I$(SDK_PATH)/include/utils \
			-I$(SDK_PATH)/include/camera/ \
			-I$(SDK_PATH)/media \
			-I$(LICHEE_TOOL_DIR)/arm-linux-$(MISC_GNUEABI)/libc/usr/include/ \
			-I$(LICHEE_TOOL_DIR)/arm-linux-$(MISC_GNUEABI)/libc/usr/include/arm-linux-$(MISC_GNUEABI)/ \
			-I$(LICHEE_TOOL_DIR)/arm-linux-$(MISC_GNUEABI)/include \
			-I./libs/ \
			-I./ \

INCS += $(DEFINC)
INCS += $(GPUINC)

CSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c)) 
CPPSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cpp))

COBJS := $(CSRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)

CFLAGS+=-g -O0 -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -fPIC
CPPFLAGS=-g -O0 -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -fPIC

all:$(Target) 
	@echo "make finish!!!"

$(COBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)
$(CPPOBJS) : %.o: %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)

$(Target) : $(COBJS) $(CPPOBJS) 
	$(CPP) -o $(Target) $(COBJS) $(CPPOBJS) $(LIBS) $(LDFLAGS) $(CEDAR_MACORS)
	@echo "generate $(Target) success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall install distclean

clean:
	-rm -f $(Target) $(COBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 
	
distclean:cleanall 

install:
	-cp $(Target) $(INSTATLL_PATH)
distclean:cleanall 

install:
	-cp $(Target) $(INSTATLL_PATH)