/***************************************
FileName:
Copyright:
Author:
Description:
***************************************/

#define LOG_TAG "RecordCamera"
#include <sdklog.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/time.h>

#include <sys/syscall.h>

#include "audio_hal.h"
#include "CdxMuxer.h"
#include "posixTimer.h"
#include "CameraFileCfg.h"
#include "StorageManager.h"
#include "MuxerWriter.h"

#include "RecordCamera.h"
#include "DvrRecordManager.h"
/************Macro*********************/

#define ENABLE_PRINT_ENCODE_TIME 0

#define _ENCODER_TIME_

#ifdef _ENCODER_TIME_
static long long GetNowUs()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000 + now.tv_usec;
}
#endif

#define gettid() syscall(__NR_gettid)

#define PIC_NAME_LEN    128
#define MAX_PIC_NUM     512
#define LOCK_VIDEO      "lockVideo"
#define PARK_MONITOR    "parkMonitor"
#define CAMERA_360_ID   9

char g_PicPath[MAX_SUPPORT_CAM][PIC_NAME_LEN] = { };   //mod lss
char g_NamePic[MAX_SUPPORT_CAM][CM_MAX_PICTURE_NUM][PIC_NAME_LEN] = { };

char *pVideoPath[MAX_SUPPORT_CAM]={
    "frontVideo0",
    "rearVideo1",
    // "leftVideo2",
    // "rightVideo3",
    // "frontVideoCvbs4",
    // "rearVideoCvbs5",
    // "leftVideoCvbs6",
    // "rightVideoCvbs7",    
    // "4ChVideoCvbs8",
    // "4ChVideoCsi9",
};

char *pPicPath[MAX_SUPPORT_CAM] = {
    "frontPicture0",
    "rearPicture1",
    // "leftPicture2",
    // "rightPicture3",
    // "frontPictureCvbs4",
    // "rearPictureCvbs5",
    // "leftPictureCvbs6",
    // "rightPictureCvbs7",
    // "4ChPictureCvbs8",
    // "4ChPictureCsi9",
};

char *pSuffix[MAX_SUPPORT_CAM] = {
    "front", "rear"};
    //  "left", "right",
    // "frontCvbs", "rearCvbs", "leftCvbs", "rightCvbs",
    // "4ChCvbs", "4ChCsi"};


/************Variable******************/

/************Function******************/

/**************************************
Function:
Description:
***************************************/
RecordCamera::RecordCamera(int cameraId)
  : mux(NULL), 
    usrDatCb(NULL),
    mCbUserDat(NULL),
    mNotifyCb(NULL),
    mCbUser(NULL),
    mCameraId(cameraId),
    mCurRecordFileNameType(CurRecordFileNameType_NORMAL),
    mCurRecordStat(RecordStat_NORMAL),
    mNeedThumbpic(0),
    mAudioflag(0),
    mAudioHdl(0),
    mCurRecordLockOps(LockOps_CreateNewAfterClose)
{
    ALOGV("RecordCamera construct");
    istestrtsp = 0;
    storage_state = 0;
    fs_mode = FSWRITEMODE_DIRECT;
    mNeedNewFile = 0;
    FileNewStampBase = 0;
    mCurRecordPos = 0;
    mTimeridVaild = 0;
    pRecVideoEnc = NULL;
    mNeedExit =false;
    rtsp_started = 0;
    can_deliver_rtspdata = 0;

    iMaxPicNum = MAX_PIC_NUM;
    ppSuffix = pSuffix;
    pFileManger = &gFilemanger;
    pfileLock = &gfileLock;

    OSAL_QueueCreate(&mQueueBufferRecordFile, 96);
    // init record thread
    pthread_mutex_init(&mRecordFileMutex, NULL);
    pthread_cond_init(&mRecordFileCond, NULL);

    recordStat = RECORD_STATE_PAUSED;
    mRecordFileThread = new RecordFileThread(this);
    mRecordFileThread->startThread();
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::enc_parm_destory(void)
{
    dma_mem_des_t setparmMemops;
    if (rtsp_enc_baseConfig.memops) {
        memset(&setparmMemops, 0, sizeof(dma_mem_des_t));
        setparmMemops.ops = rec_enc_baseConfig.memops;
        int ret = allocClose(MEM_TYPE_CDX_NEW, &setparmMemops, NULL);
        if (ret < 0) {
            ALOGE("enc_parm_destory:allocClose failed");
            return -1;
        }
    }
    return 0;
}

RecordCamera::~RecordCamera()
{
    F_LOG;

    if (mRecordFileThread != NULL) {
        mRecordFileThread->stopThread();
        mNeedExit = true;
        pthread_mutex_lock(&mRecordFileMutex);
        pthread_cond_signal(&mRecordFileCond);
        usleep(300000);
        pthread_cond_signal(&mRecordFileCond);//avoid block miss singal,i found that when sync() in record thread,singal miss
        ALOGV("singal record file exit");
        pthread_mutex_unlock(&mRecordFileMutex);
        mRecordFileThread->join();
        mRecordFileThread.clear();
        mRecordFileThread = 0;
    }

    pthread_mutex_destroy(&mRecordFileMutex);
    pthread_cond_destroy(&mRecordFileCond);

    OSAL_QueueTerminate(&mQueueBufferRecordFile);

    enc_parm_destory();
}

/**************************************
Function:
Description:
***************************************/
//int 1 for normal  2:lock  3:save
int RecordCamera::setCurRecordFileLock()
{
    mCurRecordFileNameType = CurRecordFileNameType_LOCK;
    return 0;
}

int RecordCamera::setCurRecordFileSave()
{
    mCurRecordFileNameType = CurRecordFileNameType_SAVE;
    return 0;
}

int RecordCamera::setCurRecordFileNormal()
{
    mCurRecordFileNameType = CurRecordFileNameType_NORMAL;
    return 0;
}

int RecordCamera::setCurRecordLockOps(int ops)
{
//#define LockOps_CreateNewNow 1
//#define LockOps_CreateNewAfterClose 2
    if ((ops != LockOps_CreateNewNow) && (ops != LockOps_CreateNewNow))
        return -1;
    mCurRecordLockOps = ops;
    return 0;
}

//for 1 :normal for 2:stop car record
int RecordCamera::setCurRecordStat(int stat)
{
    //need check parm
    mCurRecordStat = stat;
}

void RecordCamera::setCallbacks(notify_callback notify_cb, void *user)
{
    mNotifyCb = notify_cb;
    mCbUser = user;
}

status_t RecordCamera::audioRecMuxerCb(int32_t msgType,
                                char *dataPtr,int dalen,
                                void *user)
{
    RecordCamera*p=(RecordCamera*)user;

    int ret = OSAL_Queue(&p->mQueueBufferRecordFile, dataPtr);
    if (ret != 0) {
        pthread_mutex_lock(&p->mRecordFileMutex);
        pthread_cond_signal(&p->mRecordFileCond);
        pthread_mutex_unlock(&p->mRecordFileMutex);
        return -1;
    }
    //media_msg_t *pkmsg=(media_msg_t *)dataPtr;
    //CdxMuxerPacketT *ppkt=(CdxMuxerPacketT *)&pkmsg->mesg_data[0];

    //ALOGD("%s usr=%p msg=%p pkbuf=%p cid=%d",__FUNCTION__,p,dataPtr,ppkt->buf,p->mCameraId);
    pthread_mutex_lock(&p->mRecordFileMutex);
    pthread_cond_signal(&p->mRecordFileCond);
    pthread_mutex_unlock(&p->mRecordFileMutex);
    return 0;
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::videoEncParmInit(int sw, int sh, int dw, int dh, unsigned int bitrate, int framerate,
                               VENC_CODEC_TYPE type,VENC_PIXEL_FMT pix)
{
    F_LOG;
    //Mutex::Autolock locker(&mObjectLock);
    memset(&rec_enc_baseConfig,0,sizeof(VencBaseConfig ));
    memset(&encode_param, 0, sizeof(encode_param));
    encode_param.src_width = sw;
    encode_param.src_height = sh;
    encode_param.dst_width = dw;
    encode_param.dst_height = dh;
    encode_param.bit_rate = bitrate * 1024 * 1024;
    encode_param.frame_rate = framerate;
    encode_param.maxKeyFrame = framerate;
    encode_param.encode_format = type;
    encode_param.encode_frame_num = 0;

    rec_enc_baseConfig.eInputFormat = pix;
    setVideoEncParm();

    return 0;

}

void RecordCamera::setMaxKeyFrameInterval(int interval)
{
    VideoEncSetParameter(pRecVideoEnc, VENC_IndexParamMaxKeyInterval, &interval);
}

void RecordCamera::setForceKeyFrame(bool force)
{
    int value = force;
    VideoEncSetParameter(pRecVideoEnc, VENC_IndexParamMaxKeyInterval, &value);
}

int RecordCamera::videoEncDeinit()
{
    F_LOG;
    //Mutex::Autolock locker(&mObjectLock);
#ifdef USE_CDX_LOWLEVEL_API
    if (pRecVideoEnc != NULL) {

        VideoEncoderReset(pRecVideoEnc);
        int result = VideoEncUnInit(pRecVideoEnc);
        if (result != 0) {
            ALOGE("VideoEncUnInit error result=%d...", result);
        }

        VideoEncDestroy(pRecVideoEnc);

        pRecVideoEnc = NULL;
    }
#if 0
    if (rec_enc_baseConfig.memops) {
        dma_mem_des_t enc_de_Memops;
        memset(&enc_de_Memops, 0, sizeof(dma_mem_des_t));
        enc_de_Memops.ops = rec_enc_baseConfig.memops;
        allocClose(MEM_TYPE_CDX_NEW,&enc_de_Memops, NULL);
        rec_enc_baseConfig.memops = NULL;
    }
#endif
#endif

    return 0;
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::generatepicFile()
{
    int fd;
    //int i;
    struct tm *tm = NULL;

    Mutex::Autolock locker(pfileLock);
    file_status_t *p = pFileManger;

    char buf[128] = { 0 };
    memset(buf, 0x00, sizeof(buf));

    int idx = 0;
    idx = config_get_normalpicidx(mCameraId);

    int l32_CameraId = (360 == mCameraId) ? CAMERA_360_ID : mCameraId;

    if (idx > iMaxPicNum) {
        ALOGI("pic file idx %d lager than max_idx %d)", idx, iMaxPicNum);
        idx = 0;
    }

    config_set_normalpicidx(mCameraId, idx + 1);
    //remove the old idx file
    if (strlen(g_NamePic[l32_CameraId][idx])) {
        remove(g_NamePic[l32_CameraId][idx]);
        ALOGI("rm pic file (%s cur_file_idx %d)", g_NamePic[l32_CameraId][idx], idx);
    }
    ALOGV("%s %d", __FUNCTION__, __LINE__);
    time_t now = getDateTime(&tm);

    snprintf(buf, 127, "%s%s%d-%04d%02d%02d_%02d%02d%02d_%s%s", g_PicPath[l32_CameraId], "/",
             idx, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min,
             tm->tm_sec, ppSuffix[l32_CameraId], EXT_PIC);

    fd = open(buf, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        ALOGE("failed to open file '%s'!!", buf);
        return RET_IO_OPEN_FILE;
    }

    //save the new idx name
    sprintf(g_NamePic[l32_CameraId][idx], "%s", buf);
    ALOGW("PictureName:%s", buf);

    return fd;
}
/**************************************
Function:
Description:
***************************************/
int RecordCamera::generateThumbFile()
{

    int fd;
    //struct tm *tm = NULL;

    file_status_t *p = pFileManger;;

    char buf[128] = { 0 };
    buf[127] = '\0';

    int l32_CameraId = (360 == mCameraId) ? CAMERA_360_ID : mCameraId;

    ALOGV("%s %d", __FUNCTION__, __LINE__);

    sprintf(buf, "%s%s%s%d%c%s%s%s", p->cur_filedir[l32_CameraId], "/", CM_THUMB_DIR,
            p->cur_file_idx, '-', "thumb_", ppSuffix[l32_CameraId], EXT_PIC);

    //ALOGW("generateThumbFile %s",buf);
    fd = open(buf, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        ALOGE("failed to open file '%s'!!", buf);
        return RET_IO_OPEN_FILE;
    }
    return fd;
}
/**************************************
Function:
Description:
***************************************/
int RecordCamera::savePicture(void *data, int size, int fd)
{
    int bytes_write = 0;
    int bytes_to_write = size;
    void *ptr = data;

    ALOGW("savePciture, size is %d", size);

    while ((bytes_write = write(fd, ptr, bytes_to_write))) {
        if ((bytes_write == -1) && (errno != EINTR)) {
            ALOGE("wirte error: %s", strerror(errno));
            break;
        } else if (bytes_write == bytes_to_write) {
            break;
        } else if (bytes_write > 0) {
            ptr = (void *) ((char *) ptr + bytes_write);
            bytes_to_write -= bytes_write;
        }
    }
    if (bytes_write == -1) {
        ALOGE("save picture failed: %s", strerror(errno));
        return -1;
    }

    fsync(fd);
    close(fd);

    return 0;
}
/**************************************
Function:
Description:
***************************************/
int RecordCamera::setDuration(int sec)
{
    if (sec == 0)
        return -1;
    Mutex::Autolock locker(&mObjectLock);
    ALOGV("setDuration %d", sec);
    mDuration = sec;
    return 0;

}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::getDuration()
{
    return mDuration;
}

/**************************************
Function:
Description:
***************************************/
void RecordCamera::dataCallback(int32_t msgType,
                               char *dataPtr, camera_frame_metadata_t * metadata, void *user)
{
    if (msgType & CAMERA_MSG_COMPRESSED_IMAGE) {
        ALOGV("store pic us time %p us size=%d", dataPtr, metadata->number_of_faces);
        long long time1 = GetNowUs();
        int fd = generatepicFile();
        ALOGV("store pic us time us fd=%d", fd);
        int len = metadata->number_of_faces;
#ifdef FILE_HOLES_SYS_SUPPORT
        if (fallocate(fd, FALLOC_FL_KEEP_SIZE, 0, ALIGN_4K(len))) {
            fprintf(stderr, "fallocate line %d len=%d %s", __LINE__, ALIGN_4K(len),
                    strerror(errno));
        }
        fsync(fd);
#endif
        savePicture(dataPtr, len, fd);
        long long time2 = GetNowUs();
        ALOGV("store pic us time %lld us len=%d", time2 - time1, len);
        //__notify_cb(CAMERA_MSG_COMPRESSED_IMAGE, ret, len, mCbUser);  //can i del this?

    }
}

/**************************************
Function:
Description:
***************************************/
#ifndef V4L2_PIX_FMT_H264
#define v4l2_fourcc(a, b, c, d)\
    ((__u32)(a) | ((__u32)(b) << 8) | ((__u32)(c) << 16) | ((__u32)(d) << 24))
#define V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#endif

status_t RecordCamera::dataCallbackTimestamp(nsecs_t timestamp,
                                            int32_t msgType, char *dataPtr, void *user)
{
    int ret=0;
    int isKeyframe = 0;
    CdxMuxerPacketT pkt;

    memset(&pkt, 0, sizeof(CdxMuxerPacketT));
    if (can_deliver_rtspdata) {
        //CdxMuxerPacketT *pt=push_ringbuf(&rtspQbuf);
        encode_rtsp((V4L2BUF_t *) dataPtr, NULL, NULL, user, 0);
    }

    if (mCaptureFmt != V4L2_PIX_FMT_H264) {
#if ENABLE_PRINT_ENCODE_TIME
        struct timeval lRunTimeEnd;
        gettimeofday(&lRunTimeEnd, NULL);
        long long time1 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
        long long time2 = 0;
        long long time3 = 0 ;
#endif

        ret = encode((V4L2BUF_t *) dataPtr, (char *) &pkt, NULL, user);
        if (ret < 0) {
            ALOGW("encode fail");
            return -1;
        }
        if (ret == 1)
            isKeyframe = 1;

#if ENABLE_PRINT_ENCODE_TIME
        gettimeofday(&lRunTimeEnd, NULL);
        time2 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
        time3 = time2 - time1 ;
        ALOGV("encode use runtime %lldus(%lldms)",time3,time3/1000);
        time1 = time2;
#endif
    }

    if (usrDatCb != NULL) {
        if (0 == sps_pps_flag) {
            sps_pps_flag = 1;
            VencHeaderData sps_pps_data;

            VideoEncGetParameter(pRecVideoEnc, VENC_IndexParamH264SPSPPS, &sps_pps_data);
            //fwrite(sps_pps_data.pBuffer, 1, sps_pps_data.nLength, pfileH264);
            usrDatCb(0, (char *) sps_pps_data.pBuffer, sps_pps_data.nLength, mCbUserDat); //up to app
        }

        usrDatCb(0, (char *) pkt.buf, pkt.buflen, mCbUserDat); //up to app
    }

    media_msg_t *mesg = NULL;

    mesg = (media_msg_t *) malloc(sizeof(media_msg_t));

    if (mesg == NULL) {
        ALOGE("encode fail");
        return -1;
    }

    memcpy(&mesg->mesg_data[0], &pkt, sizeof(CdxMuxerPacketT));
    //mesg->mesg_type = CDX_MEDIA_AUDIO;
    mesg->timestamp = pkt.pts;
    mesg->user = user;
    mesg->mesg_len = sizeof(CdxMuxerPacketT);

    mesg->mesg_type = msgType;
    mesg->iskeyframe = isKeyframe;

    ret = OSAL_Queue(&mQueueBufferRecordFile, mesg);
    if (ret != 0) {
        mVideoRecordQueueErr++;
        ALOGW("Carmera[%d] record queue full  mVideoRecordQueueErr:%d", mCameraId,mVideoRecordQueueErr);
        free(pkt.buf);
        free(mesg);
        // pthread_mutex_lock(&mRecordFileMutex);
        // pthread_cond_signal(&mRecordFileCond);
        // pthread_mutex_unlock(&mRecordFileMutex);
        return FAILED_TRANSACTION;

    }

    pthread_mutex_lock(&mRecordFileMutex);
    pthread_cond_signal(&mRecordFileCond);
    pthread_mutex_unlock(&mRecordFileMutex);
    //ALOGV("record queue inform a pack");

    return NO_ERROR;
}


/**************************************
Function:
Description:
***************************************/
int RecordCamera::start()
{
    F_LOG;
    Mutex::Autolock locker(&mObjectLock);

    pthread_mutex_lock(&mRecordFileMutex);
    // singal to start capture thread
    recordStat = RECORD_STATE_STARTED;

    pthread_cond_signal(&mRecordFileCond);
    pthread_mutex_unlock(&mRecordFileMutex);
    return 0;


}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::stop()
{
    Mutex::Autolock locker(&mObjectLock);
    if (rtsp_started) {
        stop_rtsp();
        rtsp_started = 0;
    }
    pthread_mutex_lock(&mRecordFileMutex);

    if (recordStat == RECORD_STATE_NULL) {
        ALOGE("error state of capture thread, %s", __FUNCTION__);
        pthread_mutex_unlock(&mRecordFileMutex);
        return EINVAL;
    }

    if (recordStat == RECORD_STATE_PAUSED) {
        ALOGW("RecordCamera::stop capture thread has already paused");
        pthread_mutex_unlock(&mRecordFileMutex);
        return NO_ERROR;
    }

    recordStat = RECORD_STATE_PAUSED;
    pthread_cond_signal(&mRecordFileCond);

    pthread_mutex_unlock(&mRecordFileMutex);

    return NO_ERROR;

}


/**************************************
Function:
Description:
***************************************/
int RecordCamera::startRecord()
{
    Mutex::Autolock locker(&mObjectLock);
    F_LOG;
    encode_param.encode_frame_num = 0;
    mDvrWriteFrameNum = 0;

    char bufname[512];

    memset(bufname, 0, 512);
    config_get_curfiledir(mCameraId, bufname);
    bool rt = false;
    if (bufname[0] == 0) {
        ALOGV("#######find the pat is NULL");
        rt = initFileListDir(MOUNT_POINT);
    } else {
        rt = initFileListDir(bufname);
    }

    if (rt) {
        mNeedNewFile = 1;
        pthread_mutex_lock(&mRecordFileMutex);

        if (recordStat == RECORD_STATE_NULL) {
            ALOGE("startRecord error state of capture thread, %s", __FUNCTION__);
            pthread_mutex_unlock(&mRecordFileMutex);
            //return EINVAL;
        }

        if (recordStat == RECORD_STATE_STARTED) {
            ALOGW("startRecord capture thread has already started");
            pthread_mutex_unlock(&mRecordFileMutex);
            //return NO_ERROR;
        }
        // singal to start capture thread
        recordStat = RECORD_STATE_STARTED;
        pthread_cond_signal(&mRecordFileCond);
        pthread_mutex_unlock(&mRecordFileMutex);

        mVideoRecordQueueErr = 0;
    } else {
        return INVALID_OPERATION;
    }

    return NO_ERROR;
}
/**************************************
Function:
Description:
***************************************/

int RecordCamera::stopRecord()
{
    F_LOG;
    pthread_mutex_lock(&mRecordFileMutex);

    if (recordStat == RECORD_STATE_NULL) {
       ALOGE("error state of capture thread, %s", __FUNCTION__);
       pthread_mutex_unlock(&mRecordFileMutex);
       return EINVAL;
    }

    if (recordStat == RECORD_STATE_PAUSED) {
       ALOGW("stopRecord capture thread has already paused");
       pthread_mutex_unlock(&mRecordFileMutex);
       return NO_ERROR;
    }

    recordStat = RECORD_STATE_PAUSED;
    pthread_cond_signal(&mRecordFileCond);
    pthread_mutex_unlock(&mRecordFileMutex);

    encode_param.encode_frame_num = 0;
    if (mTimeridVaild == 1) {
        ALOGW("stop timer cid=%d", mCameraId);
        stopTimer(mTimerID);
        mCurRecordPos = 0;
    }
    return NO_ERROR;

}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::prepare()
{
    F_LOG;
    Mutex::Autolock locker(&mObjectLock);
#ifdef USE_CDX_LOWLEVEL_API
    /****************************** Define MUXER Paramerter ********************************************/

    CdxMuxerMediaInfoT media_info;
    //CdxStreamT *mp4writer = NULL;

    /****************************** Define MUXER Paramerter ********************************************/
    char name_buf[512] = { 0 };

    memset(name_buf, 0, 512);
    genfilename(name_buf);
    dvrsetvideoname(name_buf);
    ALOGI("VIDEO_NAME:%s,id=%d", name_buf, mCameraId);

    __notify_cb(CAMERA_MSG_DVR_NEW_FILE, gFilemanger.cur_file_idx, mCameraId, mCbUser);

    /******************************* Set Muxer Parameters ****************************/
    memset(&media_info, 0, sizeof(CdxMuxerMediaInfoT));
#ifdef USE_CDX_LOWLEVEL_API_AUDIO
    AutAudioMuxInit(&media_info);
#else
    media_info.audioNum = 0;
#endif
    media_info.videoNum = 1;
    media_info.video.nWidth = encode_param.dst_width;
    media_info.video.nHeight = encode_param.dst_height;
    media_info.video.nFrameRate = encode_param.frame_rate;
    media_info.video.eCodeType = (VENC_CODEC_TYPE) encode_param.encode_format;

    memset(&mp4stream, 0, sizeof(CdxDataSourceT));

    mp4stream.uri = strdup(encode_param.mp4_file);
#ifdef CDX_V27
    extern CdxWriterT *CdxWriterCreat();
#endif
    if ((writer = CdxWriterCreat()) == NULL) {
        ALOGE("writer creat failed");
        return -1;
    }
    mw = (MuxerWriterT *) writer;
    strcpy(mw->file_path, mp4stream.uri);
    mw->file_mode = FD_FILE_MODE;
    int ret = MWOpen(writer);
    mux = CdxMuxerCreate(CDX_MUXER_MOV, writer);
    if (mux < 0) {
        ALOGE("CdxMuxerCreate failed");
        return -1;
    }
    int iscard = 0;
    CdxMuxerControl(mux, SET_IS_SDCARD_DISAPPEAR, &iscard);
    CdxMuxerSetMediaInfo(mux, &media_info);
#if FS_WRITER

#if  1
    memset(&fs_cache_mem, 0, sizeof(CdxFsCacheMemInfo));

    fs_cache_mem.m_cache_size = 2 * 1024 * 1024;    // must be less than 512 * 1024
    fs_cache_mem.mp_cache = (cdx_uint8 *) malloc(fs_cache_mem.m_cache_size);
    if (fs_cache_mem.mp_cache == NULL) {
        ALOGE("fs_cache_mem.mp_cache malloc failed");
        goto nofscache;
    }
    CdxMuxerControl(mux, SET_CACHE_MEM, &fs_cache_mem);
    fs_mode = FSWRITEMODE_CACHETHREAD;
#else

    int fs_cache_size = 1024 * 1024;
    CdxMuxerControl(mux, SET_FS_SIMPLE_CACHE_SIZE, &fs_cache_size);
    fs_mode = FSWRITEMODE_SIMPLECACHE;

#endif
    //fs_mode = FSWRITEMODE_DIRECT;
    CdxMuxerControl(mux, SET_FS_WRITE_MODE, &fs_mode);
  nofscache:

#endif
    CdxMuxerWriteHeader(mux);

    /******************************* Set Muxer Parameters ****************************/
#ifdef SPS_PPS_FILE
    out_file = fopen("/mnt/UDISK/640p.h264", "wb");
#endif
    //char name_test[1024]= {0};
    //sprintf(name_test,"%s.h264",name_buf);
    //out_file = fopen(name_test, "wb");
    if (mTimeridVaild == 1) {
        stopTimer(mTimerID);
        mCurRecordPos = 0;
        setPeriodTimer(1, 0, mTimerID);    //restart
    }
    else {
        if (createTimer(this, &mTimerID, __timer_cb) == 0) {
            mCurRecordPos = 0;
            setPeriodTimer(1, 0, mTimerID);
            mTimeridVaild = 1;
        } else {
            mTimeridVaild = 0;
        }
    }
    mDvrWriteFrameNum = 0;
    VencHeaderData sps_pps_data;

    if (encode_param.encode_format == VENC_CODEC_H264) {

        VideoEncGetParameter(pRecVideoEnc, VENC_IndexParamH264SPSPPS, &sps_pps_data);
        CdxMuxerWriteExtraData(mux, sps_pps_data.pBuffer, sps_pps_data.nLength, 0);

#ifdef SPS_PPS_FILE
        if (out_file != NULL)
            fwrite(sps_pps_data.pBuffer, 1, sps_pps_data.nLength, out_file);
#endif
        //ALOGD("sps_pps_data.nLength: %d", sps_pps_data.nLength);
        //int head_num;
        //for(head_num=0; head_num<sps_pps_data.nLength; head_num++)
        //  ALOGD("the sps_pps :%02x", *(sps_pps_data.pBuffer+head_num));
    } else if (encode_param.encode_format == VENC_CODEC_H265) {
        VideoEncGetParameter(pRecVideoEnc, VENC_IndexParamH265Header, &sps_pps_data);
        CdxMuxerWriteExtraData(mux, sps_pps_data.pBuffer, sps_pps_data.nLength, 0);
    }
#endif

    return 0;
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::closemux()
{
#ifdef USE_CDX_LOWLEVEL_API
    ALOGD("close mux");
    if (mux == NULL) {
        ALOGD("closemux mux null");
        return 0;
    }
#ifdef SPS_PPS_FILE
    if (out_file != NULL) {
        fclose(out_file);
        out_file = NULL;
    }
#endif
    if (storage_state == 1) {
        int result = CdxMuxerWriteTrailer(mux);
        if (result) {
            ALOGD("CdxMuxerWriteTrailer failed");
            return -1;
        } else {
            ALOGD("CdxMuxerWriteTrailer success");
        }
    } else {
        //CdxMuxerWriteTrailer(mux);//some problem so comment
        ALOGD("closemux storage_state != 1");
    }

    CdxMuxerClose(mux);

    mux = NULL;

    if (mp4stream.uri) {
        free(mp4stream.uri);
        mp4stream.uri = NULL;
    }
    if (writer) {
        MWClose(writer);
        CdxWriterDestroy(writer);
        F_LOG;
        writer = NULL;
        mw = NULL;
    }
    if (fs_cache_mem.mp_cache != NULL) {
        free(fs_cache_mem.mp_cache);
        fs_cache_mem.mp_cache = NULL;
    }
    ALOGD("closemux done");
#endif
    return 0;
}


/**************************************
Function:
Description:
***************************************/
int RecordCamera::camera_video_file_save(char *name, int filetype)
{
    int ret = -1;
    char nameback[256];
    memset(nameback, 0, 256);

    int len = strlen(name);

    strcpy(nameback, name);
    nameback[len - 4] = 0;
    if (filetype == CurRecordFileNameType_SAVE) {
        strcat(nameback, CM_SAVE_FILE_MARK);
    } else if (filetype == CurRecordFileNameType_LOCK) {
        strcat(nameback, CM_LOCK_FILE_MARK);
        ALOGW("Lock_file_name: %s", nameback);
    }

    strcat(nameback, EXT_VIDEO);
    ALOGW("video_file_name: %s", nameback);

    //ALOGE("new name =%s",nameback);
    ret = rename(name, nameback);
    if (ret == 0) {
        //ALOGE("video%d rename rt =%s success",g_cm_run_status.videono,nameback);
    }
    return ret;
}


/**************************************
Function:
Description:
***************************************/
int RecordCamera::camera_change_file_name(int filetype)
{
    int ret = 0;

    Mutex::Autolock locker(pfileLock);
    file_status_t *p = pFileManger;

    int cur_idx = p->cur_file_idx;
    //int pre_idx = cur_idx > 0 ? cur_idx - 1 : p->cur_max_filenum - 1;
    //save cur file and pre file
    ret = camera_video_file_save(p->cur_filename[cur_idx], filetype);
    if (ret == 0) {
        memset(p->cur_filename[cur_idx], 0, CM_MAX_FILE_LEN);
        p->cur_dir_file_num--;
    }
    return 0;
}


/**************************************
Function:
Description:
***************************************/
void RecordCamera::__timer_cb(sigval_t sig)
{
    RecordCamera *__this = static_cast < RecordCamera * >(sig.sival_ptr);
    //ALOGV("__timer_cb-----");
    if (__this != NULL) {
        __this->mCurRecordPos++;
        if (((__this->mCurRecordPos == 10) && (__this->mNeedNewFile == 1))
                || (__this->mCurRecordPos > __this->mDuration + 15)) {

            media_msg_t *mesg = NULL;

            mesg = (media_msg_t *) malloc(sizeof(media_msg_t));
            if (mesg == NULL) {
                ALOGE("__timer_cb malloc fail");
                return;
            }

            mesg->mesg_type = RECORD_CMD_TIMEOUT;
            mesg->timestamp = (int64_t) systemTime();
            memset(&mesg->mesg_data[0], 0, sizeof(CdxMuxerPacketT));    //blank
            mesg->mesg_len = sizeof(CdxMuxerPacketT);

            int pp = 0;
            ALOGW("record __timer_cb timeout  id=%d pos=%d pp=%p", __this->mCameraId,
                 __this->mCurRecordPos, &pp);
            //fprintf(stderr,"record __timer_cb timeout  id=%d pos=%d pp=%p",__this->mCameraId,__this->mCurRecordPos,&pp);

            int ret = OSAL_QueueUrgent(&__this->mQueueBufferRecordFile, mesg, &pp);
            if (ret != 0) {
                ALOGE("xxxrecord __timxxer_cb timeout  id=%d", __this->mCameraId);
                free(mesg);
                pthread_mutex_lock(&__this->mRecordFileMutex);
                pthread_cond_signal(&__this->mRecordFileCond);
                pthread_mutex_unlock(&__this->mRecordFileMutex);
                return;

            }
            ALOGW("get a  pp = %p", pp);
            media_msg_t *pmg = (media_msg_t *) pp;

            if (pmg != NULL) {
                CdxMuxerPacketT *ppkt = (CdxMuxerPacketT *) & pmg->mesg_data[0];
                ALOGW("ppkt data-----%p------", ppkt);

                if (ppkt != NULL) {
                    if (ppkt->buf != NULL) {
                        ALOGW("free ppkt->buf = %p", ppkt->buf);
                        free(ppkt->buf);
                    }
                }
                ALOGW("free pmg = %p", pmg);
                free(pmg);
                pmg = 0;
            }

            ALOGW("release done-----------");

            pthread_mutex_lock(&__this->mRecordFileMutex);
            pthread_cond_signal(&__this->mRecordFileCond);
            pthread_mutex_unlock(&__this->mRecordFileMutex);
            return;
        }

        if (__this->mCurRecordPos == __this->mDuration - 1) {
            ALOGW("__timer_cb is %d", __this->mCurRecordPos);
            __this->mNeedNewFile = 1;    //temply no mutex pretect
        }
    }
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::AutAudioMuxInit(CdxMuxerMediaInfoT *pmedia_info)
{
    int ret=0;
    AudioEncConfig audioConfig;
    audioConfig.nType = AUDIO_ENCODER_AAC_TYPE;
    audioConfig.nInChan = 2;
    audioConfig.nInSamplerate = 44100;
    audioConfig.nOutChan = 2;
    audioConfig.nOutSamplerate = 44100;
    audioConfig.nSamplerBits = 16;

    pmedia_info->audio.eCodecFormat = audioConfig.nType;//AUDIO_ENCODER_AAC_TYPE;

    pmedia_info->audioNum = 1;
    pmedia_info->audio.nAvgBitrate = audioConfig.nBitrate;
    pmedia_info->audio.nBitsPerSample =audioConfig.nSamplerBits;
    pmedia_info->audio.nChannelNum = audioConfig.nOutChan;
    pmedia_info->audio.nMaxBitRate = audioConfig.nBitrate;
    pmedia_info->audio.nSampleRate = audioConfig.nOutSamplerate;
    pmedia_info->audio.nSampleCntPerFrame = 1024;

    return ret;
}

/**************************************
Function:
Description:
***************************************/
#define FILE_NO_REMOVE 1
//if define then when card is full,rename old idx file or delete near  2files if space not enough
//if not define ,when card is full,remove old idx file,and re cale space for new file

#define FILE_HOLES_SYS_SUPPORT 1
//depend on FILE_NO_REMOVE,
//ifdefineFILE_NO_REMOVE and  FILE_HOLES_SYS_SUPPORT  use fat32 falloc patch ,see kernel fat pacth
//if not define only define FILE_NO_REMOVE when card is full,remove old idx file,and re cale space for new file

#define FALLOC_FL_KEEP_SIZE 0x01    /* default is extend size */

extern int xxCreateMyFile(char *szFileName, int nFileLength);

int RecordCamera::genfilename(char *name)
{
    char rec_filename[256];
    int rmidx = 0, reidx = 0;

    Mutex::Autolock locker(pfileLock);
    file_status_t *p = pFileManger;

    int l32_CameraId = (360 == mCameraId) ? CAMERA_360_ID : mCameraId;

    if (name == NULL)
        return -1;

    p->cur_file_idx = config_get_camfileidx(0);
    if (p->cur_file_idx >= p->cur_max_filenum) {
        p->cur_file_idx = 0;
    }

    unsigned long long as = availSize(p->cur_filedir[l32_CameraId]);
    //unsigned long afile_size = ((mDuration * encode_param.bit_rate) >> 23) + (13 * mDuration) / 60;
    int afile_blksize = (mDuration / 60) * gAFileOccupySizePerMinMb;
    ALOGI("as is %lluM,re is %dM dur=%d bitrate=0x%x", as, (int) (afile_blksize + RESERVED_SIZE),
          mDuration, encode_param.bit_rate);

    rmidx = p->cur_file_idx;
    reidx = 0;
    int ret;
    do {
        if (reidx >= CM_MAX_RECORDFILE_NUM) {
            break;
        } else {
            reidx++;
        }

        as = availSize(p->cur_filedir[l32_CameraId]);
        ALOGV("dbg-rec as is %lldM,re is %dM", as, (int) (afile_blksize + RESERVED_SIZE));

        if (as > (afile_blksize + RESERVED_SIZE)) {
            break;                //we have enough room
        } else {
            if (strlen(p->cur_filename[rmidx]) != 0) {
                ALOGV("dbg-rec no av room!rm [%d] %s,FileSize=%dM,OccupySizeMb=%d", rmidx,
                      p->cur_filename[rmidx], getFileSize(p->cur_filename[rmidx]),
                      getFileOccupySizeMb(p->cur_filename[rmidx]));
                //remove thumb
                char buf2[CM_MAX_FILE_LEN];
                memset(buf2, 0, CM_MAX_FILE_LEN);
                sprintf(buf2, "%s%s%s%d%c%s%s%s", p->cur_filedir[0], "/", CM_THUMB_DIR,
                        p->cur_file_idx, '-', "thumb_", ppSuffix[0], EXT_PIC);
                if (access(buf2, F_OK) == 0) {
                    remove(buf2);
                }

                memset(buf2, 0, CM_MAX_FILE_LEN);
                sprintf(buf2, "%s%s%s%d%c%s%s%s", p->cur_filedir[1], "/", CM_THUMB_DIR,
                        p->cur_file_idx, '-', "thumb_", ppSuffix[1], EXT_PIC);
                if (access(buf2, F_OK) == 0) {
                    remove(buf2);
                }

                if (access(p->cur_filename[rmidx], F_OK) != 0) {
                    ALOGV("file[%d] %s doesn't exist,pass this file.", rmidx,
                          p->cur_filename[rmidx]);
                    memset(p->cur_filename[rmidx], 0, CM_MAX_FILE_LEN);
                    if (rmidx >= CM_MAX_RECORDFILE_NUM) {
                        rmidx = 0;
                    } else {
                        rmidx++;
                    }
                    continue;
                }
                int oldfileSize = getFileOccupySizeMb(p->cur_filename[rmidx]);
                if (afile_blksize <= (oldfileSize - gAFileOccupySizePerMinMb)) {
                    ALOGV("dbg-rec file size dismatch,remove idx[%d] file now,oldfilesize=%d",
                          rmidx, oldfileSize);
                    ret = remove(p->cur_filename[rmidx]);
                    if (ret == 0)
                        memset(p->cur_filename[rmidx], 0, CM_MAX_FILE_LEN);
                    else
                        ALOGE("dbg-rec old file room is too large,but rm file %s fail %d",
                              p->cur_filename[rmidx], errno);
                } else if ((afile_blksize <= oldfileSize) && (afile_blksize >= (oldfileSize - gAFileOccupySizePerMinMb))) {
                    if (rmidx == p->cur_file_idx) {    //can use curr file
                        ALOGV("dbg-rec no need to rm[%d],oldfilesize=%d,just use the old one",
                              rmidx, oldfileSize);
                        break;
                    }

                    ALOGV("dbg-rec rmidx != curr_idx,can not use,rm[%d]", rmidx);

                    ret = remove(p->cur_filename[rmidx]);
                    if (ret == 0) {
                        memset(p->cur_filename[rmidx], 0, CM_MAX_FILE_LEN);
                    } else {
                        ALOGE("dbg-rec file room is match but rm file %s fail %d",
                              p->cur_filename[rmidx], errno);
                    }

                } else {
                    ALOGV("dbg-rec need to rm[%d]", rmidx);
                    ret = remove(p->cur_filename[rmidx]);
                    if (ret == 0) {
                        memset(p->cur_filename[rmidx], 0, CM_MAX_FILE_LEN);
                    } else {
                        ALOGE("dbg-rec old file room is too small,but rm file %s fail %d",
                              p->cur_filename[rmidx], errno);
                    }

                }
            }

            if (rmidx >= CM_MAX_RECORDFILE_NUM) {
                rmidx = 0;
            } else {
                rmidx++;
            }
        }
    }
    while (1);
    struct tm *tm = NULL;
    time_t now = getDateTime(&tm);
    sprintf(rec_filename, "%s%s%d%c%04d%02d%02d_%02d%02d%02d_%s%s", p->cur_filedir[l32_CameraId],
            "/", p->cur_file_idx, '-', tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour,
            tm->tm_min, tm->tm_sec, ppSuffix[l32_CameraId], EXT_VIDEO);

#ifdef FILE_NO_REMOVE
#ifdef FILE_HOLES_SYS_SUPPORT

    int perfilesize = (gAFileOccupySizePerMinMb << 20) * (mDuration / 60);
    if (access(p->cur_filename[p->cur_file_idx], F_OK) == 0) {
        ALOGW("dbg-rec t a file %s ", p->cur_filename[p->cur_file_idx]);
        ret = xxCreateMyFile(p->cur_filename[p->cur_file_idx], perfilesize);    //this is needed to prevent kernel crash
        if (ret < 0) {
            ret = remove(p->cur_filename[p->cur_file_idx]);
            if (ret == 0) {
                ALOGW("dbg-rec room dismatch,rm old file first and then create it again");
                ret = xxCreateMyFile(p->cur_filename[p->cur_file_idx], perfilesize);    //this is needed to prevent kernel crash

            } else {
                ALOGE("dbg-rec old file OccupySize is not match the new one ,but rm old file err%d",
                      errno);
            }
        }

        ret = truncate(p->cur_filename[p->cur_file_idx], 0);
        if (ret != 0) {
            ALOGW("dbg-rec t a file %s ret=%d (%d):%s", rec_filename, ret, errno, strerror(errno));
        }

        ret = rename(p->cur_filename[p->cur_file_idx], rec_filename);
        if (ret != 0) {
            ALOGE("genfile re file faile %s ret=%d (%d):%s", rec_filename, ret, errno,
                  strerror(errno));
        }

    } else {
        ALOGV("dbg-rec f a file %s size=%dM", rec_filename, perfilesize >> 20);
        xxCreateMyFile(rec_filename, perfilesize);
    }

    //ALOGV("dbg-rec ids=[%d] perfilesize=%dM,getFileOccupySizeMb=%d,getFileSize=%d",p->cur_file_idx,(perfilesize>>20),
    //                                      getFileOccupySizeMb(rec_filename),getFileSize(rec_filename));
#endif

#else //haven't define FILE_NO_REMOVE
    ret = rename(p->cur_filename[p->cur_file_idx], rec_filename);
    if (ret != 0) {
        ALOGE("genfile re file fail ");
    }
#endif

    strcpy(p->cur_filename[p->cur_file_idx], rec_filename);

    strcpy(name, rec_filename);

    ALOGD("genfile %s", name);

    if (p->cur_file_idx >= p->cur_max_filenum) {
        p->cur_file_idx = 0;
    } else {
        p->cur_file_idx++;
    }
    config_set_camfileidx(0, p->cur_file_idx);

    return 0;
}


/**************************************
Function:
Description:
***************************************/
int RecordCamera::dvrsetvideoname(char *name)
{
    F_LOG;

    int ret = -1;
    if (name != NULL) {
        strcpy((char *) encode_param.mp4_file, name);    //        "write:///mnt/UDISK/720p_h264.mp4");
        ret = 0;
    }
    return ret;
}

/**************************************
Function:
Description:
***************************************/
int RecordCamera::scan_picture(const char *path, int mCameraId)
{
    DIR *dir_ptr;
    struct dirent *direntp;
    char rmbuf[256] = { };
    char tmpbuf[256] = { };
    int l32_CameraId = (360 == mCameraId) ? CAMERA_360_ID : mCameraId;

    if ((dir_ptr = opendir(path)) == NULL) {
        ALOGE("open picture path %s failed", path);
        return -1;
    } else {
        int i = 0;
        int idx = 0;
        //chdir(path);
        while ((direntp = readdir(dir_ptr)) != NULL) {
            ALOGV("dbg scan_picture d_name=%s", direntp->d_name);
            for (i = 0; i < strlen(direntp->d_name); ++i) {
                if (direntp->d_name[i] == '-') {
                    if (strstr(direntp->d_name, "mp4")) {
                        ALOGV("dbg scan_picture this file is mp4,continue!");
                        continue;
                    }

                    memset(tmpbuf, 0, 256);
                    memcpy(tmpbuf, direntp->d_name, i);
                    idx = atoi(tmpbuf);
                    if ((idx < CM_MAX_PICTURE_NUM) && (idx >= 0) && (idx <= iMaxPicNum)) {
                        if (strlen(g_NamePic[l32_CameraId][idx]) == 0) {
                            sprintf(g_NamePic[l32_CameraId][idx], "%s/%s", path, direntp->d_name);
                        } else {
                            memset(rmbuf, 0, 256);
                            strcat(rmbuf, direntp->d_name);

                            if (strstr(g_NamePic[l32_CameraId][idx], rmbuf) != NULL) {
                                int rmret = 0;
                                ALOGI("find duplicate pic  so rm old %s idx=%d  name=%s ",
                                      g_NamePic[l32_CameraId][idx], idx, direntp->d_name);
                                rmret = remove(g_NamePic[l32_CameraId][idx]);
                                ALOGI("rmpicfile ret %s", rmret == 0 ? "OK" : "FAIL");
                                sprintf(g_NamePic[l32_CameraId][idx], "%s/%s", path,
                                        direntp->d_name);
                            }
                        }
                        //ALOGI("parse success  idx= %d  name= %s ",idx,direntp->d_name);
                    } else {
                        char tname[256] = { };
                        sprintf(tname, "%s", g_PicPath[l32_CameraId]);
                        remove(tname);
                    }
                }
            }

        }
        closedir(dir_ptr);
    }
    return 0;

/********************scan picture path end*******************************/
}

/**************************************
Function:
Description:
***************************************/
bool RecordCamera::initFileListDir(char *dirname)
{
    DIR *dir_ptr;

    struct dirent *direntp;
    unsigned int i;
    int idx;
    char tmpbuf[256];
    char rmbuf[256];

    char real_path[256];
    char camera_path[256];
    char thumb_path[256];

    Mutex::Autolock locker(pfileLock);
    file_status_t *p = pFileManger;

    unsigned long long totMB = 0;
    int rmret = 0;
    int l32_CameraId = (360 == mCameraId) ? CAMERA_360_ID : mCameraId;

    if (l32_CameraId > MAX_SUPPORT_CAM) {
        l32_CameraId = 0;
    }

    F_LOG;
    if (dirname == NULL) {
        ALOGE("dirname ==null");
        return false;
    }

    int len = strlen(dirname);

    if (len < 2) {
        ALOGE("video dir can toshort ");
        return false;
    }

    strcpy(tmpbuf, dirname);
    for (i = 0; i < len; i++) {
        if (tmpbuf[len - 1 - i] == '/') {
            tmpbuf[len - 1 - i] = 0;
        } else {
            break;
        }
    }

    rmret = readlink(tmpbuf, real_path, sizeof(real_path));
    if (rmret < 0) {
        ALOGV("mount path not a symlink %s err=%d", tmpbuf, errno);

        strcpy(real_path, tmpbuf);
    } else {
        ALOGV("mount real path is %s ", real_path);
    }

    if (isMounted(real_path)) {
        ALOGV("-------sdmmc------mounted");
        storage_state = 1;

    } else {
        ALOGE("!!!-------sdmmc------unmounted");
        return false;
    }

    memset(camera_path, 0, sizeof(camera_path));
    sprintf(camera_path, "%s/%s", real_path, pVideoPath[l32_CameraId]);
    strcpy(tmpbuf, camera_path);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create camera_path dir %s fail", tmpbuf);
        return false;
    }
    memset(thumb_path, 0, sizeof(thumb_path));
    sprintf(thumb_path, "%s/%s", camera_path, CM_THUMB_DIR);
    strcpy(tmpbuf, thumb_path);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create thumb dir %s fail", tmpbuf);
        //return false;
    }

    memset(g_PicPath[l32_CameraId], 0, sizeof(g_PicPath[l32_CameraId]));
    sprintf(g_PicPath[l32_CameraId], "%s/%s", real_path, (char *)pPicPath[l32_CameraId]);
    strcpy(tmpbuf, g_PicPath[l32_CameraId]);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create picture_path dir %s fail", tmpbuf);
        return false;
    }
//create lockvideo path
    memset(rmbuf, 0, sizeof(rmbuf));
    sprintf(rmbuf, "%s/%s", real_path, LOCK_VIDEO);
    strcpy(tmpbuf, rmbuf);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create lock dir %s fail", tmpbuf);
        //return false;
    }
    memset(thumb_path, 0, sizeof(thumb_path));
    sprintf(thumb_path, "%s/%s", tmpbuf, CM_THUMB_DIR);
    strcpy(tmpbuf, thumb_path);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create lockVideo thumb dir %s fail", tmpbuf);
        //return false;
    }

//create parkmonitor path

    memset(rmbuf, 0, sizeof(rmbuf));
    sprintf(rmbuf, "%s/%s", real_path, PARK_MONITOR);
    strcpy(tmpbuf, rmbuf);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create parkMonitor dir %s fail", tmpbuf);
        //return false;
    }
    memset(thumb_path, 0, sizeof(thumb_path));
    sprintf(thumb_path, "%s/%s", tmpbuf, CM_THUMB_DIR);
    strcpy(tmpbuf, thumb_path);
    if (createdir(tmpbuf) != 0) {
        ALOGE("create parkMonitor thumb dir %s fail", tmpbuf);
        //return false;
    }

    memset(p->cur_filedir[l32_CameraId], 0, CM_MAX_FILE_LEN);
    strcpy(p->cur_filedir[l32_CameraId], camera_path);

    if ((dir_ptr = opendir(camera_path)) == NULL) {

    } else {
        totMB = totalSize(real_path);
        unsigned long afile_size =
            ((mDuration * encode_param.bit_rate) >> 23) + (13 * mDuration) / 60;

        ALOGW("----total size=%llu,afilesize =%lu syctime=%d bit=0x%x", totMB, afile_size,
              mDuration, encode_param.bit_rate);
        if (afile_size == 0) {
            ALOGW("get afilesize =0");
            afile_size = (totMB - RESERVED_SIZE) / CM_MAX_RECORDFILE_NUM;
        }

        //= (bit_rate*60/8)+13 => bit_rate*7.5+13 ==>bit_rate*8+13 ==>(bit_rate>>20)<<8 + 13==>(bit_rate>>17)+ 13;
        if (gAFileOccupySizePerMinMb < ((encode_param.bit_rate >> 17) + 23)) {
            gAFileOccupySizePerMinMb = (encode_param.bit_rate >> 17) + 23;
        } else {
            ALOGV("dbg-rec only use the higher bit_rate[%d] to calc A file occupy size",
                  (gAFileOccupySizePerMinMb - 23) >> 3);
        }

        p->cur_max_filenum =
            (totMB - RESERVED_SIZE) / ((mDuration / 60) * gAFileOccupySizePerMinMb);

        if (p->cur_max_filenum > CM_MAX_RECORDFILE_NUM)
            p->cur_max_filenum = CM_MAX_RECORDFILE_NUM;
        config_set_normalvideomax(mCameraId, p->cur_max_filenum);
        //config_set_lockvideomax(mCameraId, p->cur_max_filenum);
        ALOGV("dbg-rec max_filenum=%d", p->cur_max_filenum);
        //  150k * 6 ~ 1M
        iMaxPicNum = (totMB - RESERVED_SIZE * 2);
        config_set_normalpicmax(mCameraId, iMaxPicNum);
        //ALOGW("----max file num =%d ",p->cur_max_filenum);
        ALOGW("AW :TotalMB= %lluMB  afile_size = %luMB -max_file_num =%d", totMB, afile_size,
              p->cur_max_filenum);
        //ALOGI("--------dvr mode%d------%d,%d,%d,%d",p->camera_mode,totMB,afile_size,p->cur_max_filenum,p->pcamera_param->continue_record);

        while ((direntp = readdir(dir_ptr)) != NULL) {
            if (strstr(direntp->d_name, CM_SAVE_FILE_MARK) != NULL)
                continue;
            if (strstr(direntp->d_name, CM_LOCK_FILE_MARK) != NULL)
                continue;

            for (i = 0; i < strlen(direntp->d_name); i++) {
                if (direntp->d_name[i] == '-') {
                    memset(tmpbuf, 0, 256);
                    memcpy(tmpbuf, direntp->d_name, i);
                    idx = atoi(tmpbuf);
                    if ((idx < CM_MAX_RECORDFILE_NUM) && (idx >= 0)) {
                        if (strlen(p->cur_filename[idx]) == 0) {
                            strcpy(p->cur_filename[idx], camera_path);
                            strcat(p->cur_filename[idx], "/");
                            strcat(p->cur_filename[idx], direntp->d_name);
                            //ALOGI("cur file %d %s ",idx,p->cur_filename[idx]);
                            p->cur_dir_file_num++;
                        } else {
                            memset(rmbuf, 0, 256);
                            strcat(rmbuf, direntp->d_name);

                            if (strstr(p->cur_filename[idx], rmbuf) == NULL) {
                                ALOGW("find duplicate  so rm old %s idx=%d  name=%s ",
                                      p->cur_filename[idx], idx, direntp->d_name);
                                rmret = remove(p->cur_filename[idx]);
                                ALOGW("rmfile ret %s", rmret == 0 ? "OK" : "FAIL");
                                strcpy(p->cur_filename[idx], camera_path);
                                strcat(p->cur_filename[idx], "/");
                                strcat(p->cur_filename[idx], direntp->d_name);
                                ALOGW("newidx file %s len=%d", p->cur_filename[idx],
                                      strlen(p->cur_filename[idx]));

                                //remove thumb
                                sprintf(tmpbuf, "%s%s%s%d%c%s%s", p->cur_filedir[l32_CameraId], "/",
                                        CM_THUMB_DIR, idx, '-', "thumb", EXT_PIC);
                                remove(tmpbuf);
                            }

                        }
                        //ALOGI("parse success  idx= %d  name= %s ",idx,direntp->d_name);
                    } else {
                        //ALOGD("can't parse idx= %d  name= %s ",idx,direntp->d_name);
                    }
                }
            }

        }

        scan_picture(g_PicPath[l32_CameraId], mCameraId);
        closedir(dir_ptr);
        sync;
    }
    return true;
}


/**************************************
end
***************************************/
