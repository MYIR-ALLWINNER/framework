LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

include $(LOCAL_PATH)/../../config.mk
CEDARC = $(TOP)/frameworks/av/media/libcedarc/
CEDARX = $(LOCAL_PATH)/../../
################################################################################
## set flags for golobal compile and link setting.
################################################################################

CONFIG_FOR_COMPILE = 
CONFIG_FOR_LINK = 

LOCAL_CFLAGS += $(CONFIG_FOR_COMPILE)
LOCAL_MODULE_TAGS := optional

## set the include path for compile flags.
LOCAL_SRC_FILES = \
                $(notdir $(wildcard $(LOCAL_PATH)/*.c))

LOCAL_C_INCLUDES := $(SourcePath)                             \
                    $(LOCAL_PATH)/../../                      \
        $(TOP)/frameworks/av/                               \
        $(TOP)/frameworks/av/include/                       \
        $(TOP)/frameworks/native/include/                   \
                    $(CEDARC)/include/                        \
                    $(CEDARX)/awrecorder/                     \
                    $(CEDARX)/libcore/base/                   \
                    $(CEDARX)/libcore/include/                \
                    $(CEDARX)/libcore/base/include/           \
                    $(CEDARX)/libcore/muxer/include/          \
                    $(CEDARX)/external/include/aencoder/      \
                    $(CEDARX)/external/include/               \

LOCAL_SHARED_LIBRARIES := \
			libvencoder \
			libvenc_base \
			libcdx_muxer  \
			libawrecorder   \
			libVE       \
			libMemAdapter   \
            libcutils       \
            libutils        \
            liblog         \
            libcdc_base     \
            libcdx_base     \
            libcdx_common   \
            libcrypto

LOCAL_32_BIT_ONLY := true
LOCAL_MODULE:= recorderdemo

include $(BUILD_EXECUTABLE)
