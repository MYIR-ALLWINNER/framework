#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T15:04:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  qml quick quickwidgets

TARGET = CarlifeDemo
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
        src/carlifewindow.cpp \
    src/frmmessagebox.cpp \
    src/closebutton.cpp \
    src/scene.cpp \
    src/graphicsview.cpp

HEADERS += \
        src/carlifewindow.h \
    src/frmmessagebox.h \
    src/closebutton.h \
    src/scene.h \
    src/graphicsview.h

FORMS += \
        ui/carlifewindow.ui \
    ui/frmmessagebox.ui \
    ui/closebutton.ui \
    ui/scene.ui

RESOURCES += \
    image.qrc \
    font.qrc \
    qml.qrc
	
LIBSDK_PATH = ../../sdk_lib

#-lcdc_sdecoder -lsubdecoder
unix:!macx: LIBS += -L$$PWD/libs -lcarlifeservice -lcarlifevehicle -lprotobuf -lh264xplayer -ltinyplay -L$$PWD/$$LIBSDK_PATH/ -lsdk \
	-L$$PWD/$$LIBSDK_PATH/libs/ -lsdk_compose  -lsdk_disp -lsdk_dvr  -lsdk_g2d -lsdk_player  -lsdk_tr \
	-L$$PWD/$$LIBSDK_PATH/cedarx/lib/ -Wl,--no-undefined   -lcdx_playback -lcdx_common -laencoder -lawrecorder -lxplayer \
	-lcdx_muxer -lcdx_parser -lsubdecoder -lvideoengine -lvdecoder -lcdx_stream   -lvencoder -lVE   -lcdc_base -lMemAdapter \
	-ladecoder -laencoder -lxmetadataretriever -lcdx_base -lrt -lpthread -lz -lcrypto -lssl -ltinyalsa \
	-L../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/lib/ -lGLESv2 

INCLUDEPATH += 	$$PWD/$$LIBSDK_PATH \
				$$PWD/$$LIBSDK_PATH/audioenc \
				$$PWD/$$LIBSDK_PATH/include \
				$$PWD/$$LIBSDK_PATH/include/disp2 \
				$$PWD/$$LIBSDK_PATH/media  \
				$$PWD/$$LIBSDK_PATH/camera \
				$$PWD/$$LIBSDK_PATH/include/utils ./ ./src/ \
				$$PWD/../../../external-packages/gpu/mali400/fbdev/header_files/include/  \
				$$PWD/../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/include  \
				$$PWD/Commons \
				$$PWD/libs \
				$$PWD/$$LIBSDK_PATH/storage/ \
				$$PWD/$$LIBSDK_PATH/sound/ \
				$$PWD/$$LIBSDK_PATH/misc/ \
				$$PWD/$$LIBSDK_PATH/camera/allwinnertech/include \
				$$PWD/$$LIBSDK_PATH/camera/allwinnertech/water_mark/ \
				$$PWD/$$LIBSDK_PATH/camera/adas/ $$PWD/$$LIBSDK_PATH/storage/ \
				$$PWD/$$LIBSDK_PATH/sound/ \
				$$PWD/$$LIBSDK_PATH/memory/ \
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
                $$PWD/../../../../tools/pack/chips/sun8iw17p1/hal/gpu/fbdev/include \
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
