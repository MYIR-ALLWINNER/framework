LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#/home/linbeihong/workspace/A83/android/prebuilts/ndk/9/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi/libsupc++.a
#/android/prebuilts/ndk/9/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi-v7a/libsupc++.a

#STL_PATH = /home/linbeihong/workspace/A83/android/prebuilts/ndk/9/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi-v7a

#32bits
STL_PATH = /home/linbeihong/workspace/A64/android/prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a
#64bits
#STL_PATH = /home/linbeihong/workspace/A64/android/prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a

LOCAL_LDLIBS += -L$(STL_PATH) -lsupc++

#$(warning $(LOCAL_LDLIBS))

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/BasicUsageEnvironment/include \
    $(LOCAL_PATH)/UsageEnvironment/include \
    $(LOCAL_PATH)/groupsock/include \
    $(LOCAL_PATH)/liveMedia \
    $(LOCAL_PATH)/liveMedia/include               

LOCAL_CFLAGS := -DSOCKLEN_T=socklen_t -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -fPIC -DPIC -DNO_SSTREAM=1 -DLOCALE_NOT_USED \
   -O2 -g -fexceptions 

#LOCAL_CFLAGS += $(CDX_CFLAGS)

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := liblive555

#LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \
    libliveMedia \
    libBasicUsageEnvironment \
    libUsageEnvironment \
    libgroupsock
    
#LOCAL_LDFLAGS += \
#    /home/linbeihong/workspace/A83/android/prebuilts/ndk/9/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi/libsupc++.a

LOCAL_SHARED_LIBRARIES = libcutils libstdc++ libc libdl

ifeq ($(TARGET_ARCH),arm)
    LOCAL_CFLAGS += -Wno-psabi
endif

LOCAL_MULTILIB := 32
#LOCAL_MULTILIB := 64 

include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
