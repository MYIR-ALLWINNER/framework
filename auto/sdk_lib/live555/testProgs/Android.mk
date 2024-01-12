LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := openRTSP.cpp playCommon.cpp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/ \
    $(LOCAL_PATH)/../BasicUsageEnvironment/include \
    $(LOCAL_PATH)/../UsageEnvironment/include \
    $(LOCAL_PATH)/../groupsock/include \
    $(LOCAL_PATH)/../liveMedia \
    $(LOCAL_PATH)/../liveMedia/include

LOCAL_CFLAGS += 
LOCAL_STATIC_LIBRARIES += liblive555

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE := openRTSP
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := testRTSPClient.cpp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/ \
    $(LOCAL_PATH)/../BasicUsageEnvironment/include \
    $(LOCAL_PATH)/../UsageEnvironment/include \
    $(LOCAL_PATH)/../groupsock/include \
    $(LOCAL_PATH)/../liveMedia \
    $(LOCAL_PATH)/../liveMedia/include

LOCAL_CFLAGS += 
LOCAL_STATIC_LIBRARIES += liblive555

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE := testRTSPClient
include $(BUILD_EXECUTABLE)
