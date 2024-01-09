
include $(top_srcdir)/Makefile.inc

bin_PROGRAMS = demoVdecoder

demoVdecoder_SOURCES =  ./demoVdecoder.c

demoVdecoder_CFLAGS = $(CFLAGS_CDXG)
#jpegdemo_CPPFLAGS = $(CPPFLAGS_CDXG)
LOCAL_INCLUDE = -I$(top_srcdir) \
		-I$(top_srcdir)/libcore/base/include \
		-I$(top_srcdir)/libcore/stream/include \
		-I$(top_srcdir)/libcore/parser/include \
		-I$(top_srcdir)/libcore/common/iniparser \
		-I$(top_srcdir)/external/include/adecoder \
 		-I$(top_srcdir)/external/include \
		-I$(top_srcdir)/../libcedarc/include

demoVdecoder_CFLAGS += $(LOCAL_INCLUDE)

demoVdecoder_LDFLAGS = $(LDFLAGS_CDXG)

demoVdecoder_LDADD = $(top_srcdir)/libcore/parser/base/libcdx_parser.la \
			$(top_srcdir)/libcore/base/libcdx_base.la \
			$(top_srcdir)/libcore/stream/base/libcdx_stream.la \
			$(top_srcdir)/libcore/common/libcdx_common.la

LOCAL_LIB = -lpthread -lz -lssl -lvdecoder  -lVE \
		-lcrypto -lMemAdapter -lcdc_base -lvideoengine
demoVdecoder_LDFLAGS += $(LOCAL_LIB)

