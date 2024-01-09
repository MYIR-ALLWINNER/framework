
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

#include "AWVideoDecoder.h"
#include "sunxiMemInterface.h"

/*-------------------------------------------------------------------------
                                define
-------------------------------------------------------------------------*/

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
         if(a!=0){\
           DEBUG(HL_RED "[E]" "[%s] fail! line:%d ret:%d \n" PF_CLR, __FUNCTION__, __LINE__,a);\
           return a; \
           }\
    } while (0)

typedef unsigned char     uint8;
typedef char              int8;


namespace awvideodecoder
{

static const int VE_FREQ = 300 * 1000 * 1000;
static const int NAL_DEF_SIZE = 200 * 1000;

static const int DISP_X_DEFAULT = 0;
static const int DISP_Y_DEFAULT = 0;
static const int DISP_W_DEFAULT = 1024;
static const int DISP_H_DEFAULT = 600;

static const int SCR_ID_DEFAULT = 0;
static const int CHL_ID_DEFAULT = 0;
static const int LYR_ID_DEFAULT = 0;
static const int ZORDER_DEFAULT = 2;

static const int DISP_F_DEFAULT = 0x4d;//DISP_FORMAT_YUV420_SP_VUVU;
static const int VIDEO_QUEUE_WARN_HOLD = 30 * 1;

class AWVideoDecoderImpl: public AWVideoDecoder
{
public:
    AWVideoDecoderImpl(DecodeParam* param);
    AWVideoDecoderImpl();
    ~AWVideoDecoderImpl();

    virtual int init(DecodeParam* param, AWVideoDecoderDataCallback* cbk);
    virtual int decode(const void* inputBuf, unsigned int inputLen,
                       void* outputBuf, unsigned int outputLen);
    virtual int decodeAsync(const void* inputBuf, unsigned int inputLen);
    virtual int requestPicture(AVPacket* picBuf);
    virtual int releasePicture(AVPacket* picBuf);
    virtual int decode(const AVPacket* inPacket) ;
    int stopAndGetLeftFream(void* outputBuf, unsigned int outputLen);

private:
    void finish();

    int writeOutputBuf(void* buf, int len);
    int readInputBuf(void* buf, int len);
    int writeCallback(void* buf, int len, void* buf1 = NULL, int len1 = 0);

    void saveNV21Picture(VideoPicture* pPicture, char* file);
    int getFrameBitSize(int w, int h, PixelFmt fmt);

    VConfig             mVideoConf;
    VideoStreamInfo     mStreamInfo;

    const void* mOutputBuf;
    int mOutputBufLen ;
    int mOutputBufPos;
    const void* mInputBuf;
    int mInputBufLen ;
    int mInputBufPos ;

    //struct ScMemOpsS*   memops;
	paramStruct_t mSetparmMemops;
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
    DecodeParam* mParam;
    AWVideoDecoderDataCallback* mDataCbk = NULL;

};

/*-------------------------------------------------------------------------
                                AWVideoDecoder
-------------------------------------------------------------------------*/
AWVideoDecoder* AWVideoDecoder::create(DecodeParam* param)
{
    AWVideoDecoder* pDecoder = (AWVideoDecoder*) new AWVideoDecoderImpl(param);
    return pDecoder;
}

AWVideoDecoder* AWVideoDecoder::create()
{
    AWVideoDecoder* pDecoder = (AWVideoDecoder*) new AWVideoDecoderImpl();
    return pDecoder;
}

void AWVideoDecoder::destroy(AWVideoDecoder* decoder)
{
    delete decoder;
}

/*-------------------------------------------------------------------------
                                AWVideoDecoderImpl
-------------------------------------------------------------------------*/

int AWVideoDecoderImpl::getFrameBitSize(int w, int h, PixelFmt fmt)
{
    int pixelNum = w * h;
    //logd("pic size:[%dx%d]\n",w,h);
    int frameBitSize = 0;
    switch (fmt)
    {
    case PIXEL_DEFAULT:
    case PIXEL_YUV_PLANER_420:
    case PIXEL_YUV_MB32_420:
    case PIXEL_YV12...PIXEL_NV12:
        frameBitSize = pixelNum * 3 / 2;
        break;

    case PIXEL_YUV_PLANER_422:
    case PIXEL_YUV_MB32_422:
    case PIXEL_PLANARUV_422:
    case PIXEL_PLANARVU_422:
    case PIXEL_YUYV...PIXEL_VYUY:
        frameBitSize = pixelNum * 2;
        break;

    case PIXEL_YUV_PLANER_444:
    case PIXEL_YUV_MB32_444:
    case PIXEL_PLANARUV_444:
    case PIXEL_PLANARVU_444:
        frameBitSize = pixelNum * 3;
        break;

    case PIXEL_ARGB...PIXEL_BGRA:
        frameBitSize = pixelNum * 4;
        break;
    }
    return frameBitSize;
}

AWVideoDecoderImpl::AWVideoDecoderImpl()
{
    printf("new AWVideoDecoderImpl() version:%s\n", MODULE_VERSION);
    mOutputBuf = NULL;
    mOutputBufLen = 0;
    mOutputBufPos = 0;
    mInputBuf = NULL;
    mInputBufLen = 0;
    mInputBufPos = 0;
    pVideoDec = NULL;
    pPicture = NULL;
    nValidSize = 0;
    nRequestDataSize = 0;
    packet_buf = NULL;
    packet_buflen = 0;
    packet_ringBuf = NULL;
    packet_ringBufLen = 0;
    mParam = NULL;
}

int AWVideoDecoderImpl::init(DecodeParam* param, AWVideoDecoderDataCallback* cbk)
{
    int ret = 0;
    pVideoDec = NULL;
    pPicture = NULL;

    memset((void*)&mVideoConf, 0, sizeof(VConfig));
    memset((void*)&mStreamInfo, 0, sizeof(VideoStreamInfo));

	memset(&mSetparmMemops, 0, sizeof(paramStruct_t));

	ret = allocOpen(MEM_TYPE_CDX_NEW, &mSetparmMemops, NULL);
	if (ret < 0) {
		loge("setparm:allocOpen failed");
	}
    mVideoConf.memops = (struct ScMemOpsS*)mSetparmMemops.ops;
    //memops = MemAdapterGetOpsS();
    if (mVideoConf.memops == NULL)
    {
        printf("memops is NULL\n");
        return -1;
    }
    //CdcMemOpen(memops);

    mStreamInfo.eCodecFormat = param->codecType;

    mVideoConf.eOutputPixelFormat  = param->pixelFormat;
    //mVideoConf.memops = memops;
    mVideoConf.nDisplayHoldingFrameBufferNum = 1;
    mVideoConf.nDecodeSmoothFrameBufferNum = 3;
    mVideoConf.nVeFreq = 300 * 1000 * 1000;   //300MH
    //mVideoConf.bIsFullFramePerPiece = 1;

    if (0 != param->scaleRatio)
    {
        mVideoConf.bScaleDownEn = 1;
        mVideoConf.nHorizonScaleDownRatio = param->scaleRatio;
        mVideoConf.nVerticalScaleDownRatio = param->scaleRatio;
    }
    if (0 != param->rotation)
    {
        mVideoConf.bRotationEn = 1;
        mVideoConf.nRotateDegree = param->rotation;
    }
    mParam = param;

    pVideoDec = CreateVideoDecoder();                                   //VdecH264:step1
    if (pVideoDec == NULL)
    {
        loge(" decoder demom CreareateVideoDecoder() error \n");
        return -3;
    }

    ret = InitializeVideoDecoder(pVideoDec, &mStreamInfo, &mVideoConf); //VdecH264:step2

    if (ret != 0)
    {
        loge("decoder demom initialize video decoder fail.");
        DestroyVideoDecoder(pVideoDec);
        pVideoDec = NULL;
        return -4;
    }

    mDataCbk = cbk;
}

AWVideoDecoderImpl::AWVideoDecoderImpl(DecodeParam* param)
{
    init(param, NULL);
}

AWVideoDecoderImpl::~AWVideoDecoderImpl()
{
    printf("~ AWVideoDecoderImpl()\n");
    finish();
}

void AWVideoDecoderImpl::finish()
{
    if (NULL != pVideoDec)
    {
        DestroyVideoDecoder(pVideoDec);
        pVideoDec = NULL;
    }
    if (mVideoConf.memops != NULL)
    {
        //CdcMemClose(baseConfig.memops);
        allocClose(MEM_TYPE_CDX_NEW,&mSetparmMemops, NULL);
        mVideoConf.memops = NULL;
    }
}

int AWVideoDecoderImpl::writeOutputBuf(void* buf, int len)
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

int AWVideoDecoderImpl::readInputBuf(void* buf, int len)
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

void AWVideoDecoderImpl::saveNV21Picture(VideoPicture* pPicture, char* file)
{
    int nSizeY, nSizeUV;
    static FILE* fp = fopen(file, "ab");

    if (pPicture == NULL)
    {
        loge(" demo decoder save nv21 picture error, picture pointer equals NULL\n");
        return;
    }

    if (fp == NULL)
    {
        loge(" demo decoder save picture error, open file fail \n");
        return;
    }

    nSizeY = pPicture->nWidth * pPicture->nHeight ;
    nSizeUV = nSizeY >> 1;
    //logd(" save picture to file: %s, size: %dx%d, top: %d, bottom: %d, left: %d, right: %d",
    //        file, pPicture->nWidth, pPicture->nHeight,pPicture->nTopOffset,
    //        pPicture->nBottomOffset, pPicture->nLeftOffset, pPicture->nRightOffset);

    fwrite(pPicture->pData0, 1, nSizeY, fp);
    fwrite(pPicture->pData1, 1, nSizeUV, fp);

    fclose(fp);

}

int AWVideoDecoderImpl::decodeAsync(const void* inputBuf, unsigned int inputLen)
{
    mInputBuf = inputBuf;
    mInputBufLen = inputLen;
    mInputBufPos = 0;

    if ((NULL == inputBuf) )
    {
        loge("buffer is NULL!\n");
        return -1;
    }

    //logw("inputLen = %d,%02x %02x %02x %02x %02x,%02x %02x %02x",inputLen,
    //              data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
    //-----------------------dcoder-------------------

    int nRet;
    nRequestDataSize = inputLen;
    nValidSize = VideoStreamBufferSize(pVideoDec, 0) - VideoStreamDataSize(pVideoDec, 0);
    if (nRequestDataSize > nValidSize)
    {
        logw("nRequestDataSize > nValidSize\n");
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
        logw(" RequestVideoStreamBuffer fail. request size: %d, valid size: %d ",
             nRequestDataSize, nValidSize);
        return -2;
    }

    if (packet_buflen + packet_ringBufLen < nRequestDataSize)
    {
        logw(" RequestVideoStreamBuffer fail, require size is too small\n");
        //goto parser_exit;
    }
    //loge("VdecH264 dbg:RequestVideoStreamBuffer ok\n");

    //-------------------------fill the NALU data----------------------------------
    if (packet_buf == NULL)
    {
        logw("packet_buf == NULL");
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
    nRet = SubmitVideoStreamData(pVideoDec, &dataInfo, 0);      //VdecH264:step4
    if (nRet != 0)
    {
        loge(" parser thread  SubmitVideoStreamData() error \n");
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
        logw("DecodeVideoStream invalid! nRet:%d\n", nRet);
        return -4;
    }
    //-----------------decode end-------------------------------------------------

    //-----------------get the yuv pic begin--------------------------------------
    nRet = ValidPictureNum(pVideoDec, 0);
    return nRet;
}

int AWVideoDecoderImpl::requestPicture(AVPacket* picBuf)
{
    int ret = -1;
    VideoPicture* pic = RequestPicture(pVideoDec, 0/*the major stream*/); //VdecH264:step6
    if (pic != NULL)
    {
        int bitSize = getFrameBitSize(pic->nWidth, pic->nHeight,
                                      (PixelFmt)mVideoConf.eOutputPixelFormat);
        picBuf->pAddrPhy0 = (unsigned char*)pic->phyYBufAddr;
        picBuf->pAddrPhy1 = (unsigned char*)pic->phyCBufAddr;
        picBuf->pAddrVir0 = (unsigned char*)pic->pData0;
        picBuf->pAddrVir1 = (unsigned char*)pic->pData1;
        picBuf->dataLen0 = bitSize;
        picBuf->handler = (unsigned char*)pic;
        ret = 0;
        logd("%s %p\n",__FUNCTION__,picBuf->handler);
    }
    return ret;
}
int AWVideoDecoderImpl::releasePicture(AVPacket* picBuf)
{
    int ret = 0;
    ret = ReturnPicture(pVideoDec, (VideoPicture*)picBuf->handler);                         //VdecH264:step7
    logd("%s %p,ret:%d\n",__FUNCTION__,picBuf->handler,ret);
    return ret;
}

int AWVideoDecoderImpl::decode(const void* inputBuf, unsigned int inputLen,
                               void* outputBuf, unsigned int outputLen)
{
    mInputBuf = inputBuf;
    mInputBufLen = inputLen;
    mInputBufPos = 0;

    mOutputBuf = outputBuf;
    mOutputBufLen = outputLen;
    mOutputBufPos = 0;

    if ((NULL == inputBuf) || (NULL == outputBuf))
    {
        loge("buffer is NULL!\n");
        return -1;
    }

    //logw("inputLen = %d,%02x %02x %02x %02x %02x,%02x %02x %02x",inputLen,
    //              data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
    //-----------------------dcoder-------------------
    //printf("\t\t\t YGC Get inputLen:%d\n", inputLen);

    int nRet;
    nRequestDataSize = inputLen;
    nValidSize = VideoStreamBufferSize(pVideoDec, 0) - VideoStreamDataSize(pVideoDec, 0);
    if (nRequestDataSize > nValidSize)
    {
        loge("nRequestDataSize > nValidSize\n");
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
        loge(" RequestVideoStreamBuffer fail. request size: %d, valid size: %d ",
             nRequestDataSize, nValidSize);
        return -2;
    }

    if (packet_buflen + packet_ringBufLen < nRequestDataSize)
    {
        logw(" RequestVideoStreamBuffer fail, require size is too small\n");
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
    }

    memset(&dataInfo, 0, sizeof(VideoStreamDataInfo));
    dataInfo.pData          = packet_buf;
    dataInfo.nLength      = nRequestDataSize;
    dataInfo.nPts          = packet_pts;
    dataInfo.nPcr          = packet_pcr;
    dataInfo.bIsFirstPart = 1;
    dataInfo.bIsLastPart = 1;
    nRet = SubmitVideoStreamData(pVideoDec, &dataInfo, 0);      //VdecH264:step4
    if (nRet != 0)
    {
        loge(" parser thread  SubmitVideoStreamData() error \n");
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
        loge("nValidPicNum<0,DecodeVideoStream ret:%d\n", nValidPicNum);
        return nRet;
    }
    else if (nValidPicNum > 1)
    {
        logw("ValidPictureNum:%d,may be loss frame.\n", nValidPicNum);
    }

    pPicture = RequestPicture(pVideoDec, 0/*the major stream*/); //VdecH264:step6
    if (pPicture != NULL)
    {
#ifdef BOGUS
        if (pPicture->nWidth * pPicture->nHeight > 0)
        {
            char path[60];
            struct timeval time;
            gettimeofday(&time, NULL);
            static int a = 1;
            sprintf(path, "/tmp/output/[%dx%d]nv21.yuv",
                    pPicture->nWidth, pPicture->nHeight);
            saveNV21Picture(pPicture, path);
        }
#endif /* BOGUS */
        mParam->dstW = pPicture->nWidth;
        mParam->dstH = pPicture->nHeight;
        int bitSize = getFrameBitSize(pPicture->nWidth, pPicture->nHeight,
                                      (PixelFmt)mVideoConf.eOutputPixelFormat);

        if (outputLen < bitSize)
        {
            logw("output buffer is not enough current:%u,need:%d!\n", outputLen, bitSize);
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            return bitSize;
        }

        nRet = writeOutputBuf(pPicture->pData0, pPicture->nWidth * pPicture->nHeight);
        if (nRet != 0)
        {
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            CHECK_RETURN(nRet);
        }

        nRet = writeOutputBuf(pPicture->pData1, pPicture->nWidth * pPicture->nHeight / 2);
        if (nRet != 0)
        {
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            CHECK_RETURN(nRet);
        }

        nRet =  mOutputBufPos;
        ReturnPicture(pVideoDec, pPicture);                         //VdecH264:step7
    }
    else
    {
        logd("pPicture == NULL\n");
        return -6;

    }
    return nRet;
}

int AWVideoDecoderImpl::decode(const AVPacket* inPacket)
{
    //logw("inputLen = %d,%02x %02x %02x %02x %02x,%02x %02x %02x",inputLen,
    //              data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
    //-----------------------dcoder-------------------
    //printf("\t\t\t YGC Get inputLen:%d\n", inputLen);

    int nRet;
    nRequestDataSize = inPacket->dataLen0;
    nValidSize = VideoStreamBufferSize(pVideoDec, 0) - VideoStreamDataSize(pVideoDec, 0);
    if (nRequestDataSize > nValidSize)
    {
        loge("nRequestDataSize > nValidSize\n");
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
        logw(" RequestVideoStreamBuffer fail. request size: %d, valid size: %d ",
             nRequestDataSize, nValidSize);
        return -2;
    }

    if (packet_buflen + packet_ringBufLen < nRequestDataSize)
    {
        logw(" RequestVideoStreamBuffer fail, require size is too small\n");
        //goto parser_exit;
    }
    //loge("VdecH264 dbg:RequestVideoStreamBuffer ok\n");

    //-------------------------fill the NALU data----------------------------------
    if (packet_buf == NULL)
    {
        logw("packet_buf == NULL");
        return -3;
    }
    //printf("b4 bug[%d<%d]\n",inputLen,packet_buflen);usleep(10*1000);
    //printf("\t\t\t nal%d<%d[%d+%d]\n",inputLen,(packet_buflen+packet_ringBufLen), \
    //packet_buflen, packet_ringBufLen);

    if (inPacket->dataLen0 <= packet_buflen)
    {
        memcpy(packet_buf, inPacket->pAddrVir0, inPacket->dataLen0);
        //readInputBuf(packet_buf, inPacket->dataLen0);
    }
    else if ((NULL != packet_ringBuf) && (inPacket->dataLen0 <= (packet_buflen + packet_ringBufLen)))
    {
        memcpy(packet_buf, inPacket->pAddrVir0, packet_buflen);
        memcpy(packet_ringBuf, inPacket->pAddrVir0 + packet_buflen, inPacket->dataLen0 - packet_buflen);
        //readInputBuf(packet_buf, packet_buflen);
        //readInputBuf(packet_ringBuf, inPacket->dataLen0 - packet_buflen);
    }
    else
    {
        loge("VideoStreamBuf is not enough:%d>%d[%d+%d]\n", inPacket->dataLen0, \
             (packet_buflen + packet_ringBufLen), \
             packet_buflen, packet_ringBufLen);
    }

    //printf("af bug\n");//usleep(10*1000);

    //-------------------------fill the NALU data end------------------------------

    memset(&dataInfo, 0, sizeof(VideoStreamDataInfo));
    dataInfo.nID          = inPacket->id;
    dataInfo.nPts          = inPacket->pts;
    dataInfo.pData          = packet_buf;
    dataInfo.nLength      = nRequestDataSize;
    dataInfo.nPcr          = packet_pcr;
    dataInfo.bIsFirstPart = 1;
    dataInfo.bIsLastPart = 1;

    nRet = SubmitVideoStreamData(pVideoDec, &dataInfo, 0);      //VdecH264:step4
    if (nRet != 0)
    {
        logw(" parser thread  SubmitVideoStreamData() error \n");
        //goto parser_exit;
    }

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
        loge("nValidPicNum<0,DecodeVideoStream ret:%d\n", nValidPicNum);
        return nRet;
    }
    else if (nValidPicNum > 1)
    {
        logw("ValidPictureNum:%d,may be loss frame nal:%d.\n", nValidPicNum,inPacket->dataLen0);
    }
    else if (nValidPicNum == 0)
    {
        logw("ValidPictureNum:%d,may be no frame nal:%d.\n", nValidPicNum,inPacket->dataLen0);
    }

    pPicture = RequestPicture(pVideoDec, 0/*the major stream*/); //VdecH264:step6
    if (pPicture != NULL)
    {
        mParam->dstW = pPicture->nWidth;
        mParam->dstH = pPicture->nHeight;
        int bitSize = getFrameBitSize(pPicture->nWidth, pPicture->nHeight,
                                      (PixelFmt)mVideoConf.eOutputPixelFormat);

        AVPacket outPacket;
        outPacket.id = pPicture->nID;
        outPacket.pts = pPicture->nPts;

        outPacket.pAddrPhy0 = (unsigned char*)pPicture->phyYBufAddr;
        outPacket.pAddrVir0 = (unsigned char*)pPicture->pData0;
        outPacket.dataLen0 = pPicture->nWidth * pPicture->nHeight;

        outPacket.pAddrPhy1 = (unsigned char*)pPicture->phyCBufAddr;
        outPacket.pAddrVir1 = (unsigned char*)pPicture->pData1;
        outPacket.dataLen1 = outPacket.dataLen0 / 2;

        if (NULL != mDataCbk)
        {
            mDataCbk->decoderDataReady(&outPacket);
        }

        ReturnPicture(pVideoDec, pPicture);                         //VdecH264:step7
    }
    else
    {
        logw("pPicture == NULL,nal:%d\n",inPacket->dataLen0);
        return -6;

    }
    return nRet;
}

int AWVideoDecoderImpl::stopAndGetLeftFream(void* outputBuf, unsigned int outputLen)
{
    int nRet;
    mOutputBuf = outputBuf;
    mOutputBufLen = outputLen;
    mOutputBufPos = 0;

    if ( (NULL == outputBuf))
    {
        loge("buffer is NULL!\n");
        return -1;
    }

    int leftFream = VideoStreamFrameNum(pVideoDec, 0);
    logd("VideoStreamFrameNum:%d\n", leftFream);
    if (leftFream > 0)
    {
        int waitLoop = 0;
        while (leftFream > 0)
        {
            nRet = DecodeVideoStream(pVideoDec,
                                     1 /*eos*/,
                                     0/*key frame only*/,
                                     0/*drop b frame*/,
                                     0/*current time*/);
            logd("DecodeVideoStream:%d\n", nRet);
            if ((nRet == VDECODE_RESULT_NO_FRAME_BUFFER) ||
                    (nRet == VDECODE_RESULT_NO_BITSTREAM))
            {
                break;
            }

            usleep(10 * 1000);
            waitLoop++;
            if (waitLoop > 50)
            {
                logw("decode eos time out > 10 ms!\n");
                break;
            }
        }
    }
    else
    {
        logd("There is no left fream to decode!\n");
    }

    int nValidPicNum = ValidPictureNum(pVideoDec, 0);
    if (nValidPicNum < 0)
    {
        nRet = -2;
        logw("nValidPicNum:%d, no pic left.\n", nValidPicNum);
        return nRet;
    }

    pPicture = RequestPicture(pVideoDec, 0/*the major stream*/); //VdecH264:step6
    if (pPicture != NULL)
    {
        logd("RequestPicture.\n");
        mParam->dstW = pPicture->nWidth;
        mParam->dstH = pPicture->nHeight;
        int bitSize = getFrameBitSize(pPicture->nWidth, pPicture->nHeight,
                                      (PixelFmt)mVideoConf.eOutputPixelFormat);

        if (outputLen < bitSize)
        {
            loge("output buffer is not enough current:%u,need:%d!\n", outputLen, bitSize);
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            return bitSize;
        }

        nRet = writeOutputBuf(pPicture->pData0, pPicture->nWidth * pPicture->nHeight);
        if (nRet != 0)
        {
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            CHECK_RETURN(nRet);
        }

        nRet = writeOutputBuf(pPicture->pData1, pPicture->nWidth * pPicture->nHeight / 2);
        if (nRet != 0)
        {
            ReturnPicture(pVideoDec, pPicture);                     //VdecH264:step7
            CHECK_RETURN(nRet);
        }

        nRet =  mOutputBufPos;
        ReturnPicture(pVideoDec, pPicture);                         //VdecH264:step7
    }
    else
    {
        logw("pPicture == NULL.\n");
        return -2;

    }
    return nRet;
}
}

