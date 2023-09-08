##### Change the following for your environment:
TARGET = liblive555.so
include ../makefile_cfg
CROSS_COMPILE=       ${LICHEE_CROSS_COMPILER}-
#CROSS_COMPILE=        /home/ytr/workdir/T113/T113-i_v1.0/out/gcc-linaro-5.3.1-2016.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-
COMPILE_OPTS =        $(INCLUDES) -I. -O2 -DSOCKLEN_T=socklen_t -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -fPIC
C =            c
C_COMPILER =        $(CROSS_COMPILE)gcc
CFLAGS +=        $(COMPILE_OPTS)
C_FLAGS = $(CFLAGS)
CPP =            cpp
CPLUSPLUS_COMPILER =    $(CROSS_COMPILE)g++
CPLUSPLUS_FLAGS =    $(COMPILE_OPTS) -Wall -DBSD=1
CPLUSPLUS_FLAGS += $(CPPFLAGS) -fexceptions
OBJ =            o
LINK =            $(CROSS_COMPILE)g++ -o
LINK_OPTS =        -L. $(LDFLAGS)
CONSOLE_LINK_OPTS =    $(LINK_OPTS)
LIBRARY_LINK =        $(CROSS_COMPILE)ar cr 
LIBRARY_LINK_OPTS =    
LIB_SUFFIX =            a
LIBS_FOR_CONSOLE_APPLICATION = $(CXXLIBS)
LIBS_FOR_GUI_APPLICATION = $(LIBS_FOR_CONSOLE_APPLICATION)
EXE =
##### End of variables to change

LIVEMEDIA_DIR = liveMedia
GROUPSOCK_DIR = groupsock
USAGE_ENVIRONMENT_DIR = UsageEnvironment
BASIC_USAGE_ENVIRONMENT_DIR = BasicUsageEnvironment

TESTPROGS_DIR = testProgs

MEDIA_SERVER_DIR = mediaServer

PROXY_SERVER_DIR = proxyServer



all:
	cd $(LIVEMEDIA_DIR) ; $(MAKE)
	cd $(GROUPSOCK_DIR) ; $(MAKE)
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE)
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE)
	cd $(TESTPROGS_DIR) ; $(MAKE)
	cd $(MEDIA_SERVER_DIR) ; $(MAKE)
	cd $(PROXY_SERVER_DIR) ; $(MAKE)
	$(C_COMPILER) -shared  -Wl,--whole-archive ./BasicUsageEnvironment/libBasicUsageEnvironment.a \
		./liveMedia/libliveMedia.a ./groupsock/libgroupsock.a \
		./UsageEnvironment/libUsageEnvironment.a  \
		-Wl,--no-whole-archive -o $(TARGET)
	#@cp $(TARGET) $(SDK_LIBS)/
	@cp $(TARGET) $(SDK_PATH)/cedarx/lib/
	@echo -e '\e[1;33m cp $(TARGET) $(SDK_LIBS) \e[0m'
	@echo "generate $(TARGET) success!!!"	

install:
	cd $(LIVEMEDIA_DIR) ; $(MAKE) install
	cd $(GROUPSOCK_DIR) ; $(MAKE) install
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE) install
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE) install
	cd $(TESTPROGS_DIR) ; $(MAKE) install
	cd $(MEDIA_SERVER_DIR) ; $(MAKE) install
	cd $(PROXY_SERVER_DIR) ; $(MAKE) install

clean:
	cd $(LIVEMEDIA_DIR) ; $(MAKE) clean
	cd $(GROUPSOCK_DIR) ; $(MAKE) clean
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE) clean
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE) clean
	cd $(TESTPROGS_DIR) ; $(MAKE) clean
	cd $(MEDIA_SERVER_DIR) ; $(MAKE) clean
	cd $(PROXY_SERVER_DIR) ; $(MAKE) clean
	rm -rf $(TARGET)
	rm -rf  $(SDK_LIBS)/$(TARGET)

distclean: clean
	-rm -f $(LIVEMEDIA_DIR)/Makefile $(GROUPSOCK_DIR)/Makefile \
	  $(USAGE_ENVIRONMENT_DIR)/Makefile $(BASIC_USAGE_ENVIRONMENT_DIR)/Makefile \
	  $(TESTPROGS_DIR)/Makefile $(MEDIA_SERVER_DIR)/Makefile \
	  $(PROXY_SERVER_DIR)/Makefile Makefile
