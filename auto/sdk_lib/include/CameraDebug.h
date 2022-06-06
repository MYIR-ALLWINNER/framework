#ifndef __HAL_CAMERA_DEBUG_H__
#define __HAL_CAMERA_DEBUG_H__

#define CAMERA_HAL_VERSION      "3000130327_V1.0"

#define CAMERA_HAL_MODE_OLD     1
#if (CAMERA_HAL_MODE_OLD == 1)
#define USE_OLD_MODE
#else
#define USE_NEW_MODE
#endif


//enable 4in1for 360 
#define CAMERA_MANAGER_ENABLE

//note:T7's 360compose video is /dev/video0~3
//if not T7,360compose video is /dev/video4~7
#if defined(_T507_)
#define TVD_DEV_ID_START 2
#elif defined(_T7_P1_)
#define TVD_DEV_ID_START 0
#else
#define TVD_DEV_ID_START 4
#endif

#define NB_CAMERA 4 //number of camera



#define ALIGN_4K(x) (((x) + (4095)) & ~(4095))
#define ALIGN_32B(x) (((x) + (31)) & ~(31))
#define ALIGN_16B(x) (((x) + (15)) & ~(15))
#define ALIGN_8B(x) (((x) + (7)) & ~(7))

#define DBG_CAMERA_HARDWARE     0
#define DBG_V4L2_CAMERA         0
#define DBG_PREVIEW             0
#define DBG_CALLBACK            0
#define DBG_CAMERA_FACTORY      0
#define DBG_CAMERA_CONFIG       0
#define DBG_BUFFER_LIST         0

/* Defines whether we should trace parameter changes. */
#define DEBUG_PARAM 1

#define DEBUG_MSG   1

// enable all print information
//#define LOG_NDEBUG 0

#define F_LOG (void(0)); //ALOGV("%s, line: %d", __FUNCTION__, __LINE__);

#ifndef LOGV
#define LOGV    ALOGV
#define LOGD    ALOGD
#define LOGW    ALOGW
#define LOGE    ALOGE
#endif

#ifndef ALOGE_IF
#define LOGE_IF ALOGE_IF
#define LOGW_IF ALOGW_IF
#endif

// performance debug
#define DBG_TIME_ENABLE     0
#if DBG_TIME_ENABLE
#define LOG_TIME            ALOGD
#define DBG_TIME_BEGIN(inf, en)                                         \
    int64_t llt_ms = systemTime() / 1000000;                            \
    int64_t lt_ms = llt_ms;                                             \
    int64_t nt_ms = 0;                                                  \
    if (en) LOG_TIME("\t[T_DBG_bgn] %s timestamp: %lld", inf, lt_ms);

#define DBG_TIME_DIFF(inf)                                              \
    nt_ms = systemTime() / 1000000;                                     \
    LOG_TIME("\t[T_DBG_dff] %s use: %lld(ms)", inf, (nt_ms - lt_ms));   \
    lt_ms = nt_ms;

#define DBG_TIME_END(inf, en)                                           \
    nt_ms = systemTime() / 1000000;                                     \
    LOG_TIME("\t[T_DBG_end] %s use: %lld(ms)", inf, (nt_ms - llt_ms));  \
    if (en) LOG_TIME("\t[T_DBG_end] %s timestamp: %lld", inf, nt_ms);
#else
#define DBG_TIME_BEGIN(inf, en)
#define DBG_TIME_DIFF(inf)
#define DBG_TIME_END(inf, en)
#endif

#define DBG_TIME_AVG_ENABLE     0
#if DBG_TIME_AVG_ENABLE
#define LOG_TIME_AVG            ALOGD
#define DBG_TIME_AVG_BEGIN(tag)                                         \
    static int64_t tag##_time = 0;                                      \
    static int tag##_cnt = 0;

#define DBG_TIME_AVG_INIT(tag)                                          \
    tag##_time = 0; tag##_cnt = 0;

#define DBG_TIME_AVG_AREA_IN(tag)                                       \
    int64_t tag##_diff = systemTime();

#define DBG_TIME_AVG_AREA_OUT(tag)                                      \
    tag##_diff = systemTime() - tag##_diff;                             \
    tag##_time += tag##_diff;                                           \
    tag##_cnt++;

#define DBG_TIME_AVG_END(tag, inf)                                      \
    if (tag##_cnt > 0) LOG_TIME_AVG("\t[T_DBG_avg] %s cnt: %d, average use: %lld(us)", inf, tag##_cnt, tag##_time/tag##_cnt/1000);
#else
#define DBG_TIME_AVG_BEGIN(tag)
#define DBG_TIME_AVG_INIT(tag)
#define DBG_TIME_AVG_AREA_IN(tag)
#define DBG_TIME_AVG_AREA_OUT(tag)
#define DBG_TIME_AVG_END(tag, inf)
#endif


#ifdef __SUN4I__
#define USE_MP_CONVERT
#endif

#ifdef __SUN6I__
#define USE_MP_CONVERT
#endif

#ifdef __SUN9I__
//#define USE_MP_CONVERT
#endif

//#define  DEFAULT_CVBS_CAMERA_TYPE_PAL 1

#define USE_MP_CONVERT
#ifndef CAMERA_MANAGER_ENABLE
#endif

#define BIRDVIEW_PAL_WIDTH                  720
#define BIRDVIEW_PAL_HEIGHT                 576
#define BIRDVIEW_NTSC_WIDTH                 720
#define BIRDVIEW_NTSC_HEIGHT                480

#define BIRDVIEW_4PAL_WIDTH                 (BIRDVIEW_PAL_WIDTH*2)
#define BIRDVIEW_4PAL_HEIGHT                (BIRDVIEW_PAL_HEIGHT*2)
#define BIRDVIEW_4NTSC_WIDTH                (BIRDVIEW_NTSC_WIDTH*2)
#define BIRDVIEW_4NTSC_HEIGHT               (BIRDVIEW_NTSC_HEIGHT*2)

#define BIRDVIEW_OUTPUT_WIDTH               BIRDVIEW_NTSC_WIDTH
#define BIRDVIEW_OUTPUT_HEIGHT              BIRDVIEW_NTSC_HEIGHT
#define BIRDVIEW_INPUT_WIDTH                (BIRDVIEW_OUTPUT_WIDTH*2)
#define BIRDVIEW_INPUT_HEIGHT               (BIRDVIEW_OUTPUT_HEIGHT*2)

#ifdef BIRDVIEW_SUPPORT_PAL_INPUT
#define BIRDVIEW_SOURCE_ALL_WIDTH           BIRDVIEW_4PAL_WIDTH
#define BIRDVIEW_SOURCE_ALL_HEIGHT          BIRDVIEW_4PAL_HEIGHT
#define BIRDVIEW_SOURCE_SINGLE_WIDTH        BIRDVIEW_PAL_WIDTH
#define BIRDVIEW_SOURCE_SINGLE_HEIGHT       BIRDVIEW_PAL_HEIGHT
#else
#define BIRDVIEW_SOURCE_ALL_WIDTH           BIRDVIEW_4NTSC_WIDTH
#define BIRDVIEW_SOURCE_ALL_HEIGHT          BIRDVIEW_4NTSC_HEIGHT
#define BIRDVIEW_SOURCE_SINGLE_WIDTH        BIRDVIEW_NTSC_WIDTH
#define BIRDVIEW_SOURCE_SINGLE_HEIGHT       BIRDVIEW_NTSC_HEIGHT
#endif

#define BIRDVIEW_SOURCE_BUF_SIZE            (BIRDVIEW_SOURCE_ALL_WIDTH * BIRDVIEW_SOURCE_ALL_HEIGHT * 2)

#ifdef BIRDVIEW_SUPPORT_PAL_OUTPUT
#define BIRDVIEW_DEST_WIDTH                 BIRDVIEW_PAL_WIDTH
#define BIRDVIEW_DEST_HEIGHT                BIRDVIEW_PAL_HEIGHT
#else
#define BIRDVIEW_DEST_WIDTH                 BIRDVIEW_NTSC_WIDTH
#define BIRDVIEW_DEST_HEIGHT                BIRDVIEW_NTSC_HEIGHT
#endif

#define BIRDVIEW_DEST_BUF_SIZE              (BIRDVIEW_DEST_WIDTH * BIRDVIEW_DEST_HEIGHT * 2)

#ifndef BV_TYPE_CHANNEL_OPTION
#define BV_TYPE_VIDEO_LUMA                  0xA6        // 那車?米芍芍?豕
#define BV_TYPE_VIDEO_HUE                   0xA7        // 那車?米谷?2那?豕
#define BV_TYPE_VIDEO_SATURATION            0xA8        // 那車?米㊣ㄓo赤?豕
#define BV_TYPE_VIDEO_CONTRAST              0xA9        // 那車?米??㊣豕?豕
#define BV_VIDEO_VALUE_MIN                  0           // 2?那y℅?D??米
#define BV_VIDEO_VALUE_MAX                  100         // 2?那y℅?∩車?米

#define BV_TYPE_CHANNEL_OPTION              0xA2        // 豕??～赤“米角
#endif

typedef enum VideoChannel {
    BV_CHANNEL_ALL = 0,
    BV_CHANNEL_FRONT,
    BV_CHANNEL_BACK,
    BV_CHANNEL_LEFT,
    BV_CHANNEL_RIGHT,
    BV_CHANNEL_BIRDVIEW
} e_VideoChannel;

typedef struct VideoBufferInfo {
    // 4in1 source buffer
    unsigned char *srcVirY;
    unsigned char *srcPhyY;

    // destination buffer
    unsigned char *dstVirY;
    unsigned char *dstPhyY;
    
    // single source buffer: front
    unsigned char *frontVirY;
    unsigned char *frontPhyY;
    // single source buffer: back
    unsigned char *backVirY;
    unsigned char *backPhyY;
    // single source buffer: left
    unsigned char *leftVirY;
    unsigned char *leftPhyY;
    // single source buffer: right
    unsigned char *rightVirY;
    unsigned char *rightPhyY;
} t_VideoBufferInfo;

#include "memoryAdapter.h"
#include <sc_interface.h>

#endif // __HAL_CAMERA_DEBUG_H__

