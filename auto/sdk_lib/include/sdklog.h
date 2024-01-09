#ifndef _SDKLOG_H_
#define _SDKLOG_H_

#include <execinfo.h>
#include "stdio.h"

#ifdef USE_LOGCAT
#include <cutils/log.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
int sdk_log_print(int prio, const char *tag,const char *fmt, ...);
int sdk_log_tag_print(int prio, const char *log_tag, const char *tag,const char *fmt, ...);

#ifdef USE_LOGCAT

#else

#ifndef LOG_TAG
#define LOG_TAG ""
#endif

#define ALOGD(...) sdk_log_tag_print(5,LOG_TAG,"(D) : ",__VA_ARGS__)
#define ALOGV(...) sdk_log_tag_print(4,LOG_TAG,"(V) : ",__VA_ARGS__)
#define ALOGI(...) sdk_log_tag_print(3,LOG_TAG,"(I) : ",__VA_ARGS__)
#define ALOGW(...) sdk_log_tag_print(2,LOG_TAG,"(W) : ",__VA_ARGS__)
#define ALOGE(...) sdk_log_tag_print(1,LOG_TAG,"(E) : ",__VA_ARGS__)

#define SLOGE ALOGE
#define SLOGD ALOGD
#define SLOGW ALOGW
#define SLOGV ALOGV

#define LOGE ALOGE
#define LOGD ALOGD
#define LOGW ALOGW
#define LOGV ALOGV
#define __android_log_print sdk__android_log_print

#endif

int sdk_log_setlevel(int prio);
void print_stacktrace();

#ifdef __cplusplus
} // extern "C"
#endif
#endif