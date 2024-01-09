TARGET = libsdk_camera.so

CUR_MODULE_VERSION = "V2.5.20220530"

DEFINES += -DMODULE_VERSION=\"$(CUR_MODULE_VERSION)\"

include ../makefile_cfg

CFLAGS+= -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX \
		-DHAVE_POSIX_CLOCKS -DHAVE_PRCTL -DWATERMARK -DCDX_V27 -DSUPPORT_NEW_DRIVER -DUSE_LOGCAT

LDFLAGS := -rdynamic -lpthread -fPIC -shared

DEFINC = 	-I./ \
			-I$(SDK_PATH)/include \
			-I$(SDK_PATH)/include/storage \
			-I$(SDK_PATH)/include/disp2 \
			-I$(SDK_PATH)/include/cutils \
			-I$(SDK_PATH)/include/utils \
			-I$(SDK_PATH)/include/camera/ \
			-I$(SDK_PATH)/media \

DEFINES += $(ANDROID_UTILS_DEF) $(SDKLIB_DEF)

INCS += $(DEFINC)
SUBDIRS = $(shell find . -maxdepth 3 -type d)
CSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CPPSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cpp))

COBJS := $(CSRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)

CFLAGS+=-g -O0 -pipe -Wall -W -Wno-unused-parameter -Wno-reorder -Wno-write-strings  -Wno-unused-function -Wno-unused-value -D_REENTRANT -fPIC
CPPFLAGS=-g -O0 -pipe -Wall -W -Wno-unused-parameter -Wno-reorder -Wno-write-strings -Wno-unused-function -Wno-unused-value -D_REENTRANT -fPIC

all: CHECK $(TARGET) 
	@echo "make finish!!!"

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)

$(COBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)
$(CPPOBJS) : %.o: %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)

$(TARGET) : $(COBJS) $(CPPOBJS) 
	$(CPP) -o $(TARGET) $(COBJS) $(CPPOBJS) $(LIBS) $(LDFLAGS)
	@cp -f $(TARGET) $(SDK_LIBS)
	@echo -e '\e[1;33m cp -f $(TARGET) $(SDK_LIBS) \e[0m'

.PHONY:clean cleanall install distclean

install:
	cp $(TARGET) $(SDK_LIBS)

clean:
	-rm -f $(TARGET) $(COBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(SDK_LIBS)/$(TARGET)

distclean:cleanall
