#include "AWVideoDecoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>

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


using namespace awvideodecoder;

#define DEFAULT_BUF_LEN   (500*1024)

const char* pixelExt[] =
{
    "default",
    "planer_420",
    "planer_422",
    "planer_444",
    "yv12",
    "nv21",
    "nv12",
    "mb32_420",
    "mb32_422",
    "mb32_444",
    "rgba",
    "argb",
    "abgr",
    "bgra",
    "yuyv",
    "yvyu",
    "uyvy",
    "vyuy",
    "planaruv_422",
    "planarvu_422",
    "planaruv_444",
    "planarvu_444",
};

typedef struct TestParm_
{
    char intputFile[256];
    char outputFile[256];
    int  testWay;
    int  testTimes;
} TestParm;

DecodeParam    decodeParam;
TestParm    testParam;

struct ThreadParm
{
    int pixel;
};

typedef enum
{
    INPUT,
    HELP,
    DECODE_FORMAT,
    PIXEL_FORMAT,
    OUTPUT,
    SRC_W,
    SRC_H,
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
        "-f",  "--codecType",  DECODE_FORMAT,
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
        "-w",  "--test way",  TEST_WAY,
        "(0:single test, 1:multiDecoderTest)"
    },
    {
        "-t",  "--test times",  TEST_TIMES,
        " testTimes"
    },
};

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

static void ParseArguType(DecodeParam* decodeParam, TestParm* testParam, char* argument, char* value)
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
    case DECODE_FORMAT:
        sscanf(value, "%32u", &decodeParam->codecType);
        break;
    case PIXEL_FORMAT:
        sscanf(value, "%32u", &decodeParam->pixelFormat);
        break;
    case OUTPUT:
        memset(testParam->outputFile, 0, sizeof(testParam->outputFile));
        sscanf(value, "%255s", testParam->outputFile);
        logd(" get output file: %s \n", testParam->outputFile);
        break;
    case SRC_W:
        sscanf(value, "%32u", &decodeParam->srcW);
        logd(" get srcW: %dp \n", decodeParam->srcW);
        break;
    case SRC_H:
        sscanf(value, "%32u", &decodeParam->srcH);
        logd(" get dstH: %dp \n", decodeParam->srcH);
        break;
//    case BIT_RATE:
//        sscanf(value, "%32d", &decodeParam->bitRate);
//        logd(" bit rate: %d \n", decodeParam->bitRate);
//        break;
//    case ENCODE_FRAME_NUM:
//        sscanf(value, "%32u", &decodeParam->frameCount);
//        break;
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

static void printfArgs(DecodeParam    decodeParam)
{
    logd("\t -i:%d\n", testParam.intputFile);
    logd("\t -s:[%dx%d]\n", decodeParam.srcW, decodeParam.srcH);
    logd("\t -f:%d\n", decodeParam.codecType);
    logd("\t -p:%d\n", decodeParam.pixelFormat);
    logd("\t -o:%d\n", testParam.outputFile);

}

int find264NALFragment(char* data, size_t size, int* fragSize)
{
    static const char kStartCode[4] = { 0x00, 0x00, 0x00, 0x01 };
    if (size < 4)
    {
        printf("size %d < 4\n", size);
        return -1;
    }

    if (memcmp(kStartCode, data, 4))
    {
        printf("StartCode not found in %.2x %.2x %.2x %.2x\n", data[0], data[1], data[2], data[3]);
        return -2;
    }

    size_t offset = 4;
    while (offset + 3 < size && memcmp(kStartCode, &data[offset], 4))
    {
        ++offset;
    }

    if (offset > (size - 4))
    {
        printf("offset>(size-4)\n");
        offset = size;
    }
    *fragSize = offset;

    return (int)(data[4] & 0x1f);
}

int getFrameBitSize(int w, int h, PixelFmt fmt)
{
    int pixelNum = w * h;
    //logd("pic size:[%dx%d]\n",w,h);
    int frameBitSize = 0;

    switch (fmt)
    {
    case PIXEL_YV12...PIXEL_NV21:
        frameBitSize = pixelNum * 3 / 2;
        break;
    default:
        frameBitSize = pixelNum * 3 / 2;
        break;
    }
#ifdef BOGUS

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
#endif /* BOGUS */
    return frameBitSize;
}

void getExpectSize(int* w, int* h)
{
    int dstW = decodeParam.srcW >> decodeParam.scaleRatio;
    int dstH = decodeParam.srcH >> decodeParam.scaleRatio;
    if ((decodeParam.rotation == Angle_90) || (decodeParam.rotation == Angle_270))
    {
        * w = dstH;
        * h = dstW;
    }
    else
    {
        * w = dstW;
        * h = dstH;
    }
}

class MyDecoderCallback: public AWVideoDecoderDataCallback
{
public:
    MyDecoderCallback(FILE* file): mFile(file) {}
    virtual int decoderDataReady(AVPacket* packet)
    {
        if ((NULL != packet->pAddrVir0) && (packet->dataLen0 > 0))
            fwrite(packet->pAddrVir0, 1, packet->dataLen0, mFile);

        if ((NULL != packet->pAddrVir1) && (packet->dataLen1 > 0))
            fwrite(packet->pAddrVir1, 1, packet->dataLen1, mFile);

    };
private:
    FILE* mFile;
};

int singleDecoderTest()
{
    logd("\t\t ================================\n");
    logd("\t\t ====     CedarC  Decoder    ====\n");
    logd("\t\t ====    singleDecoderTest    ====\n");
    logd("\t\t ================================\n");

    int ret = 0;

    FILE* inFile = NULL;
    FILE* outputFile = NULL;
    char* inputBuf = NULL;
    int intputLen = 0;
    char* outputBuf = NULL;
    int outputLen = 0;

    AWVideoDecoder* pDecoder = NULL;
    MyDecoderCallback* pCallback = NULL;
    int fileSize;

    int decodePos = 0;
    int readTmpLen = 0;
    int nalLen = 0;
    int count = 0x100;
    int data = 1;
    int dstW;
    int dstH;
    AVPacket inPacket;

    inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        loge("open inFile:%s fail\n", testParam.intputFile);
        return -1;
    }
    outputFile = NULL;
    getExpectSize(&dstW, &dstH);
    int bitSize = getFrameBitSize(dstW, dstH, decodeParam.pixelFormat);

    inputBuf = (char*)malloc(DEFAULT_BUF_LEN);
    intputLen = DEFAULT_BUF_LEN;
    outputBuf = (char*)malloc(bitSize);
    outputLen = bitSize;

    if (outputFile == NULL)
    {
        char outputFilePath[256];
        sprintf(outputFilePath, "%s[%dx%d]%s_sgl.yuv", testParam.outputFile,
                decodeParam.dstW, decodeParam.dstH, pixelExt[decodeParam.pixelFormat]);

        outputFile = fopen(outputFilePath, "wb");
        if (outputFile == NULL)
        {
            loge("open outputFile fail\n");
            goto EXIT;
        }
    }

    pDecoder = AWVideoDecoder::create();
    pCallback = new MyDecoderCallback(outputFile);
    ret = pDecoder->init(&decodeParam, pCallback);
    if (ret < 0)
    {
        loge("pDecoder->init fail:%d \n", ret);
        goto EXIT;
    }

    fseek(inFile, 0L, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    while (decodePos < fileSize)
    {
        //logd("decode process[%d/%d]\n", decodePos,fileSize);
        count++;
        readTmpLen = ((fileSize - decodePos) < intputLen) ? (fileSize - decodePos) : intputLen;
        fread(inputBuf, 1, readTmpLen, inFile);
        nalLen = 0;
        ret = find264NALFragment((char*)inputBuf, readTmpLen, &nalLen);
        if (nalLen < 4)
        {
            loge("find264NALFragment fail \n");
            break;
        }

        inPacket.pAddrVir0 = (unsigned char*)inputBuf;
        inPacket.dataLen0 = nalLen;
        inPacket.id = count;
        struct timeval now;
        gettimeofday(&now, NULL);
        inPacket.pts = now.tv_sec * 1000000 + now.tv_usec;

        //logd("fmt_sgl[%s-%d]decode %d bytes.\n",pixelExt[decodeParam.pixelFormat],data++,nalLen);
        ret = pDecoder->decode(&inPacket);
        if (0 < ret)
        {
            decodePos += nalLen;
            fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.

            //logd("fmt_sgl[%s-%d]write %d bytes.\n",pixelExt[decodeParam.pixelFormat],count++,ret);
        }
        else
        {
            logw("decode failed,error code:%d\n", ret);
            decodePos += nalLen;
            fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        }
    }

    printfArgs(decodeParam);
    printf("output file is saved:%s\n\n\n", testParam.outputFile);

EXIT:
    delete pCallback;
    AWVideoDecoder::destroy(pDecoder);

    free(inputBuf);
    free(outputBuf);

    if (outputFile)
        fclose(outputFile);
    if (inFile)
        fclose(inFile);

}

void mjpegDecodeTest()
{
    logd("\t\t ================================\n");
    logd("\t\t ====     CedarC  Decoder    ====\n");
    logd("\t\t ====     mjpegDecodeTest    ====\n");
    logd("\t\t ================================\n");

    int ret;
    int fileCount = 13;
    char inFilePath[60] = {0};
    char outFilePath[60] = {0};
    int fileSize = 0;

    char* inputBuf = NULL;
    int inputLen = 0;
    char* outputBuf = NULL;
    int outputLen = 0;

    decodeParam.codecType = CODEC_MJPEG;
//    decodeParam.srcW = 1920;
//    decodeParam.srcH = 1080;
//    int dstW = 0;
//    int dstH = 0;
//    getExpectSize(&dstW,&dstH);
    outputLen = getFrameBitSize(1920, 1080, decodeParam.pixelFormat);
    outputBuf = (char*)malloc(outputLen);

    FILE* outputFile = NULL;
    FILE* inputFile = NULL;

    AWVideoDecoder* pDecoder = AWVideoDecoder::create(&decodeParam);

    for (int i = 1; i <= fileCount; i++)
    {
        sprintf(inFilePath, "%s%d.jpg", "/tmp/input/", i);
        inputFile = fopen(inFilePath, "rb");
        if (inputFile == NULL)
        {
            printf("open nal fail[%d]:%s\n", i, inFilePath);
            continue;
        }

        printf("open file:%s\n", inFilePath);
        fseek(inputFile, 0L, SEEK_END);
        fileSize = ftell(inputFile);
        fseek(inputFile, 0L, SEEK_SET);

        inputBuf = (char*)malloc(fileSize);
        fread(inputBuf, 1, fileSize, inputFile);
        fclose(inputFile);

        //decode
        ret = pDecoder->decode(inputBuf, fileSize, outputBuf, outputLen);
        if (ret > 0)
        {
            if (outputFile == NULL)
            {

                sprintf(outFilePath, "%s[%dx%d]%s_mult.yuv", testParam.outputFile,
                        decodeParam.dstW, decodeParam.dstH, pixelExt[decodeParam.pixelFormat]);
                outputFile = fopen(outFilePath, "wb");
                if (outputFile == NULL)
                {
                    loge("open outputFile fail\n");
                    fclose(inputFile);
                }
            }

            if (ret > outputLen)
            {
                logw("output buf not enough,re-malloc and decode agian,i=%d.\n", i);
                free(outputBuf);
                outputBuf = (char*)malloc(ret);
                outputLen = ret;
                i -= 1;
                continue;
            }

            fwrite(outputBuf, 1, ret, outputFile);
        }
        else
        {
            loge("decode fail:%s\n", inFilePath);
        }

        free(inputBuf);

    }

    AWVideoDecoder::destroy(pDecoder);

    free(outputBuf);

    if (outputFile)
        fclose(outputFile);


}

void* decodeThread(void* arg)
{
    DecodeParam* parm = (DecodeParam*)arg;

    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        loge("open inFile fail\n");
        return NULL;
    }

    FILE* outputFile = NULL;

    int ret = 0;
    int ExpectW;
    int ExpectH;
    getExpectSize(&ExpectW, &ExpectH);
    int bitSize = getFrameBitSize(ExpectW, ExpectH, decodeParam.pixelFormat);
    char* inputFile = (char*)malloc(DEFAULT_BUF_LEN);
    int inputLen = DEFAULT_BUF_LEN;
    char* outputBuf = (char*)malloc(bitSize);
    int outputLen = bitSize;
    char outputFilePath[256];

    int fmt = parm->pixelFormat;
    parm->pixelFormat = PIXEL_NV21;//only support PIXEL_NV21 now
    AWVideoDecoder* pDecoder = AWVideoDecoder::create(parm);

    int fileSize;
    fseek(inFile, 0L, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    int decodePos = 0;
    int readTmpLen = 0;
    int nalLen = 0;
    int count = 1;
    int data = 1;

    while (decodePos < fileSize)
    {
        //logd("decode process[%d/%d]\n", decodePos,fileSize);
        readTmpLen = ((fileSize - decodePos) < inputLen) ? (fileSize - decodePos) : inputLen;
        fread(inputFile, 1, readTmpLen, inFile);

        nalLen = 0;
        ret = find264NALFragment((char*)inputFile, readTmpLen, &nalLen);
        if (nalLen < 4)
        {
            loge("find264NALFragment fail \n");
            break;
        }

        //logd("fmt[%s-%d]decode %d bytes.\n",pixelExt[fmt],data++,nalLen);
        ret = pDecoder->decode(inputFile, nalLen, outputBuf, outputLen);
        //logd("pDecoder->decode [%d<=%d]??? \n",ret,outputLen);
        if ((0 < ret) && (ret <= outputLen))
        {
            if (outputFile == NULL)
            {
                //logd("parm:%#X,[%dx%d]\n",parm,parm->dstW,parm->dstH);
                sprintf(outputFilePath, "%s[%dx%d]%s_mult.yuv", testParam.outputFile,
                        parm->dstW, parm->dstH, pixelExt[fmt]);

                outputFile = fopen(outputFilePath, "wb");
                if (outputFile == NULL)
                {
                    loge("open outputFile fail\n");
                    fclose(inFile);
                    return NULL;
                }
            }
            fwrite(outputBuf, 1, ret, outputFile);
            //logd("fmt[%s-%d]write %d bytes.\n",pixelExt[fmt],count++,ret);
            decodePos += nalLen;
            fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        }
        else if (ret > outputLen)
        {
            logw("output buf not enough,re-malloc and decode agian.\n");
            free(outputBuf);
            outputBuf = (char*)malloc(ret);
            outputLen = ret;
            fseek(inFile, decodePos, SEEK_SET); //stay the current decode position.
            continue;
        }
        else
        {
            loge("decode failed,error code:%d\n", ret);
            decodePos += nalLen;
            fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        }
    }

    printfArgs(*parm);
    printf("output file is saved:%s\n\n\n", outputFile);

    AWVideoDecoder::destroy(pDecoder);

    free(inputFile);
    free(outputBuf);

    if (outputFile)
        fclose(outputFile);
    if (inFile)
        fclose(inFile);

}

int  multiDecoderTest()
{
    logd("\t\t ================================\n");
    logd("\t\t ====    CedarC   Decoder    ====\n");
    logd("\t\t ====    multiDecoderTest    ====\n");
    logd("\t\t ================================\n");

    decodeParam.rotation = Angle_0;
    decodeParam.scaleRatio = ScaleOneHalf;

    int startFmt = PIXEL_YUV_PLANER_420;
    int stopFmt = PIXEL_YUV_MB32_420;

    DecodeParam mDecodeParam[PIXEL_P010_VU];
    pthread_t threah[PIXEL_P010_VU];

    memset(mDecodeParam, 0, sizeof(mDecodeParam));
    for (int i = startFmt; i <= stopFmt; i++)
    {
        mDecodeParam[i].srcW = decodeParam.srcW;
        mDecodeParam[i].srcH = decodeParam.srcH;
        mDecodeParam[i].rotation = decodeParam.rotation;
        mDecodeParam[i].codecType = decodeParam.codecType;
        mDecodeParam[i].scaleRatio = decodeParam.scaleRatio;
        mDecodeParam[i].pixelFormat = PixelFmt(i);
    }

    for (int i = startFmt; i <= stopFmt; i++)
    {
        pthread_create(&threah[i], 0, decodeThread, (void*)&mDecodeParam[i]);
    }

    for (int i = startFmt; i <= stopFmt; i++)
    {
        pthread_join(threah[i], NULL);
    }

}

//encoder -i /tmp/test/800x480x93_nv21.yuv -o /tmp/800x480x93_nv21  -p 1 -f 1 -t 0 1
int main(int argc, char** argv)
{
    /******** begin set the default encode param ********/
    memset(&decodeParam, 0, sizeof(decodeParam));
    memset(&testParam, 0, sizeof(testParam));

    decodeParam.srcW = 800;
    decodeParam.srcH = 480;
    decodeParam.dstW = 800;
    decodeParam.dstH = 480;
    decodeParam.rotation = Angle_0;
    decodeParam.scaleRatio = ScaleNone;
    decodeParam.codecType = CODEC_H264;
    decodeParam.pixelFormat = PIXEL_NV21;

    testParam.testTimes = 1;
    testParam.testWay = 0;
    strcpy((char*)testParam.intputFile,        "/tmp/input/tmp.h264");
    strcpy((char*)testParam.outputFile,        "/tmp/output/");

    /******** begin parse the config paramter ********/
    int i;
    if (argc >= 2)
    {
        for (i = 1; i < (int)argc; i += 2)
        {
            ParseArguType(&decodeParam, &testParam, argv[i], argv[i + 1]);
        }
    }

    for (int k = 1; k <= testParam.testTimes; k++)
    {
        if (testParam.testWay == 0)
        {
            singleDecoderTest();
            //mjpegDecodeTest();
        }
        else
        {
            multiDecoderTest();
        }
        printf("Test %d times.\n\n\n\n", k);
    }

    return 0;
}


