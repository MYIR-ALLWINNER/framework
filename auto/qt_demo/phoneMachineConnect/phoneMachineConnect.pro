#-------------------------------------------------
#
# Project created by QtCreator 2018-09-21T16:26:08
#
#-------------------------------------------------
!include(../car_app/prodefine){
    #error(" Couldn't find the prodefinei file! ")
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phoneMachineConnect
TEMPLATE = app
CONFIG+=debug
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -L../navigation/libs -lnavigation

SOURCES += \
        main.cpp \
        pmmain.cpp \
    customwidget.cpp \
    failprompt.cpp \
    help.cpp \
    declaraction.cpp

HEADERS += \
        pmmain.h \
    customwidget.h \
    failprompt.h \
    help.h \
    declaraction.h

FORMS += \
        pmmain.ui \
    failprompt.ui \
    help.ui \
    declaraction.ui

RESOURCES += \
    pmImages.qrc
CEDAR_LINK_NEW = -ladecoder -laencoder -lcdx_base -lcdx_common \
-lcdx_muxer -lcdx_parser -lcdx_playback -lcdx_stream \
-lMemAdapter  -lcdc_base  -lsubdecoder -lvdecoder -lvencoder -lVE -lvideoengine \
-lxmetadataretriever -lxplayer

AWSDK_DIR=	$$PWD/../../sdk_lib/
dbusc_DIR=	$$PWD/../../dbuscommirror/

unix:!macx: LIBS += -L$$AWSDK_DIR/ -lsdk -L$$AWSDK_DIR/libs/ -lawcommirror -leve_event -lsdk_g2d -lmdas -lsdk_compose  -lsdk_disp  -lsdk_dvr   -lsdk_player  -lsdk_tr \
-L $$PWD/../../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/lib/ -lGLESv2 \
-L$$AWSDK_DIR/cedarx/lib/ -Wl,--no-undefined $$CEDAR_LINK_NEW -lrt -lpthread -lz -lcrypto -lssl -ltinyalsa

INCLUDEPATH += 	$$dbusc_DIR $$AWSDK_DIR/ \
                                $$AWSDK_DIR/include/ \
                                $$AWSDK_DIR/include/disp2/ \
                                $$AWSDK_DIR/media  \
                                $$AWSDK_DIR/camera \
								  $$AWSDK_DIR/misc/ \
                                $$AWSDK_DIR/include/utils/ \
                                $$PWD/../../../../external-packages/gpu/mali400/fbdev/header_files/include/  \
                                $$PWD/../../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/include \
                                $$AWSDK_DIR/storage/ \
                                $$AWSDK_DIR/sound/ \
                                $$AWSDK_DIR/misc/ \
                                $$AWSDK_DIR/camera/allwinnertech/include \
                                $$AWSDK_DIR/camera/allwinnertech/water_mark/ \
                                $$AWSDK_DIR/camera/adas/ $$AWSDK_DIR/storage/ \
                                $$AWSDK_DIR/sound/ \
                                $$AWSDK_DIR/memory/ \
                                $$AWSDK_DIR/cedarx/include \
                                $$AWSDK_DIR/cedarx/include/xplayer \
                                $$AWSDK_DIR/cedarx/include/xplayer/include \
                                $$AWSDK_DIR/cedarx/include/xmetadataretriever/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/common/plugin/	\
                                $$AWSDK_DIR/cedarx/include/libcore/common/iniparser/	\
                                $$AWSDK_DIR/cedarx/include/libcore/base/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/bd/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/hls/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/playlist/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/wav/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mpg/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/aiff/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/id3v2/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/sstr/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/flv/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/dash/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ogg/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/base/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/env/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/awts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mp3/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mms	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/flac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/AwSpecialStream/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mmshttp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/dsd/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/m3u9/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ape/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/g729/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/pmp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/aac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mkv/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/asf/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/atrac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/AwRawStream/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/remux/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/amr/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/avi/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/caf/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mov/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/base/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/aac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/mp4/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/ts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/playback/	\
                                $$AWSDK_DIR/cedarx/include/libcore/playback/include	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/aes/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/mms/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/http/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/dtmb/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/rtsp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/rtmp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/udp/	\
                                $$AWSDK_DIR/cedarx/include/libcedarc/include/	\
                                $$AWSDK_DIR/cedarx/include/external/include/live/	\
                                $$AWSDK_DIR/cedarx/include/external/include/alsa/	\
                                $$AWSDK_DIR/cedarx/include/external/include/alsa/sound/	\
                                $$AWSDK_DIR/cedarx/include/external/include/openssl/	\
                                $$AWSDK_DIR/cedarx/include/external/include/libxml/	\
                                $$AWSDK_DIR/cedarx/include/external/include/adecoder/	\
                                $$AWSDK_DIR/cedarx/include/external/include/aencoder/	\
                                $$AWSDK_DIR/cedarx/include/external/include/zlib/

DEPENDPATH +=$$dbusc_DIR  $$PWD/../../sdk_t7 $$AWSDK_DIR/include/ \
                $$AWSDK_DIR/include/disp2 \
                $$AWSDK_DIR/media/  \
                $$AWSDK_DIR/camera/ \
				$$AWSDK_DIR/misc/ \
                $$AWSDK_DIR/memory/ \
                $$AWSDK_DIR/include/utils  \
                $$PWD/../../../../external-packages/gpu/mali400/fbdev/header_files/include/  \
                $$PWD/../../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/include/ \
                $$AWSDK_DIR/storage/ \
                $$AWSDK_DIR/sound/  \
                $$AWSDK_DIR/misc/ \
                                $$AWSDK_DIR/cedarx/include \
                                $$AWSDK_DIR/cedarx/include/xplayer \
                                $$AWSDK_DIR/cedarx/include/xplayer/include \
                                $$AWSDK_DIR/cedarx/include/xmetadataretriever/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/common/plugin/	\
                                $$AWSDK_DIR/cedarx/include/libcore/common/iniparser/	\
                                $$AWSDK_DIR/cedarx/include/libcore/base/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/bd/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/hls/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/playlist/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/wav/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mpg/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/aiff/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/id3v2/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/sstr/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/flv/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/dash/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ogg/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/base/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/env/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/awts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mp3/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mms	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/flac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/AwSpecialStream/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mmshttp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/dsd/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/m3u9/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ape/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/g729/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/pmp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/aac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mkv/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/asf/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/atrac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/AwRawStream/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/remux/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/amr/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/avi/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/ts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/caf/	\
                                $$AWSDK_DIR/cedarx/include/libcore/parser/mov/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/base/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/aac/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/mp4/	\
                                $$AWSDK_DIR/cedarx/include/libcore/muxer/ts/	\
                                $$AWSDK_DIR/cedarx/include/libcore/playback/	\
                                $$AWSDK_DIR/cedarx/include/libcore/playback/include	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/include/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/aes/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/mms/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/http/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/dtmb/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/rtsp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/rtmp/	\
                                $$AWSDK_DIR/cedarx/include/libcore/stream/udp/	\
                                $$AWSDK_DIR/cedarx/include/libcedarc/include/	\
                                $$AWSDK_DIR/cedarx/include/external/include/live/	\
                                $$AWSDK_DIR/cedarx/include/external/include/alsa/	\
                                $$AWSDK_DIR/cedarx/include/external/include/alsa/sound/	\
                                $$AWSDK_DIR/cedarx/include/external/include/openssl/	\
                                $$AWSDK_DIR/cedarx/include/external/include/libxml/	\
                                $$AWSDK_DIR/cedarx/include/external/include/adecoder/	\
                                $$AWSDK_DIR/cedarx/include/external/include/aencoder/	\
                                $$AWSDK_DIR/cedarx/include/external/include/zlib/

DEFINES += CDX_V27 HAVE_PTHREADS SUPPORT_NEW_DRIVER HAVE_SYS_UIO_H ANDROID_SMP=1 __ARM_HAVE_DMB __ARM_HAVE_LDREX_STREX __ARM_HAVE_LDREXD \
           __ARM_HAVE_VFP __ARM_HAVE_NEON OPTION_CC_GNUEABIHF=1 OPTION_CC_GNUEABI=2 OPTION_CC_UCGNUEABI=3 \
           _GNU_SOURCE OPTION_CC_GNUEABIHF=1 OPTION_CC_GNUEABI=2 OPTION_CC_UCGNUEABI=3 OPTION_CC_LINUX_UCGNUEABI=4 OPTION_CC_LINUX_MUSLGNUEABI=5 OPTION_CC_LINUX_MUSLGNUEABI64=6 OPTION_OS_ANDROID=1 OPTION_OS_LINUX=2 OPTION_OS_VERSION_ANDROID_4_2=1 OPTION_OS_VERSION_ANDROID_4_4=2 OPTION_OS_VERSION_ANDROID_5_0=3 OPTION_OS_VERSION_ANDROID_6_0=4 OPTION_MEMORY_DRIVER_SUNXIMEM=1 OPTION_MEMORY_DRIVER_ION=2 OPTION_PRODUCT_PAD=1 OPTION_PRODUCT_TVBOX=2 OPTION_PRODUCT_OTT_CMCC=3 OPTION_PRODUCT_IPTV=4 OPTION_PRODUCT_DVB=5 OPTION_PRODUCT_LOUDSPEAKER=6 OPTION_CHIP_R8=1 OPTION_CHIP_R16=2 OPTION_CHIP_C500=3 OPTION_CHIP_R58=4 OPTION_CHIP_R18=5 OPTION_CHIP_T2=6 OPTION_CHIP_T3=7 OPTION_DRAM_INTERFACE_DDR1_16BITS=1 OPTION_DRAM_INTERFACE_DDR1_32BITS=2 OPTION_DRAM_INTERFACE_DDR2_16BITS=3 OPTION_DRAM_INTERFACE_DDR2_32BITS=4 OPTION_DRAM_INTERFACE_DDR3_16BITS=5 OPTION_DRAM_INTERFACE_DDR3_32BITS=6 OPTION_DRAM_INTERFACE_DDR3_64BITS=7 OPTION_CMCC_NO=0 OPTION_CMCC_YES=1 OPTION_DTV_NO=0 OPTION_DTV_YES=1 OPTION_ALI_YUNOS_NO=0 OPTION_ALI_YUNOS_YES=1 OPTION_IS_CAMERA_DECODER_NO=0 OPTION_IS_CAMERA_DECODER_YES=1 OPTION_VE_IPC_DISABLE=1 OPTION_VE_IPC_ENABLE=2 OPTION_NO_DEINTERLACE=0 OPTION_HW_DEINTERLACE=1 OPTION_SW_DEINTERLACE=2 LINUX_VERSION_3_4=1 LINUX_VERSION_3_10=2 DROP_DELAY_FRAME_NONE=0 DROP_DELAY_FRAME_720P=1 DROP_DELAY_FRAME_4K=2 ZEROCOPY_PIXEL_FORMAT_NONE=0 ZEROCOPY_PIXEL_FORMAT_YUV_MB32_420=1 ZEROCOPY_PIXEL_FORMAT_YV12=2 ZEROCOPY_PIXEL_FORMAT_NV21=3 GPU_Y16_C16_ALIGN=1 GPU_Y32_C16_ALIGN=2 GPU_Y16_C8_ALIGN=3 ZEROCOPY_HAL_PIXEL_FORMAT_AW_YUV_PLANNER420=1 ZEROCOPY_HAL_PIXEL_FORMAT_AW_YVU_PLANNER420=2 DEINTERLACE_FORMAT_MB32_12=1 DEINTERLACE_FORMAT_NV=2 DEINTERLACE_FORMAT_NV21=3 DEINTERLACE_FORMAT_NV12=4 OUTPUT_PIXEL_FORMAT_NV21=1 OUTPUT_PIXEL_FORMAT_YV12=2 OUTPUT_PIXEL_FORMAT_MB32=3 GPU_ALIGN_STRIDE_16=1 GPU_ALIGN_STRIDE_32=2 OPTION_HAVE_ZLIB=1 OPTION_NO_ZLIB=2 OPTION_HAVE_SSL=1 OPTION_NO_SSL=2 OPTION_HAVE_LIVE555=1 OPTION_NO_LIVE555=2 CONFIG_CC=4 CONFIG_OS=2 CONFIG_CHIP=7 CONFIG_ALI_YUNOS=0 CONFIG_OS_VERSION=2 CONFIG_TARGET_PRODUCT= CONFIG_PRODUCT=2 CONFIG_HAVE_ZLIB=1 CONFIG_HAVE_SSL=1 CONFIG_HAVE_LIVE555=2 CONFIG_MEMORY_DRIVER=2 CONFIG_DRAM_INTERFACE=6 CONFIG_VE_IPC=1 CONFIG_CMCC=0 CONFIG_DTV=0 CONFIG_IS_CAMERA_DECODER=0 CONFIG_DEINTERLACE=0 GPU_TYPE_MALI=1 CONFIG_ARM_VERSION= ENABLE_SUBTITLE_DISPLAY_IN_CEDARX=0 DTV=no LINUX_VERSION=2 USE_NEW_BDMV_STREAM=0 PLAYREADY_DRM_INVOKE=0 H265_4K_CHECK_SCALE_DOWN=1 NON_H265_4K_NOT_SCALE_DOWN=0 SUPPORT_H265=0 ANTUTU_NOT_SUPPORT=1 ENABLE_MEDIA_BOOST=1 DROP_DELAY_FRAME=2 ROTATE_PIC_HW=0 VE_PHY_OFFSET=0x40000000 ZEROCOPY_PIXEL_FORMAT=3 GPU_Y_C_ALIGN=1 SEND_3_BLACK_FRAME_TO_GPU=0 ZEROCOPY_DYNAMIC_CHECK=1 GRALLOC_PRIV=0 VIDEO_DIRECT_ACCESS_DE=0 KEY_PARAMETER_GET=0 DISPLAY_CMD_SETVIDEOSIZE_POSITION=0 DEINTERLACE_IOWR=0 DEINTERLACE_FORMAT=4 NEW_DISPLAY_DOUBLE_STREAM_NEED_NV21=1 OUTPUT_PIXEL_FORMAT=1 NOT_DROP_FRAME=1 SOUND_DEVICE_SET_RAW_FLAG=0 NATIVE_WIN_DISPLAY_CMD_GETDISPFPS=0 IMG_NV21_4K_ALIGN=0 DEINTERLACE_ADDR_64=0

DEFINES +=  WATERMARK_ENABLE HAVE_PRCTL WATERMARK ADAS_ENABLE
