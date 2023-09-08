/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : EncoderTest.c
 * Description : EncoderTest
 * History :
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vencoder.h"
#include <sys/time.h>
#include <time.h>
#include <memoryAdapter.h>
#include "AWVideoEncoder.h"
#include <pthread.h>
#include "sunxiMemInterface.h"

#define DEMO_FILE_NAME_LEN 256
#define USE_H265_ENC
#define ROI_NUM 4
#define NO_READ_WRITE 0
#define MAX_BIT_MAPS  (13)
#define ENABLE_MOTION_DETECT (0)
#define ENABLE_RC_VBR (1)
//#define YU12_NV12
//#define USE_AFBC_INPUT
//#define YU12_NV21
//#define VBR

//#define USE_SVC
//#define USE_VIDEO_SIGNAL
//#define USE_ASPECT_RATIO
//#define USE_SUPER_FRAME

//#define GET_MB_INFO
//#define SET_MB_INFO
//#define SET_SMART

#define ALIGN_XXB(y, x) (((x) + ((y)-1)) & ~((y)-1))

#define ENCODE_LOG
#ifdef ENCODE_LOG
#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#define HL_TWK_RED_YEL  "\033[1m\033[5;31;43m"
#define HL_RED_WRT      "\033[1;31;47m"
#define HL_RED          "\033[1;31m"
#define HL_YEL          "\033[1;33m"

#define PF_CLR  "\033[0m"

#define MODULE_VERSION "V2.0.20220506"

enum LOG_LEVEL
{
    LOG_LEVEL_OFF = 0,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DBG,
    LOG_LEVEL_ALL,
};

static const int log_level = LOG_LEVEL_ERR;

#define logv(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_FATAL)\
           DEBUG(HL_TWK_RED_YEL "[F]" PF_CLR"[%s]%s line:%d " format,__FILE__,__FUNCTION__, __LINE__,##__VA_ARGS__);\
    } while (0)

#define loge(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_ERR)\
           DEBUG(HL_RED_WRT "[E]" PF_CLR"[%s]%s line:%d " format,__FILE__,__FUNCTION__, __LINE__,##__VA_ARGS__);\
    } while (0)

#define logw(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_WARN)\
           DEBUG(HL_YEL "[W]" PF_CLR"[%s]%s line:%d " format,__FILE__,__FUNCTION__, __LINE__,##__VA_ARGS__);\
    } while (0)

#define logi(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_INFO)\
           DEBUG(HL_RED "[I]" PF_CLR"%s line:%d " format,__FUNCTION__,__LINE__,##__VA_ARGS__);\
    } while (0)

#define logd(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_DBG){\
           DEBUG( "[D]" "%s "  format,__FUNCTION__,##__VA_ARGS__);\
           }\
    } while (0)

#define logr \
    do { \
         if(log_level>=LOG_LEVEL_ALL){\
           DEBUG(HL_RED "[I]" PF_CLR"%s line:%d is run!\n", __FUNCTION__,__LINE__);\
           }\
    } while (0)

#define CHECK_RETURN(a) \
    do { \
         if(a<0){\
           DEBUG(HL_RED "[E]" "[%s] fail! line:%d ret:%d\n" PF_CLR, __FUNCTION__, __LINE__,a);\
           pthread_mutex_unlock(&mEncodeMutex);\
           return a; \
           }\
    } while (0)


namespace awvideoencoder
{

typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int widthAligh16;
    unsigned int heightAligh16;
    unsigned char* argbAddr;
    unsigned int size;
} BitMapInfoS;

typedef struct
{
    EXIFInfo                exifInfo;
    int                     quality;
    int                     jpegMode;
    VencJpegVideoSignal     videoSignal;
    int                     jpegBiteRate;
    int                     jpegFrameRate;
    VencBitRateRange        bitRateRange;
    VencOverlayInfoS        sOverlayInfo;
} JpegFunc;

typedef struct
{
    VencHeaderData          spsPpsData;
    VencH264Param           h264Param;
    VencMBModeCtrl          h264MBMode;
    VencMBInfo              MBInfo;
    VencFixQP           fixQP;
    VencSuperFrameConfig    sSuperFrameCfg;
    VencH264SVCSkip         SvcSkip; // set SVC and skip_frame
    VencH264AspectRatio     sAspectRatio;
    VencH264VideoSignal     sVideoSignal;
    VencCyclicIntraRefresh  sIntraRefresh;
    VencROIConfig           sRoiConfig[ROI_NUM];
    VeProcSet               sVeProcInfo;
    VencOverlayInfoS        sOverlayInfo;
    VencSmartFun            sH264Smart;
} H264Func;

typedef struct
{
    VencH265Param               h265Param;
    VencH265GopStruct           h265Gop;
    VencHVS                     h265Hvs;
    VencH265TendRatioCoef       h265Trc;
    VencSmartFun                h265Smart;
    VencMBModeCtrl              h265MBMode;
    VencMBInfo                  MBInfo;
    VencFixQP               fixQP;
    VencSuperFrameConfig        sSuperFrameCfg;
    VencH264SVCSkip             SvcSkip; // set SVC and skip_frame
    VencH264AspectRatio         sAspectRatio;
    VencH264VideoSignal         sVideoSignal;
    VencCyclicIntraRefresh      sIntraRefresh;
    VencROIConfig               sRoiConfig[ROI_NUM];
    VencAlterFrameRateInfo sAlterFrameRateInfo;
    int                         h265RcFrameTotal;
    VeProcSet               sVeProcInfo;
    VencOverlayInfoS        sOverlayInfo;
} H265Func;

class AWVideoEncoderImpl: public AWVideoEncoder
{
public:

    AWVideoEncoderImpl(EncodeParam* config);
    AWVideoEncoderImpl();
    ~AWVideoEncoderImpl();

    virtual int init(EncodeParam* param, AWVideoEncoderDataCallback* cbk = NULL);
    virtual int getHeader(void* spsHeader);
    virtual int setVBR(unsigned int bitrate);
    virtual int setJpgQuality(int quality);
    virtual int setRoi(AvRoiRegionArray* roiRegions);
    virtual int encode(const void* inputBuf, unsigned int inputLen,
                       void* outputBuf, unsigned int outputLen);

    int encodePhy(const void* inputBuf, unsigned int inputLen,
	                               void* outputBuf, unsigned int outputLen);
    virtual int encode(AVPacket* packet);

private:
    int SeekPrefixNAL(char* begin);
    void initJpegExif(EXIFInfo* exifInfo);
    void initH265Gop(VencH265GopStruct* h265Gop);
    void initFixQp(VencFixQP* fixQP);
    void initSuperFrameCfg(VencSuperFrameConfig* sSuperFrameCfg);
    void initSvcSkip(VencH264SVCSkip* SvcSkip);
    void initAspectRatio(VencH264AspectRatio* sAspectRatio);
    void initVideoSignal(VencH264VideoSignal* sVideoSignal);
    void initIntraRefresh(VencCyclicIntraRefresh* sIntraRefresh);
    void initRoi(VencROIConfig* sRoiConfig);
    void initAlterFrameRateInfo(VencAlterFrameRateInfo* pAlterFrameRateInfo);
    void initEncProcInfo(VeProcSet* veProcSet);
    void initOverlayInfo(VencOverlayInfoS* pOverlayInfo);
    void unInitOverlayInfo();
    void initJpegRateCtrl(JpegFunc* jpegFunc, EncodeParam* encodeParam);
    int initH264Func(H264Func* h264Func, EncodeParam* encodeParam);
    int initH265Func(H265Func* h265Func, EncodeParam* encodeParam);
    int initJpegFunc(JpegFunc* jpegFunc, EncodeParam* encodeParam);
    int setEncParam(VideoEncoder* pVideoEnc, EncodeParam* encodeParam);

#ifdef SET_MB_INFO
    void initMbMode(VencMBModeCtrl* pMBMode, EncodeParam* encodeParam);
    void initMbInfo(VencMBInfo* MBInfo, EncodeParam* encodeParam);
    void setMbMode(VideoEncoder* pVideoEnc, EncodeParam* encodeParam);
    void getMbMinfo(VideoEncoder* pVideoEnc, EncodeParam* encodeParam);
    void releaseMb(EncodeParam* encodeParam);
#endif
    int encode();
    int finish();
    int writeOutputBuf(void* buf, int len);
    int readInputBuf(void* buf, int len);

    VencBaseConfig baseConfig;
    VencAllocateBufferParam bufferParam;
    paramStruct_t mSetparmMemops;
    VideoEncoder* pVideoEnc = NULL;
    VencInputBuffer inputBuffer;
    VencOutputBuffer outputBuffer;
    VencHeaderData spsPpsData;
    unsigned int afbcHeaderSize;

    VencROIConfig mRoiConfig[MAX_ROI_REGION];
#ifdef GET_MB_INFO
    VencMBSumInfo sMbSumInfo;
    unsigned long long sumSse = 0;
    unsigned long long minSse = 0;
    unsigned long long maxSse = 0;
    unsigned long long avrSse = 0;
    unsigned int       minSseFrame = 0;
    unsigned int       maxSseFrame = 0;
#endif
    JpegFunc jpegFunc;
    H264Func h264Func;
    H265Func h265Func;

    //BitMapInfoS bitMapInfo[MAX_BIT_MAPS];

    EncodeParam*    mEncodeParam = NULL;
    const void* mOutputBuf = NULL;
    int mOutputBufLen = 0;
    int mOutputBufPos = 0;
    const void* mInputBuf;
    int mInputBufLen = 0;
    int mInputBufPos = 0;
    AWVideoEncoderDataCallback* mDataCbk = NULL;

    pthread_mutex_t     mEncodeMutex;
    int mFreamIndex = 0;
    long long time1 = 0;
    long long time2 = 0;
    long long time3 = 0;

    static long long GetNowUs()
    {
        struct timeval now;
        gettimeofday(&now, NULL);
        return now.tv_sec * 1000000 + now.tv_usec;
    }
};

AWVideoEncoder* AWVideoEncoder::create(EncodeParam* param)
{
    AWVideoEncoder* encoder = new AWVideoEncoderImpl(param);
    return encoder;
}

AWVideoEncoder* AWVideoEncoder::create()
{
    AWVideoEncoder* encoder = new AWVideoEncoderImpl();
    return encoder;
}

void AWVideoEncoder::destroy(AWVideoEncoder* encoder)
{
    delete encoder;
}

AWVideoEncoderImpl::AWVideoEncoderImpl()
{
    printf("new AWVideoEncoderImpl() version:%s\n", MODULE_VERSION);
    afbcHeaderSize = 0;
    memset(&jpegFunc, 0, sizeof(JpegFunc));
    memset(&h265Func, 0, sizeof(H265Func));
    mInputBuf = NULL;
}

AWVideoEncoderImpl::AWVideoEncoderImpl(EncodeParam* param)
{
    init(param);
}

AWVideoEncoderImpl::~AWVideoEncoderImpl()
{
    printf("~ AWVideoEncoderImpl()\n");
    finish();
}

int AWVideoEncoderImpl::init(EncodeParam* param, AWVideoEncoderDataCallback* cbk)
{
    int ret;
    if ((NULL != mEncodeParam) || (NULL != mDataCbk))
    {
        loge("The decoder has been initialized before.");
        return -1;
    }
    mEncodeParam = param;
    mDataCbk = cbk;

    pthread_mutex_init(&mEncodeMutex, NULL);

    /******** begin set baseConfig param********/
    memset(&baseConfig, 0, sizeof(VencBaseConfig));
    memset(&bufferParam, 0, sizeof(VencAllocateBufferParam));

	memset(&mSetparmMemops, 0, sizeof(paramStruct_t));

	ret = allocOpen(MEM_TYPE_CDX_NEW, &mSetparmMemops, NULL);
	if (ret < 0) {
		loge("setparm:allocOpen failed");
	}
    baseConfig.memops = (struct ScMemOpsS*)mSetparmMemops.ops;

    
    //baseConfig.memops = (struct ScMemOpsS*)setparmMemops.ops;
    if (baseConfig.memops == NULL)
    {
        printf("MemAdapterGetOpsS failed\n");
        return -1;
    }

    //ret = CdcMemOpen(baseConfig.memops);

    baseConfig.eInputFormat = (VENC_PIXEL_FMT)mEncodeParam->pixelFormat;
    baseConfig.nInputWidth = mEncodeParam->srcW;
    baseConfig.nInputHeight = mEncodeParam->srcH;
    baseConfig.nStride = mEncodeParam->srcW;
    baseConfig.nDstWidth = mEncodeParam->dstW;
    baseConfig.nDstHeight = mEncodeParam->dstH;

    bufferParam.nSizeY = baseConfig.nInputWidth * baseConfig.nInputHeight;
    bufferParam.nSizeC = baseConfig.nInputWidth * baseConfig.nInputHeight / 2;
    bufferParam.nBufferNum = 1;

#ifdef USE_AFBC_INPUT
    afbcHeaderSize = ((baseConfig.nInputWidth + 127) >> 7) * ((baseConfig.nInputHeight + 31) >> 5) * 96;
    logd("size_y:%x, size_c:%x, afbc_header:%x\n",
         bufferParam.nSizeY,
         bufferParam.nSizeC,
         afbcHeaderSize);
    bufferParam.nSizeY += afbcHeaderSize + bufferParam.nSizeC;
    bufferParam.nSizeC = 0;
    logd("afbc buffer size:%x\n", bufferParam.nSizeY);
    baseConfig.eInputFormat = VENC_PIXEL_AFBC_AW;
#endif
    /******** end set baseConfig param********/

    //create encoder
    logd("mEncodeParam.codecType:%p\n", mEncodeParam->codecType);
    pVideoEnc = VideoEncCreate((VENC_CODEC_TYPE)mEncodeParam->codecType);
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }

    //set enc parameter
    ret = setEncParam(pVideoEnc, mEncodeParam);
    if (ret)
    {
        loge("setEncParam error, return");
        return -1;
    }

    ret = VideoEncInit(pVideoEnc, &baseConfig);
    if (ret)
    {
        loge("setEncParam error, return");
        return -1;
    }

    ret = AllocInputBuffer(pVideoEnc, &bufferParam);
    if (ret)
    {
        loge("setEncParam error, return");
        return -1;
    }

    if ((mEncodeParam->codecType == CODEC_H264 || \
            mEncodeParam->codecType == CODEC_H265) &&
            (NULL != mDataCbk))
    {
        unsigned int head_num = 0;
        if (mEncodeParam->codecType == CODEC_H264)
        {
            VideoEncGetParameter(pVideoEnc, VENC_IndexParamH264SPSPPS, &spsPpsData);
            unsigned char value = 1;
            //VideoEncGetParameter(pVideoEnc, VENC_IndexParamAllParams, &value);
        }
        else if (mEncodeParam->codecType == CODEC_H265)
        {
            VideoEncGetParameter(pVideoEnc, VENC_IndexParamH265Header, &spsPpsData);
            unsigned char value = 1;
            //VideoEncGetParameter(pVideoEnc, VENC_IndexParamAllParams, &value);
        }

        logd("call %p \n", mDataCbk );
        AVPacket packet;
        memset(&packet, 0, sizeof(AVPacket));
        packet.id = -1;
        packet.pts = -1;
        packet.pAddrVir0 = spsPpsData.pBuffer;
        packet.dataLen0  = spsPpsData.nLength;
        mDataCbk->encoderDataReady(&packet);
    }

    return 0;
}

int AWVideoEncoderImpl::finish()
{
    //logd("the average encode time is %lldus,file size:%d...\n", time3 / mFreamIndex);
    ReleaseAllocInputBuffer(pVideoEnc);

    if (pVideoEnc)
    {
        VideoEncDestroy(pVideoEnc);
        pVideoEnc = NULL;
    }

    if (baseConfig.memops)
    {
        //CdcMemClose(baseConfig.memops);
        allocClose(MEM_TYPE_CDX_NEW,&mSetparmMemops, NULL);
        baseConfig.memops = NULL;
    }

    //unInitOverlayInfo();

#ifdef SET_MB_INFO
    releaseMb(mEncodeParam);
#endif
    pthread_mutex_destroy(&mEncodeMutex);


}

int AWVideoEncoderImpl::writeOutputBuf(void* buf, int len)
{
    if (mOutputBufLen < mOutputBufPos + len)
    {
        loge("writeOutputBuf out of range!!\n");
        return -1;
    }
    memcpy((char*)mOutputBuf + mOutputBufPos, buf, len);
    mOutputBufPos += len;
    return 0;
}

int AWVideoEncoderImpl::readInputBuf(void* buf, int len)
{
    if (mInputBufLen < mInputBufPos + len)
    {
        loge("readInputBuf out of range!\n");
        return -1;
    }

    memcpy(buf, (char*)mInputBuf + mInputBufPos, len);
    mInputBufPos += len;
    return 0;
}

int AWVideoEncoderImpl::SeekPrefixNAL(char* begin)
{
    unsigned int i;
    char* pchar = begin;
    char isPrefixNAL = 1;
    char NAL[4] = {0x00, 0x00, 0x00, 0x01};

    if (!pchar)
    {
        return -1;
    }

    for (i = 0; i < 4; i++)
    {
        if (pchar[i] != NAL[i])
        {
            isPrefixNAL = 0;
            break;
        }
    }
    if (isPrefixNAL == 1)
    {
        isPrefixNAL = 0;
        char PrefixNAL[3] = {0x6e, 0x4e, 0x0e};
        for (i = 0; i < 3; i++)
        {
            if (pchar[4] == PrefixNAL[i])
            {
                isPrefixNAL = 1;
                break;
            }
        }
    }
    // read temporal_id
    if (isPrefixNAL == 1)
    {
        char TemporalID = pchar[7];
        TemporalID >>= 5;
        return TemporalID;
    }

    return -1;
}

void AWVideoEncoderImpl::initJpegExif(EXIFInfo* exifInfo)
{
    exifInfo->ThumbWidth = 640;
    exifInfo->ThumbHeight = 480;

    strcpy((char*)exifInfo->CameraMake,        "allwinner make test");
    strcpy((char*)exifInfo->CameraModel,        "allwinner model test");
    strcpy((char*)exifInfo->DateTime,         "2014:02:21 10:54:05");
    strcpy((char*)exifInfo->gpsProcessingMethod,  "allwinner gps");

    exifInfo->Orientation = 0;

    exifInfo->ExposureTime.num = 2;
    exifInfo->ExposureTime.den = 1000;

    exifInfo->FNumber.num = 20;
    exifInfo->FNumber.den = 10;
    exifInfo->ISOSpeed = 50;

    exifInfo->ExposureBiasValue.num = -4;
    exifInfo->ExposureBiasValue.den = 1;

    exifInfo->MeteringMode = 1;
    exifInfo->FlashUsed = 0;

    exifInfo->FocalLength.num = 1400;
    exifInfo->FocalLength.den = 100;

    exifInfo->DigitalZoomRatio.num = 4;
    exifInfo->DigitalZoomRatio.den = 1;

    exifInfo->WhiteBalance = 1;
    exifInfo->ExposureMode = 1;

    exifInfo->enableGpsInfo = 1;

    exifInfo->gps_latitude = 23.2368;
    exifInfo->gps_longitude = 24.3244;
    exifInfo->gps_altitude = 1234.5;

    exifInfo->gps_timestamp = (long)time(NULL);

    strcpy((char*)exifInfo->CameraSerialNum,  "123456789");
    strcpy((char*)exifInfo->ImageName,  "exif-name-test");
    strcpy((char*)exifInfo->ImageDescription,  "exif-descriptor-test");
}

void AWVideoEncoderImpl::initH265Gop(VencH265GopStruct* h265Gop)
{
    h265Gop->gop_size = 8;
    h265Gop->intra_period = 16;

    h265Gop->use_lt_ref_flag = 1;
    if (h265Gop->use_lt_ref_flag)
    {
        h265Gop->max_num_ref_pics = 2;
        h265Gop->num_ref_idx_l0_default_active = 2;
        h265Gop->num_ref_idx_l1_default_active = 2;
        h265Gop->use_sps_rps_flag = 0;
    }
    else
    {
        h265Gop->max_num_ref_pics = 1;
        h265Gop->num_ref_idx_l0_default_active = 1;
        h265Gop->num_ref_idx_l1_default_active = 1;
        h265Gop->use_sps_rps_flag = 1;
    }
    //1:user config the reference info; 0:encoder config the reference info
    h265Gop->custom_rps_flag = 0;
    if (1 == h265Gop->custom_rps_flag)
    {
        int pos = 0;
        for (pos = 0; pos < h265Gop->gop_size; pos++)
        {
            h265Gop->ref_str[pos].slice_type = H265_P_SLICE;
            h265Gop->ref_str[pos].poc = pos + 1;
            h265Gop->ref_str[pos].qp_offset = 0;
            h265Gop->ref_str[pos].tc_offset_div2 = 0;
            h265Gop->ref_str[pos].beta_offset_div2 = 0;
            h265Gop->ref_str[pos].num_ref_pics = 2;
            h265Gop->ref_str[pos].reference_pics[0] = -1;
            h265Gop->ref_str[pos].reference_pics[1] = -(pos + 1);
            h265Gop->ref_str[pos].discard_pics[0] = -2;
            h265Gop->ref_str[pos].lt_ref_flag = 1;
            h265Gop->ref_str[pos].lt_ref_poc = 0;
            h265Gop->ref_str[pos].predict = 1;
            h265Gop->ref_str[pos].delta_rps_idx = 1;
            h265Gop->ref_str[pos].delta_rps = -1;
            h265Gop->ref_str[pos].num_ref_idcs = 3;
            h265Gop->ref_str[pos].reference_idcs[0][0] = REF_IDC_DISCARD;
            h265Gop->ref_str[pos].reference_idcs[0][1] = REF_IDC_CURRENT_USE;
            h265Gop->ref_str[pos].reference_idcs[0][2] = REF_IDC_LONG_TERM;
        }

        h265Gop->ref_str[0].num_ref_pics = 1;
        h265Gop->ref_str[0].reference_pics[1] = -1;
        h265Gop->ref_str[0].discard_pics[1] = -(h265Gop->gop_size + 1);
        h265Gop->ref_str[0].lt_ref_flag = 0;
        h265Gop->ref_str[0].predict = 0;
        h265Gop->ref_str[0].num_ref_idcs = 3;
        h265Gop->ref_str[0].reference_idcs[0][1] = REF_IDC_CURRENT_USE;
        h265Gop->ref_str[0].reference_idcs[0][2] = REF_IDC_DISCARD;

        h265Gop->ref_str[1].num_ref_idcs = 2;
        h265Gop->ref_str[1].reference_idcs[0][0] = REF_IDC_CURRENT_USE;
        h265Gop->ref_str[1].reference_idcs[0][1] = REF_IDC_LONG_TERM;

        h265Gop->ref_str[h265Gop->gop_size].slice_type = H265_IDR_SLICE;
        h265Gop->ref_str[h265Gop->gop_size].poc = 0;
        h265Gop->ref_str[h265Gop->gop_size].predict = 0;

        if (h265Gop->use_lt_ref_flag)
        {
            h265Gop->ref_str[h265Gop->gop_size + 1].num_ref_pics = 1;
            h265Gop->ref_str[h265Gop->gop_size + 1].reference_pics[0] = -1;
            h265Gop->ref_str[h265Gop->gop_size + 1].delta_rps_idx = 1;
            h265Gop->ref_str[h265Gop->gop_size + 1].delta_rps = -1;
            h265Gop->ref_str[h265Gop->gop_size + 1].num_ref_idcs = 1;
            h265Gop->ref_str[h265Gop->gop_size + 1].reference_idcs[0][0] = REF_IDC_CURRENT_USE;
        }
    }
}

void AWVideoEncoderImpl::initFixQp(VencFixQP* fixQP)
{
    fixQP->bEnable = 1;
    fixQP->nIQp = 35;
    fixQP->nPQp = 35;
}

void AWVideoEncoderImpl::initSuperFrameCfg(VencSuperFrameConfig* sSuperFrameCfg)
{
    sSuperFrameCfg->eSuperFrameMode = VENC_SUPERFRAME_NONE;
    sSuperFrameCfg->nMaxIFrameBits = 30000 * 8;
    sSuperFrameCfg->nMaxPFrameBits = 15000 * 8;
}

void AWVideoEncoderImpl::initSvcSkip(VencH264SVCSkip* SvcSkip)
{
    SvcSkip->nTemporalSVC = T_LAYER_4;
    switch (SvcSkip->nTemporalSVC)
    {
    case T_LAYER_4:
        SvcSkip->nSkipFrame = SKIP_8;
        break;
    case T_LAYER_3:
        SvcSkip->nSkipFrame = SKIP_4;
        break;
    case T_LAYER_2:
        SvcSkip->nSkipFrame = SKIP_2;
        break;
    default:
        SvcSkip->nSkipFrame = NO_SKIP;
        break;
    }
}

void AWVideoEncoderImpl::initAspectRatio(VencH264AspectRatio* sAspectRatio)
{
    sAspectRatio->aspect_ratio_idc = 255;
    sAspectRatio->sar_width = 4;
    sAspectRatio->sar_height = 3;
}

void AWVideoEncoderImpl::initVideoSignal(VencH264VideoSignal* sVideoSignal)
{
    sVideoSignal->video_format = (VENC_VIDEO_FORMAT)5;
    sVideoSignal->src_colour_primaries = (VENC_COLOR_SPACE)0;
    sVideoSignal->dst_colour_primaries = (VENC_COLOR_SPACE)1;
}

void AWVideoEncoderImpl::initIntraRefresh(VencCyclicIntraRefresh* sIntraRefresh)
{
    sIntraRefresh->bEnable = 1;
    sIntraRefresh->nBlockNumber = 10;
}

void AWVideoEncoderImpl::initRoi(VencROIConfig* sRoiConfig)
{
    sRoiConfig[0].bEnable = 1;
    sRoiConfig[0].index = 0;
    sRoiConfig[0].nQPoffset = 10;
    sRoiConfig[0].sRect.nLeft = 0;
    sRoiConfig[0].sRect.nTop = 0;
    sRoiConfig[0].sRect.nWidth = 1280;
    sRoiConfig[0].sRect.nHeight = 320;

    sRoiConfig[1].bEnable = 1;
    sRoiConfig[1].index = 1;
    sRoiConfig[1].nQPoffset = 10;
    sRoiConfig[1].sRect.nLeft = 320;
    sRoiConfig[1].sRect.nTop = 180;
    sRoiConfig[1].sRect.nWidth = 320;
    sRoiConfig[1].sRect.nHeight = 180;

    sRoiConfig[2].bEnable = 1;
    sRoiConfig[2].index = 2;
    sRoiConfig[2].nQPoffset = 10;
    sRoiConfig[2].sRect.nLeft = 320;
    sRoiConfig[2].sRect.nTop = 180;
    sRoiConfig[2].sRect.nWidth = 320;
    sRoiConfig[2].sRect.nHeight = 180;

    sRoiConfig[3].bEnable = 1;
    sRoiConfig[3].index = 3;
    sRoiConfig[3].nQPoffset = 10;
    sRoiConfig[3].sRect.nLeft = 320;
    sRoiConfig[3].sRect.nTop = 180;
    sRoiConfig[3].sRect.nWidth = 320;
    sRoiConfig[3].sRect.nHeight = 180;
}

void AWVideoEncoderImpl::initAlterFrameRateInfo(VencAlterFrameRateInfo* pAlterFrameRateInfo)
{
    memset(pAlterFrameRateInfo, 0, sizeof(VencAlterFrameRateInfo));
    pAlterFrameRateInfo->bEnable = 1;
    pAlterFrameRateInfo->bUseUserSetRoiInfo = 1;
    pAlterFrameRateInfo->sRoiBgFrameRate.nSrcFrameRate = 25;
    pAlterFrameRateInfo->sRoiBgFrameRate.nDstFrameRate = 5;

    pAlterFrameRateInfo->roi_param[0].bEnable = 1;
    pAlterFrameRateInfo->roi_param[0].index = 0;
    pAlterFrameRateInfo->roi_param[0].nQPoffset = 10;
    pAlterFrameRateInfo->roi_param[0].roi_abs_flag = 1;
    pAlterFrameRateInfo->roi_param[0].sRect.nLeft = 0;
    pAlterFrameRateInfo->roi_param[0].sRect.nTop = 0;
    pAlterFrameRateInfo->roi_param[0].sRect.nWidth = 320;
    pAlterFrameRateInfo->roi_param[0].sRect.nHeight = 320;

    pAlterFrameRateInfo->roi_param[1].bEnable = 1;
    pAlterFrameRateInfo->roi_param[1].index = 0;
    pAlterFrameRateInfo->roi_param[1].nQPoffset = 10;
    pAlterFrameRateInfo->roi_param[1].roi_abs_flag = 1;
    pAlterFrameRateInfo->roi_param[1].sRect.nLeft = 320;
    pAlterFrameRateInfo->roi_param[1].sRect.nTop = 320;
    pAlterFrameRateInfo->roi_param[1].sRect.nWidth = 320;
    pAlterFrameRateInfo->roi_param[1].sRect.nHeight = 320;
}

void AWVideoEncoderImpl::initEncProcInfo(VeProcSet* veProcSet)
{
    veProcSet->bProcEnable = 1;
    veProcSet->nProcFreq = 3;
}

void AWVideoEncoderImpl::initOverlayInfo(VencOverlayInfoS* pOverlayInfo)
{
    /*
       int i;
       unsigned char num_bitMap = MAX_BIT_MAPS;
       BitMapInfoS* pBitMapInfo;
       unsigned int time_id_list[19];
       unsigned int start_mb_x;
       unsigned int start_mb_y;

       memset(pOverlayInfo, 0, sizeof(VencOverlayInfoS));
       memset(bitMapInfo, 0, sizeof(bitMapInfo));

       FILE* icon_hdle = NULL;
       int width  = 96;
       int height = 48;
       memset(time_id_list, 0, sizeof(time_id_list));

       icon_hdle = fopen("/mnt/libcedarc/data_argb.dat", "r");
       if (icon_hdle == NULL)
       {
           printf("get icon_hdle error\n");
           return;
       }

       for (i = 0; i < num_bitMap; i++)
       {
           bitMapInfo[i].argbAddr = NULL;
           bitMapInfo[i].width = width;
           bitMapInfo[i].height = height;

           bitMapInfo[i].widthAligh16 = ALIGN_XXB(16, bitMapInfo[i].width);
           bitMapInfo[i].heightAligh16 = ALIGN_XXB(16, bitMapInfo[i].height);
           if (bitMapInfo[i].argbAddr == NULL)
           {
               bitMapInfo[i].argbAddr =
                   (unsigned char*)malloc(bitMapInfo[i].widthAligh16 * bitMapInfo[i].heightAligh16 * 4);

               if (bitMapInfo[i].argbAddr == NULL)
               {
                   loge("malloc bitMapInfo[%d].argbAddr fail\n", i);
                   if (icon_hdle)
                   {
                       fclose(icon_hdle);
                       icon_hdle = NULL;
                   }

                   return;
               }
           }
           logv("bitMap[%d] size[%d,%d], size_align16[%d, %d], argbAddr:%p\n", i,
                bitMapInfo[i].width,
                bitMapInfo[i].height,
                bitMapInfo[i].widthAligh16,
                bitMapInfo[i].heightAligh16,
                bitMapInfo[i].argbAddr);

           int ret;
           ret = fread(bitMapInfo[i].argbAddr, 1,
                       bitMapInfo[i].width * bitMapInfo[i].height * 4, icon_hdle);
           if (ret != bitMapInfo[i].width * bitMapInfo[i].height * 4)
               loge("read bitMap[%d] error, ret value:%d\n", i, ret);

           bitMapInfo[i].size
               = bitMapInfo[i].widthAligh16 * bitMapInfo[i].heightAligh16 * 4;
       }
       if (icon_hdle)
       {
           fclose(icon_hdle);
           icon_hdle = NULL;
       }


       pOverlayInfo->argb_type = VENC_OVERLAY_ARGB8888;
       pOverlayInfo->blk_num = MAX_BIT_MAPS - 1;
       logd("blk_num:%d, argb_type:%d\n", pOverlayInfo->blk_num, pOverlayInfo->argb_type);

       start_mb_x = 0;
       start_mb_y = 0;
       for (i = 0; i < pOverlayInfo->blk_num; i++)
       {
           //id = time_id_list[i];
           //pBitMapInfo = &bitMapInfo[id];
           pBitMapInfo = &bitMapInfo[i];

           pOverlayInfo->overlayHeaderList[i].start_mb_x = start_mb_x;
           pOverlayInfo->overlayHeaderList[i].start_mb_y = start_mb_y;
           pOverlayInfo->overlayHeaderList[i].end_mb_x = start_mb_x
                   + (pBitMapInfo->widthAligh16 / 16 - 1);
           pOverlayInfo->overlayHeaderList[i].end_mb_y = start_mb_y
                   + (pBitMapInfo->heightAligh16 / 16 - 1);

           pOverlayInfo->overlayHeaderList[i].extra_alpha_flag = 0;
           pOverlayInfo->overlayHeaderList[i].extra_alpha = 8;
           if (i % 3 == 0)
               pOverlayInfo->overlayHeaderList[i].overlay_type = LUMA_REVERSE_OVERLAY;
           else if (i % 2 == 0 && i != 0)
               pOverlayInfo->overlayHeaderList[i].overlay_type = COVER_OVERLAY;
           else
               pOverlayInfo->overlayHeaderList[i].overlay_type = NORMAL_OVERLAY;


           if (pOverlayInfo->overlayHeaderList[i].overlay_type == COVER_OVERLAY)
           {
               pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_y = 0xa0;
               pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_u = 0xa0;
               pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_v = 0xa0;
           }

           pOverlayInfo->overlayHeaderList[i].overlay_blk_addr = pBitMapInfo->argbAddr;
           pOverlayInfo->overlayHeaderList[i].bitmap_size = pBitMapInfo->size;

           logv("blk_%d[%d], start_mb[%d,%d], end_mb[%d,%d],extra_alpha_flag:%d, extra_alpha:%d\n",
                i,
                time_id_list[i],
                pOverlayInfo->overlayHeaderList[i].start_mb_x,
                pOverlayInfo->overlayHeaderList[i].start_mb_y,
                pOverlayInfo->overlayHeaderList[i].end_mb_x,
                pOverlayInfo->overlayHeaderList[i].end_mb_y,
                pOverlayInfo->overlayHeaderList[i].extra_alpha_flag,
                pOverlayInfo->overlayHeaderList[i].extra_alpha);
           logv("overlay_type:%d, cover_yuv[%d,%d,%d], overlay_blk_addr:%p, bitmap_size:%d\n",
                pOverlayInfo->overlayHeaderList[i].overlay_type,
                pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_y,
                pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_u,
                pOverlayInfo->overlayHeaderList[i].cover_yuv.cover_v,
                pOverlayInfo->overlayHeaderList[i].overlay_blk_addr,
                pOverlayInfo->overlayHeaderList[i].bitmap_size);
           //if(i != 5)
           {
               start_mb_x += pBitMapInfo->widthAligh16 / 16;
               start_mb_y += pBitMapInfo->heightAligh16 / 16;
           }
       }
       */
    return;
}

void AWVideoEncoderImpl::unInitOverlayInfo()
{
    /*
       unsigned int bit_map_num;
       for (bit_map_num = 0; bit_map_num++; bit_map_num < MAX_BIT_MAPS)
       {
           if (bitMapInfo[bit_map_num].argbAddr)
           {
               free(bitMapInfo[bit_map_num].argbAddr);
               bitMapInfo[bit_map_num].argbAddr = NULL;
           }
       }
       logd("sizeof(bitMapInfo)=%d\n", sizeof(bitMapInfo));*/
}

void AWVideoEncoderImpl::initJpegRateCtrl(JpegFunc* jpegFunc, EncodeParam* encodeParam)
{
    jpegFunc->jpegBiteRate = encodeParam->bitRate;
    jpegFunc->jpegFrameRate = encodeParam->frameRate;
    jpegFunc->bitRateRange.bitRateMax = encodeParam->bitRate + 2 * 1024 * 1024;
    jpegFunc->bitRateRange.bitRateMin = (encodeParam->bitRate > 4 * 1024 * 1024) ? \
                                        (encodeParam->bitRate - 2 * 1024 * 1024) : encodeParam->bitRate / 2;
}

int AWVideoEncoderImpl::initH264Func(H264Func* h264Func, EncodeParam* encodeParam)
{
    memset(h264Func, 0, sizeof(H264Func));

    //init h264Param
    h264Func->h264Param.bEntropyCodingCABAC = 1;
    h264Func->h264Param.nBitrate = encodeParam->bitRate;
    h264Func->h264Param.nFramerate = encodeParam->frameRate;
    h264Func->h264Param.nCodingMode = VENC_FRAME_CODING;
    h264Func->h264Param.nMaxKeyInterval = encodeParam->maxKeyFrame;
    h264Func->h264Param.sProfileLevel.nProfile = VENC_H264ProfileHigh;
    h264Func->h264Param.sProfileLevel.nLevel = VENC_H264Level51;
#if ENABLE_RC_VBR
    h264Func->h264Param.sRcParam.eRcMode = (VENC_RC_MODE)encodeParam->rcMode;
    logd("h264Func->h264Param.sRcParam.eRcMode=%d\n", h264Func->h264Param.sRcParam.eRcMode);
    //h264Func->h264Param.sRcParam.sVbrParam.uRatioChangeQp   = 85;
    h264Func->h264Param.sRcParam.sVbrParam.nQuality    = 5;
    h264Func->h264Param.sRcParam.sVbrParam.uMaxBitRate = encodeParam->bitRate;
#endif
    h264Func->h264Param.sQPRange.nMinqp = encodeParam->minQp;
    h264Func->h264Param.sQPRange.nMaxqp = encodeParam->maxQp;
    //h264Func->h264Param.bLongRefEnable = 1;
    //h264Func->h264Param.nLongRefPoc = 0;

#if 1
    h264Func->sH264Smart.img_bin_en = 1;
    h264Func->sH264Smart.img_bin_th = 27;
    h264Func->sH264Smart.shift_bits = 2;
    h264Func->sH264Smart.smart_fun_en = 1;
#endif

#ifdef SET_MB_INFO
    //init VencMBModeCtrl
    initMbMode(&h264Func->h264MBMode, encodeParam);
    //init VencMBInfo
    initMbInfo(&h264Func->MBInfo, encodeParam);
#endif
    //init VencFixQP
    //initFixQp(&h264Func->fixQP);

    //init VencSuperFrameConfig
    initSuperFrameCfg(&h264Func->sSuperFrameCfg);

    //init VencH264SVCSkip
    initSvcSkip(&h264Func->SvcSkip);

    //init VencH264AspectRatio
    initAspectRatio(&h264Func->sAspectRatio);

    //init VencH264AspectRatio
    initVideoSignal(&h264Func->sVideoSignal);

    //init CyclicIntraRefresh
    initIntraRefresh(&h264Func->sIntraRefresh);

    //init VencROIConfig
    initRoi(h264Func->sRoiConfig);

    //init proc info
    //initEncProcInfo(&h264Func->sVeProcInfo);

    //init VencOverlayConfig
    //initOverlayInfo(&h264Func->sOverlayInfo);

    return 0;
}

int AWVideoEncoderImpl::initH265Func(H265Func* h265Func, EncodeParam* encodeParam)
{
    memset(h265Func, 0, sizeof(H264Func));

    //init h265Param
    h265Func->h265Param.nBitrate = encodeParam->bitRate;
    h265Func->h265Param.nFramerate = encodeParam->frameRate;
    h265Func->h265Param.sProfileLevel.nProfile = VENC_H265ProfileMain;
    h265Func->h265Param.sProfileLevel.nLevel = VENC_H265Level41;
    h265Func->h265Param.sQPRange.nMaxqp = encodeParam->minQp;
    h265Func->h265Param.sQPRange.nMinqp = encodeParam->maxQp;
    h265Func->h265Param.nQPInit = 30;
    h265Func->h265Param.idr_period = 30;
    h265Func->h265Param.nGopSize = h265Func->h265Param.idr_period;
    h265Func->h265Param.nIntraPeriod = h265Func->h265Param.idr_period;
    h265Func->h265Param.sRcParam.eRcMode = (VENC_RC_MODE)encodeParam->rcMode;
    //h265Func->h265Param.bLongTermRef = 1;
#if ENABLE_RC_VBR
    h265Func->h265Param.sRcParam.eRcMode = AW_CBR;
    //h265Func->h265Param.sRcParam.sVbrParam.uRatioChangeQp = 85;
    h265Func->h265Param.sRcParam.sVbrParam.nQuality       = 5;
    h265Func->h265Param.sRcParam.sVbrParam.uMaxBitRate    = encodeParam->bitRate;
#endif

    h265Func->h265Hvs.hvs_en = 1;
    h265Func->h265Hvs.th_dir = 24;
    h265Func->h265Hvs.th_coef_shift = 4;

    h265Func->h265Trc.inter_tend = 63;
    h265Func->h265Trc.skip_tend = 3;
    h265Func->h265Trc.merge_tend = 0;

    h265Func->h265Smart.img_bin_en = 1;
    h265Func->h265Smart.img_bin_th = 27;
    h265Func->h265Smart.shift_bits = 2;
    h265Func->h265Smart.smart_fun_en = 1;

    h265Func->h265RcFrameTotal = 20 * h265Func->h265Param.nGopSize;

    //init H265Gop
    initH265Gop(&h265Func->h265Gop);

#ifdef SET_MB_INFO
    //init VencMBModeCtrl
    initMbMode(&h265Func->h265MBMode, encodeParam);

    //init VencMBInfo
    initMbInfo(&h265Func->MBInfo, encodeParam);
#endif

    //init VencFixQP
    //initFixQp(&h265Func->fixQP);

    //init VencSuperFrameConfig
    initSuperFrameCfg(&h265Func->sSuperFrameCfg);

    //init VencH264SVCSkip
    initSvcSkip(&h265Func->SvcSkip);

    //init VencH264AspectRatio
    initAspectRatio(&h265Func->sAspectRatio);

    //init VencH264AspectRatio
    initVideoSignal(&h265Func->sVideoSignal);

    //init CyclicIntraRefresh
    initIntraRefresh(&h265Func->sIntraRefresh);

    //init VencROIConfig
    initRoi(h265Func->sRoiConfig);

    //init alter frameRate info
    initAlterFrameRateInfo(&h265Func->sAlterFrameRateInfo);

    //init proc info
    //initEncProcInfo(&h265Func->sVeProcInfo);

    //init VencOverlayConfig
    //initOverlayInfo(&h265Func->sOverlayInfo);

    return 0;
}

int AWVideoEncoderImpl::initJpegFunc(JpegFunc* jpegFunc, EncodeParam* encodeParam)
{
    // memset(jpegFunc, 0, sizeof(jpegFunc));

    jpegFunc->quality = encodeParam->jpgQuality;
    if (encodeParam->frameCount > 1)
        jpegFunc->jpegMode = 1;
    else
        jpegFunc->jpegMode = 0;

    if (0 == jpegFunc->jpegMode)
        initJpegExif(&jpegFunc->exifInfo);
    else if (1 == jpegFunc->jpegMode)
        initJpegRateCtrl(jpegFunc, encodeParam);
    else
    {
        loge("encoder do not support the jpegMode:%d\n", jpegFunc->jpegMode);
        return -1;
    }

    //init VencOverlayConfig
    //initOverlayInfo(&jpegFunc->sOverlayInfo);

    return 0;

}

int AWVideoEncoderImpl::setEncParam(VideoEncoder* pVideoEnc, EncodeParam* encodeParam)
{
    int result = 0;

    if (encodeParam->codecType == CODEC_JPEG)
    {
        result = initJpegFunc(&jpegFunc, encodeParam);
        if (result)
        {
            loge("initJpegFunc error, return \n");
            return -1;
        }

        if (1 == jpegFunc.jpegMode)
        {
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamJpegEncMode, &jpegFunc.jpegMode);
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &jpegFunc.jpegBiteRate);
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamFramerate, &jpegFunc.jpegFrameRate);
            VideoEncSetParameter(pVideoEnc,
                                 VENC_IndexParamSetBitRateRange, &jpegFunc.bitRateRange);

        }
        else
        {
            unsigned int vbv_size = 4 * 1024 * 1024;
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamSetVbvSize, &vbv_size);
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamJpegQuality, &jpegFunc.quality);
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamJpegExifInfo, &jpegFunc.exifInfo);
        }
    }
    else if (encodeParam->codecType == CODEC_H264)
    {
        result = initH264Func(&h264Func, encodeParam);
        if (result)
        {
            loge("initH264Func error, return \n");
            return -1;
        }
#if ENABLE_MOTION_DETECT
        MotionParam mMotionParam;

        mMotionParam.nMotionDetectEnable = 1;
        mMotionParam.nMotionDetectRatio = 0;
        mMotionParam.nStaticBitsRatio = 2;
        mMotionParam.nMaxNumStaticFrame = 4;
        mMotionParam.nMV64x64Ratio = 0.01;
        mMotionParam.nMVXTh = 2;
        mMotionParam.nMVYTh = 2;
        mMotionParam.nStaticBitsRatio = 0.5;

        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMotionDetectStatus, &mMotionParam);
#endif
        unsigned int vbv_size = 12 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamH264Param, &h264Func.h264Param);
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamSetVbvSize, &vbv_size);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamH264FixQP, &h264Func.fixQP);


#ifdef SET_MB_INFO
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMBInfoOutput, &h264Func.MBInfo);
#endif
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamRotation, &(encodeParam->rotation));
    }
    else if (encodeParam->codecType == CODEC_H265)
    {
        result = initH265Func(&h265Func, encodeParam);
        if (result)
        {
            loge("initH265Func error, return \n");
            return -1;
        }
        unsigned int vbv_size = 12 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamSetVbvSize, &vbv_size);
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamH265Param, &h265Func.h265Param);
#if ENABLE_MOTION_DETECT
        MotionParam mMotionParam;
        mMotionParam.nMotionDetectEnable = 1;
        mMotionParam.nMotionDetectRatio = 0;
        mMotionParam.nStaticBitsRatio = 2;
        mMotionParam.nMaxNumStaticFrame = 4;
        mMotionParam.nStaticBitsRatio = 0.5;
        mMotionParam.nMV64x64Ratio = 0.01;
        mMotionParam.nMVXTh = 2;
        mMotionParam.nMVYTh = 2;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMotionDetectEnable, &mMotionParam);
#endif


        unsigned int value = 1;
        //VideoEncSetParameter(pVideoEnc,
        //VENC_IndexParamAlterFrame, &h265Func.sAlterFrameRateInfo);
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamChannelNum, &value);
        value = encodeParam->maxKeyFrame;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMaxKeyInterval, &value);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamProcSet, &h265Func.sVeProcInfo);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamVirtualIFrame, &encodeParam->frameRate);
        //value = 0;
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamPFrameIntraEn, &value);
        //value = 1;
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamEncodeTimeEn, &value);
        //VideoEncSetParameter(pVideoEnc,
        //VENC_IndexParamH265ToalFramesNum,  &h265Func.h265RcFrameTotal);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamH265Gop, &h265Func.h265Gop);

        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamROIConfig, &h265Func.sRoiConfig[0]);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamH264FixQP, &h265Func.fixQP);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamH265HVS, &h265Func.h265Hvs);
        //VideoEncSetParameter(pVideoEnc, VENC_IndexParamH265TendRatioCoef, &h265Func.h265Trc);
#ifdef SET_MB_INFO
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMBInfoOutput, &h265Func.MBInfo);
#endif
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamRotation, &(encodeParam->rotation));
    }

    return 0;
}

#ifdef SET_MB_INFO
void AWVideoEncoderImpl::initMbMode(VencMBModeCtrl* pMBMode, EncodeParam* encodeParam)
{
    unsigned int mb_num;
    unsigned int j;

    mb_num = (ALIGN_XXB(16, encodeParam->dstW) >> 4)
             * (ALIGN_XXB(16, encodeParam->dstH) >> 4);
    pMBMode->p_info = (VencMBModeCtrlInfo*)malloc(sizeof(VencMBModeCtrlInfo) * mb_num);
    pMBMode->mode_ctrl_en = 1;

    for (j = 0; j < mb_num / 2; j++)
    {
        pMBMode->p_info[j].mb_en = 1;
        pMBMode->p_info[j].mb_skip_flag = 0;
        pMBMode->p_info[j].mb_qp = 22;
    }
    for (; j < mb_num; j++)
    {
        pMBMode->p_info[j].mb_en = 1;
        pMBMode->p_info[j].mb_skip_flag = 0;
        pMBMode->p_info[j].mb_qp = 32;
    }
}

void AWVideoEncoderImpl::initMbInfo(VencMBInfo* MBInfo, EncodeParam* encodeParam)
{
    if (encodeParam->codecType == CODEC_H265)
    {
        MBInfo->num_mb = (ALIGN_XXB(32, encodeParam->dstW) *
                          ALIGN_XXB(32, encodeParam->dstH)) >> 10;
    }
    else
    {
        MBInfo->num_mb = (ALIGN_XXB(16, encodeParam->dstW) *
                          ALIGN_XXB(16, encodeParam->dstH)) >> 8;
    }
    MBInfo->p_para = (VencMBInfoPara*)malloc(sizeof(VencMBInfoPara) * MBInfo->num_mb);
    if (MBInfo->p_para == NULL)
    {
        loge("malloc MBInfo->p_para error\n");
        return;
    }
    //logd("mb_num:%d, mb_info_queue_addr:%p\n", MBInfo->num_mb, MBInfo->p_para);
}

void AWVideoEncoderImpl::setMbMode(VideoEncoder* pVideoEnc, EncodeParam* encodeParam)
{
    if (encodeParam->codecType == CODEC_H264 && h264Func.h264MBMode.mode_ctrl_en)
    {
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMBModeCtrl, &h264Func.h264MBMode);
    }
    else if (encodeParam->codecType == CODEC_H265 && h265Func.h265MBMode.mode_ctrl_en)
    {
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamMBModeCtrl, &h265Func.h265MBMode);
    }
    else
        return;
}
void AWVideoEncoderImpl::releaseMb(EncodeParam* encodeParam)
{
    VencMBInfo* pMBInfo;
    VencMBModeCtrl* pMBMode;
    if (encodeParam->codecType == CODEC_H264 && h264Func.h264MBMode.mode_ctrl_en)
    {
        pMBInfo = &h264Func.MBInfo;
        pMBMode = &h264Func.h264MBMode;
    }
    else if (encodeParam->codecType == CODEC_H265 && h265Func.h265MBMode.mode_ctrl_en)
    {
        pMBInfo = &h264Func.MBInfo;
        pMBMode = &h265Func.h265MBMode;
    }
    else
        return;

    if (pMBInfo->p_para)
        free(pMBInfo->p_para);
    if (pMBMode->p_info)
        free(pMBMode->p_info);
}

#endif
#ifdef GET_MB_INFO
void AWVideoEncoderImpl::getMbMinfo(VideoEncoder* pVideoEnc, EncodeParam* encodeParam)
{
    VencMBInfo* pMBInfo;

    if (encodeParam->codecType == CODEC_H264 && h264Func.h264MBMode.mode_ctrl_en)
    {
        pMBInfo = &h264Func.MBInfo;
    }
    else if (encodeParam->codecType == CODEC_H265 && h265Func.h265MBMode.mode_ctrl_en)
    {
        pMBInfo = &h265Func.MBInfo;
    }
    else
        return;


    int i;
    for (i = 0; i < pMBInfo->num_mb; i++)
    {
        logd("No.%d MB: mad=%d, qp=%d, sse=%d, psnr=%f\n", i, pMBInfo->p_para[i].mb_mad,
             pMBInfo->p_para[i].mb_qp, pMBInfo->p_para[i].mb_sse, pMBInfo->p_para[i].mb_psnr);
    }
}
#endif


int AWVideoEncoderImpl::getHeader (void* spsHeader)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    if (mEncodeParam->codecType == CODEC_H264 || \
            mEncodeParam->codecType == CODEC_H265)
    {
        unsigned int head_num = 0;
        if (mEncodeParam->codecType == CODEC_H264)
        {
            VideoEncGetParameter(pVideoEnc, VENC_IndexParamH264SPSPPS, &spsPpsData);
            unsigned char value = 1;
            //VideoEncGetParameter(pVideoEnc, VENC_IndexParamAllParams, &value);
        }
        else if (mEncodeParam->codecType == CODEC_H265)
        {
            VideoEncGetParameter(pVideoEnc, VENC_IndexParamH265Header, &spsPpsData);
            unsigned char value = 1;
            //VideoEncGetParameter(pVideoEnc, VENC_IndexParamAllParams, &value);
        }

        memcpy(spsHeader, spsPpsData.pBuffer, spsPpsData.nLength);
        return spsPpsData.nLength;
        //fwrite(spsPpsData.pBuffer, 1, spsPpsData.nLength, out_file);
        //writeOutputBuf(spsPpsData.pBuffer, spsPpsData.nLength);

        //logd("spsPpsData.nLength: %d\n", spsPpsData.nLength);
        //for(head_num=0; head_num<spsPpsData.nLength; head_num++)
        //logd("the sps_pps :%02x\n", *(spsPpsData.pBuffer+head_num));
    }
}
int AWVideoEncoderImpl::setVBR(unsigned int bitrate)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    pthread_mutex_lock(&mEncodeMutex);
    unsigned int bitRate = bitrate;
    VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    pthread_mutex_unlock(&mEncodeMutex);
}

int AWVideoEncoderImpl::setJpgQuality(int quality)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    pthread_mutex_lock(&mEncodeMutex);
    int jpgQuality = quality;
    VideoEncSetParameter(pVideoEnc, VENC_IndexParamJpegQuality, &jpgQuality);
    pthread_mutex_unlock(&mEncodeMutex);
}
int AWVideoEncoderImpl::setRoi(AvRoiRegionArray* roiRegions)
{
	int ret = 0;
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    pthread_mutex_lock(&mEncodeMutex);

    if(NULL != roiRegions)
    {
        logd("set roiRegions Num:%d \n",roiRegions->roiNum);
        if((roiRegions->roiNum)>MAX_ROI_REGION)
        {
            roiRegions->roiNum = MAX_ROI_REGION;
        }
        for(int k = 0; k < roiRegions->roiNum; k++)
        {
            mRoiConfig[k].bEnable         =  roiRegions->region[k].enable;
            mRoiConfig[k].index           =  k; 
            mRoiConfig[k].nQPoffset       =  roiRegions->region[k].QPoffset;
            mRoiConfig[k].roi_abs_flag    =  roiRegions->region[k].absFlag;
            mRoiConfig[k].sRect.nLeft     =  roiRegions->region[k].x;
            mRoiConfig[k].sRect.nTop      =  roiRegions->region[k].y;
            mRoiConfig[k].sRect.nWidth    =  roiRegions->region[k].w;
            mRoiConfig[k].sRect.nHeight   =  roiRegions->region[k].h;

            ret = VideoEncSetParameter(pVideoEnc, VENC_IndexParamROIConfig, &mRoiConfig[k]);
            CHECK_RETURN(ret);
            logd("mRoiConfig[%d].bEnable      :%d\n",k,mRoiConfig[k].bEnable        );
            logd("mRoiConfig[%d].index        :%d\n",k,mRoiConfig[k].index          );
            logd("mRoiConfig[%d].nQPoffset    :%d\n",k,mRoiConfig[k].nQPoffset      );
            logd("mRoiConfig[%d].roi_abs_flag :%d\n",k,mRoiConfig[k].roi_abs_flag   );
            logd("mRoiConfig[%d].sRect.nLeft  :%d\n",k,mRoiConfig[k].sRect.nLeft    );
            logd("mRoiConfig[%d].sRect.nTop   :%d\n",k,mRoiConfig[k].sRect.nTop     );
            logd("mRoiConfig[%d].sRect.nWidth :%d\n",k,mRoiConfig[k].sRect.nWidth   );
            logd("mRoiConfig[%d].sRect.nHeight:%d\n",k,mRoiConfig[k].sRect.nHeight  );
        }
    }
    pthread_mutex_unlock(&mEncodeMutex);
	return ret;
}

int AWVideoEncoderImpl::encode(AVPacket* inPacket)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    int result;

    pthread_mutex_lock(&mEncodeMutex);

    memset(&inputBuffer,0,sizeof(VencInputBuffer));
    memset(&outputBuffer,0,sizeof(VencOutputBuffer));
    if ((NULL != inPacket->pAddrPhy0) && (NULL != inPacket->pAddrPhy1))
    {
        logd("use phy addr.\n");
        inputBuffer.pAddrPhyY = inPacket->pAddrPhy0;
        inputBuffer.pAddrPhyC = inPacket->pAddrPhy1;;
    }
    else
    {
        logd("use vir addr.\n");
        if ((NULL == inPacket->pAddrVir0) || (NULL == inPacket->pAddrVir1))
        {
            loge("input data is null.");
            pthread_mutex_unlock(&mEncodeMutex);
            return -1;
        }

        GetOneAllocInputBuffer(pVideoEnc, &inputBuffer);

        if (inPacket->dataLen0 == baseConfig.nInputWidth * baseConfig.nInputHeight)
        {
            memcpy(inputBuffer.pAddrVirY, inPacket->pAddrVir0, baseConfig.nInputWidth * baseConfig.nInputHeight);
        }
        else
        {
            loge("input data error.");
            pthread_mutex_unlock(&mEncodeMutex);
            return -1;
        }
        if (inPacket->dataLen1 == baseConfig.nInputWidth * baseConfig.nInputHeight / 2)
        {
            memcpy(inputBuffer.pAddrVirC, inPacket->pAddrVir1, baseConfig.nInputWidth * baseConfig.nInputHeight / 2);
        }
        else
        {
            loge("input data error.");
            pthread_mutex_unlock(&mEncodeMutex);
            return -1;
        }
        FlushCacheAllocInputBuffer(pVideoEnc, &inputBuffer);
    }

    inputBuffer.nID = inPacket->id;
    inputBuffer.nPts = inPacket->pts;
    
    if(inputBuffer.nFlag = inPacket->isKeyframe)
    {
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamForceKeyFrame, &inputBuffer.nFlag);
    }
    
    AddOneInputBuffer(pVideoEnc, &inputBuffer);
    logd("inputBuffer.addr:%lx->%lx \n",inputBuffer.pAddrPhyY,inputBuffer.pAddrPhyC);

    VideoEncodeOneFrame(pVideoEnc);

    int validNum = ValidBitstreamFrameNum(pVideoEnc);
    //logd("ValidBitstreamFrameNum is :%d.\n", validNum);
    if (validNum < 1)
    {
        logw("ValidBitstreamFrameNum is 0.\n");
    }
    AlreadyUsedInputBuffer(pVideoEnc, &inputBuffer);

    if ((NULL == inPacket->pAddrPhy0) && (NULL != inPacket->pAddrVir0))
    {
        logd("ret vir addr.\n");
        ReturnOneAllocInputBuffer(pVideoEnc, &inputBuffer);
    }

    result = GetOneBitstreamFrame(pVideoEnc, &outputBuffer);
    CHECK_RETURN(result);

    AVPacket outPacket;
    outPacket.id           = outputBuffer.nID;
    outPacket.pts          = outputBuffer.nPts;
    if (outPacket.id != inPacket->id)
    {
        logd("change outPacket.id:%lx->%lx %lx\n", outPacket.id, inputBuffer.nID, inPacket->id);
        outPacket.id = inPacket->id;
    }
    if (outPacket.pts != inPacket->pts)
    {
        logd("change outPacket.pts:%llx->%llx %llx\n", outPacket.pts, inputBuffer.nPts, inPacket->pts);
        outPacket.pts = inPacket->pts;
    }

    outPacket.pAddrVir0    = outputBuffer.pData0;
    outPacket.dataLen0     = outputBuffer.nSize0;
    outPacket.pAddrVir1    = outputBuffer.pData1;
    outPacket.dataLen1     = outputBuffer.nSize1;

    if (mDataCbk)
    {
        mDataCbk->encoderDataReady(&outPacket);
    }
    else
    {
        loge("AWVideoEncoderDataCallback is NULL.");
    }

    FreeOneBitStreamFrame(pVideoEnc, &outputBuffer);
    mFreamIndex++;
    pthread_mutex_unlock(&mEncodeMutex);
    return 0;
}

int AWVideoEncoderImpl::encodePhy(const void* inputBuf, unsigned int inputLen,
                               void* outputBuf, unsigned int outputLen)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    int result;
    pthread_mutex_lock(&mEncodeMutex);
    memset(&inputBuffer,0,sizeof(VencInputBuffer));
    memset(&outputBuffer,0,sizeof(VencOutputBuffer));
    mOutputBuf = outputBuf;
    mOutputBufLen = outputLen;
    mOutputBufPos = 0;
    
    if (NULL != inputBuf)
    {
        //logd("use phy addr.\n");
        inputBuffer.pAddrPhyY = (unsigned char*)inputBuf;
        inputBuffer.pAddrPhyC = (unsigned char*)inputBuf + baseConfig.nInputWidth * baseConfig.nInputHeight;
    }

    AddOneInputBuffer(pVideoEnc, &inputBuffer);

    VideoEncodeOneFrame(pVideoEnc);

    int validNum = ValidBitstreamFrameNum(pVideoEnc);
    //logd("ValidBitstreamFrameNum is :%d.\n", validNum);
    if (validNum < 1)
    {
        logw("ValidBitstreamFrameNum is 0.\n");
    }
    AlreadyUsedInputBuffer(pVideoEnc, &inputBuffer);

    result = GetOneBitstreamFrame(pVideoEnc, &outputBuffer);
    CHECK_RETURN(result);

    result = writeOutputBuf(outputBuffer.pData0, outputBuffer.nSize0);
    CHECK_RETURN(result);

    if (outputBuffer.nSize1)
    {
        result = writeOutputBuf(outputBuffer.pData1, outputBuffer.nSize1);
        CHECK_RETURN(result);
    }

    FreeOneBitStreamFrame(pVideoEnc, &outputBuffer);

    pthread_mutex_unlock(&mEncodeMutex);
    return mOutputBufPos;
}
int AWVideoEncoderImpl::encode(const void* inputBuf, unsigned int inputLen,
                               void* outputBuf, unsigned int outputLen)
{
    if (NULL == pVideoEnc)
    {
        loge("VideoEncCreate error, return");
        return -1;
    }
    int result;
    mInputBuf = inputBuf;
    mInputBufLen = inputLen;
    mInputBufPos = 0;
    mOutputBuf = outputBuf;
    mOutputBufLen = outputLen;
    mOutputBufPos = 0;

    pthread_mutex_lock(&mEncodeMutex);

#ifdef USE_SVC
    // used for throw frame test with SVC
    int TemporalLayer = -1;
    char p9bytes[9] = {0};
#endif

    GetOneAllocInputBuffer(pVideoEnc, &inputBuffer);
    {
#if NO_READ_WRITE
        if (mFreamIndex == 0)
#endif
        {
#ifdef USE_AFBC_INPUT
            //unsigned int size1, size2;
            //size1 = fread(inputBuffer.pAddrVirY, 1, bufferParam.nSizeY, in_file);
            //if(size1!= bufferParam.nSizeY)
            //{
            //fseek(in_file, 0L, SEEK_SET);
            //size1 = fread(inputBuffer.pAddrVirY, 1, bufferParam.nSizeY, in_file);
            //}

            result = readInputBuf(inputBuffer.pAddrVirY, bufferParam.nSizeY);
            CHECK_RETURN(result);
#else
//                unsigned int size1, size2;
//                size1 = fread(inputBuffer.pAddrVirY, 1,
//                        baseConfig.nInputWidth*baseConfig.nInputHeight, in_file);
//                size2 = fread(inputBuffer.pAddrVirC, 1,
//                          baseConfig.nInputWidth*baseConfig.nInputHeight/2, in_file);

//                if((size1!= baseConfig.nInputWidth*baseConfig.nInputHeight)
//                 || (size2!= baseConfig.nInputWidth*baseConfig.nInputHeight/2))
//                {
//                    fseek(in_file, 0L, SEEK_SET);
//                    size1 = fread(inputBuffer.pAddrVirY, 1,
//                             baseConfig.nInputWidth*baseConfig.nInputHeight, in_file);
//                    size2 = fread(inputBuffer.pAddrVirC, 1,
//                             baseConfig.nInputWidth*baseConfig.nInputHeight/2, in_file);
//                }
            result = readInputBuf(inputBuffer.pAddrVirY, baseConfig.nInputWidth * baseConfig.nInputHeight);
            CHECK_RETURN(result);
            result = readInputBuf(inputBuffer.pAddrVirC, baseConfig.nInputWidth * baseConfig.nInputHeight / 2);
            CHECK_RETURN(result);
#endif
        }
    }
    inputBuffer.bEnableCorp = 0;
    inputBuffer.sCropInfo.nLeft =  240;
    inputBuffer.sCropInfo.nTop  =  240;
    inputBuffer.sCropInfo.nWidth  =  240;
    inputBuffer.sCropInfo.nHeight =  240;
    FlushCacheAllocInputBuffer(pVideoEnc, &inputBuffer);
    inputBuffer.nPts += 1 * 1000 / mEncodeParam->frameRate;
    AddOneInputBuffer(pVideoEnc, &inputBuffer);

#ifdef SET_MB_INFO
    setMbMode(pVideoEnc, mEncodeParam);
#endif

#ifdef SET_SMART
    if (mFreamIndex == 0)
    {
        if (mEncodeParam->codecType == CODEC_H264)
        {
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamSmartFuntion, &h264Func.sH264Smart);
        }
        else if (mEncodeParam->codecType == CODEC_H265)
        {
            VideoEncSetParameter(pVideoEnc, VENC_IndexParamSmartFuntion, &h265Func.h265Smart);
        }
    }
#endif

#ifdef VBR
    unsigned int bitRate = 50 * 1024 * 1024;
    if (mFreamIndex == 0)
    {
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    }
    if (mFreamIndex == 90)
    {
        bitRate = 80 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    }
    else if (mFreamIndex == 180)
    {
        bitRate = 50 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    }
    else if (mFreamIndex == 250)
    {
        bitRate = 80 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    }
    else if (mFreamIndex == 1500)
    {
        bitRate = 50 * 1024 * 1024;
        VideoEncSetParameter(pVideoEnc, VENC_IndexParamBitrate, &bitRate);
    }
#endif


    //time1 = GetNowUs();
    VideoEncodeOneFrame(pVideoEnc);
    //time2 = GetNowUs();
    //logv("encode frame %d use time is %lldus..\n", mFreamIndex, (time2 - time1));
    //time3 += time2 - time1;

#ifdef GET_MB_INFO
    memset(&sMbSumInfo, 0, sizeof(VencMBSumInfo));

    getMbMinfo(pVideoEnc, &mEncodeParam);

    if (mEncodeParam->codecType == CODEC_H264)
    {
        VideoEncGetParameter(pVideoEnc, VENC_IndexParamMBSumInfoOutput, &sMbSumInfo);
    }
    else if (mEncodeParam->codecType == CODEC_H265)
    {
        VideoEncGetParameter(pVideoEnc, VENC_IndexParamMBSumInfoOutput, &sMbSumInfo);
    }

    avrSse += sMbSumInfo.sumSse;
    sumSse = avrSse;
    if (mFreamIndex == 0)
    {
        minSse = sMbSumInfo.sumSse;
        maxSse = sMbSumInfo.sumSse;
    }
    else
    {
        if (sMbSumInfo.sumSse < minSse)
        {
            minSse = sMbSumInfo.sumSse;
            minSseFrame = mFreamIndex;
        }
        else if (sMbSumInfo.sumSse > maxSse)
        {
            maxSse = sMbSumInfo.sumSse;
            maxSseFrame = mFreamIndex;
        }
    }
    if (mFreamIndex == (mEncodeParam->frameCount - 1))
    {
        double min_psnr, max_psnr, avr_psnr;
        unsigned pic_size = mEncodeParam->dstW * mEncodeParam->dstH;

        avrSse /= mEncodeParam->frameCount;
        max_psnr = 10.0 * log10(255.0 * 255.0 * 1024 / (1.0 * minSse / pic_size));
        min_psnr = 10.0 * log10(255.0 * 255.0 * 1024 / (1.0 * maxSse / pic_size));
        avr_psnr = 10.0 * log10(255.0 * 255.0 * 1024 / (1.0 * avrSse / pic_size));
        logd("frame[%u] get min_psnr:%f, frame[%u] get max_psnr:%f, average_psnr:%f\n",
             maxSseFrame,
             min_psnr,
             minSseFrame,
             max_psnr,
             avr_psnr);
    }
#endif

    int validNum = ValidBitstreamFrameNum(pVideoEnc);
    //logd("ValidBitstreamFrameNum is :%d.\n", validNum);
    if (validNum < 1)
    {
        logw("ValidBitstreamFrameNum is 0.\n");
    }
    AlreadyUsedInputBuffer(pVideoEnc, &inputBuffer);
    ReturnOneAllocInputBuffer(pVideoEnc, &inputBuffer);

    result = GetOneBitstreamFrame(pVideoEnc, &outputBuffer);
    CHECK_RETURN(result);

#ifdef USE_SUPER_FRAME
    if ((sSuperFrameCfg.eSuperFrameMode == VENC_SUPERFRAME_DISCARD) && (result == -1))
    {
        logd("VENC_SUPERFRAME_DISCARD: discard frame %d\n", mFreamIndex);
        continue;
    }
#endif

#ifdef USE_SVC
    // used for throw frame test with SVC
    memcpy(p9bytes, outputBuffer.pData0, 9);
    TemporalLayer = SeekPrefixNAL(p9bytes);

    switch (TemporalLayer)
    {

    case 3:
    case 2:
    case 1:
        logv("just write the PrefixNAL\n");
        //fwrite(outputBuffer.pData0, 1, 9, out_file);
        result = writeOutputBuf(outputBuffer.pData0, 9);
        CHECK_RETURN(result);
        break;

    default:
        logv("\nTemporalLayer=%d,  mFreamIndex=%d\n", TemporalLayer, mFreamIndex);
        //fwrite(outputBuffer.pData0, 1, outputBuffer.nSize0, out_file);
        result = writeOutputBuf(outputBuffer.pData0, outputBuffer.nSize0);
        CHECK_RETURN(result);
        if (outputBuffer.nSize1)
        {
            //fwrite(outputBuffer.pData1, 1, outputBuffer.nSize1, out_file);
            result = writeOutputBuf(outputBuffer.pData1, outputBuffer.nSize1);
            CHECK_RETURN(result);
        }
        break;
    }
#else

#if NO_READ_WRITE

#else
    //fwrite(outputBuffer.pData0, 1, outputBuffer.nSize0, out_file);
    result = writeOutputBuf(outputBuffer.pData0, outputBuffer.nSize0);
    CHECK_RETURN(result);

    if (outputBuffer.nSize1)
    {
        //fwrite(outputBuffer.pData1, 1, outputBuffer.nSize1, out_file);
        result = writeOutputBuf(outputBuffer.pData1, outputBuffer.nSize1);
        CHECK_RETURN(result);
    }
#endif
#endif
    FreeOneBitStreamFrame(pVideoEnc, &outputBuffer);
    mFreamIndex++;
    pthread_mutex_unlock(&mEncodeMutex);
    return mOutputBufPos;
}

}



