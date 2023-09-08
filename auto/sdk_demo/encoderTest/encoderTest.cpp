
#include "AWVideoEncoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "sunxiMemInterface.h"
#include <atomic>

#define ALIGN(x,a) (((x) + (a-1)) & ~(a-1))

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
#define ALIGN(x,a) (((x) + (a-1)) & ~(a-1))

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

static const int log_level = LOG_LEVEL_ALL;

#define logv(format, ...) \
    do { \
         if(log_level>=LOG_LEVEL_FATAL)\
           DEBUG(HL_TWK_RED_YEL "[F]" PF_CLR"[%s]%s line:%d"format,__FILE__,__FUNCTION__, __LINE__,##__VA_ARGS__);\
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

#define CHECK_DISP_RETURN(a,b) \
    do { \
         if(a<0){\
           DEBUG(HL_RED "[E]" "[%s]%s fail! line:%d " PF_CLR, __FUNCTION__,b, __LINE__);\
           return; \
           }\
    } while (0)


using namespace awvideoencoder;
using namespace std;
atomic<int> mJpgIndex;

const char* codecExt[5] =
{
    ".264",
    ".jpg",
    ".ver2",
    ".265",
    ".vp8",
};

typedef struct TestParm_
{
    char intputFile[256];
    char outputFile[256];
    int  testWay;
    int  testTimes;
} TestParm;

struct ThreadParm
{
    FILE* inFile;
    FILE* outFile;
    EncodeParam* param;
};

typedef enum
{
    INPUT,
    HELP,
    ENCODE_FRAME_NUM,
    ENCODE_FORMAT,
    PIXEL_FORMAT,
    OUTPUT,
    SRC_W,
    SRC_H,
    BIT_RATE,
    TEST_WAY,
    TEST_TIMES,
    INVALID
} ArguType;

typedef struct
{
    char option[8];
    char type[128];
    ArguType argument;
    char description[512];
} Argument;

static const Argument ArguTypeMapping[] =
{
    {
        "-h",  "--help",    HELP,
        "Print this help"
    },
    {
        "-i",  "--input",   INPUT,
        "Input file path"
    },
    {
        "-n",  "--frameCount",   ENCODE_FRAME_NUM,
        "After encoder n frames, encoder stop"
    },
    {
        "-f",  "--codecType",  ENCODE_FORMAT,
        "0:h264 encoder, 1:jpeg_encoder, 3:h265 encoder"
    },
    {
        "-p",  "--pixelFormat",  PIXEL_FORMAT,
        "0: YUV420SP, 1:YVU420SP, 3:YUV420P"
    },
    {
        "-o",  "--output",  OUTPUT,
        "output file path"
    },
    {
        "-sw",  "--srcw",  SRC_W,
        "SRC_W"
    },
    {
        "-sh",  "--srch",  SRC_H,
        "SRC_H"
    },
    {
        "-b",  "--bitrate",  BIT_RATE,
        "bitRate:kbps"
    },
    {
        "-w",  "--test way",  TEST_WAY,
        "(0:single test, 1:multiDecoderTest)"
    },
    {
        "-t",  "--test times",  TEST_TIMES,
        " testTimes"
    },
};

EncodeParam    encodeParam;
TestParm    testParam;

static ArguType GetArguType(char* name)
{
    int i = 0;
    int num = sizeof(ArguTypeMapping) / sizeof(Argument);
    while (i < num)
    {
        if ((0 == strcmp(ArguTypeMapping[i].type, name)) ||
                ((0 == strcmp(ArguTypeMapping[i].option, name)) &&
                 (0 != strcmp(ArguTypeMapping[i].option, "--"))))
        {
            return ArguTypeMapping[i].argument;
        }
        i++;
    }
    return INVALID;
}

static void PrintDemoUsage(void)
{
    int i = 0;
    int num = sizeof(ArguTypeMapping) / sizeof(Argument);
    printf("Usage:");
    while (i < num)
    {
        printf("%s %-32s %s", ArguTypeMapping[i].option, ArguTypeMapping[i].type,
               ArguTypeMapping[i].description);
        printf("\n");
        i++;
    }
}

static void ParseArguType(EncodeParam* encodeParam, TestParm* testParam, char* argument, char* value)
{
    ArguType arg;

    arg = GetArguType(argument);

    switch (arg)
    {
    case HELP:
        PrintDemoUsage();
        exit(-1);
    case INPUT:
        memset(testParam->intputFile, 0, sizeof(testParam->intputFile));
        sscanf(value, "%255s", testParam->intputFile);
        logd(" get input file: %s \n", testParam->intputFile);
        break;
    case ENCODE_FRAME_NUM:
        sscanf(value, "%32u", &encodeParam->frameCount);
        break;
    case ENCODE_FORMAT:
        sscanf(value, "%32u", &encodeParam->codecType);
        break;
    case PIXEL_FORMAT:
        sscanf(value, "%32u", &encodeParam->pixelFormat);
        break;
    case OUTPUT:
        memset(testParam->outputFile, 0, sizeof(testParam->outputFile));
        sscanf(value, "%255s", testParam->outputFile);
        logd(" get output file: %s \n", testParam->outputFile);
        break;
    case SRC_W:
        sscanf(value, "%32u", &encodeParam->srcW);
        logd(" get srcW: %dp \n", encodeParam->srcW);
        break;
    case SRC_H:
        sscanf(value, "%32u", &encodeParam->srcH);
        logd(" get srcH: %dp \n", encodeParam->srcH);

        break;
    case BIT_RATE:
        sscanf(value, "%32d", &encodeParam->bitRate);
        logd(" bit rate: %d \n", encodeParam->bitRate);
        break;
    case TEST_WAY:
        sscanf(value, "%32d", &testParam->testWay);
        logd(" test %d->%d times \n", testParam->testWay, testParam->testTimes);

    case TEST_TIMES:
        sscanf(value, "%32d", &testParam->testTimes);
        logd(" test %d->%d times \n", testParam->testWay, testParam->testTimes);

        break;
    case INVALID:
    default:
        logd("unknowed argument :  %s", argument);
        break;
    }

}

static void printfArgs(EncodeParam    encodeParam)
{
    logd("\t -s:%dx%d\n", encodeParam.srcW, encodeParam.srcH);

    logd("\t -n:%d\n", encodeParam.frameCount);
    logd("\t -f:%d\n", encodeParam.codecType);
    logd("\t -p:%d\n", encodeParam.pixelFormat);
    logd("\t -r:%d\n", encodeParam.frameRate);
    logd("\t -d:%dx%d\n", encodeParam.dstW, encodeParam.dstH);
}

int getFrameBitSize(int w, int h, PixelFmt fmt)
{
    int pixelNum = w * h;
    int frameBitSize = 0;
    switch (fmt)
    {
    case PIXEL_YUV420SP...PIXEL_YVU420P:
        frameBitSize = pixelNum * 3 / 2;
        break;
//        case PIXEL_YUV422SP...PIXEL_VYUY422:
//            frameBitSize = pixelNum*2;
//            break;
//        case PIXEL_ARGB...PIXEL_BGRA:
//            frameBitSize = pixelNum*4;
//            break;
    }
    return frameBitSize;
}

class MyEncoderCallback: public AWVideoEncoderDataCallback
{
public:
    MyEncoderCallback(FILE* file, EncodeParam* param): mFile(file), mParam(param) {}
    virtual int encoderDataReady(AVPacket* packet)
    {
        //logd("\t encdoe data id=0x%x,pts=0x%llx\n",packet->id, packet->pts);
        if ((CODEC_JPEG == mParam->codecType) &&
                (ONLY_ONE_FRAME == mParam->frameCount))
        {
            //Save all jpg files.
            char outPutfile[60];
            sprintf(outPutfile, "%s_sgl_%d.%s", testParam.outputFile, mJpgIndex++, "jpg");

            mFile = fopen(outPutfile, "wb");
            if (mFile == NULL)
            {
                loge("open outFile fail\n");
                fclose(mFile);
                return -1;
            }
            fwrite(packet->pAddrVir0, 1, packet->dataLen0, mFile);
            if ((nullptr != packet->pAddrVir1) && (packet->dataLen1 > 0))
            {
                fwrite(packet->pAddrVir1, 1, packet->dataLen1, mFile);
            }
            fclose(mFile);
            mFile = NULL;
        }
        else
        {
            fwrite(packet->pAddrVir0, 1, packet->dataLen0, mFile);
            if ((nullptr != packet->pAddrVir1) && (packet->dataLen1 > 0))
            {
                fwrite(packet->pAddrVir1, 1, packet->dataLen1, mFile);
            }
        }
    };
private:
    FILE* mFile;
    EncodeParam* mParam;
};

#define USB_CBK
#define USE_PHY_ADDR
#define USE_ROI (0)

#ifdef USB_CBK
int encodeFile(EncodeParam* param, FILE* inFile, FILE* outFile)
{
    int inputFileLen;
    int oneFrameLen, totalFrameNum,oneFrameLenAlign;
    int ret;
    int frameIndex = 0;
    AVPacket packet;
    AvRoiRegionArray roiRegion;
    paramStruct_t ionMem;
    paramStruct_t* pIonMem = &ionMem;
    memset(&packet, 0, sizeof(AVPacket));

    oneFrameLen = getFrameBitSize(param->srcW, param->srcH, \
                                  param->pixelFormat);

    oneFrameLenAlign = getFrameBitSize(ALIGN(param->srcW,16),ALIGN(param->srcH,16), \
                                  param->pixelFormat);
#ifdef USE_PHY_ADDR
    ret = allocOpen(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    if (ret < 0)
    {
        printf("ion_alloc_open failed\n");
        return ret;
    }
    pIonMem->size = oneFrameLenAlign;
    ret = allocAlloc(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    if (ret < 0)
    {
        printf("allocAlloc failed\n");
        return ret;
    }
    packet.pAddrVir0 = (unsigned char*)pIonMem->vir;
#else
    packet.pAddrVir0 = (unsigned char*)malloc(oneFrameLenAlign);
#endif

    logd("malloc pIonMem->vir=%p!\n", pIonMem->vir);
    AWVideoEncoder* pEncoder = AWVideoEncoder::create();
    MyEncoderCallback* pCallback = new MyEncoderCallback(outFile, param);
    if ((inFile == NULL) || (outFile == NULL) || (NULL == pEncoder))
    {
        loge("open inFile fail\n");
        return -1;
    }

    ret = pEncoder->init(param, pCallback);
    if (0 != ret)
    {
        loge("init:%x\n", ret);
        goto EXIT;
    }

    fseek(inFile, 0L, SEEK_END);
    inputFileLen = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    totalFrameNum = inputFileLen / oneFrameLen;
    logd("\t frameBitSize:%d\n", oneFrameLen);
    logd("\t totalFrameNum:%d %s\n", totalFrameNum, __TIME__);

    if (!packet.pAddrVir0)
    {
        loge("malloc failed!\n");
        goto EXIT;
    }

    while (frameIndex < totalFrameNum)
    {
        packet.id = frameIndex + 0x100;
        if (USE_ROI) //(frameIndex%2)
        {
            roiRegion.roiNum = MAX_ROI_REGION;
            for (int j = 0; j < roiRegion.roiNum; j++)
            {
                roiRegion.region[j].enable = 1;
                roiRegion.region[j].QPoffset = 1;
                roiRegion.region[j].absFlag = 0;
                roiRegion.region[j].x = 5 + j * 150;
                roiRegion.region[j].y = 5 + j * 100;
                roiRegion.region[j].w = 150;
                roiRegion.region[j].h = 100;
            }
            pEncoder->setRoi(&roiRegion);
        }

        struct timeval now;
        gettimeofday(&now, NULL);
        packet.pts += 1 * 1000 / param->frameRate;; //= now.tv_sec * 1000000 + now.tv_usec;

        fread((void*)pIonMem->vir, 1, oneFrameLen, inFile);

#ifdef USE_PHY_ADDR

        packet.pAddrPhy0 = (unsigned char*)pIonMem->phy;
        packet.dataLen0 = param->srcW * param->srcH;

        packet.pAddrPhy1 = (unsigned char*)pIonMem->phy + param->srcW * param->srcH;
        packet.dataLen1 =  param->srcW * param->srcH / 2;
        flushCache(MEM_TYPE_CDX_NEW, pIonMem, NULL);
#else
        packet.dataLen0 = param->srcW * param->srcH;
        packet.pAddrVir1 = packet.pAddrVir0 + param->srcW * param->srcH;
        packet.dataLen1 =  param->srcW * param->srcH / 2;
#endif
        logd("\t encdoe process1:[%d/%d] id=0x%x,pts=0x%llx\n", frameIndex, totalFrameNum, packet.id, packet.pts);
        pEncoder->encode(&packet);
        if ((CODEC_JPEG == param->codecType) &&
                (ONLY_ONE_FRAME == param->frameCount))
        {
            pEncoder->setJpgQuality(frameIndex % 2 ? 10 : 100);
            //break;
        }

        frameIndex++;
        usleep(30 * 1000);

    }
#ifdef USE_PHY_ADDR
    allocFree(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    allocClose(MEM_TYPE_CDX_NEW, pIonMem, NULL);
#else
    free packet.pAddrVir0;
    packet.pAddrVir0 = NULL;
#endif
EXIT:
    AWVideoEncoder::destroy(pEncoder);
    delete pCallback;
}
#else
int encodeFile(EncodeParam* param, FILE* inFile, FILE* outFile)
{
    if ((CODEC_H265 == param->codecType))
    {
        param->bitRate = param->bitRate * 70 / 100;
    }

    if ((inFile == NULL) || (outFile == NULL))
    {
        loge("open inFile fail\n");
        return -1;
    }
    int ret;
    int inputFileLen;
    int oneFrameLen, totalFrameNum;
    paramStruct_t ionMem;
    paramStruct_t* pIonMem = &ionMem;

    void* intputBuf;
    int outputLen;
    void* outputBuf;

    oneFrameLen = getFrameBitSize(param->srcW, param->srcH, \
                                  param->pixelFormat);

    fseek(inFile, 0L, SEEK_END);
    inputFileLen = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    totalFrameNum = inputFileLen / oneFrameLen;
    logd("\t frameBitSize:%d\n", oneFrameLen);
    logd("\t totalFrameNum:%d\n", totalFrameNum);
#ifdef USE_PHY_ADDR
    ret = allocOpen(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    if (ret < 0)
    {
        printf("ion_alloc_open failed\n");
        return ret;
    }
    pIonMem->size = oneFrameLen;
    ret = allocAlloc(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    if (ret < 0)
    {
        printf("allocAlloc failed\n");
        return ret;
    }
    intputBuf = (unsigned char*)pIonMem->vir;
#else
    intputBuf = malloc(oneFrameLen);
#endif

    outputBuf = malloc(oneFrameLen);

    if (!intputBuf || !outputBuf)
    {
        loge("malloc failed!\n");
        return 0;
    }

    AWVideoEncoder* pEncoder = AWVideoEncoder::create(param);

    loge("encodeParam.codecType:%d\n", param->codecType);
    if ((CODEC_H264 == param->codecType)
            || (CODEC_H264_VER2 == param->codecType)
            || (CODEC_H265 == param->codecType))
    {
        logd("CODEC_H264 == encodeParam.codecType!\n");
        int  headerLen;
        headerLen = pEncoder->getHeader(outputBuf);
        fwrite(outputBuf, 1, headerLen, outFile);
    }

    int frameIndex = 0;
    while (frameIndex < totalFrameNum)
    {
        fread(intputBuf, 1, oneFrameLen, inFile);
#ifdef USE_PHY_ADDR
        flushCache(MEM_TYPE_CDX_NEW, pIonMem, NULL);
        outputLen = pEncoder->encodePhy((void*)pIonMem->phy, oneFrameLen, outputBuf, oneFrameLen);
#else
        outputLen = pEncoder->encode(intputBuf, oneFrameLen, outputBuf, oneFrameLen);
#endif
        if (outputLen > 0)
        {
            fwrite(outputBuf, 1, outputLen, outFile);
        }

        logd("\t file %#X:[%d/%d]\n", outFile, frameIndex, totalFrameNum);
        frameIndex++;
    }

    AWVideoEncoder::destroy(pEncoder);

#ifdef USE_PHY_ADDR
    allocFree(MEM_TYPE_CDX_NEW, pIonMem, NULL);
    allocClose(MEM_TYPE_CDX_NEW, pIonMem, NULL);
#else
    if (intputBuf)
        free(intputBuf);
#endif
    if (outputBuf)
        free(outputBuf);
}
#endif
int singleEncoderTest()
{
    logd("\t\t ================================\n");
    logd("\t\t ====     CedarC  Encoder    ====\n");
    logd("\t\t ====    singleDecoderTest    ====\n");
    logd("\t\t ================================\n");
    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        loge("open inFile fail\n");
        return -1;
    }

    char outPutfile[60];
    sprintf(outPutfile, "%s_sgl%s", testParam.outputFile, codecExt[encodeParam.codecType]);

    FILE* outFile = fopen(outPutfile, "wb");
    if (outFile == NULL)
    {
        loge("open outFile fail\n");
        fclose(inFile);
        return -1;
    }
    printfArgs(encodeParam);


    encodeFile(&encodeParam, inFile, outFile);

    printfArgs(encodeParam);
    printf("output file is saved:%s\n\n\n", testParam.outputFile);


    if (outFile)
        fclose(outFile);
    if (inFile)
        fclose(inFile);

}

void* encodeFileThread(void* arg)
{
    FILE* inFile;
    FILE* outFile;

    ThreadParm* pParm = (ThreadParm*)arg;
    inFile = pParm->inFile;
    outFile = pParm->outFile;
    encodeFile(pParm->param, pParm->inFile, pParm->outFile);
}

int  _18_ch_EncoderTest()
{
    const static int MAIN_CHANNELS_NUM  = 6;
    const static int ATLI_CHANNELS_NUM  = 6;
    const static int JPEG_CHANNELS_NUM  = 6;

    const static int TOTAL_CHANNELS_NUM  = MAIN_CHANNELS_NUM + ATLI_CHANNELS_NUM + JPEG_CHANNELS_NUM;

    logd("\t\t ================================\n");
    logd("\t\t ====    CedarC   Encoder    ====\n");
    logd("\t\t ====   _18_ch_EncoderTest   ====\n");
    logd("\t\t ================================\n");

    ThreadParm threadParm[TOTAL_CHANNELS_NUM];
    EncodeParam mEncodeParam[TOTAL_CHANNELS_NUM];
    pthread_t threah[TOTAL_CHANNELS_NUM];

    char outPutfile[60];

    for (int i = 0; i < TOTAL_CHANNELS_NUM; i++)
    {
        memset(&mEncodeParam[i], 0, sizeof(EncodeParam));
        switch (i)
        {
        case 0 ... 5:
        {
            mEncodeParam[i].dstW = encodeParam.dstW;
            mEncodeParam[i].dstH = encodeParam.dstH;
            mEncodeParam[i].codecType = CODEC_H264;
        }
        break;
        case 6 ... 11:
        {
            mEncodeParam[i].dstW = encodeParam.dstW / 2;
            mEncodeParam[i].dstH = encodeParam.dstH / 2;
            mEncodeParam[i].codecType = CODEC_H264;
        }
        break;
        case 12 ... 17:
        {
            mEncodeParam[i].dstW = encodeParam.dstW;
            mEncodeParam[i].dstH = encodeParam.dstH;
            mEncodeParam[i].codecType = CODEC_JPEG;
        }
        break;
        default:
            mEncodeParam[i].dstW = encodeParam.dstW;
            mEncodeParam[i].dstH = encodeParam.dstH;
            mEncodeParam[i].codecType = CODEC_H264;
            break;
        }

        threadParm[i].inFile = fopen(testParam.intputFile, "r");
        if ((threadParm[i].inFile == NULL))
        {
            loge("open file fail:%s\n", testParam.intputFile);
            fclose(threadParm[i].inFile);
            return -1;
        }

        sprintf(outPutfile, "%s_18_%d_%s", testParam.outputFile, i, codecExt[mEncodeParam[i].codecType]);
        threadParm[i].outFile = fopen(outPutfile, "wb");
        if ((threadParm[i].outFile == NULL))
        {
            loge("open file fail:%s.\n", outPutfile);
            fclose(threadParm[i].outFile);
            return -1;
        }

        mEncodeParam[i].srcW = encodeParam.srcW;
        mEncodeParam[i].srcH = encodeParam.srcH ;
        mEncodeParam[i].rotation = encodeParam.rotation;
        mEncodeParam[i].bitRate = encodeParam.bitRate;
        mEncodeParam[i].frameRate = encodeParam.frameRate;
        mEncodeParam[i].maxKeyFrame = encodeParam.maxKeyFrame;
        mEncodeParam[i].pixelFormat = encodeParam.pixelFormat;
        mEncodeParam[i].frameCount = encodeParam.frameCount;
        mEncodeParam[i].jpgQuality = encodeParam.jpgQuality;
        mEncodeParam[i].rcMode = encodeParam.rcMode;

        threadParm[i].param = &mEncodeParam[i];
        printfArgs(mEncodeParam[i]);

    }

    for (int i = 0; i < TOTAL_CHANNELS_NUM; i++)
    {
        pthread_create(&threah[i], 0, encodeFileThread, (void*)&threadParm[i]);
    }

    for (int i = 0; i < TOTAL_CHANNELS_NUM; i++)
    {
        pthread_join(threah[i], NULL);
        logd("\t\t encoder[%d] is end.\n", i);

        if (threadParm[i].outFile)
        {
            fclose(threadParm[i].outFile);
            threadParm[i].outFile = NULL;
        }

        if (threadParm[i].inFile)
        {
            fclose(threadParm[i].inFile);
            threadParm[i].inFile = NULL;
        }
    }

}
int  multiEncoderTest()
{
    logd("\t\t ================================\n");
    logd("\t\t ====    CedarC   Encoder    ====\n");
    logd("\t\t ====    multiDecoderTest    ====\n");
    logd("\t\t ================================\n");
    ThreadParm threadParm[CODEC_VP8 + 1];
    EncodeParam mEncodeParam[CODEC_VP8 + 1];
    pthread_t threah[CODEC_VP8 + 1];

    char outPutfile[60];

    for (int i = 0; i < CODEC_VP8; i++)
    {
        threadParm[i].inFile = fopen(testParam.intputFile, "r");
        if ((threadParm[i].inFile == NULL))
        {
            loge("open file fail:%s\n", testParam.intputFile);
            fclose(threadParm[i].inFile);
            return -1;
        }

        sprintf(outPutfile, "%s_multi%s", testParam.outputFile, codecExt[i]);
        threadParm[i].outFile = fopen(outPutfile, "wb");
        if ((threadParm[i].outFile == NULL))
        {
            loge("open file fail:%s.\n", outPutfile);
            fclose(threadParm[i].outFile);
            return -1;
        }

        memset(&mEncodeParam[i], 0, sizeof(EncodeParam));
        mEncodeParam[i].srcW = encodeParam.srcW;
        mEncodeParam[i].srcH = encodeParam.srcH ;
        mEncodeParam[i].dstW = encodeParam.dstW;
        mEncodeParam[i].dstH = encodeParam.dstH;
        mEncodeParam[i].rotation = encodeParam.rotation;
        mEncodeParam[i].bitRate = encodeParam.bitRate;
        mEncodeParam[i].frameRate = encodeParam.frameRate;
        mEncodeParam[i].maxKeyFrame = encodeParam.maxKeyFrame;
        mEncodeParam[i].codecType = (CodecType)i;
        mEncodeParam[i].pixelFormat = encodeParam.pixelFormat;
        mEncodeParam[i].frameCount = encodeParam.frameCount;
        mEncodeParam[i].jpgQuality = encodeParam.jpgQuality;
        mEncodeParam[i].rcMode = encodeParam.rcMode;

        threadParm[i].param = &mEncodeParam[i];
        printfArgs(mEncodeParam[i]);

    }

    for (int i = 0; i < CODEC_VP8; i++)
    {
        pthread_create(&threah[i], 0, encodeFileThread, (void*)&threadParm[i]);
    }

    for (int i = 0; i < CODEC_VP8; i++)
    {
        pthread_join(threah[i], NULL);

        if (threadParm[i].outFile)
        {
            fclose(threadParm[i].outFile);
            threadParm[i].outFile = NULL;
        }

        if (threadParm[i].inFile)
        {
            fclose(threadParm[i].inFile);
            threadParm[i].inFile = NULL;
        }
    }

}

//encoder -i /tmp/test/800x480x93_nv21.yuv -o /tmp/800x480x93_nv21  -p 1 -f 1 -t 0 1
int main(int argc, char** argv)
{
    printf("encoderTest version:%s\n", MODULE_VERSION);
    /******** begin set the default encode param ********/
    memset(&encodeParam, 0, sizeof(encodeParam));
    memset(&testParam, 0, sizeof(testParam));

    encodeParam.srcW = 800;
    encodeParam.srcH = 480;
    encodeParam.dstW = encodeParam.srcW;
    encodeParam.dstH = encodeParam.srcH;
    encodeParam.rotation = Angle_0;
    encodeParam.bitRate = 1 * 1024 * 1024;
    encodeParam.frameRate = 30;
    encodeParam.maxKeyFrame = 30;
    encodeParam.codecType = CODEC_H265;
    encodeParam.pixelFormat = PIXEL_YVU420SP;
    encodeParam.frameCount = ONLY_ONE_FRAME;
    encodeParam.jpgQuality = 50;
    encodeParam.rcMode = VBR;
    encodeParam.minQp = 10;
    encodeParam.maxQp = 50;

    testParam.testTimes = 1;
    testParam.testWay = 0;
    strcpy((char*)testParam.intputFile,        "/tmp/720_480.yuv");
    strcpy((char*)testParam.outputFile,        "/tmp/output");

    /******** begin parse the config paramter ********/
    int i;
    if (argc >= 2)
    {
        for (i = 1; i < (int)argc; i += 2)
        {
            ParseArguType(&encodeParam, &testParam, argv[i], argv[i + 1]);
        }
    }
    encodeParam.dstW = encodeParam.srcW;
    encodeParam.dstH = encodeParam.srcH;

    for (int k = 1; k <= testParam.testTimes; k++)
    {
        if (testParam.testWay == 0)
        {
            singleEncoderTest();
        }
        else if (testParam.testWay == 1)
        {
            multiEncoderTest();
        }
        else if (testParam.testWay == 2)
        {
            _18_ch_EncoderTest();
        }
        printf("Test %d times.\n\n\n\n", k);
    }

    return 0;
}


