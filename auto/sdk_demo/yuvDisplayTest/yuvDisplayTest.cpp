
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include "hwdisp2.h"

#include "memoryAdapter.h"
#include "sunxiMemInterface.h"

using namespace android;



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



#define DEFAULT_BUF_LEN   (500*1024)
#define MAX_NAL_SIZE  (1024*1024)

#define SCREEN_W    (1280)
#define SCREEN_H    (800)
#define TV_W        (720)
#define NTSC_H      (480)
#define PAL_H       (576)
#define TV_H(mode)  ((mode==NTSC)?NTSC_H:PAL_H)

typedef enum TV_MODE_
{
    NONE,
    NTSC,
    PAL,
} TV_MODE;

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

typedef struct PlayerParam_
{
    unsigned int dispX;         //default value 0.
    unsigned int dispY;         //default value 0.
    unsigned int dispW;         //default value 1024.
    unsigned int dispH;         //default value 600.

    unsigned int cropX;         //default value 0.
    unsigned int cropY;         //default value 0.
    unsigned int cropW;         //default value 1024.
    unsigned int cropH;         //default value 600.

    unsigned int chLID;         //default value 0.
    unsigned int lyrID;         //default value 0.
    unsigned int zorder;        //default value 2.

    unsigned int srcW;          //If you don't know, set 0.
    unsigned int srcH;          //If you don't know, set 0.

    int   codecType;      //default value h264.

    int scaleRatio;  //0, 1/2, 1/4, 1/8, 16bit fill with 0.
    int rotation;     //Clockwise,90 degree.

    TV_MODE tvOut;         //CVBS out: 0 none,1 NTSC,2 PAL.
    unsigned int tvDispX;       //default value 0.
    unsigned int tvDispY;       //default value 0.
    unsigned int tvDispW;       //default value 720.
    unsigned int tvDispH;       //default value 480.
    
} PlayerParam;

PlayerParam    decodeParam;
TestParm    testParam;
dma_mem_des_t mG2dMem;
HwDisplay* gVdecDisp = NULL;
int video_layer0 = -1;
int video_layer1 = -1;

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
    DISP_W,
    DISP_H,
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
        "-dw",  "--dispw",  DISP_W,
        "DISP_W"
    },
    {
        "-dh",  "--disph",  DISP_H,
        "DISP_H"
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
#ifdef BOGUS
    case DECODE_FORMAT:
        sscanf(value, "%32u", &decodeParam->codecType);
        break;
#endif /* BOGUS */
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
        sscanf(value, "%32u", &decodeParam->srcH);
        printf(" get dstH: %dp \n", decodeParam->srcH);
        break;
    case DISP_W:
        sscanf(value, "%32u", &decodeParam->dispW);
        printf(" get srcW: %dp \n", decodeParam->dispW);
        break;
    case DISP_H:
        sscanf(value, "%32u", &decodeParam->dispH);
        printf(" get dstH: %dp \n", decodeParam->dispH);
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
    printf("\t -i:%d\n", testParam.intputFile);
    printf("\t -s:[%dx%d]\n", decodeParam.srcW, decodeParam.srcH);
    printf("\t -o:%d\n", testParam.outputFile);

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
typedef enum PixelFmt
{
    PIXEL_YUV420SP,
    PIXEL_YVU420SP,
    PIXEL_YUV420P,
    PIXEL_YVU420P,
    PIXEL_YUV422SP,
    PIXEL_YVU422SP,
    PIXEL_YUV422P,
    PIXEL_YVU422P,
    PIXEL_YUYV422,
    PIXEL_UYVY422,
    PIXEL_YVYU422,
    PIXEL_VYUY422,
    PIXEL_ARGB,
    PIXEL_RGBA,
    PIXEL_ABGR,
    PIXEL_BGRA,
} PixelFmt;

int getFrameBitSize(int w,int h,PixelFmt fmt)
{
    int pixelNum = w*h;
    int frameBitSize = 0;
    switch(fmt)
    {
        case PIXEL_YUV420SP...PIXEL_YVU420P:
            frameBitSize = pixelNum*3/2;
            break;
        case PIXEL_YUV422SP...PIXEL_VYUY422:
            frameBitSize = pixelNum*2;
            break;
        case PIXEL_ARGB...PIXEL_BGRA:
            frameBitSize = pixelNum*4;
            break;
    }
    return frameBitSize;
}
void reallocDMA(int size)
{
    int ret;
    
    allocFree(MEM_TYPE_CDX_NEW, &mG2dMem, (void*)NULL);
    mG2dMem.size = size; //default use the display size.
    ret = allocAlloc(MEM_TYPE_CDX_NEW, &mG2dMem, NULL);
    if (ret < 0)
    {
        loge("allocAlloc failed\n");
        return;
    }
}
#define ALIGN(x,a) (((x) + (a-1)) & ~(a-1))
static const int PIXEL_FORMAT_NV21               = 5;
static const int SCR_ID_DEFAULT = 0;
static const int PIX_FMT_DEFAULT = PIXEL_FORMAT_NV21;
static const int DISP_PIXEL_FORMAT_DEFAULT = DISP_FORMAT_YUV420_SP_VUVU;
static const int SCR_ID_CVBS = 1;

static void openDisp()
{
    int ret;
    PlayerParam* mParam = &decodeParam;
    if (gVdecDisp == NULL)
        gVdecDisp = HwDisplay::getInstance();
    if ( (video_layer0 == -1))
    {
        struct view_info screen = {mParam->dispX, mParam->dispY, ALIGN(mParam->dispW,32), ALIGN(mParam->dispH,32)};
        video_layer0 = gVdecDisp->aut_hwd_layer_request(&screen,SCR_ID_DEFAULT, mParam->chLID, mParam->lyrID);
        CHECK_DISP_RETURN(video_layer0, "aut_hwd_layer_request");

        struct view_info crop;
        
        crop = {mParam->cropX,mParam->cropY,mParam->cropW,mParam->cropH};

        ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer0, &crop);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");
        
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);

        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer0, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer0, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

    }


    if ( (video_layer1 == -1)&&(decodeParam.tvOut))
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
        crop = {mParam->cropX,mParam->cropY,mParam->cropW,mParam->cropH};
        ret = gVdecDisp->aut_hwd_layer_set_rect(video_layer1, &crop);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_rect");
            
        logd("crop:(%d,%d)[%d:%d]\n",crop.x, crop.y,crop.w,crop.h);
        logd("screen:(%d,%d)[%d:%d]\n",screen.x, screen.y,screen.w,screen.h);
        ret = gVdecDisp->aut_hwd_layer_sufaceview(video_layer1, &screen);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_sufaceview");

        ret = gVdecDisp->aut_hwd_layer_set_zorder(video_layer1, mParam->zorder);
        CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_zorder");

	    ret = gVdecDisp->hwd_other_screen(SCR_ID_CVBS,DISP_OUTPUT_TYPE_TV,mode);
        CHECK_DISP_RETURN(ret, "hwd_other_screen");
       
    }
}
void showPicture_DE(unsigned int src_w,unsigned int src_h,unsigned long addr,int share_fd)
{
    int ret = 0;
    PlayerParam* mParam = &decodeParam;


    struct src_info src;

    src = {ALIGN(src_w,32), ALIGN(src_h,32), DISP_PIXEL_FORMAT_DEFAULT};
    ret = gVdecDisp->aut_hwd_layer_set_src(video_layer0, &src, (unsigned long)&addr,share_fd);
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
    
    ret = gVdecDisp->aut_hwd_layer_open(video_layer0);
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");
}
void showPicture_TV(unsigned int src_w,unsigned int src_h,unsigned long addr,int share_fd)
{
    //request ->setsrc->setrect(maybe)->open->render(maybe if disp addr every change)->close->releases
    PlayerParam* mParam = &decodeParam;
    int ret = 0;

    struct src_info src;

    src = {ALIGN(src_w,32), ALIGN(src_h,32), DISP_PIXEL_FORMAT_DEFAULT};
    ret = gVdecDisp->aut_hwd_layer_set_src(video_layer1, &src, (unsigned long)&addr,share_fd);
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_set_src");
    
    ret = gVdecDisp->aut_hwd_layer_open(video_layer1);
    CHECK_DISP_RETURN(ret, "aut_hwd_layer_open");

}
static void closeDisp()
{
    if(gVdecDisp)
    {
        system("cat /sys/class/disp/disp/attr/sys");

        if(video_layer0!=-1)
            gVdecDisp->aut_hwd_layer_release(video_layer0);
        if(video_layer1!=-1)
            gVdecDisp->aut_hwd_layer_release(video_layer1);

        gVdecDisp = NULL;
        video_layer0=-1;
        video_layer1=-1;
    }
	usleep(20*1000);
}

int nv21Test()
{
    printf("\t\t ================================\n");
    printf("\t\t ====        nv21Test        ====\n");
    printf("\t\t ================================\n");

    int freamLen = getFrameBitSize(decodeParam.srcW,decodeParam.srcH,PIXEL_YUV420SP);
    int ret = 0;
    FILE* inFile = fopen(testParam.intputFile, "r");
    if (inFile == NULL)
    {
        printf("open inFile fail\n");
        return -1;
    }

    int dstW;
    int dstH;

    int fileSize;
    fseek(inFile, 0L, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0L, SEEK_SET);

    int decodePos = 0;
    int count = 1;
    int data = 1;

    memset(&mG2dMem, 0, sizeof(dma_mem_des_t));
    int nRet = allocOpen(MEM_TYPE_DMA, &mG2dMem, NULL);
    if (nRet < 0)
    {
        loge("ion_alloc_open failed\n");
        return nRet;
    }

    //mG2dMem.share_data_fd;

    mG2dMem.size = freamLen;     //default use the display size.
    nRet = allocAlloc(MEM_TYPE_DMA, &mG2dMem, NULL);
    if (nRet < 0)
    {
        loge("allocAlloc failed\n");
        return nRet;
    }
    printf("mG2dMem.phy=%lx,aw_fd=%d\n",mG2dMem.phy,mG2dMem.ion_buffer.fd_data.aw_fd);
    while (decodePos < fileSize)
    {
        static int i=0;        if(++i>150)        	break;
        printf("decode process[%d/%d]\n", decodePos,fileSize);
        fread((void*)mG2dMem.vir, 1, freamLen, inFile);
        
        switch(((i/10)%2)==0)
        {
            case 0:
                showPicture_DE(decodeParam.srcW,decodeParam.srcH,0,mG2dMem.ion_buffer.fd_data.aw_fd);
                break;
            case 1:
                showPicture_DE(decodeParam.srcW,decodeParam.srcH,mG2dMem.phy,-1);
                break;
            default:
                showPicture_DE(decodeParam.srcW,decodeParam.srcH,0,mG2dMem.ion_buffer.fd_data.aw_fd);
                break;
        }
        if(decodeParam.tvOut)
        {
            showPicture_TV(decodeParam.srcW,decodeParam.srcH,mG2dMem.phy,-1);
        }
        decodePos += freamLen;
        fseek(inFile, decodePos, SEEK_SET); //go to the real decode position.
        usleep(30*1000);
    }

    printfArgs(decodeParam);


    if (inFile)
        fclose(inFile);

}
static void terminate(int sig_no)
{
	printf("Got signal %d, exiting ...\n", sig_no);
    closeDisp();
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
    install_sig_handler();
    /******** begin set the default encode param ********/
    memset(&decodeParam, 0, sizeof(decodeParam));
    memset(&testParam, 0, sizeof(testParam));

    decodeParam.srcW = 1280;
    decodeParam.srcH = 800;
    decodeParam.dispW = SCREEN_W;
    decodeParam.dispH = SCREEN_H;
    
    decodeParam.tvOut = PAL;
    decodeParam.tvDispW = TV_W;
    decodeParam.tvDispH = TV_H(decodeParam.tvOut);

    decodeParam.lyrID = 0;
    decodeParam.chLID= 0;
    
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
  
    openDisp();

    for (int k = 1; k <= testParam.testTimes; k++)
    {
        if (testParam.testWay == 0)
        {
            nv21Test();
        }
        else
        {
            
        }
        printf("Test %d times.\n\n\n\n", k);
    }
    closeDisp();
    printf("\n\n The End!\n\n ");
    return 0;
}


