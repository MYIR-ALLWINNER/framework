
include $(top_srcdir)/Makefile.inc

lib_LTLIBRARIES = liblog.la

liblog_la_SOURCES =  logd_write.c \
                     logprint.c   \
                     event_tag_map.c

liblog_la_CFLAGS = $(KUN_CFLAGS)

LOCAL_INCLUDE = -I$(top_srcdir)/ \
                -I$(top_srcdir)/include \
                -I$(top_srcdir)/include/log 

liblog_la_CFLAGS += $(LOCAL_INCLUDE) \
                    -DANDROID_SMP=0 -DLIBC_STATIC \
                    -DDLMALLOC_DEBUG \
                    -DHAVE_PTHREADS -DHOST_OS=linux

liblog_la_LDFLAGS = $(KUN_LDFLAGS_FL)
