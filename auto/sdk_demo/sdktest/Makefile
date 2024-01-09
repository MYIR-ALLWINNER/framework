Target = sdktest

include ../makefile_cfg

CUR_MODULE_VERSION = "V2.1.20220518"

DEFINES += -DMODULE_VERSION=\"$(CUR_MODULE_VERSION)\"

SDK_PATH = ../../sdk_lib

CEDAR_LINK_NEW = -L$(SDK_PATH)/cedarx/lib/ -Wl,--no-undefined -ladecoder -laencoder -lcdx_base -lcdx_common \
	-lcdx_muxer -lcdx_parser -lcdx_playback -lcdx_stream -lMemAdapter -lcdc_base -lsubdecoder -lvdecoder \
	-lvencoder -lVE -lvideoengine -lxmetadataretriever -lxplayer -lvenc_base -lvenc_codec -lcdx_ion	-lasound \
	-lvenc_common -lvenc_h264 -lvenc_h265 -lvenc_jpeg -lsbm -laftertreatment -lscaledown -lfbm

CEDAR_MACORS = -D_GNU_SOURCE -DCONFIG_CHIP=7 -DCONFIG_TARGET_PRODUCT= -DCONFIG_PRODUCT=2 \
				-DCONFIG_VE_IPC=1 -DROTATE_PIC_HW=0 -DVE_PHY_OFFSET=0x40000000 -DCONFIG_LOG_LEVEL=0

#DMS_LIB = -L$(PWD)/../../dms/allwinner/lib -ldms_sdk_protobuf_parser -lhobot_dms -lhobotdms_hal -lupload_config -lstorage_manager -lhobotdms_sdk -ljpeg \
#	 	-lopencv_world -lturbojpeg -lv4l2 -lx264 -lxvidcore
#LIBS = $(DMS_LIB)

LIBS = -L$(SDK_PATH)/libs -lsdk_compose -lsdk_disp -lsdk_g2d -lsdk_dvr -lsdk_player -lsdk_log -lsdk_camera \
		 -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_misc

LIBS += -lMemAdapter -lvencoder -lVE -lcdc_base -lvenc_jpeg -lvenc_common -lvenc_h264 -lvenc_h265  -lvenc_base
LIBS += -lrt -lpthread -lz -lcrypto -lssl
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
	-I$(SDK_PATH)/sdk_camera/moudle \
	-I$(SDK_PATH)/sdk_camera \
	-I$(SDK_PATH)/include/storage/ \
	-I$(SDK_PATH)/include/sound/ \
	-I$(SDK_PATH)/include/memory/ \
	-I$(SDK_PATH)/sdk_misc/ \
	-I$(SDK_PATH)/include/audioenc/

#LIBS += $(EVELIBS)
#EVEINC = -I./eve_module/ \
# 	-I./eve_module/include
#INC += $(EVEINC)

#LIBS += -law_opengles
#LIBS +=  $(LICHEE_BR_OUT)/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/libmali.so

all: $(Target)

$(Target): $(Target).cpp
	$(CPP) -c $(Target).cpp -o $(Target).o -g -no-pie $(INC) $(CEDAR_MACORS) $(DEFINES)
	$(CPP) -o $(Target) $(Target).o $(LIBS) $(CEDAR_LINK_NEW)
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo "generate $(Target) success!!!"

.PHONY:clean cleanall install distclean

#清除所有目标文件以及生成的最终目标文件
clean:
	-rm -f $(Target).o $(Target)

cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target)

distclean:cleanall

install:
	-cp $(Target) $(INSTATLL_PATH)
