//SDKLIB_TEST have already defined by Makefile

#define LOG_TAG "sdktest"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sdklog.h>
#include <time.h>
#include <cutils/log.h>

#include "posixTimer.h"

#include "aw_ini_parser.h"
#include "CameraFileCfg.h"

#include "DvrFactory.h"
#include "DvrRecordManager.h"

#include "moudle/Display.h"

#include "audio_hal.h"

#include "sdktest.h"
#define MAX_TEST_CAMERA_NUM 4

#define ENABLE_AUDIO_RECORD 0
#define ENABLE_VIDEO_RECORD 1
#define ENABLE_WATER_MARK   0
#define ENABLE_TAKE_PICTURE 0

typedef struct {
    int record;
    int preview;
} dvrstat_t;
dvrstat_t dvr_stat[MAX_TEST_CAMERA_NUM];
dvr_factory *dvrs[MAX_TEST_CAMERA_NUM];

//static FILE *pfileH264 = NULL;
static int camera_nums = 0;
static int running_aging_flag = 1;
static int camera_id_table[MAX_TEST_CAMERA_NUM] = { 0 };

timer_t  mTimerID;

void testStop(int signo)
{
    ALOGD("oops! stop!!! %d\n", signo);
    _exit(0);
}

/**************************************
Function:usr_datacb
Description:dataPtr has encoded data such as H264 or jpeg data
***************************************/
status_t usr_datacb(int32_t msgType, char *dataPtr, int dalen, void *user)
{
    dvr_factory *p_dvr = (dvr_factory *) user;
    return 0;
}

/**************************************
Function:
Description:
***************************************/
void usernotifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void *user)
{
    ALOGD("notifyCallback msgType:%x, data:%p", msgType, user);
    RecordCamera *p_dvr = (RecordCamera*) user;

    if ((msgType & CAMERA_MSG_ERROR) == CAMERA_MSG_ERROR) {
        ALOGD("msgType:CAMERA_MSG_ERROR, code:%d", ext1);
    }
    if ((msgType & CAMERA_MSG_DVR_NEW_FILE) == CAMERA_MSG_DVR_NEW_FILE) {
        //dvr_factory *p_dvr = (dvr_factory *) user;
        ALOGD("CameraID[%d]: msgType:CAMERA_MSG_DVR_NEW_FILE", p_dvr->mCameraId);
    }

    if ((msgType & CAMERA_MSG_DVR_STORE_ERR) == CAMERA_MSG_DVR_STORE_ERR) {
        ALOGD("CameraID[%d]: msgType:CAMERA_MSG_DVR_STORE_ERR", p_dvr->mCameraId);
        //dvr_factory *p_dvr = (dvr_factory *) user;
        p_dvr->storage_state = 0;
    }
    return ;
}

/**************************************
Function:
Description:
***************************************/
void userdataCallback(int32_t msgType, char *dataPtr, camera_frame_metadata_t * metadata,void *user)
{
    int i;

    dvr_factory *p_dvr = (dvr_factory *) user;
    V4L2BUF_t *pv4l2_buf = (V4L2BUF_t *) dataPtr;

    if (CAMERA_MSG_PREVIEW_FRAME == msgType) {

    }
    return ;
}

/**************************************
Function:
Description:data is from V4l2 captureThread,it's NV21 format YUV
***************************************/
void userdataCallbackTimestamp(nsecs_t timestamp, int32_t msgType, char *dataPtr, void *user)
{
    V4L2BUF_t *pbuf = (V4L2BUF_t *) (dataPtr);
}

void testaudiocb(int32_t msgType, nsecs_t timestamp, int card, int device,
                                   char *dataPtr, int dsize,
                                   void* user)
{
    ALOGD("testaudiocb date:%p, len:%d, usrp:%p",dataPtr, dsize, user);
}

static void terminate(int sig_no)
{
    ALOGD("Got signal %d, exiting ...\n", sig_no);
    for (int i = 0; i < camera_nums; i++) {
        if (dvr_stat[i].preview == 1) {
            dvrs[i]->stopPriview();
            dvr_stat[i].preview = 0;
        }

        if (dvr_stat[i].record == 1) {
            dvr_stat[i].record = 0;
            dvrs[i]->stopRecord();
        }
        dvrs[i]->stop();
        delete dvrs[i];
        dvrs[i] = NULL;
    }
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

void suspend_timer_cb(sigval_t sig)
{
    ALOGD("into suspend_timer_cb");

    int i = 0;
    int ret = 0;
    struct view_info vv = { 0, 0, 1280, 800 };
    dvr_factory *tmp_dvr;

    for (i = 0; i < camera_nums; i++) {
        if (dvr_stat[i].preview == 1) {
            ret = dvrs[i]->stopPriview();
            dvr_stat[i].preview = 0;
        }

        if (dvr_stat[i].record == 1) {
            dvr_stat[i].record = 0;
            dvrs[i]->stopRecord();
        }
        sleep(2);
        ret = dvrs[i]->stop();
#if ENABLE_AUDIO_RECORD
        dvrs[i]->mAudioCap->releaseAudioSource(dvrs[i]->mAudioHdl);
#endif
#if ENABLE_WATER_MARK
        dvrs[i]->disableWaterMark();
#endif
        sleep(2);
        delete dvrs[i];
        dvrs[i] = NULL;
    }

    //system("cat /sys/class/disp/disp/attr/sys");
    sleep(2);
    stopTimer(mTimerID);

    system("echo mem > /sys/power/state");

    for (i = 0; i < camera_nums; i++) {
        dvr_stat[i].record = 0;
        dvr_stat[i].preview = 0;

        dvrs[i] = new dvr_factory(camera_id_table[i]);
        tmp_dvr = dvrs[i];

        tmp_dvr->SetDataCB(usr_datacb, tmp_dvr);
        tmp_dvr->setCallbacks(usernotifyCallback, userdataCallback, userdataCallbackTimestamp, tmp_dvr);

#if ENABLE_VIDEO_RECORD
        ret = dvrs[i]->recordInit();
        if (ret != 0) {
            ALOGE("pdvr->recordInit error\n");
            //return -1;
        }
        dvrs[i]->startRecord();
        dvr_stat[i].record = 1;
#endif
    }

    for (i = 0; i < camera_nums; i++) {
        ret = dvrs[i]->start();
        if (ret < 0) {
            ALOGE("dvrs[%d]->start() error\n",i);
        }
        sleep(2);
    }

    DisplayInit(DISP_GET_CONFIG, dvrs[0]->mCameraId);
    //while(1)
    {
        for (i = 0; i < camera_nums; i++) {
#if ENABLE_WATER_MARK
            char bufname[512];
            dvrs[i]->enableWaterMark();
            sprintf(bufname,"64,64,0,64,150,T113 SDK,64,250,ALLWINNER");
            dvrs[i]->setWaterMarkMultiple(bufname);
#endif
            ret = dvrs[i]->startPriview(vv);
            dvr_stat[i].preview = 1;
            sleep(5);
            //dvrs[i]->stopPriview();
            //dvr_stat[i].preview = 0;
            //sleep(3);
        }
    }
}

void argsAnalysis(int argc, char *argv[])
{
    //======Analysis argv=========
    ALOGD("argc num:%d", argc);
    int i = 0, j = 0;
    int suspend_delay_second = 0;

    if (argc > 2) {
        camera_nums = atoi(argv[1]);
        if ((camera_nums > MAX_TEST_CAMERA_NUM) || (camera_nums < 1)) {
            ALOGD("camera_nums:%d is not support, max support camera numbers:%d", camera_nums, MAX_TEST_CAMERA_NUM);
            exit(-1);
        }
        if (argc < camera_nums + 2) {
            ALOGD("camera id table is invalid\n");
            exit(-1);
        }
        for (i = 0; i < camera_nums; i++) {
            camera_id_table[i] = atoi(argv[i + 2]);
        }
        for (i = 0; i < camera_nums; i++) {
            // 4in1, T113 not support
            if (camera_id_table[i] == 360) {
                for (j = 0; j < camera_nums; j++) {
                    if((camera_id_table[j] == 2) || (camera_id_table[j] == 3)
                        || (camera_id_table[j] == 4) || (camera_id_table[j] == 5)) {
                        ALOGD("when use 4in1 camera, can not use camera%d", camera_id_table[j]);
                        exit(-1);
                    }
                }
            }
            // 2in1, todo
            if (camera_id_table[i] == 180) {
                for (j = 0; j < camera_nums; j++) {
                    if((camera_id_table[j] == 4) || (camera_id_table[j] == 5)) {
                        ALOGD("when use 2in1 camera, can not use camera%d",camera_id_table[j]);
                        exit(-1);
                    }
                }
            }
        }

        if (argc > (camera_nums + 2)) {
            if (argv[camera_nums + 2] && (strcmp(argv[camera_nums+2], "t") == 0)) {
                running_aging_flag = 1;
                ALOGD("sdktest set to always running");
            }
        }

        if (argc > (camera_nums + 3)) {
            suspend_delay_second = atoi(argv[camera_nums + 3]);
            ALOGD("suspend_delay_second set to %ds", suspend_delay_second);
            if (suspend_delay_second > 0) {
                if (createTimer(NULL, &mTimerID, suspend_timer_cb) == 0) {
                    setPeriodTimer(suspend_delay_second, 0, mTimerID);
                } else {
                    ALOGD("[suspend] createTimer fail");
                }
            }
        }
        ALOGD("argsAnalysis successed!!");
    } else {
        printf("---------------------------sdktest---------------------------\n"
            "camera id : 0,1\n"
            "arg1 : N : camera number \n"
            "arg2->arg(N+1) : camera id : /dev/video0 ... /dev/videoN \n"
            "arg(N+2) : 't' : runing always flag \n"
            "arg(N+3) : m : suspend delay time(s) \n\n"
            "for example:\n");
        printf("/sdktest 1 0          //for test /dev/video0 \n");
        printf("/sdktest 1 0 t        //for test /dev/video0 and running always \n");
        printf("/sdktest 1 0 t 99     //suspend after 99 seconds \n");
        printf("---------------------------sdktest---------------------------\n");
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    //setenv("MALLOC_TRACE", "/tmp/output", 1);
    //mtrace();
    sigset_t set1;
    sigemptyset(&set1);
    //block SIGIO signal in main thread,SIGIO will wakeup sleep
    sigaddset(&set1, SIGIO);
    pthread_sigmask(SIG_BLOCK, &set1, NULL);
    sigpending(&set1);
    signal(SIGINT, testStop);
    install_sig_handler();

    sdk_log_setlevel(6);
    ALOGD("sdktest ver:%s", MODULE_VERSION);

    int ret = 0;
    int i;

    //======moudle init===========
    for (i = 0; i < MAX_TEST_CAMERA_NUM; i++) {
        camera_id_table[i] = -1;
    }

    //camera_id_table[i] will be: 0/1
    argsAnalysis(argc, argv);

    //======start record===========
#if ENABLE_AUDIO_RECORD
    sp < AudioCapThread > audiocap = new AudioCapThread();
#endif
    DvrRecordManagerInit();

    dvr_factory *tmp_dvr;
    for (i = 0; i < camera_nums; i++) {
        dvr_stat[i].record = 0;
        dvr_stat[i].preview = 0;
        ALOGD("start init cameraID:%d", camera_id_table[i]);
        if (360 == camera_id_table[i]) {
            ALOGD("Camera[%d] is not support!", camera_id_table[i]);
            return -1;
        }
        dvrs[i] = new dvr_factory(camera_id_table[i]);
        tmp_dvr = dvrs[i];
        tmp_dvr->SetDataCB(usr_datacb, tmp_dvr);
        tmp_dvr->setCallbacks(usernotifyCallback, userdataCallback, userdataCallbackTimestamp, tmp_dvr);

#if ENABLE_AUDIO_RECORD
        int hdl= audiocap->reqAudioSource(tmp_dvr->__dvr_audio_data_cb_timestamp,(void *)tmp_dvr);
        tmp_dvr->setAudioOps(audiocap, hdl);
#endif
#if ENABLE_VIDEO_RECORD
        ret = tmp_dvr->recordInit();
        if (ret != 0) {
            ALOGE("dvrs[%d]->recordInit error", i);
            return -1;
        } else {
            ALOGD("dvrs[%d]->recordInit success", i);
        }
        tmp_dvr->startRecord();
        dvr_stat[i].record = 1;
#endif
    }

    for (i = 0; i < camera_nums; i++) {
        ret = dvrs[i]->start();
        if (ret < 0) {
            ALOGE("dvrs[%d]->start() error", i);
            return -1;
        }
    }

#if ENABLE_TAKE_PICTURE
    //======takepicture=======
    dvrs[0]->takePicture();
#endif

    //======start preview===========
    DisplayInit(DISP_GET_CONFIG, dvrs[0]->mCameraId);

    struct view_info vv = { 0, 0, 1024, 600 };
    int recordcnt = 0;

    for (i = 0; i < 1; i++) {
#if ENABLE_WATER_MARK
        char bufname[512];
        dvrs[i]->enableWaterMark();
        sprintf(bufname,"64,64,0,64,150,T113 SDK,64,250,ALLWINNER");
        dvrs[i]->setWaterMarkMultiple(bufname);
#endif
        ret = dvrs[i]->startPriview(vv);
        if (ret != 0) {
            ALOGE("dvrs[%d]->startPreview error", i);
            return -1;
        }
        dvr_stat[i].preview = 1;
        sleep(60);
        while (running_aging_flag == 1) {
            ALOGD("running aging testing...");
            sleep(60);
        }
#if ENABLE_WATER_MARK
        ALOGD("disable watermark");
        dvrs[i]->disableWaterMark();
#endif
    }

    //======stop and exit===========
    ALOGD("stopPriview and stopRecord\n");
    for (i = 0; i < camera_nums; i++) {
        if (dvr_stat[i].preview == 1) {
            ret = dvrs[i]->stopPriview();
            dvr_stat[i].preview = 0;
        }

        if (dvr_stat[i].record == 1) {
            dvr_stat[i].record = 0;
            dvrs[i]->stopRecord();
        }
        sleep(1);
        ret = dvrs[i]->stop();
#if ENABLE_AUDIO_RECORD
        dvrs[i]->mAudioCap->releaseAudioSource(dvrs[i]->mAudioHdl);
#endif
    }

    sleep(1);
    for (i = 0; i < camera_nums; i++) {
        delete dvrs[i];
        dvrs[i] = NULL;
    }
    sleep(5);

#if ENABLE_AUDIO_RECORD
    audiocap->stopAudio();
#endif

    ALOGD("----------test---------- end\n");
//    muntrace();
    return 0;
}
