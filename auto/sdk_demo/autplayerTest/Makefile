Target = autplayerTest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib

CXXFLAGS = -I$(SDK_PATH)/cedarx/include/libcedarc/include
CXXFLAGS += -I$(SDK_PATH)/
CXXFLAGS += -L$(SDK_PATH)/libs
CXXFLAGS += -I$(SDK_PATH)/include
CXXFLAGS += -I$(SDK_PATH)/include/cutils
CXXFLAGS += -I$(SDK_PATH)/include/camera
CXXFLAGS += -I$(SDK_PATH)/include/disp2
CXXFLAGS += -I$(SDK_PATH)/memory

LDFLAGS = -L$(SDK_PATH) -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ 

CEDAR_LINK_NEW = -L$(SDK_PATH)/cedarx/lib/ -Wl,--no-undefined -ladecoder -laencoder -lcdx_base -lcdx_common \
	-lcdx_muxer -lcdx_parser -lcdx_playback -lcdx_stream -lMemAdapter -lcdc_base -lsubdecoder -lvdecoder \
	-lvencoder -lVE -lvideoengine -lxmetadataretriever -lxplayer -lvenc_base -lvenc_codec -lcdx_ion -lasound \
	-lrt -lpthread -lz -lcrypto -lssl -lvenc_common -lvenc_h264 -lvenc_h265 -lvenc_jpeg -lsbm -laftertreatment -lscaledown -lfbm
	
CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0 

ANDROID_UTILS_DEF = -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX -DHAVE_POSIX_CLOCKS -DHAVE_PRCTL

SDKLIB_DEF = -DWATERMARK -DCDX_V27 -DSUPPORT_NEW_DRIVER 

DEFINES += $(ANDROID_UTILS_DEF) $(SDKLIB_DEF) $(CEDAR_MACORS)

LIBS += -lMemAdapter -lvdecoder -lVE -lcdc_base -lvideoengine -lcdx_common -lcdx_base 

#LIBS += -L$(SDK_PATH)/libs -lsdk_compose -lsdk_disp -lsdk_g2d -lsdk_dvr -lsdk_player \
#		 -lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_misc 
		 
#LIBS += -L$(SDK_PATH)/libs -lsdk_disp -lsdk_g2d -lsdk_player \
#		 -lsdk_log -lsdk_sound -lsdk_storage \

LIBS += -lsdk_log -lsdk_player -lsdk_sound  -lsdk_disp -lsdk_memory  -lsdk_misc 

all: $(Target) 

$(Target): autplayerTest.cpp
	$(CPP) autplayerTest.cpp -o $(Target) $(CXXFLAGS) $(LDFLAGS) $(DEFINES) $(CEDAR_LINK_NEW) $(LIBS)
	@echo "generate $(Target) success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall install distclean

#清除所有目标文件以及生成的最终目标文仿
clean:
	-rm -f $(Target) $(COBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)	
