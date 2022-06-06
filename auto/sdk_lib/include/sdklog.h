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
#ifdef USE_LOGCAT
#else
#define ALOGD(...) sdk_log_print(5,"(D) ",__VA_ARGS__)
#define ALOGV(...) sdk_log_print(4,"(V) ",__VA_ARGS__)
#define ALOGI(...) sdk_log_print(3,"(I) ",__VA_ARGS__)
#define ALOGW(...) sdk_log_print(2,"(W) ",__VA_ARGS__)
#define ALOGE(...) sdk_log_print(1,"(E) ",__VA_ARGS__)
#endif

int sdk_log_setlevel(int prio);
#ifdef USE_LOGCAT
#else
#define SLOGE ALOGE
#define SLOGD ALOGD
#define SLOGW ALOGW
#define SLOGV ALOGV
#define __android_log_print sdk__android_log_print
#endif
void print_stacktrace();
#ifdef __cplusplus
} // extern "C"
#endif
#endif