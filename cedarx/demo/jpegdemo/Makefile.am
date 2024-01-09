
include $(top_srcdir)/Makefile.inc

bin_PROGRAMS = jpegdemo

jpegdemo_SOURCES =  ./jpegdemo.c

jpegdemo_CFLAGS = $(CFLAGS_CDXG)
jpegdemo_CPPFLAGS = $(CPPFLAGS_CDXG)
LOCAL_INCLUDE = -I$(top_srcdir) \
                -I$(top_srcdir)/../libcedarc/include \
                -I$(top_srcdir)/../libcedarc/base/include \
                -I$(top_srcdir)/libcore/base/include

jpegdemo_CFLAGS += $(LOCAL_INCLUDE)
jpegdemo_CPPFLAGS += $(LOCAL_INCLUDE)

jpegdemo_LDFLAGS = $(LDFLAGS_CDXG)

LOCAL_LIB = -lpthread -lz -lvdecoder -lvencoder -lVE \
            -lcrypto -lMemAdapter -lcdc_base -lcdx_base -lvideoengine
jpegdemo_LDFLAGS += $(LOCAL_LIB)

