#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T11:20:17
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/CameraUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
MOC_DIR = build
RCC_DIR = build
UI_DIR = build
OBJECTS_DIR = build

SOURCES += \
        src/main.cpp \
        src/main_desktop.cpp \
    src/setfirst.cpp \
    src/settings.cpp \
    src/about.cpp \
    src/front_adas_setting.cpp \
    src/front_camera_setting.cpp \
    src/rear_adas_setting.cpp \
    src/rear_camera_setting.cpp \
    src/reverseline.cpp \
    src/timesetting.cpp \
    src/preview.cpp \
    src/adas.cpp \
    src/mylabel.cpp \
    src/dashboard.cpp \
    src/myspeed.cpp \
    src/slave_picturewidget.cpp \
    src/slave_videowidget.cpp \
    src/cprojectionpicture.cpp \
    src/frmmessagebox.cpp \
    src/reverselinewidget.cpp \
    src/reverseline_setting.cpp \
    src/midwindow.cpp \
    src/AutoMount.cpp \
    unicodeandutf8.cpp \
    src/picture_view.cpp \
    src/picturewidget.cpp \
    src/cameraseldlg.cpp \
    src/recordseldlg.cpp

HEADERS += \
        src/main_desktop.h \
    src/setfirst.h \
    src/settings.h \
    src/about.h \
    src/front_adas_setting.h \
    src/front_camera_setting.h \
    src/rear_adas_setting.h \
    src/rear_camera_setting.h \
    src/reverseline.h \
    src/timesetting.h \
    src/preview.h \
    src/adas.h \
    src/mylabel.h \
    src/picture_view.h \
    src/picturewidget.h \
    src/dashboard.h \
    src/myspeed.h \
    src/slave_picturewidget.h \
    src/slave_videowidget.h \
    src/cprojectionpicture.h \
    src/frmmessagebox.h \
    src/reverselinewidget.h \
    src/reverseline_setting.h \
    src/midwindow.h \
    src/AutoMount.h \
    unicodeandutf8.h \
    src/cameraseldlg.h \
    src/recordseldlg.h


FORMS += \
        ui/main_desktop.ui \
    ui/setfirst.ui \
    ui/settings.ui \
    ui/about.ui \
    ui/front_adas_setting.ui \
    ui/front_camera_setting.ui \
    ui/rear_adas_setting.ui \
    ui/rear_camera_setting.ui \
    ui/reverseline.ui \
    ui/timesetting.ui \
    ui/preview.ui \
    ui/adas.ui \
    ui/picture_view.ui \
    ui/videowidget.ui \
    ui/picturewidget.ui \
    ui/dashboard.ui \
    ui/slave_picturewidget.ui \
    ui/slave_videowidget.ui \
    ui/frmmessagebox.ui \
    ui/reverseline_setting.ui \
    ui/cameraseldlg.ui \
    ui/recordseldlg.ui

RESOURCES += \
    image/image.qrc \
    image/font.qrc

LIBSDK_PATH = ../../sdk_lib

#unix:!macx: LIBS += -L$$PWD/$$LIBSDK_PATH/ -lsdk -L$$PWD/$$LIBSDK_PATH/libs/ -lsdk_func \
unix:!macx: LIBS += -L$$PWD/$$LIBSDK_PATH/ -L$$PWD/$$LIBSDK_PATH/libs/ -lsdk_compose  -lsdk_disp  -lsdk_dvr  -lsdk_g2d -lsdk_player  \
-lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_misc \
-L../../../../../tools/pack/chips/$$(LICHEE_CHIP)/hal/gpu/fbdev/lib/ \
                                        -L$$PWD/$$LIBSDK_PATH/cedarx/lib/ -Wl,--no-undefined   -lcdx_playback -lcdx_common -laencoder -lawrecorder -lxplayer   -lcdx_muxer \
										-lvenc_h264 -lvenc_h265 -lvenc_base -lvenc_common -laftertreatment -lsbm -lscaledown -lfbm -lvenc_jpeg \
             -lcdx_parser -lsubdecoder -lvideoengine -lvdecoder -llive555 -lcdx_stream   -lvencoder -lVE   -lcdc_base -lMemAdapter -ladecoder -laencoder -lxmetadataretriever -lcdx_base \
			 -lrt -lpthread -lz -lcrypto -lssl -ltinyalsa -lvenc_base -lcdx_ion -lasound

INCLUDEPATH += 		$$PWD/$$LIBSDK_PATH \
					$$PWD/$$LIBSDK_PATH/eve_module/include \
					$$PWD/$$LIBSDK_PATH/eve_module \
					$$PWD/$$LIBSDK_PATH/include \
					$$PWD/$$LIBSDK_PATH/include/disp2 \
					$$PWD/$$LIBSDK_PATH/media  \
					$$PWD/$$LIBSDK_PATH/include/camera \
					$$PWD/$$LIBSDK_PATH/sdk_misc \
					$$PWD/$$LIBSDK_PATH/include/utils ./ ./src/ \
					$$PWD/../../../external-packages/gpu/mali400/fbdev/header_files/include/  \
					$$PWD/../../../../tools/pack/chips/$$(LICHEE_CHIP)/hal/gpu/fbdev/include  \
					$$PWD/Commons \
					$$PWD/$$LIBSDK_PATH/include/storage/ \
					$$PWD/$$LIBSDK_PATH/storage/ \
					$$PWD/$$LIBSDK_PATH/sound/ \
					$$PWD/$$LIBSDK_PATH/misc/ \
					$$PWD/$$LIBSDK_PATH/camera/allwinnertech/include \
					$$PWD/$$LIBSDK_PATH/camera/allwinnertech/water_mark/ \
					$$PWD/$$LIBSDK_PATH/camera/adas/ $$PWD/$$LIBSDK_PATH/storage/ \
					$$PWD/$$LIBSDK_PATH/sound/ \
					$$PWD/$$LIBSDK_PATH/memory/ \
					$$PWD/$$LIBSDK_PATH/audioenc/ \	
				$$PWD/$$LIBSDK_PATH/cedarx/include \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xplayer \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xplayer/include \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xmetadataretriever/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/common/plugin/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/common/iniparser/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/base/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/bd/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/hls/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/playlist/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/wav/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mpg/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/aiff/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/id3v2/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/sstr/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/flv/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/dash/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ogg/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/base/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/env/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/awts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mp3/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mms	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/flac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/AwSpecialStream/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mmshttp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/dsd/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/m3u9/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ape/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/g729/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/pmp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/aac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mkv/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/asf/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/atrac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/AwRawStream/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/remux/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/amr/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/avi/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/caf/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mov/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/base/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/aac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/mp4/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/ts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/playback/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/playback/include	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/aes/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/mms/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/http/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/dtmb/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/rtsp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/rtmp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/udp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcedarc/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/live/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/alsa/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/alsa/sound/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/openssl/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/libxml/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/adecoder/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/aencoder/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/zlib/	
#DEFINES += QT_ROTATE_APP
				  
DEPENDPATH += $$PWD/$$LIBSDK_PATH $$PWD/$$LIBSDK_PATH/include \
                $$PWD/$$LIBSDK_PATH/include/disp2 \
                $$PWD/$$LIBSDK_PATH/media  \
                $$PWD/$$LIBSDK_PATH/camera \
                $$PWD/$$LIBSDK_PATH/memory \
                $$PWD/$$LIBSDK_PATH/include/utils . ./src/ \
                $$PWD/../../../external-packages/gpu/mali400/fbdev/header_files/include/  \
                $$PWD/../../../../tools/pack/chips/$$(LICHEE_CHIP)/hal/gpu/fbdev/include \
                $$PWD/$$LIBSDK_PATH/storage/ \
                $$PWD/$$LIBSDK_PATH/sound/  \
                $$PWD/$$LIBSDK_PATH/misc/ \
				$$PWD/$$LIBSDK_PATH/cedarx/include \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xplayer \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xplayer/include \
				$$PWD/$$LIBSDK_PATH/cedarx/include/xmetadataretriever/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/common/plugin/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/common/iniparser/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/base/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/bd/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/hls/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/playlist/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/wav/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mpg/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/aiff/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/id3v2/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/sstr/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/flv/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/dash/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ogg/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/base/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/env/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/awts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mp3/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mms	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/flac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/AwSpecialStream/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mmshttp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/dsd/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/m3u9/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ape/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/g729/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/pmp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/aac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mkv/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/asf/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/atrac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/AwRawStream/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/remux/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/amr/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/avi/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/ts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/caf/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/parser/mov/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/base/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/aac/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/mp4/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/muxer/ts/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/playback/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/playback/include	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/aes/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/mms/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/http/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/dtmb/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/rtsp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/rtmp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcore/stream/udp/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/libcedarc/include/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/live/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/alsa/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/alsa/sound/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/openssl/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/libxml/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/adecoder/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/aencoder/	\
				$$PWD/$$LIBSDK_PATH/cedarx/include/external/include/zlib/	
				
#DEFINES += QT_ROTATE_APP
DEFINES += CDX_V27 HAVE_PTHREADS SUPPORT_NEW_DRIVER HAVE_SYS_UIO_H ANDROID_SMP=1 __ARM_HAVE_DMB __ARM_HAVE_LDREX_STREX __ARM_HAVE_LDREXD \
                                __ARM_HAVE_VFP __ARM_HAVE_NEON OPTION_CC_GNUEABIHF=1 OPTION_CC_GNUEABI=2 OPTION_CC_UCGNUEABI=3 \
           _GNU_SOURCE OPTION_CC_GNUEABIHF=1 OPTION_CC_GNUEABI=2 OPTION_CC_UCGNUEABI=3 OPTION_CC_LINUX_UCGNUEABI=4 OPTION_CC_LINUX_MUSLGNUEABI=5 OPTION_CC_LINUX_MUSLGNUEABI64=6 OPTION_OS_ANDROID=1 OPTION_OS_LINUX=2 OPTION_OS_VERSION_ANDROID_4_2=1 OPTION_OS_VERSION_ANDROID_4_4=2 OPTION_OS_VERSION_ANDROID_5_0=3 OPTION_OS_VERSION_ANDROID_6_0=4 OPTION_MEMORY_DRIVER_SUNXIMEM=1 OPTION_MEMORY_DRIVER_ION=2 OPTION_PRODUCT_PAD=1 OPTION_PRODUCT_TVBOX=2 OPTION_PRODUCT_OTT_CMCC=3 OPTION_PRODUCT_IPTV=4 OPTION_PRODUCT_DVB=5 OPTION_PRODUCT_LOUDSPEAKER=6 OPTION_CHIP_R8=1 OPTION_CHIP_R16=2 OPTION_CHIP_C500=3 OPTION_CHIP_R58=4 OPTION_CHIP_R18=5 OPTION_CHIP_T2=6 OPTION_CHIP_T3=7 OPTION_DRAM_INTERFACE_DDR1_16BITS=1 OPTION_DRAM_INTERFACE_DDR1_32BITS=2 OPTION_DRAM_INTERFACE_DDR2_16BITS=3 OPTION_DRAM_INTERFACE_DDR2_32BITS=4 OPTION_DRAM_INTERFACE_DDR3_16BITS=5 OPTION_DRAM_INTERFACE_DDR3_32BITS=6 OPTION_DRAM_INTERFACE_DDR3_64BITS=7 OPTION_CMCC_NO=0 OPTION_CMCC_YES=1 OPTION_DTV_NO=0 OPTION_DTV_YES=1 OPTION_ALI_YUNOS_NO=0 OPTION_ALI_YUNOS_YES=1 OPTION_IS_CAMERA_DECODER_NO=0 OPTION_IS_CAMERA_DECODER_YES=1 OPTION_VE_IPC_DISABLE=1 OPTION_VE_IPC_ENABLE=2 OPTION_NO_DEINTERLACE=0 OPTION_HW_DEINTERLACE=1 OPTION_SW_DEINTERLACE=2 LINUX_VERSION_3_4=1 LINUX_VERSION_3_10=2 DROP_DELAY_FRAME_NONE=0 DROP_DELAY_FRAME_720P=1 DROP_DELAY_FRAME_4K=2 ZEROCOPY_PIXEL_FORMAT_NONE=0 ZEROCOPY_PIXEL_FORMAT_YUV_MB32_420=1 ZEROCOPY_PIXEL_FORMAT_YV12=2 ZEROCOPY_PIXEL_FORMAT_NV21=3 GPU_Y16_C16_ALIGN=1 GPU_Y32_C16_ALIGN=2 GPU_Y16_C8_ALIGN=3 ZEROCOPY_HAL_PIXEL_FORMAT_AW_YUV_PLANNER420=1 ZEROCOPY_HAL_PIXEL_FORMAT_AW_YVU_PLANNER420=2 DEINTERLACE_FORMAT_MB32_12=1 DEINTERLACE_FORMAT_NV=2 DEINTERLACE_FORMAT_NV21=3 DEINTERLACE_FORMAT_NV12=4 OUTPUT_PIXEL_FORMAT_NV21=1 OUTPUT_PIXEL_FORMAT_YV12=2 OUTPUT_PIXEL_FORMAT_MB32=3 GPU_ALIGN_STRIDE_16=1 GPU_ALIGN_STRIDE_32=2 OPTION_HAVE_ZLIB=1 OPTION_NO_ZLIB=2 OPTION_HAVE_SSL=1 OPTION_NO_SSL=2 OPTION_HAVE_LIVE555=1 OPTION_NO_LIVE555=2 CONFIG_CC=4 CONFIG_OS=2 CONFIG_CHIP=7 CONFIG_ALI_YUNOS=0 CONFIG_OS_VERSION=2 CONFIG_TARGET_PRODUCT= CONFIG_PRODUCT=2 CONFIG_HAVE_ZLIB=1 CONFIG_HAVE_SSL=1 CONFIG_HAVE_LIVE555=2 CONFIG_MEMORY_DRIVER=2 CONFIG_DRAM_INTERFACE=6 CONFIG_VE_IPC=1 CONFIG_CMCC=0 CONFIG_DTV=0 CONFIG_IS_CAMERA_DECODER=0 CONFIG_DEINTERLACE=0 GPU_TYPE_MALI=1 CONFIG_ARM_VERSION= ENABLE_SUBTITLE_DISPLAY_IN_CEDARX=0 DTV=no LINUX_VERSION=2 USE_NEW_BDMV_STREAM=0 PLAYREADY_DRM_INVOKE=0 H265_4K_CHECK_SCALE_DOWN=1 NON_H265_4K_NOT_SCALE_DOWN=0 SUPPORT_H265=0 ANTUTU_NOT_SUPPORT=1 ENABLE_MEDIA_BOOST=1 DROP_DELAY_FRAME=2 ROTATE_PIC_HW=0 VE_PHY_OFFSET=0x40000000 ZEROCOPY_PIXEL_FORMAT=3 GPU_Y_C_ALIGN=1 SEND_3_BLACK_FRAME_TO_GPU=0 ZEROCOPY_DYNAMIC_CHECK=1 GRALLOC_PRIV=0 VIDEO_DIRECT_ACCESS_DE=0 KEY_PARAMETER_GET=0 DISPLAY_CMD_SETVIDEOSIZE_POSITION=0 DEINTERLACE_IOWR=0 DEINTERLACE_FORMAT=4 NEW_DISPLAY_DOUBLE_STREAM_NEED_NV21=1 OUTPUT_PIXEL_FORMAT=1 NOT_DROP_FRAME=1 SOUND_DEVICE_SET_RAW_FLAG=0 NATIVE_WIN_DISPLAY_CMD_GETDISPFPS=0 IMG_NV21_4K_ALIGN=0 DEINTERLACE_ADDR_64=0

DEFINES +=  WATERMARK_ENABLE HAVE_PRCTL WATERMARK

TRANSLATIONS +=filemanager_zh.ts

OTHER_FILES += \
    filemanager_zh.qm \
    filemanager_zh.ts
