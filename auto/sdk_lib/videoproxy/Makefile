Target = libvideoproxy.so

include ../makefile_cfg

PWD=$(shell pwd)
SDK_PATH = $(PWD)/../../sdk_lib

STD_11=-std=c++11 -std=gnu++11

DEFINES += -DUSE_LOGCAT
LOGCAT = logcat



CEDAR_LINK_NEW = -L$(SDK_PATH)/cedarx/lib/ -Wl,--no-undefined -ladecoder -laencoder -lcdx_base -lcdx_common \
	-lcdx_muxer -lcdx_parser -lcdx_playback -lcdx_stream -lMemAdapter  -lcdc_base  -lsubdecoder -lvdecoder \
	-lvencoder -lVE -lvideoengine -lxmetadataretriever -lxplayer -lvenc_codec -lvenc_base
CEDAR_LINK_NEW += -lcdx_ion	
CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0 
DMS_LIB = -L$(PWD)/../../dms/allwinner/lib -ldms_sdk_protobuf_parser -lhobot_dms -lhobotdms_hal -lupload_config -lstorage_manager -lhobotdms_sdk -ljpeg \
	   	-lopencv_world -lturbojpeg -lv4l2 -lx264 -lxvidcore

#LIBS = $(DMS_LIB)
        
LIBS += -L$(SDK_LIBS)/ -lsdk_compose  -lsdk_disp  -lsdk_g2d -lsdk_dvr   -lsdk_player \
		 -lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_egl -lsdk_misc -lsdk_shm

CEDAR_INC = -I$(SDK_PATH)/cedarx/include   \
		-I$(SDK_PATH)/cedarx/include/external/include/adecoder   \
		-I$(SDK_PATH)/cedarx/include/external/include/aencoder   \
		-I$(SDK_PATH)/cedarx/include/external/include/alsa/sound   \
		-I$(SDK_PATH)/cedarx/include/external/include/adecoder   \
		-I$(SDK_PATH)/cedarx/include/external/include/libxml    \
		-I$(SDK_PATH)/cedarx/include/external/include/live    \
		-I$(SDK_PATH)/cedarx/include/external/include/openssl    \
		-I$(SDK_PATH)/cedarx/include/external/include/sdecoder   \
		-I$(SDK_PATH)/cedarx/include/external/include/zlib    \
		-I$(SDK_PATH)/cedarx/include/libcedarc/include    \
		-I$(SDK_PATH)/cedarx/include/libcore/base/include    \
		-I$(SDK_PATH)/cedarx/include/libcore/muxer/include    \
		-I$(SDK_PATH)/cedarx/include/libcore/parser/include    \
		-I$(SDK_PATH)/cedarx/include/libcore/playback/include    \
		-I$(SDK_PATH)/cedarx/include/libcore/stream/include \
		-I$(SDK_PATH)/cedarx/include/libcore/common/iniparser \
		-I$(SDK_PATH)/cedarx/include/libcore/common/plugin \
		-I$(SDK_PATH)/cedarx/include/xmetadataretriever/include   \
		-I$(SDK_PATH)/cedarx/include/xplayer/include \
		-I$(SDK_PATH)/dbusmedia
		
INCLUDES  +=  			-I$(SYSROOT)/usr/include/glib-2.0
INCLUDES  +=  			-I$(SYSROOT)/usr/lib/glib-2.0/include
INCLUDES  +=  			-I$(SYSROOT)/usr/include/gio-unix-2.0
INCLUDES  +=  			-I$(SYSROOT)/usr/lib/glib-2.0/include

ANDROID_UTILS_DEF = -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX  -DHAVE_POSIX_CLOCKS -DHAVE_PRCTL
SDKLIB_DEF = -DWATERMARK -DCDX_V27  -DSUPPORT_NEW_DRIVER
DEFINES +=  $(ANDROID_UTILS_DEF) $(SDKLIB_DEF)

#INC = -I$(PWD)/../../dms/include 

INC += -I./  \
	-I$(SDK_PATH)/include  \
	-I$(SDK_PATH)/include/disp2  \
	-I$(SDK_PATH)/include/utils  \
	-I$(SDK_PATH)//include/cutils/  \
	-I$(SDK_PATH)/media  \
	-I$(SDK_PATH)/camera  \
	-I$(SDK_PATH)/camera/moudle \
	-I$(SDK_PATH)/camera/allwinnertech/include  \
	-I$(SDK_PATH)/camera/allwinnertech/water_mark/  \
	-I$(SDK_PATH)/camera/adas/  \
	-I$(SDK_PATH)/storage/  \
	-I$(SDK_PATH)/sound/   \
	-I$(SDK_PATH)/memory/   \
	-I$(SDK_PATH)/misc/   \
	-I$(SDK_PATH)/audioenc/  \
	-I$(SDK_PATH)/eve_module/include \
	-I$(SDK_PATH)/eve_module 
	
INC += $(CEDAR_INC)
INC += $(INCLUDES)

all:  CHECK 
	$(CPP) -c ./videoprosy.cpp -o ./videopro.o -rdynamic -fPIC -shared  $(CPPFLAGS) $(DEFINES)  $(CEDAR_MACORS) $(DEFINC) -I$(INC)  -lsdk_shm -I$(SDK_PATH)/../dbusmedia/
	$(CPP)  -o $(Target)  ./videopro.o  -rdynamic -fPIC -shared -L./cedarx/lib/ -Wl,--no-undefined $(CEDAR_LINK_NEW) -lrt -lpthread -lz -lcrypto -lssl $(LIBS) -L$(SDK_PATH)  \
		-lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_egl -lsdk_misc  \
		-L$(SDK_PATH)    -lsdk_shm -lawcommediavideo  -I../shm/ -I../dbusmedia/	

		cp $(Target) $(SDK_LIBS)
		@echo "generate $(Target) success!!!"

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)
	
.PHONY:clean cleanall install distclean

install:
	-cp $(Target) $(SDK_LIBS)

#清除所有目标文件以及生成的最终目标文件
clean:            
	-rm -f *.o $(Target)
	
cleanall:clean
	-rm -f $(SDK_LIBS)/$(Target) 

distclean:cleanall 
	