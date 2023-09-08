TARGET = libsdk_log.so

include ../makefile_cfg

CONFIG_USE_LOGCAT = true
ifeq ($(CONFIG_USE_LOGCAT), true)
DEFINES += -DUSE_LOGCAT
LOGCAT = logcat
endif

LDFLAGS := -rdynamic -lpthread -fPIC -shared 
MAKE = make

INCS = 	-I./ \
	-I$(SDK_PATH)/include \
	-I$(SDK_PATH)/include/cutils 

CSRCS := \
	event_tag_map.c \
	fake_log_device.c \
	logd_write.c \
	logprint.c \
	sdklog.c \
	uio.c
	
CPPSRCS := 

COBJS := $(CSRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)

CFLAGS+=-g -O0 -pipe -Wall -W -Wno-unused-parameter -Wno-unused-function -fPIC 
CPPFLAGS=-g -O0 -pipe -Wall -W -Wno-unused-parameter -Wno-unused-function -fPIC


DEFINES += $(ANDROID_UTILS_DEF)

all: CHECK $(TARGET) 
	@echo "make finish!!!"

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)

$(COBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFINES) $(INCS)
$(CPPOBJS) : %.o: %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(DEFINES) $(INCS)

$(TARGET) : $(COBJS) $(CPPOBJS) 
	$(CPP) -o $(TARGET) $(COBJS) $(CPPOBJS) $(LIBS) $(LDFLAGS) 
	cp $(TARGET) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(TARGET) $(SDK_LIBS) \e[0m'

include $(CPPDEF)
.PHONY:clean cleanall install distclean

install:
	cp $(TARGET) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(TARGET) $(SDK_LIBS) \e[0m'
	
clean:
	-rm -f $(TARGET) $(COBJS) $(CPPOBJS)

cleanall:clean
	-rm -f $(SDK_LIBS)/$(TARGET) 

distclean:cleanall
	
