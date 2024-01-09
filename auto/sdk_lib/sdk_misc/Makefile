TARGET = libsdk_misc.so

include ../makefile_cfg
				
DEFINES = -DHAVE_PTHREADS -DSUPPORT_NEW_DRIVER -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX -D__ARM_HAVE_LDREXD \
				-D__ARM_HAVE_VFP -D__ARM_HAVE_NEON -DHAVE_POSIX_CLOCKS -DWATERMARK_ENABLE -DHAVE_PRCTL -DRTSP_SERVER -DWATERMARK -D_XOPEN_SOURCE -DADB_HOST=0 -DALLOW_ADBD_ROOT=1 -DADB_TRACE -DCDX_V27
				
LDFLAGS := -rdynamic -lpthread -fPIC -shared 


INCS += -I./ 

SUBDIRS = $(shell find . -maxdepth 3 -type d)
CSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c)) 
CPPSRCS = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cpp))

COBJS := $(CSRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)

CFLAGS+=-g -O0 $(SDKDEBUG_FLAGS) -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -Wno-unused-value -Wno-unused-function -fPIC 
CPPFLAGS=-g -O0 $(SDKDEBUG_FLAGS) -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -Wno-unused-value -Wno-unused-function -fPIC 


all: CHECK $(TARGET) 
	@echo "make finish!!!"

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)

$(COBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)
$(CPPOBJS) : %.o: %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(DEFINES) $(CEDAR_MACORS) $(INCS)


$(TARGET) : $(COBJS) $(CPPOBJS) 
	$(CPP) -o $(TARGET) $(COBJS) $(CPPOBJS) $(LIBS) $(LDFLAGS) $(CEDAR_MACORS)
	@cp $(TARGET) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(TARGET) $(SDK_LIBS) \e[0m'
	
.PHONY:clean cleanall install distclean

install:
	cp $(TARGET) $(SDK_LIBS)

clean: 
	-rm -f $(TARGET) $(COBJS) $(CPPOBJS) *.d
#rm *.d
cleanall:clean
	-rm -f $(SDK_LIBS)/$(TARGET) *.d

distclean:cleanall 
	
