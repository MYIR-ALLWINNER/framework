LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

CEDARC = $(TOP)/frameworks/av/media/libcedarc/
CEDARX = $(LOCAL_PATH)/../../

CONFIG_FOR_COMPILE =
CONFIG_FOR_LINK =

LOCAL_CFLAGS += $(CONFIG_FOR_COMPILE)
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES:= jpegdemo.c

LOCAL_C_INCLUDES := $(SourcePath)                        \
                    $(CEDARC)/base/include     \
                    $(CEDARC)/include         \
                    $(CEDARC)/../libcedarx/libcore/base/include

LOCAL_SHARED_LIBRARIES := \
            libvdecoder     \
            liblog          \
            libvideoengine  \
            libcdc_base     \
            libcdx_base     \
            libVE           \
            libMemAdapter   \

LOCAL_MODULE:= jpegdemo

include $(BUILD_EXECUTABLE)
