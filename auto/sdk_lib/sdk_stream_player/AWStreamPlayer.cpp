
/************************************************************
    Copyright (c) 2018 by Allwinnertech Co., Ltd.

            http://www.allwinnertech.com

************************************************************
File Name           :
Version             :   release 0.1
Author              :   yuanguochao

Description         :   This decord is depend on Tinyalsa with cerdaX
                        for AllWinner T7 Soc system.
                        It will be build with cerdaX,
                        plz read Makefile for more information.
public functions    :

History Information Description
Date                    Author                  Modification
2018.11.15             yuanguochao               Created file
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <queue>

#include "vdecoder.h"
#include "memoryAdapter.h"
#include "sunxiMemInterface.h"

#include "AWStreamPlayer.h"
#include "hwdisp2.h"
#include "G2dApi.h"

//#include "sunxiMemInterface.h"
using namespace android;
using namespace g2dapi;

#define MODULE_VERSION "V2.0.20220506"

/*-------------------------------------------------------------------------
                                define
-------------------------------------------------------------------------*/
//#define DUMP_YUV_DATAS
#define DUMP_YUV_COUNTS (10)
#define FREAM_TEST
#define DECODE_LOG
#ifdef DECODE_LOG
#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#define HL_TWK_RED_YEL  "\033[1m\033[5;31;43m"
#define HL_RED_WRT      "\033[1;31;47m"
#define HL_RED          "\033[1;31m"
#define HL_YEL          "\033[1;33m"

#define PF_CLR  "\033[0m"

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

static int log_level = LOG_LEVEL_ALL;

#define logf(format, ...) \
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
           DEBUG( "[D]"  format,##__VA_ARGS__);\
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
         if(a!=0){\
           DEBUG(HL_RED "[E]" "[%s] fail! line:%d ret:%d \n" PF_CLR, __FUNCTION__, __LINE__,a);\
           return a; \
           }\
    } while (0)
#define CHECK_DISP_RETURN(a,b) \
    do { \
         if(a<0){\
           DEBUG(HL_RED "[E]" "[%s]%s fail! line:%d " PF_CLR, __FUNCTION__,b, __LINE__);\
           return; \
           }\
    } while (0)

typedef unsigned char     uint8;
typedef char              int8;

#define ALIGN(x,a) (((x) + (a-1)) & ~(a-1))

namespace awstreamplayer
{

static const int VE_FREQ = 300 * 1000 * 1000;
static const int NAL_DEF_SIZE = 2000 * 1000;

static const int DISP_X_DEFAULT = 0;
static const int DISP_Y_DEFAULT = 0;
static const int DISP_W_DEFAULT = 1280;
static const int DISP_H_DEFAULT = 800;

static const int SCR_ID_DEFAULT = 0;
static const int SCR_ID_CVBS = 1;
static const int CHL_ID_DEFAULT = 0;
static const int LYR_ID_DEFAULT = 0;
static const int ZORDER_DEFAULT = 2;

static const int CODEC_FMT_DEFAULT = CODEC_H264;
static const int PIX_FMT_DEFAULT = PIXEL_FORMAT_NV21;
static const int DISP_PIXEL_FORMAT_DEFAULT = DISP_FORMAT_YUV420_SP_VUVU;
static const int VIDEO_QUEUE_WARN_HOLD = 30 * 1;


class AWStreamPlayerImpl: public AWStreamPlayer
{
public:
    AWStreamPlayerImpl(PlayerParam* param);
    ~AWStreamPlayerImpl();

    virtual void resetPPS();
    virtual void reset(PlayerParam* param);
    virtual void startThread();
    virtual int sendFrameToThread(unsigned char* data, unsigned int len);
    virtual void stopThread();
    virtual int setLogLevel(int level);

    int decodeFrameDrectly(unsigned char* data, unsigned int len);
    int decodeFrame(const void* inputBuf, unsigned int inputLen);
    void hideDisplay(bool hide);
    int stopAndGetLeftFream(void* outputBuf, unsigned int outputLen);

private:
    int initial();
    void finish();

    int reMallocDecodeBuf(int bufLen);
    int getDecodeBufLen();
    void exitVideoQueData();
    void freeDecodeBuf();

    void pushVideoQueData(unsigned char* data, unsigned int len);
    int getVideoQueDataWait();
    void freeVideoQueData();

    typedef enum DecodeState_
    {
        DECODE_STATE_ERROR = -1,
        DECODE_STATE_STOP = 0,
        DECODE_STATE_START,
        DECODE_STATE_IDLE
    } DecodeState;

    typedef struct PicInfo_
    {
        int dataW;
        int dataH;
        int vildW;
        int vildH;
        int fmt;
        int fd;
        void* pAddr;
    } PicInfo;
    void setDecodeState(DecodeState state);
    DecodeState getDecodeState(void);

    void reallocDMA(int size);
    int g2dProcees(PicInfo* pSrc,PicInfo* pDst,int rotation);
    void saveNV21Picture(VideoPicture* pPicture);
    void saveRotPicture(PicInfo* pic);
    
    void showPicture_DE(PicInfo* pPicture);
    void hidePicture_DE();
    void showPicture_TV(PicInfo* pPicture);
    void hidePicture_TV();
    void ratate(PicInfo* pPicture);
    
    void startDecodeThread();
    void stopDecodeThread();
    static void* VDecordThread(void* param);
    int doDataVDecode();

    int writeOutputBuf(void* buf, int len);
    int readInputBuf(void* buf, int len);



    VConfig             mVideoConf;
    VideoStreamInfo     mStreamInfo;

    HwDisplay* gVdecDisp;
    int video_layer0;
    int video_layer1;
    dma_mem_des_t mG2dMem;
    int mG2dFd;
    
    const void* mOutputBuf;
    int mOutputBufLen ;
    int mOutputBufPos;
    const void* mInputBuf;
    int mInputBufLen ;
    int mInputBufPos ;

    struct ScMemOpsS*   memops;
    VideoDecoder* pVideoDec;
    VideoPicture* pPicture;
    VideoStreamDataInfo  dataInfo;
    int nValidSize;
    int nRequestDataSize;   //=one NALU frame size
    char* packet_buf;
    int packet_buflen;
    char* packet_ringBuf;
    int packet_ringBufLen;
    int64_t packet_pts;
    int64_t packet_pcr;
    PlayerParam* mParam;
    bool paramUpdate;

    uint8* mDecodeBuf;
    int  mDecodeBufLen;
    bool hideImage;

    pthread_t mThread;
    pthread_mutex_t     mDecodeMutex;
    pthread_cond_t      mDecodeCond;

    pthread_mutex_t     mQueueMutex;
    pthread_cond_t      mQueueCond;

    sem_t mQueueSem;

    DecodeState mDecordState;

    typedef struct videoData_
    {
        void* data;
        int len;
    } videoData;

    std::queue<videoData> mVideoQue;
};

/*-------------------------------------------------------------------------
                                AWStreamPlayer
-------------------------------------------------------------------------*/
AWStreamPlayer* AWStreamPlayer::create(PlayerParam* param)
{
    AWStreamPlayer* pDecoder = (AWStreamPlayer*) new AWStreamPlayerImpl(param);
    return pDecoder;
}

void AWStreamPlayer::destroy(AWStreamPlayer* decoder)
{
    delete decoder;
}

/*-------------------------------------------------------------------------
                                AWStreamPlayerImpl
-------------------------------------------------------------------------*/


AWStreamPlayerImpl::AWStreamPlayerImpl(PlayerParam* param)
{
    printf("new AWStreamPlayerImpl() version:%s\n", MODULE_VERSION);
    pVideoDec = NULL;
    pPicture = NULL;
    gVdecDisp = NULL;
    video_layer0 = -1;
    video_layer1 = -1;
    mDecodeBuf = NULL;
    mG2dFd = -1;

    pthread_mutex_init(&mDecodeMutex, NULL);
    pthread_cond_init(&mDecodeCond, NULL);

    pthread_mutex_init(&mQueueMutex, NULL);
    pthread_cond_init(&mQueueCond, NULL);

    sem_init(&mQueueSem,0,0);
    setDecodeState(DECODE_STATE_ERROR);
    mParam = new PlayerParam;
    
    if(NULL!=param)
    {
        memcpy(mParam , param,sizeof(PlayerParam));
    }
    else
    {
        mParam->dispW = DISP_W_DEFAULT;
        mParam->dispH = DISP_H_DEFAULT;
        mParam->zorder = ZORDER_DEFAULT;
        mParam->codecType = (CodecType)CODEC_FMT_DEFAULT;
    }
        
    logw("initial:(%d,%d)[%d:%d],(%d,%d)[%d:%d]\n", \
                    mParam->dispX, mParam->dispY, mParam->dispW, mParam->dispH,\
                    mParam->cropX, mParam->cropY, mParam->cropW, mParam->cropH);

    if (0 > initial())
    {
        loge("AWStreamPlayer initial failed!\n");
    }
    setDecodeState(DECODE_STATE_STOP);
}

int AWStreamPlayerImpl::setLogLevel(int level)
{
    log_level = level;
}

AWStreamPlayerImpl::~AWStreamPlayerImpl()
{
    printf("~ AWStreamPlayerImpl()\n");
    stopThread();
    finish();
    delete mParam;
    sem_destroy(&mQueueSem);
    pthread_mutex_destroy(&mDecodeMutex);
    pthread_cond_destroy(&mDecodeCond);

    pthread_mutex_destroy(&mQueueMutex);
    pthread_cond_destroy(&mQueueCond);
}
void AWStreamPlayerImpl::resetPPS()
{
    if (pVideoDec == NULL)
    {
        loge(" decoder demom CreareateVideoDecoder() error \n");
        return  ;
    }
    hidePicture_DE();
    ResetVideoDecoder(pVideoDec);
    ReopenVideoEngine(pVideoDec, &mVideoConf, &mStreamInfo);
}

void AWStreamPlayerImpl::reset(PlayerParam* param)
{
    memcpy(mParam,param,sizeof(PlayerParam));
    paramUpdate = true;
    hideImage = false;
}

int AWStreamPlayerImpl::initial()
{
    int nRet = 0;
    int i;
//    timeval start1;
//    gettimeofday( &start1, NULL );

    memset((void*)&mVideoConf, 0, sizeof(VConfig));
    memset((void*)&mStreamInfo, 0, sizeof(VideoStreamInfo));

    memops = MemAdapterGetOpsS();
    if (memops == NULL)
    {
        printf("memops is NULL\n");
        return -1;
    }
    CdcMemOpen(memops);

    mStreamInfo.eCodecFormat = mParam->codecType;

    mVideoConf.eOutputPixelFormat  = PIX_FMT_DEFAULT;
    mVideoConf.nDisplayHoldingFrameBufferNum = 1;
    mVideoConf.nDecodeSmoothFrameBufferNum = 3;
    mVideoConf.memops = memops;
    mVideoConf.nVeFreq = 300 * 1000 * 1000;   //300MH
    //mVideoConf.bQuickDecoder = 1;    //
    logd("nDisplayHoldingFrameBufferNum::%d\n", mVideoConf.nDisplayHoldingFrameBufferNum);
    logd("nDecodeSmoothFrameBufferNum:%d\n", mVideoConf.nDecodeSmoothFrameBufferNum);
    //logd("bQuickDecoder:%d\n", mVideoConf.bQuickDecoder);

    if (0 != mParam->scaleRatio)
    {
        mVideoConf.bScaleDownEn = 1;
        mVideoConf.nHorizonScaleDownRatio = mParam->scaleRatio;
        mVideoConf.nVerticalScaleDownRatio = mParam->scaleRatio;
    }
#if 1
    if (0 != mParam->rotation)
    {
        mVideoConf.bRotationEn = 1;
        mVideoConf.nRotateDegree = mParam->rotation;
    }
#endif /* BOGUS */
    logd("disp:(%d,%d)[%d:%d]\n", mParam->dispX, mParam->dispY, mParam->dispW, mParam->dispH);
    logd("crop:(%d,%d)[%d:%d]\n", mParam->cropX, mParam->cropY, mParam->cropW, mParam->cropH);
    logd("args:(%d,%d,%d)f:%d\n", mParam->chLID, mParam->lyrID, mParam->zorder, mParam->codecType);

//    timeval Create1;
//    gettimeofday( &Create1, NULL );
//    long long int timeuse = 1000000 * ( Create1.tv_sec - start1.tv_sec ) + Create1.tv_usec - start1.tv_usec;
//    logd("init parm - %lld ms",timeuse,timeuse/1000);

    AddVDPlugin();
    pVideoDec = CreateVideoDecoder();                                   //VdecH264:step1
    if (pVideoDec == NULL)
    {
        loge(" decoder demom CreareateVideoDecoder() error \n");
        return -1;
    }
       
    nRet = InitializeVideoDecoder(pVideoDec, &mStreamInfo, &mVideoConf); //VdecH264:step2

    if (nRet != 0)
    {
        loge("decoder demom initialize video decoder fail.");
        DestroyVideoDecoder(pVideoDec);
        pVideoDec = NULL;
    }

    if (gVdecDisp == NULL)
        gVdecDisp = HwDisplay::getInstance();

    memset(&mG2dMem, 0, sizeof(dma_mem_des_t));
    nRet = allocOpen(MEM_TYPE_DMA, &mG2dMem, NULL);
    if (nRet < 0)
    {
        loge("ion_alloc_open failed\n");
        return nRet;
    }
    
    mG2dMem.size = mParam->dispW*mParam->dispH*3/2;     //default use the display size.
    nRet = allocAlloc(MEM_TYPE_DMA, &mG2dMem, NULL);
    if (nRet < 0)
    {
        loge("allocAlloc failed\n");
        return nRet;
    }
    return nRet;
}

void AWStreamPlayerImpl::finish()
{
    pthread_mutex_lock(&mDecodeMutex);

    mDecordState = DECODE_STATE_STOP;

    freeDecodeBuf();

    if (NULL != pVideoDec)
    {
        DestroyVideoDecoder(pVideoDec);
        pVideoDec = NULL;
    }

    if (NULL != memops)
    {
        CdcMemClose(memops);
        memops = NULL;
    }

    if (NULL != gVdecDisp)
    {
        gVdecDisp = NULL;
    }

    if(mG2dFd >= 0)
    {
        g2dUnit(mG2dFd);
    }
    allocFree(MEM_TYPE_DMA, &mG2dMem, (void*)NULL);
    pthread_mutex_unlock(&mDecodeMutex);

}
void AWStreamPlayerImpl::setDecodeState(DecodeState state)
{
    pthread_mutex_lock(&mDecodeMutex);
    mDecordState = state;
    pthread_mutex_unlock(&mDecodeMutex);
}

AWStreamPlayerImpl::DecodeState AWStreamPlayerImpl::getDecodeState(void)
{
    DecodeState ret;
    pthread_mutex_lock(&mDecodeMutex);
    ret = mDecordState;
    pthread_mutex_unlock(&mDecodeMutex);
    return ret;
}
void AWStreamPlayerImpl::startThread()
{
    if(DECODE_STATE_START == getDecodeState())
    {
        return;
    }
    if (getDecodeState() < 0)
    {
        loge("AWStreamPlayer can not wrok\n");
        return;
    }

    setDecodeState(DECODE_STATE_START);
    startDecodeThread();
}

void AWStreamPlayerImpl::stopThread()
{
    if(DECODE_STATE_STOP == getDecodeState())
    {
        return;
    }
    setDecodeState(DECODE_STATE_STOP);
    sem_post(&mQueueSem);
    stopDecodeThread();
    freeVideoQueData();
    hidePicture_DE();
    hidePicture_TV();
}

void AWStreamPlayerImpl::pushVideoQueData(unsigned char* data, unsigned int len)
{
    //pthread_mutex_lock( &mQueueMutex );
    //logd("pushVideoQueData:%#X,len:%d\n", data, len);

    videoData newVideo;
    newVideo.len = len;
    newVideo.data = malloc(len);
    memset(newVideo.data, 0, len);
    memcpy(newVideo.data, data, len);
    //logd("videoData malloc newVideo.data:%#X,len:%d\n", newVideo.data, newVideo.len);
    mVideoQue.push(newVideo);

    //data_cond.notify_one();  
    //pthread_cond_signal(&mQueueCond);
    #ifdef FREAM_TEST
    static int i=0;
    struct timeval time;
    gettimeofday(&time, NULL);
    logd("[FREAM_TEST]QU0:%5u,[%10ld-%10ld],%p %8u\n",len,time.tv_sec,time.tv_usec,data,len);
    #endif
    sem_post(&mQueueSem);
    //pthread_mutex_unlock(&mQueueMutex);
    #ifdef FREAM_TEST
    gettimeofday(&time, NULL);
    logd("[FREAM_TEST]QU1:%5u,[%10ld-%10ld],%p %8u\n",len,time.tv_sec,time.tv_usec,data,len);
    #endif

    if (mVideoQue.size() > VIDEO_QUEUE_WARN_HOLD)
    {
        logw("video data queue is too large:%zu,plz check!!\n", mVideoQue.size());
    }
}

int AWStreamPlayerImpl::getVideoQueDataWait()
{
    int curFreamLen = 0;
    //std::unique_lock<std::mutex>lk(mut);
    //data_cond.wait(lk,[this]{return !this->data_queue.empty();});
    pthread_mutex_lock( &mQueueMutex );

    if (DECODE_STATE_START != getDecodeState())
    {
        logw("decode state is idle,out!\n");
        pthread_mutex_unlock(&mQueueMutex );
        return curFreamLen;
    }
    if (mVideoQue.empty())
    {
        //pthread_cond_wait(&mQueueCond, &mQueueMutex);
        sem_wait(&mQueueSem);
    }

    if (mVideoQue.empty())
    {
        logd("mVideoQue.empty!\n");
        pthread_mutex_unlock(&mQueueMutex );
        return curFreamLen;
    }

    videoData newVideo;
    newVideo = mVideoQue.front();
    mVideoQue.pop();

    curFreamLen = newVideo.len;

    if (getDecodeBufLen() >= curFreamLen)
    {
        memcpy(mDecodeBuf, newVideo.data, curFreamLen);
    }
    else
    {
        logw("mDecodeBuf not enough,len:%d < remalloc:%d!\n", getDecodeBufLen(), curFreamLen);

        reMallocDecodeBuf(curFreamLen);

        if (getDecodeBufLen() >= curFreamLen)
        {
            memcpy(mDecodeBuf, newVideo.data, curFreamLen);
        }
    }

    free(newVideo.data);

    pthread_mutex_unlock(&mQueueMutex );
    return curFreamLen;
}
void AWStreamPlayerImpl::exitVideoQueData()
{
    pthread_mutex_lock( &mQueueMutex );
    //pthread_cond_broadcast(&mQueueCond);
    sem_post(&mQueueSem);
    pthread_mutex_unlock(&mQueueMutex );
}

void AWStreamPlayerImpl::freeVideoQueData()
{
    pthread_mutex_lock( &mQueueMutex );

    logw("mVideoQue.size:%zu\n", mVideoQue.size());
    while (!mVideoQue.empty())
    {
        videoData newVideo;
        newVideo = mVideoQue.front();
        logd("videoData free newVideo.data:%#X\n", (unsigned int)newVideo.data);
        free(newVideo.data);
        mVideoQue.pop();
    }
    //pthread_cond_broadcast(&mQueueCond);
    sem_post(&mQueueSem);
    pthread_mutex_unlock(&mQueueMutex );
}

void AWStreamPlayerImpl::freeDecodeBuf()
{
    if (NULL != mDecodeBuf)
    {
        free(mDecodeBuf);
        mDecodeBuf = NULL;
        mDecodeBufLen = 0;
    }
}

int AWStreamPlayerImpl::getDecodeBufLen()
{
    return mDecodeBufLen;
}

int AWStreamPlayerImpl::reMallocDecodeBuf(int bufLen)
{
    freeDecodeBuf();

    mDecodeBuf = (uint8*)malloc(bufLen);

    if (NULL == mDecodeBuf)
    {
        loge("buf is not enough!\n");
        return 0;
    }

    memset(mDecodeBuf, 0, bufLen);
    mDecodeBufLen = bufLen;
}

int AWStreamPlayerImpl::doDataVDecode()
{
    int freamLen;
    int nRet;

    reMallocDecodeBuf(NAL_DEF_SIZE);
    while (DECODE_STATE_START == mDecordState)
    {
        freamLen = getVideoQueDataWait();
        if (freamLen > getDecodeBufLen())
        {
            logw("buf len error,freamLen len:%d,mDecodeBufLen:%d\n", freamLen, getDecodeBufLen());
            continue;
        }

        if (freamLen < 4)
        {
            logw("freamLen < 4, there is no data.\n");
            continue;
        }

        if (DECODE_STATE_START == mDecordState)
        {
            decodeFrame(mDecodeBuf, freamLen);
        }

    }
    logi("doDataVDecode thread exit!\n");

}

int AWStreamPlayerImpl::sendFrameToThread(unsigned char* data, unsigned int len)
{
    int ret = 0;
    if(DECODE_STATE_START == mDecordState)
    {
        pushVideoQueData(data,  len);
    }
    else
    {
        ret = -1;
    }
    return ret;
}

int AWStreamPlayerImpl::decodeFrameDrectly(unsigned char* data, unsigned int len)
{
    decodeFrame(data, len);
}

void* AWStreamPlayerImpl::VDecordThread(void* param)
{
    AWStreamPlayerImpl* pThis = static_cast<AWStreamPlayerImpl*>(param);
    if (NULL != pThis)
    {
        pThis->doDataVDecode();
    }
    else
    {
        loge(" there is no object for MicRecordThread!\n");
    }
}
void AWStreamPlayerImpl::startDecodeThread()
{
    int result = pthread_create(&mThread, NULL, VDecordThread, (void*)this);
    if (result != 0)
    {
        loge("Create pthread error!\n");
    }
}

void AWStreamPlayerImpl::stopDecodeThread()
{
    exitVideoQueData();
    int ret = pthread_join(mThread, NULL);
    logi("pthread_join ret:%d \n", ret);
}

int AWStreamPlayerImpl::writeOutputBuf(void* buf, int len)
{
    if (mOutputBufLen < mOutputBufPos + len)
    {
        loge("writeOutputBuf out of range[%d<%d]!!\n", mOutputBufLen, mOutputBufPos + len);
        return mOutputBufPos + len;
    }
    memcpy((char*)mOutputBuf + mOutputBufPos, buf, len);
    mOutputBufPos += len;
    return 0;
}

int AWStreamPlayerImpl::readInputBuf(void* buf, int len)
{
    if (mInputBufLen < mInputBufPos + len)
    {
        loge("readInputBuf out of range!\n");
        return mInputBufPos + len;
    }

    memcpy(buf, (char*)mInputBuf + mInputBufPos, len);
    mInputBufPos += len;
    return 0;
}

void AWStreamPlayerImpl::saveNV21Picture(VideoPicture* pPicture)
{
    
    char path[60];
    struct timeval time;
    gettimeofday(&time, NULL);
    sprintf(path, "/tmp/[%dx%d]nv21%lld.yuv",
            pPicture->nWidth, pPicture->nHeight,time.tv_usec);
    
    int nSizeY, nSizeUV;
    #if 1
        static FILE* fp = NULL;
        if (fp == NULL)
        {
            fp = fopen(path, "ab+");
        }
        nSizeY = pPicture->nWidth * pPicture->nHeight ;
        nSizeUV = nSizeY >> 1;
        fwrite(pPicture->pData0, 1, nSizeY, fp);
        fwrite(pPicture->pData1, 1, nSizeUV, fp);
        fclose(fp);
    #else
        static int count = 0;
        if(count++>DUMP_YUV_COUNTS)return;

        FILE* fp = fopen(path, "ab");
        nSizeY = pPicture->nWidth * pPicture->nHeight ;
        nSizeUV = nSizeY >> 1;
        fwrite(pPicture->pData0, 1, nSizeY, fp);
        fwrite(pPicture->pData1, 1, nSizeUV, fp);
        fclose(fp);
    #endif
}

void AWStreamPlayerImpl::saveRotPicture(PicInfo* pPicture)
{
    
    char path[60];
    struct timeval time;
    gettimeofday(&time, NULL);
    sprintf(path, "/tmp/[%d_%d]nv21_rot%lld.yuv",pPicture->dataW, pPicture->dataH,time.tv_usec);
    
    #if 0
        static FILE* fp = NULL;
        if (fp == NULL)
        {
            fp = fopen(path, "ab");
        }
        fwrite((void*)mG2dMem.vir, 1, mG2dMem.size, fp);
    #else
        static int count = 0;
        if(count++>DUMP_YUV_COUNTS)return;

        FILE* fp = fopen(path, "ab");
        fwrite((void*)mG2dMem.vir, 1, mG2dMem.size, fp);
        fclose(fp);
    #endif
}
int AWStreamPlayerImpl::decodeFrame(const void* inputBuf, unsigned int inputLen)
{
    mInputBuf = inputBuf;
    mInputBufLen = inputLen;
    mInputBufPos = 0;
    void *pops;
    if ((NULL == inputBuf))
    {
        loge("buffer is NULL!\n");
        return -1;
    }
    #ifdef FREAM_TEST
    static int DCDi=0;
    struct timeval time;
    gettimeofday(&time, NULL);
    logd("[FREAM_TEST]DCD:%5u,[%10ld-%10ld],%p %8d\n",inputLen,time.tv_sec,time.tv_usec,inputBuf,DCDi);
    #endif

    //logw("inputLen = %d,%02x %02x %02x %02x %02x,%02x %02x %02x",inputLen,
    //              data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
    //-----------------------dcoder-------------------
    //printf("\t\t\t YGC Get inputLen:%d\n", inputLen);

    int nRet;
    nRequestDataSize = inputLen;
    nValidSize = VideoStreamBufferSize(pVideoDec, 0) - VideoStreamDataSize(pVideoDec, 0);
    if (nRequestDataSize > nValidSize)
    {
        loge("nRequestDataSize=%d > nValidSize=%d\n",nRequestDataSize,nValidSize);
        return -1;
    }

    nRet = RequestVideoStreamBuffer(pVideoDec,
                                    nRequestDataSize,
                                    (char**)&packet_buf,
                                    &packet_buflen,
                                    (char**)&packet_ringBuf,
                                    &packet_ringBufLen,
                                    0);                                     //VdecH264:step3
    if (nRet != 0)
    {
        loge(" RequestVideoStreamBuffer nRet=%d. request size: %d, valid size: %d ",
             nRequestDataSize, nValidSize,nRet);
        return -2;
    }

    if (packet_buflen + packet_ringBufLen < nRequestDataSize)
    {
        loge(" RequestVideoStreamBuffer fail, require size is too small\n");
        return -2;
        //goto parser_exit;
    }
    //loge("VdecH264 dbg:RequestVideoStreamBuffer ok\n");

    //-------------------------fill the NALU data----------------------------------
    if (packet_buf == NULL)
    {
        loge("packet_buf == NULL");
        return -3;
    }
    //printf("b4 bug[%d<%d]\n",inputLen,packet_buflen);usleep(10*1000);
    //printf("\t\t\t nal%d<%d[%d+%d]\n",inputLen,(packet_buflen+packet_ringBufLen), \
    //packet_buflen, packet_ringBufLen);

    if (inputLen <= packet_buflen)
    {
        //memcpy(packet_buf, inputBuf, inputLen);
        readInputBuf(packet_buf, inputLen);
    }
    else if (inputLen <= (packet_buflen + packet_ringBufLen))
    {
        //memcpy(packet_buf, inputBuf, packet_buflen);
        readInputBuf(packet_buf, packet_buflen);
        readInputBuf(packet_ringBuf, inputLen - packet_buflen);
    }
    else
    {
        loge("VideoStreamBuf is not enough:%u>%d[%d+%d]\n", inputLen, \
             (packet_buflen + packet_ringBufLen), \
             packet_buflen, packet_ringBufLen);
        return -3;
    }

    //printf("af bug\n");//usleep(10*1000);

    //-------------------------fill the NALU data end------------------------------

    memset(&dataInfo, 0, sizeof(VideoStreamDataInfo));
    dataInfo.pData          = packet_buf;
    dataInfo.nLength      = nRequestDataSize;
    dataInfo.nPts          = packet_pts;
    dataInfo.nPcr          = packet_pcr;
    dataInfo.bIsFirstPart = 1;
    dataInfo.bIsLastPart = 1;
    dataInfo.bValid = 1;
    nRet = SubmitVideoStreamData(pVideoDec, &dataInfo, 0);      //VdecH264:step4
    if (nRet != 0)
    {
        loge(" parser thread  SubmitVideoStreamData() error=%d \n",nRet);
        //goto parser_exit;
    }
    //loge("VdecH264 dbg:SubmitVideoStreamData ok\n");

    //-----------------decode begin-------------------------------------------------
    nRet = DecodeVideoStream(pVideoDec, 0 /*eos*/,
                             0/*key frame only*/, 0/*drop b frame*/,
                             0/*current time*/);                                 //VdecH264:step5
    //logd("VdecH264 dbg:DecodeVideoStream return %d\n", nRet);

    if (!(nRet == VDECODE_RESULT_KEYFRAME_DECODED ||
            nRet == VDECODE_RESULT_FRAME_DECODED ||
            nRet == VDECODE_RESULT_NO_BITSTREAM))
    {
        //usleep(1000);
        logw("DecodeVideoStream invalid! nRet:%d\n", nRet);
        return -4;
    }
    //-----------------decode end-------------------------------------------------

    //-----------------get the yuv pic begin--------------------------------------
    int nValidPicNum = ValidPictureNum(pVideoDec, 0);
    if (nValidPicNum < 0)
    {
        nRet = 0;
        logw("nValidPicNum<0,DecodeVideoStream ret:%d\n", nValidPicNum);
        return nRet;
    }
    else if (nValidPicNum > 1)
    {
        logw("ValidPictureNum:%d,may be loss frame.\n", nValidPicNum);
    }

    pPicture = RequestPicture(pVideoDec, 0/*the major stream*/); //VdecH264:step6
    if (pPicture != NULL)
    {
#ifdef DUMP_YUV_DATAS
       if (pPicture->nWidth * pPicture->nHeight > 0)
       {
           saveNV21Picture(pPicture);
       }
#endif /* BOGUS */
        logw("nColorPrimary:0x%x,phyYBufAddr:%p\n",pPicture->nColorPrimary,pPicture->phyYBufAddr);
        PicInfo  pSrc, pDst;
        pSrc.dataW = pPicture->nWidth;
        pSrc.dataH = pPicture->nHeight;
        pSrc.vildW = pPicture->nCurFrameInfo.nVidFrmDisW;
        pSrc.vildH = pPicture->nCurFrameInfo.nVidFrmDisH;
        pSrc.fmt = pPicture->ePixelFormat;
        pSrc.pAddr = (void*)pPicture->phyYBufAddr;
        pops = MemAdapterGetOpsS();
        pSrc.fd = CdcGetBufferFd((struct ScMemOpsS *)pops, (void *)pPicture->pData0);

#ifdef BOGUS
        int yuvSize = (pPicture->nWidth * pPicture->nHeight*3/2);
        IonFlushCache(pPicture->pData0,yuvSize);
        if(yuvSize > mG2dMem.size)
        {
            reallocDMA(yuvSize);
        }
        pDst.dataW = pPicture->nWidth;
        pDst.dataH = pPicture->nHeight;
        pDst.vildW = pPicture->nCurFrameInfo.nVidFrmDisW;
        pDst.vildH = pPicture->nCurFrameInfo.nVidFrmDisH;
        pDst.fmt = pPicture->ePixelFormat;
        pDst.pAddr = (int*)mG2dMem.phy;
        if((Angle_90 == mParam->rotation)||(Angle_270 == mParam->rotation))
        {//TO DO:maybe corp should reset alxis when Angle_270
            pDst.dataW = pPicture->nHeight;
            pDst.dataH = pPicture->nWidth ;
            pDst.vildW = pPicture->nCurFrameInfo.nVidFrmDisH;
            pDst.vildH = pPicture->nCurFrameInfo.nVidFrmDisW;
        }
        
    #ifdef FREAM_TEST
    static int SHWi=0;
    gettimeofday(&time, NULL);
    logd("[FREAM_TEST]SHW:%5u,[%10ld-%10ld],%p %8u\n",inputLen,time.tv_sec,time.tv_usec,inputBuf,inputLen);
    #endif
        
        g2dProcees(&pSrc,&pDst,mParam->rotation);
        flushCache(MEM_TYPE_DMA, &mG2dMem, NULL);
#endif /* BOGUS */
        
#ifdef DUMP_YUV_DATAS
        saveRotPicture(&pSrc);
#endif
        showPicture_DE(&pSrc);
        if(mParam->tvOut)
        {
            showPicture_TV(&pSrc);
        }
	    #ifdef FREAM_TEST
	    static int SHWi=0;
	    gettimeofday(&time, NULL);
	    logd("[FREAM_TEST]SHW:%5u,[%10ld-%10ld],%p %8d\n",inputLen,time.tv_sec,time.tv_usec,inputBuf,SHWi);
	    #endif
        
        if(paramUpdate)
        {
            paramUpdate = false;
        }
        ReturnPicture(pVideoDec, pPicture);                         //VdecH264:step7
    }
    else
    {
        logw("nValidPicNum == 0\n");
        return -6;

    }
    #ifdef FREAM_TEST
    static int ENDi=0;
    gettimeofday(&time, NULL);
    logd("[FREAM_TEST]END:%5u,[%10ld-%10ld],%p %8d\n",inputLen,time.tv_sec,time.tv_usec,inputBuf,ENDi);
    #endif
    return nRet;
}

void AWStreamPlayerImpl::reallocDMA(int size)
{
    int ret;
    
    allocFree(MEM_TYPE_DMA, &mG2dMem, (void*)NULL);
    mG2dMem.size = size; //default use the display size.
    ret = allocAlloc(MEM_TYPE_DMA, &mG2dMem, NULL);
    if (ret < 0)
    {
        loge("allocAlloc failed\n");
        return;
    }
}
int AWStreamPlayerImpl::g2dProcees(PicInfo* pSrc,PicInfo* pDst,int rotation)
{
    int ret ; 
    
    if(-1 == mG2dFd)
    {
        mG2dFd = g2dInit();
    }
    
    if(mParam->rotation != 0)
    {
        g2dRotateAngle rotate = (g2dRotateAngle)(rotation -1);
    	ret = g2dRotate(mG2dFd,rotate,(unsigned char*)pSrc->pAddr, pSrc->dataW, pSrc->dataH, 
                    (unsigned char*)pDst->pAddr, pDst->dataW, pDst->dataH);            
    }
    else
    {       
        ret = g2dScale(mG2dFd,(unsigned char*)pSrc->pAddr, pSrc->dataW, pSrc->dataH, 
                    (unsigned char*)pDst->pAddr, pDst->dataW, pDst->dataH);
    }
    //logd("g2dProcees[%dx%d]->Rot=%d->[%dx%d] \n",pSrc->dataW, pSrc->dataH,rotation,pDst->dataW, pDst->dataH);
    //saveRotPicture(&mG2dMem,pPicture);

    return ret;
}
void AWStreamPlayerImpl::hideDisplay(bool hide)
{
    int ret;
    if(hideImage == hide)
    {
        return;
    }

    hideImage = hide;
    int t_Ysize = mParam->dispW*mParam->dispH;
    int size = t_Ysize * 3 / 2;
    if(size>mG2dMem.size)
    {
        reallocDMA(size);
    }
    memset((char*)mG2dMem.vir, 0x00, t_Ysize);   //make it black
    memset((char*)mG2dMem.vir + t_Ysize, 0x80, t_Ysize >> 1);
    
	flushCache(MEM_TYPE_DMA, &mG2dMem, NULL);
    
    {
        struct view_info screen = {mParam->dispX, mParam->dispY, mParam->dispW, mParam->dispH};
        video_layer0 = gVdecDisp->aut_hwd_layer_request(&screen,SCR_ID_DEFAULT, mParam->chLID, mParam->lyrID);
        CHECK_DISP_RETURN(video_layer0, "aut_hwd_layer_request");

        struct src_info src;
        struct view_info crop;
        {
            src = { mParam->dispW, mParam->dispH,DISP_PIXEL_FORMAT_DEFAULT};
            ret = gVdecDisp->aut_hwd_layer_set_src(video_layer0, &src, (unsigned long)&mG2dMem.vir);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
            
            crop = {0, 0, mParam->dispW, mParam->dispH};

            ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer0, &crop);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");
        }
        
        logd("src: [%d:%d]fmt:%x\n",src.w,src.h,src.format);
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);

        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer0, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer0, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

        ret = gVdecDisp->aut_hwd_layer_open(video_layer0);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");
        ret = gVdecDisp->aut_hwd_layer_render(video_layer0, (void*)&mG2dMem.vir, 0); 
    }
    
    if(mParam->tvOut)
    {
        int mode = DISP_TV_MOD_NTSC;
        if(PAL == mParam->tvOut)
        {
            mode = DISP_TV_MOD_PAL;
        }
        struct view_info screen = {mParam->tvDispX, mParam->tvDispY, mParam->tvDispW, mParam->tvDispH};
        video_layer1 = gVdecDisp->aut_hwd_layer_request(&screen, SCR_ID_CVBS, mParam->chLID, mParam->lyrID);
        CHECK_DISP_RETURN(video_layer1, "aut_hwd_layer_request");

        struct src_info src;
        struct view_info crop;

        src = {mParam->tvDispW, mParam->tvDispH, DISP_PIXEL_FORMAT_DEFAULT};
        ret = gVdecDisp->aut_hwd_layer_set_src(video_layer1, &src, (unsigned long)&mG2dMem.vir);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src #########################");
        
        crop = {0, 0, mParam->dispW, mParam->dispH};
        ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer1, &crop);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");

        logd("src: [%d:%d]fmt:%x\n",src.w,src.h,src.format);
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);
        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer1, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer1, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

	    ret = gVdecDisp->hwd_other_screen(SCR_ID_CVBS,DISP_OUTPUT_TYPE_TV,mode);
        CHECK_DISP_RETURN(ret, "hwd_other_screen");
        ret = gVdecDisp->aut_hwd_layer_open(video_layer1);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");
       
        ret = gVdecDisp->aut_hwd_layer_render(video_layer1, (void*)&mG2dMem.vir, 0);
    }
    
}

void AWStreamPlayerImpl::showPicture_DE(PicInfo* pic)
{
    int ret = 0;
    unsigned int src_w = pic->dataW;
    unsigned int src_h = pic->dataH;
    unsigned long addr = (unsigned long)pic->pAddr;
    unsigned int fd = pic->fd;
    struct src_info src;
    src = {src_w, src_h, DISP_PIXEL_FORMAT_DEFAULT};
    
    if( (video_layer0 == -1)||(paramUpdate == 1))
    {
        //struct view_info screen = {mParam->dispX, mParam->dispY, ALIGN(mParam->dispW,32), ALIGN(mParam->dispH,32)};
        struct view_info screen = {mParam->dispX, mParam->dispY, mParam->dispW,mParam->dispH};
        video_layer0 = gVdecDisp->aut_hwd_layer_request(&screen,SCR_ID_DEFAULT, mParam->chLID, mParam->lyrID);
        CHECK_DISP_RETURN(video_layer0, "aut_hwd_layer_request");

        struct view_info crop;
        //if(mParam->rotation == 0)
        {
            ret = gVdecDisp->aut_hwd_layer_set_src(video_layer0, &src, 0, fd);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
            
            if((mParam->cropW==0)||(mParam->cropH==0))
            {
                crop = {0, 0, (unsigned int)pic->vildW, (unsigned int)pic->vildH};
            }
            else
            {
                crop = {mParam->cropX,mParam->cropY,mParam->cropW,mParam->cropH};
            }

            ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer0, &crop);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");
        }
       
        logd("src: [%d:%d]fmt:%x\n",src.w,src.h,src.format);
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);

        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer0, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer0, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

        ret = gVdecDisp->aut_hwd_layer_open(video_layer0);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");
    }

    ret = gVdecDisp->aut_hwd_layer_set_src(video_layer0, &src, (unsigned long)&addr,-1);   
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
}
void AWStreamPlayerImpl::showPicture_TV(PicInfo* pic)
{
    unsigned int src_w = pic->dataW;
    unsigned int src_h = pic->dataH;
    unsigned long addr = (unsigned long)pic->pAddr;
    struct src_info src;
    src = { src_w, src_h, DISP_PIXEL_FORMAT_DEFAULT};
    //request ->setsrc->setrect(maybe)->open->render(maybe if disp addr every change)->close->releases
    int ret = 0;
    if ( (video_layer1 == -1)||(paramUpdate == 1))
    { 
        int mode = DISP_TV_MOD_NTSC;
        if(PAL == mParam->tvOut)
        {
            mode = DISP_TV_MOD_PAL;
        }
        struct view_info screen = {mParam->tvDispX, mParam->tvDispY, mParam->tvDispW, mParam->tvDispH};
        video_layer1 = gVdecDisp->aut_hwd_layer_request(&screen, SCR_ID_CVBS, mParam->chLID, mParam->lyrID);
        CHECK_DISP_RETURN(video_layer1, "aut_hwd_layer_request");

        struct view_info crop;
        //if(mParam->rotation == 0)
        {
            ret = gVdecDisp->aut_hwd_layer_set_src(video_layer1, &src, (unsigned long)&addr);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src #########################");
            
            if((mParam->cropW==0)||(mParam->cropH==0))
            {
                crop = {0, 0, (unsigned int)pic->vildW, (unsigned int)pic->vildH};
            }
            else
            {
                crop = {mParam->cropX,mParam->cropY,mParam->cropW,mParam->cropH};
            }
            ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer1, &crop);
            CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");
        }

        logd("src: [%d:%d]fmt:%x\n",src.w,src.h,src.format);
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);
        
        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer1, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer1, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

	    ret = gVdecDisp->hwd_other_screen(SCR_ID_CVBS,DISP_OUTPUT_TYPE_TV,mode);
        CHECK_DISP_RETURN(ret, "hwd_other_screen");
        ret = gVdecDisp->aut_hwd_layer_open(video_layer1);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");
       
    }
    ret = gVdecDisp->aut_hwd_layer_set_src(video_layer1, &src, (unsigned long)&addr);
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
}

void AWStreamPlayerImpl::hidePicture_DE()
{
    int ret = 0;
    //request ->setsrc->setrect(maybe)->open->render(maybe if disp addr every change)->close->releases
    if (gVdecDisp == NULL)
    {
        loge("gVdecDisp is NULL\n");
        return ;
    }

    if(video_layer0 != -1)
    {
        ret = gVdecDisp->aut_hwd_layer_close(video_layer0);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_close");
        ret = gVdecDisp->aut_hwd_layer_release(video_layer0);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_release");
        video_layer0 = -1;
        usleep(50 * 1000);
    }
}

void AWStreamPlayerImpl::hidePicture_TV()
{
    int ret = 0;
    //request ->setsrc->setrect(maybe)->open->render(maybe if disp addr every change)->close->releases
    if (gVdecDisp == NULL)
    {
        loge("gVdecDisp is NULL\n");
        return ;
    }

    if(video_layer1 != -1)
    {
        ret = gVdecDisp->aut_hwd_layer_close(video_layer1);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_close");

        ret = gVdecDisp->aut_hwd_layer_release(video_layer1);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_release");

        video_layer1 = -1;
        usleep(50 * 1000);
    }
}

}

