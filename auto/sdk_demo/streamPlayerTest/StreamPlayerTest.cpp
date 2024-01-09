#include "AWStreamPlayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>


using namespace awstreamplayer;

#define DEFAULT_BUF_LEN   (500*1024)
#define MAX_NAL_SIZE  (1024*1024)

#define SCREEN_W    (1024)
#define SCREEN_H    (600)
#define TV_W        (720)
#define NTSC_H      (480)
#define PAL_H       (576)
#define TV_H(mode)  ((mode==NTSC)?NTSC_H:PAL_H)

#define MODULE_VERSION "V2.0.20220506"

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

PlayerParam    decodeParam;
TestParm    testParam;
AWStreamPlayer* pPlayer;
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
        "-s",  "--srcw",  SRC_W,
        "SRC_W"
    },
    {
        "-d",  "--srch",  SRC_H,
        "SRC_H"
    },
    {
        "-w",  "--test way",  TEST_WAY,
        "(0:single test, 1:multiDecoderTest,2:single h264 fream)"
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

static void ParseArguType(PlayerParam* decodeParam, TestParm* testParam, char* argument, char* value)
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
        printf(" get input file: %s \n", testParam->intputFile);
        break;
    case DECODE_FORMAT:
        sscanf(value, "%32u", &decodeParam->codecType);
        break;
    case OUTPUT:
        memset(testParam->outputFile, 0, sizeof(testParam->outputFile));
        sscanf(value, "%255s", testParam->outputFile);
        printf(" get output file: %s \n", testParam->outputFile);
        break;
    case SRC_W:
        sscanf(value, "%32u", &decodeParam->srcW);
        printf(" get srcW: %dp \n", decodeParam->srcW);
        break;
    case SRC_H:
        sscanf(value, "%32u", &decodeParam->srcW);
        printf(" get dstH: %dp \n", decodeParam->srcW);
        break;
//    case BIT_RATE:
//        sscanf(value, "%32d", &decodeParam->bitRate);
//        printf(" bit rate: %d \n", decodeParam->bitRate);
//        break;
//    case ENCODE_FRAME_NUM:
//        sscanf(value, "%32u", &decodeParam->frameCount);
//        break;
    case TEST_WAY:
        sscanf(value, "%32d", &testParam->testWay);
        printf(" test %d->%d times \n", testParam->testWay, testParam->testTimes);

    case TEST_TIMES:
        sscanf(value, "%32d", &testParam->testTimes);
        printf(" test %d->%d times \n", testParam->testWay, testParam->testTimes);

        break;
    case INVALID:
    default:
        printf("unknowed argument :  %s", argument);
        break;
    }

}

static void printfArgs(PlayerParam    decodeParam)
{
    printf("\t -i:%s\n", testParam.intputFile);
    printf("\t -s:[%dx%d]\n", decodeParam.srcW, decodeParam.srcH);
    printf("\t -f:%d\n", decodeParam.codecType);
    printf("\t -o:%s\n", testParam.outputFile);

}

int find264NALFragment(char* data, size_t size, int* fragSize)
{
    static const char kStartCode[4] = { 0x00, 0x00, 0x00, 0x01 };
    if (size < 4)
    {
        printf("size %zu < 4\n", size);
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

void CenterAlignment(int w,int h)
{
    float scale = w/h;
    if(scale<1)//Center alignment,If you don't need it, please mark it.
    {
        decodeParam.dispH = SCREEN_H;
        decodeParam.dispW = (decodeParam.dispH*w)/h;
        decodeParam.dispX = (SCREEN_W-decodeParam.dispW)/2;

        decodeParam.tvDispH = TV_H(decodeParam.tvOut);
        decodeParam.tvDispW = (decodeParam.tvDispH*w)/h;;
        decodeParam.tvDispX = (TV_W-decodeParam.tvDispW)/2;
    }
    else
    {
        decodeParam.dispW = w;
        decodeParam.dispH = h;
        decodeParam.dispX = 0;
        
        decodeParam.tvDispH = TV_H(decodeParam.tvOut);
        decodeParam.tvDispW = TV_W;
        decodeParam.tvDispX = 0;
    }
}

int h264OneFrameTest()
{
    printf("\t\t ================================\n");
    printf("\t\t ====     CedarC  Decoder    ====\n");
    printf("\t\t ====        h264Test        ====\n");
    printf("\t\t ================================\n");

    decodeParam.codecType = CODEC_H264;
    decodeParam.dispX = 0;
    decodeParam.dispW = 1280;
    decodeParam.dispH = 720;
    decodeParam.rotation = Angle_180;
    decodeParam.tvOut = PAL;

    int ret = 0;
    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        printf("open inFile:%s fail\n",testParam.intputFile);
        return -1;
    }

    char* inputBuf = NULL;
    int intputLen = 0;
    int dstW;
    int dstH;

    inputBuf = (char*)malloc(DEFAULT_BUF_LEN);
    intputLen = DEFAULT_BUF_LEN;

    pPlayer = AWStreamPlayer::create(&decodeParam);
    pPlayer->startThread();

    int fileSize;
    fseek(inFile, 0L, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    int decodePos = 0;
    int readTmpLen = 0;
    int nalLen = 0;
    int count = 0;
    int data = 1;

    while (decodePos < fileSize)
    {
        readTmpLen = ((fileSize - decodePos) < intputLen) ? (fileSize - decodePos) : intputLen;
        fread(inputBuf, 1, readTmpLen, inFile);
        nalLen = 0;
        ret = find264NALFragment((char*)inputBuf, readTmpLen, &nalLen);
        if (nalLen < 4)
        {
            printf("find264NALFragment fail \n");
            break;
        }
        decodePos += nalLen;
        printf("decode  process[%d/%d]\n", decodePos,fileSize);

        //printf("fmt_sgl[%s-%d]decode %d bytes.\n",pixelExt[decodeParam.pixelFormat],data++,nalLen);
        ret = pPlayer->sendFrameToThread((unsigned char*)inputBuf, nalLen);
        fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        if(count++>=3)break;
        usleep(5*1000*1000);
    }

    printfArgs(decodeParam);

    pPlayer->stopThread();
    AWStreamPlayer::destroy(pPlayer);

    free(inputBuf);

    if (inFile)
        fclose(inFile);

}

int h264Test()
{
    printf("\t\t ================================\n");
    printf("\t\t ====     CedarC  Decoder    ====\n");
    printf("\t\t ====        h264Test        ====\n");
    printf("\t\t ================================\n");

    decodeParam.codecType = CODEC_H264;
    decodeParam.dispX = 0;
    decodeParam.dispW = 1024;
    decodeParam.dispH = 600;
    decodeParam.rotation = Angle_0;
    decodeParam.tvOut = NONE;
    decodeParam.zorder = 20;

    int ret = 0;
    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        printf("open inFile:%s fail\n",testParam.intputFile);
        return -1;
    }

    char* inputBuf = NULL;
    int intputLen = 0;
    int dstW;
    int dstH;

    inputBuf = (char*)malloc(DEFAULT_BUF_LEN);
    intputLen = DEFAULT_BUF_LEN;

    pPlayer = AWStreamPlayer::create(&decodeParam);
    pPlayer->startThread();

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
        printf("decode  process[%d/%d]\n", decodePos,fileSize);
        readTmpLen = ((fileSize - decodePos) < intputLen) ? (fileSize - decodePos) : intputLen;
        fread(inputBuf, 1, readTmpLen, inFile);
        nalLen = 0;
        ret = find264NALFragment((char*)inputBuf, readTmpLen, &nalLen);
        if (nalLen < 4)
        {
            printf("find264NALFragment fail \n");
            break;
        }

        //printf("fmt_sgl[%s-%d]decode %d bytes.\n",pixelExt[decodeParam.pixelFormat],data++,nalLen);
        ret = pPlayer->sendFrameToThread((unsigned char*)inputBuf, nalLen);
        // ret = pPlayer->decodeFrameDrectly((unsigned char *)inputBuf, nalLen);
        decodePos += nalLen;
        fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        usleep(30*1000);
    }

    printfArgs(decodeParam);

    pPlayer->stopThread();
    AWStreamPlayer::destroy(pPlayer);

    free(inputBuf);

    if (inFile)
        fclose(inFile);

}

int decodeStreamFile()
{
    printf("\n\n\n***************************\n");
    printf("***   decodeStreamFile    ***\n");
    printf("***************************\n\n\n");

    
    //static AWStreamPlayer* pPlayer = NULL;

    decodeParam.rotation = Angle_0;
    decodeParam.scaleRatio = ScaleNone;
    decodeParam.codecType = CODEC_H264;
    decodeParam.zorder = 2;

    CenterAlignment(720,1280);
    printf("reset panel:(%d,%d)[%d:%d]\n", decodeParam.dispX,decodeParam.dispY, decodeParam.dispW, decodeParam.dispH);
    printf("reset cvbs:(%d,%d)[%d:%d]\n", decodeParam.tvDispX,decodeParam.tvDispY, decodeParam.tvDispW, decodeParam.tvDispH);
    pPlayer = AWStreamPlayer::create(&decodeParam);
    pPlayer->startThread();

    int fileSize = 0;
    int readSize = 0;
    char path[60] = {0};
    char file[60] = {0};
    int fileLoop = 30;
    
    char* nalbuf = (char*)malloc(MAX_NAL_SIZE);
    for (int i = 0; i <= fileLoop; i++)
    {
        sprintf(file, "%s%03d.h264", "/tmp/input/", i);

        FILE* fp = NULL;
        fp = fopen(file, "rb");
        if (fp == NULL)
        {
            printf("open nal fail[%d]:%s\n", i, file);
            continue;
        }
        fseek(fp, 0L, SEEK_END);
        fileSize = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        if (fileSize > MAX_NAL_SIZE)
        {
            printf("error,decode buf not enough!\n");
            continue;
        }
        readSize = fread(nalbuf, fileSize, 1, fp);
        fclose(fp);

        pPlayer->sendFrameToThread((unsigned char*)nalbuf, fileSize);

        printf("read [%d] %s->%s read:%d tol:%d \n", i, testParam.intputFile,file, readSize, fileSize);
        usleep(15 * 1000);
    }

    free(nalbuf);
    pPlayer->stopThread();
    if(NULL!= pPlayer)
    {
        AWStreamPlayer::destroy(pPlayer);
        pPlayer = NULL;
    }

}
int h265Test()
{
    printf("\t\t ================================\n");
    printf("\t\t ====     CedarC  Decoder    ====\n");
    printf("\t\t ====        h265Test        ====\n");
    printf("\t\t ================================\n");

    decodeParam.codecType = CODEC_H265;
    decodeParam.dispX = 212;
    decodeParam.dispY = 124;
    decodeParam.dispW = 600;
    decodeParam.dispH = 351;
    decodeParam.rotation = Angle_0;
    strcpy((char*)testParam.intputFile,        "/tmp/input/tmp.h265");

    int ret = 0;
    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        printf("open inFile fail\n");
        return -1;
    }

    char* inputBuf = NULL;
    int intputLen = 0;
    int dstW;
    int dstH;

    inputBuf = (char*)malloc(DEFAULT_BUF_LEN);
    intputLen = DEFAULT_BUF_LEN;

    pPlayer = AWStreamPlayer::create(&decodeParam);
    pPlayer->startThread();

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
        //printf("decode process[%d/%d]\n", decodePos,fileSize);
        readTmpLen = ((fileSize - decodePos) < intputLen) ? (fileSize - decodePos) : intputLen;
        fread(inputBuf, 1, readTmpLen, inFile);
        nalLen = 0;
        ret = find264NALFragment((char*)inputBuf, readTmpLen, &nalLen);
        if (nalLen < 4)
        {
            printf("find264NALFragment fail \n");
            break;
        }

        //printf("fmt_sgl[%s-%d]decode %d bytes.\n",pixelExt[decodeParam.pixelFormat],data++,nalLen);
        ret = pPlayer->sendFrameToThread((unsigned char*)inputBuf, nalLen);
        decodePos += nalLen;
        fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        usleep(30*1000);
    }

    printfArgs(decodeParam);

    pPlayer->stopThread();
    AWStreamPlayer::destroy(pPlayer);

    free(inputBuf);

    if (inFile)
        fclose(inFile);

}
void mjpegTest()
{
    printf("\t\t ================================\n");
    printf("\t\t ====     CedarC  Decoder    ====\n");
    printf("\t\t ====     mjpegDecodeTest    ====\n");
    printf("\t\t ================================\n");

    int ret;
    int fileCount = 13;
    char inFilePath[60] = {0};
    int fileSize = 0;

    char* inputBuf = NULL;
    int inputLen = 0;

    decodeParam.dispX = 0;
    decodeParam.dispW = 1024;
    decodeParam.dispH = 600;
    decodeParam.rotation = Angle_0;
    decodeParam.codecType = CODEC_MJPEG;
//    decodeParam.srcW = 1920;
//    decodeParam.srcH = 1080;
//    int dstW = 0;
//    int dstH = 0;
//    getExpectSize(&dstW,&dstH);

    FILE* outputFile = NULL;
    FILE* inputFile = NULL;

    printf("disp:(%d,%d)[%d:%d]\n", decodeParam.dispX,decodeParam.dispY,decodeParam.dispW, decodeParam.dispH);
    pPlayer = AWStreamPlayer::create(&decodeParam);
    pPlayer->startThread();
    
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
        ret = pPlayer->sendFrameToThread((unsigned char*)inputBuf, fileSize);

        free(inputBuf);
        usleep(30*1000);

    }
    pPlayer->stopThread();

    AWStreamPlayer::destroy(pPlayer);

}

static void terminate(int sig_no)
{
	printf("Got signal %d, exiting ...\n", sig_no);

    pPlayer->stopThread();

    AWStreamPlayer::destroy(pPlayer);
	system("cat /sys/class/disp/disp/attr/sys");
    exit(1);
}

static void install_sig_handler(void)
{
	signal(SIGBUS, terminate);
	signal(SIGFPE, terminate);
	signal(SIGHUP, terminate);
	signal(SIGILL, terminate);
	signal(SIGKILL, terminate);
	signal(SIGINT, terminate);
	signal(SIGIOT, terminate);
	signal(SIGPIPE, terminate);
	signal(SIGQUIT, terminate);
	signal(SIGSEGV, terminate);
	signal(SIGSYS, terminate);
	signal(SIGTERM, terminate);
	signal(SIGTRAP, terminate);
	signal(SIGUSR1, terminate);
	signal(SIGUSR2, terminate);
}

//encoder -i /tmp/test/800x480x93_nv21.yuv -o /tmp/800x480x93_nv21  -p 1 -f 1 -t 0 1
int main(int argc, char** argv)
{
    printf("StreamPlayer test version:%s\n", MODULE_VERSION);
    /******** begin set the default encode param ********/
    memset(&decodeParam, 0, sizeof(decodeParam));
    memset(&testParam, 0, sizeof(testParam));

    decodeParam.srcW = 800;
    decodeParam.srcH = 480;
    decodeParam.dispW = SCREEN_W;
    decodeParam.dispH = SCREEN_H;
    
    decodeParam.tvOut = PAL;
    decodeParam.tvDispW = TV_W;
    decodeParam.tvDispH = TV_H(decodeParam.tvOut);
    
    decodeParam.rotation = Angle_0;
    decodeParam.scaleRatio = ScaleNone;
    decodeParam.codecType = CODEC_H264;
    decodeParam.zorder = 2;

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
        h264Test();
        mjpegTest();
        h265Test();
        printf("Test way:%d with %d times.\n\n\n\n", testParam.testWay, k);
    }

    return 0;
}


