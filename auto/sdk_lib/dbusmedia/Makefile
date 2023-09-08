################################################################################
#
# Makefile project only supported on Mac OS X and Linux Platforms)
# Tailor to simple project , adjust it by xiaoyong pan
################################################################################
TARGET       = libawcommediavideo.so

include ../makefile_cfg
PWD=$(shell pwd)

MY_LIB_PATH = 
#$(PWD)/my_lib
EXT_OBJS = 
#$(MY_LIB_PATH)/sdklog.o

############################
# end deprecated interface #
############################
SRCS        := $(shell find -name "*.cpp")
SRCS        += $(shell find -name "*.c")

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJS += $(patsubst %.cpp, %.o, $(wildcard *.cpp))

#some marcos
CCFLAGS += -g -Wl,--no-undefined -rdynamic -pipe  -Wall -W -D_REENTRANT  -fPIC  -DGDBUSLIB_COM

INCLUDES  +=  			-I$(SYSROOT)/usr/include/glib-2.0/
INCLUDES  +=  			-I$(SYSROOT)/usr/lib/glib-2.0/include
INCLUDES  +=  			-I$(SYSROOT)/usr/include/gio-unix-2.0
			
#LIBRARIES += -L$(MY_LIB_PATH)   
LIBRARIES +=  -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 \
	-ldl -lpthread -lrt 

# Target rules
all: CHECK build

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)
	
build:${TARGET}

%.o : %.cpp
	$(CPP) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

%.o : %.c
	$(CC)  $(CCFLAGS) $(INCLUDES) -o $@ -c $<

${TARGET}: $(OBJS) $(EXT_OBJS)
	$(CPP)  $(CCFLAGS) -rdynamic -fPIC -shared $(INCLUDES) $+ -o $@ $(LIBRARIES)
	cp $(TARGET) $(SDK_LIBS)
	
.PHONY:clean cleanall install distclean

install:
	cp $(TARGET) $(SDK_LIBS)

clean:
	-rm -f  ${TARGET} $(OBJS) *~
	
cleanall:clean
	-rm -f $(SDK_LIBS)/$(TARGET)
distclean:cleanall
