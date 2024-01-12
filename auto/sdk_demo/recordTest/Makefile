Target = recordTest
include ../makefile_cfg

DEFINES += -DUSE_LOGCAT
LOGCAT = logcat

CEDAR_LINK_NEW = -L$(SDK_PATH) -L$(SDK_PATH)/libs/ -L$(SDK_PATH)/cedarx/lib/ -Wl,--no-undefined -ladecoder -laencoder -lcdx_base -lcdx_common \
	-lcdx_muxer -lcdx_parser -lcdx_playback -lcdx_stream -lMemAdapter -lcdc_base -lsubdecoder -lvdecoder \
	-lvencoder -lVE -lvideoengine -lxmetadataretriever -lxplayer -lvenc_base -lawh264 -lvenc_codec -lcdx_ion \
	-lvenc_common -lvenc_h264 -lvenc_h265 -lvenc_jpeg -lsbm -laftertreatment -lscaledown -lfbm
CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0 

LIBS = -L$(SDK_PATH)/libs -lsdk_compose -lsdk_disp -lsdk_g2d -lsdk_dvr -lsdk_player \
		 -lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage \
                -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_misc -lasound -lrt -lpthread -lz -lcrypto -lssl -llive555
		 
#LIBS +=  $(LICHEE_BR_OUT)/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/libmali.so

ANDROID_UTILS_DEF = -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP=1 -D__ARM_HAVE_DMB -D__ARM_HAVE_LDREX_STREX -DHAVE_POSIX_CLOCKS -DHAVE_PRCTL
SDKLIB_DEF = -DWATERMARK -DCDX_V27 -DSUPPORT_NEW_DRIVER
DEFINES += $(ANDROID_UTILS_DEF) $(SDKLIB_DEF)

INC = -I./ \
	-I$(SDK_PATH)/include \
	-I$(SDK_PATH)/include/disp2 \
	-I$(SDK_PATH)/include/utils \
	-I$(SDK_PATH)/include/cutils/ \
	-I$(SDK_PATH)/include/media \
	-I$(SDK_PATH)/include/camera \
	-I$(SDK_PATH)/sdk_camera \
	-I$(SDK_PATH)/include/storage/ \
	-I$(SDK_PATH)/include/sound/ \
	-I$(SDK_PATH)/include/memory/ \
	-I$(SDK_PATH)/sdk_misc/ \
	-I$(SDK_PATH)/include/audioenc/ \
	-I$(SDK_PATH)/eve_module/include \
	-I$(SDK_PATH)/eve_module \
	
INC += $(CEDAR_INC)
	
all: $(Target)

$(Target): $(Target).cpp
	$(CPP) -c $(Target).cpp -o $(Target).o -g $(INC) $(CEDAR_MACORS) $(DEFINES) -DSDKLIB_TEST 
	$(CPP) -o $(Target) $(Target).o $(LIBS) $(CEDAR_LINK_NEW) -lrt -lpthread -lz -lcrypto -lssl 
	@echo "generate $(Target) success!!!"
	
.PHONY:clean cleanall install distclean

clean:
	-rm -f $(Target).o $(Target)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)
