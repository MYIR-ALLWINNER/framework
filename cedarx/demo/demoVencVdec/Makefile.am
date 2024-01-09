
include $(top_srcdir)/Makefile.inc

bin_PROGRAMS = demoVencVdec

demoVencVdec_SOURCES =  ./EncoderDecoderTest.c

demoVencVdec_CFLAGS = $(CFLAGS_CDXG)

LOCAL_INCLUDE = -I$(top_srcdir) \
        -I$(top_srcdir)/libcore/include \
        -I$(top_srcdir)/libcore/base/include \
        -I$(top_srcdir)/../libcedarc/include

demoVencVdec_CFLAGS += $(LOCAL_INCLUDE)

demoVencVdec_LDFLAGS = $(LDFLAGS_CDXG)


LOCAL_LIB = -lpthread -lz -lvdecoder -lvencoder -lVE \
        -lcrypto -lMemAdapter -lcdc_base -lvideoengine
demoVencVdec_LDFLAGS += $(LOCAL_LIB)

