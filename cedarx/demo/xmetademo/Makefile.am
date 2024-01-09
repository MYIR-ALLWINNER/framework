
include $(top_srcdir)/Makefile.inc

bin_PROGRAMS = xmetademo

xmetademo_SOURCES =  ./xmetademo.c

xmetademo_CFLAGS = $(CFLAGS_CDXG)
xmetademo_CPPFLAGS = $(CPPFLAGS_CDXG)
LOCAL_INCLUDE = -I$(top_srcdir) \
                -I$(top_srcdir)/xmetadataretriever/include  \
                -I$(top_srcdir)/libcore/base/include \
                -I$(top_srcdir)/libcore/stream/include \
                -I$(top_srcdir)/libcore/parser/include \
                -I$(top_srcdir)/libcore/common/iniparser \
                -I$(top_srcdir)/external/include/adecoder \
                -I$(top_srcdir)/../libcedarc/include

xmetademo_CFLAGS += $(LOCAL_INCLUDE)
xmetademo_CPPFLAGS += $(LOCAL_INCLUDE)

xmetademo_LDFLAGS = $(LDFLAGS_CDXG)

xmetademo_LDADD = $(top_srcdir)/libcore/parser/base/libcdx_parser.la \
                  $(top_srcdir)/libcore/base/libcdx_base.la \
                  $(top_srcdir)/libcore/stream/base/libcdx_stream.la \
                  $(top_srcdir)/xmetadataretriever/libxmetadataretriever.la \
                  $(top_srcdir)/libcore/common/libcdx_common.la

LOCAL_LIB = -lpthread -lz -lvdecoder -lvencoder -ladecoder -lsubdecoder -lVE \
            -lcrypto -lMemAdapter -lcdc_base -lvideoengine
xmetademo_LDFLAGS += $(LOCAL_LIB)

