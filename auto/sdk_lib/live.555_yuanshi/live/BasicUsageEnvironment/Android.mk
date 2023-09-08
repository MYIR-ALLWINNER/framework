LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -O2 -DSOCKLEN_T=socklen_t -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -fPIC -DPIC -DNO_SSTREAM=1 -DLOCALE_NOT_USED -g \
    -fexceptions

LOCAL_SRC_FILES = \
		$(notdir $(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/../UsageEnvironment/include \
    $(LOCAL_PATH)/../groupsock/include 

LOCAL_MODULE := libBasicUsageEnvironment

include $(BUILD_STATIC_LIBRARY) 
