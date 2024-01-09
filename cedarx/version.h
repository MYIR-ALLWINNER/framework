/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : version.h
 * Description : cedarx version header file
 * History :
 *
 */

#ifndef CDX_VERSION_H
#define CDX_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#define REPO_TAG "cedarx"
#define REPO_BRANCH "stable_v2.8_common"
#define REPO_COMMIT "967535b8ff6a073cb4f38e85a4ae5fa6008014d8"
#define REPO_DATE "Mon, 15 May 2017 01:30:22 +0000 (09:30 +0800)"
#define RELEASE_AUTHOR ""

static inline void LogVersionInfo(void)
{
    logd("\n"
         ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CedarX <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
         "tag   : %s\n"
         "branch: %s\n"
         "commit: %s\n"
         "date  : %s\n"
         "author: %s\n"
         "----------------------------------------------------------------------\n",
         REPO_TAG, REPO_BRANCH, REPO_COMMIT, REPO_DATE, RELEASE_AUTHOR);
}

/* usage: TagVersionInfo(myLibTag) */
#define TagVersionInfo(tag) \
    static void VersionInfo_##tag(void) __attribute__((constructor));\
    void VersionInfo_##tag(void) \
    { \
        logd("-------library tag: %s-------", #tag);\
        LogVersionInfo(); \
    }

#ifdef __cplusplus
}
#endif

#endif


