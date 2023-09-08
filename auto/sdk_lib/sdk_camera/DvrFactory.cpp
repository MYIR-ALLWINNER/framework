
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <CdxIon.h>
#include "videodev2_new.h"
#include "DvrFactory.h"
#include "CameraFileCfg.h"
#include "rtspapi.h"
#include "posixTimer.h"
//#include "DvrRecordManager.h"
#include "hwdisp2.h"
#include "DvrFactory.h"

#ifdef USE_CDX_LOWLEVEL_API
#include "aencoder.h"
#endif

#define LOG_TAG "dvrfactory"
#include "sdklog.h"

//#define SUPPORT_H265    1

using namespace android;

void dvr_factory::setCallbacks(notify_callback notify_cb,
                               data_callback data_cb,
                               data_callback_timestamp data_cb_timestamp, void *user)
{
    // temp not open for users
    //if usr must use this , the cb func must process as quickly as possibale
    mNotifyCb = notify_cb;
    mDataCb = data_cb;
    mDataCbTimestamp = data_cb_timestamp;
    mCbUser = user;

    mRecordCamera->setCallbacks(notify_cb, ((dvr_factory*)user)->mRecordCamera);
}

void dvr_factory::__dvr_audio_data_cb_timestamp(int32_t msgType,nsecs_t timestamp,int card,int device,
                            char *dataPtr,int dsize,
                            void* user /*must class dvr_factory*/)
{
    dvr_factory* p= (dvr_factory*) user;
    p->mDvrAudioEnc->__audioenc_data_src(msgType, timestamp, card, device, dataPtr,dsize, p->mDvrAudioEnc);
}

void dvr_factory::notifyCallback(int32_t msgType, int32_t ext1,
                                int32_t ext2, void* user)
{
    ALOGV("dvr factory %s", __FUNCTION__);
}

void dvr_factory::__notify_cb(int32_t msg_type, int32_t ext1,int32_t ext2, void *user)
{
    ALOGV("into %s", __FUNCTION__);
    dvr_factory *__this = static_cast<dvr_factory *>(user);
    __this->notifyCallback(msg_type, ext1, ext2, user);
    if (__this->mNotifyCb != NULL) {
        ALOGV("call mNotifyCb, cbdat:%p", __FUNCTION__,__LINE__,__this->mCbUser);
        __this->mNotifyCb(msg_type, ext1, ext2, __this->mCbUser);
    }
}

//takepicture data cb
void dvr_factory::__data_cb(int32_t msg_type,
                        char *data,
                        camera_frame_metadata_t *metadata,
                        void *user)
{
    //ALOGV("%s", __FUNCTION__);
    dvr_factory *__this =static_cast<dvr_factory *>(user);
    if (__this->mDataCb != NULL) {
        __this->mDataCb(msg_type,data,metadata,__this->mCbUser); //up to the app
    }

    if (__this->mRecordCamera) {
        __this->mRecordCamera->dataCallback(msg_type, data, metadata, __this->mRecordCamera);
    }
}

//record data cb
void dvr_factory::__data_cb_timestamp(nsecs_t timestamp, int32_t msg_type,
                                char *data,
                                void *user)
{
    dvr_factory *__this = static_cast<dvr_factory *>(user);
    if (__this->mDataCbTimestamp != NULL) {
        __this->mDataCbTimestamp(timestamp, msg_type, data, __this->mCbUser);  //up to the app
    }

    if (__this->mRecordCamera) {
        __this->mRecordCamera->dataCallbackTimestamp(timestamp, msg_type, data, __this->mRecordCamera);
    }
}

int dvr_factory::start()
{
    ALOGD("F:%s, L:%d",__FUNCTION__, __LINE__);
    Mutex::Autolock locker(&mObjectLock);

    //mCaptureFmt=V4L2_PIX_FMT_H264;
    int i;
    int result = 0;
    if (360 == mCameraId) {
        for (i = 0; i < NUM_OF_360CAMERAS; i++) {
            m360Hardware[i]->mCaptureWidth = config_get_width(i + TVD_DEV_ID_START);
            m360Hardware[i]->mCaptureHeight = config_get_heigth(i + TVD_DEV_ID_START);
         }
    } else {
        mHardwareCameras->mCaptureWidth = config_get_width(mCameraId);
        mHardwareCameras->mCaptureHeight = config_get_heigth(mCameraId);
        mHardwareCameras->startRecording();
    }

    result = mRecordCamera->start();
    ALOGD("F:%s, L:%d end",__FUNCTION__, __LINE__);

    return result;
}

int dvr_factory::stop()
{
    Mutex::Autolock locker(&mObjectLock);

    ALOGW("stop camera id %d", mCameraId);
    if (360 == mCameraId) {
        if (NULL != mHardwareCameras) {
            m360CameraManager->stopPreview();
        } else {
            ALOGW("m360CameraManager=%p", mHardwareCameras);
        }
    } else {
        if (NULL != mHardwareCameras) {
            mHardwareCameras->disableMsgType(CAMERA_MSG_ALL_MSGS);
            mHardwareCameras->stopRecording();
            mHardwareCameras->stopPreview();
            mHardwareCameras->cancelPicture();
        } else {
            ALOGW("mHardwareCameras=%p", mHardwareCameras);
        }
    }

    if (NULL != mRecordCamera) {
        mRecordCamera->stop();
        mRecordCamera->videoEncDeinit();
    }

    return NO_ERROR;
}

int dvr_factory::startPriview(struct view_info vv)
{
    int h = config_get_heigth(mCameraId);
    int w = config_get_width(mCameraId);
    int ret = -1;
    struct src_info srcinfo = { w, h, 0 };

    Mutex::Autolock locker(&mObjectLock);

    if (360 == mCameraId) {
        if ((!m360CameraManager)||(!m360Hardware[0])) {
            ALOGE("startPriview error,mHardwareCameras is null");
            return -1;
        }
        int tvoutmode = 0; // config_get_tvout(mCameraId);
        m360Hardware[0]->setPreviewParam(vv, srcinfo, tvoutmode, 3);
        m360CameraManager->setOviewEnable(true);
        m360CameraManager->startPreview();
    } else {
        if (!mHardwareCameras) {
            ALOGE("startPriview error,mHardwareCameras is null");
            return -1;
        }
        //mode = config_get_tvout(mCameraId);
        int tvoutmode = 0; // config_get_tvout(mCameraId);
        mHardwareCameras->setPreviewParam(vv, srcinfo, tvoutmode, 3);
        ret = mHardwareCameras->startPreview();
        if (ret != 0) {
            return -1;
        }
        mHardwareCameras->enableMsgType(CAMERA_MSG_PREVIEW_FRAME);
    }
    return NO_ERROR;
}

int dvr_factory::stopPriview()
{
    if (360 == mCameraId) {
        m360CameraManager->stopPreview();
    } else {
        mHardwareCameras->disableMsgType(CAMERA_MSG_PREVIEW_FRAME);
    }

    return NO_ERROR;
}

int dvr_factory::startRecord()
{
    Mutex::Autolock locker(&mObjectLock);
    int ret = -1;
    F_LOG;
    if (mRecordCamera) {
        mRecordCamera->startRecord();
        if (mRecordCamera->recordStat == RECORD_STATE_STARTED) {
            if (360 == mCameraId) {
                if ((!m360CameraManager)||(!m360Hardware[0])) {
                    ALOGE("startRecord error,m360Hardware or m360CameraManager is null");
                    return -1;
                }
                m360Hardware[0]->enableMsgType(CAMERA_MSG_VIDEO_FRAME);    //enable recorder
                ret = m360Hardware[0]->startRecording();
                if (ret != 0) {
                    ALOGE("m360Hardware startRecording error");
                    return -1;
                }
            } else {
                mHardwareCameras->enableMsgType(CAMERA_MSG_VIDEO_FRAME);    //enable recorder
                ret = mHardwareCameras->startRecording();
                if (ret != 0) {
                    ALOGE("mHardwareCameras startRecording error");
                    return -1;
                }
            }
        }
    }

#ifdef USE_RECORD_AUDIO_API
    mDvrAudioEnc->AudioRecStart();
    if (mAudioCap != NULL) {
        mAudioCap->startCapture(mAudioHdl);
    }
#endif
    return NO_ERROR;

}

int dvr_factory::stopRecord()
{
    F_LOG;
    if (360 == mCameraId) {
        if ((!m360CameraManager)||(!m360Hardware[0])) {
            ALOGE("stopRecord error,m360Hardware or m360CameraManager is null");
            return -1;
        }
        m360Hardware[0]->disableMsgType(CAMERA_MSG_VIDEO_FRAME);    //enable recorder
        m360Hardware[0]->stopRecording();
    } else {
        mHardwareCameras->disableMsgType(CAMERA_MSG_VIDEO_FRAME);    //enable recorder
        mHardwareCameras->stopRecording();
    }

    mRecordCamera->stopRecord();

#ifdef USE_RECORD_AUDIO_API
    if (mAudioCap != NULL) {
        mAudioCap->stopCapture(mAudioHdl);
    }
    mDvrAudioEnc->AudioRecStop();
#endif
    usleep(2000000);
    return NO_ERROR;
}

int dvr_factory::takePicture()
{
    mHardwareCameras->enableMsgType(CAMERA_MSG_COMPRESSED_IMAGE);
    mHardwareCameras->takePicture();
    return NO_ERROR;
}

int dvr_factory::recordInit()
{
    F_LOG;
    int cycltime;
    //int cx, cy;

    recordwith = config_get_width(mCameraId);
    recordheith = config_get_heigth(mCameraId);

    cycltime = config_get_cyctime(mCameraId);
    ALOGE("recordwith = %d,recordheith = %d, cycltime = %d\n", recordwith, recordheith, cycltime);
#if SUPPORT_H265

    if (0 == mCameraId) {
        mRecordCamera->videoEncParmInit(recordwith, recordheith, recordwith, recordheith, 8, 25, VENC_CODEC_H265);
    } else {
        mRecordCamera->videoEncParmInit(recordwith, recordheith, recordwith, recordheith, 7, 30, VENC_CODEC_H265);
    }

#else

    if (0 == mCameraId) {
        mRecordCamera->videoEncParmInit(recordwith, recordheith, recordwith, recordheith, 8, 25, VENC_CODEC_JPEG);
    } else {
        mRecordCamera->videoEncParmInit(recordwith, recordheith, recordwith, recordheith, 7, 30, VENC_CODEC_JPEG);
    }

#endif

    mRecordCamera->setDuration(cycltime * 60);

    return 0;
}

int dvr_factory::updateHardwareInfo(CameraHardware * p, int id)
{
    if (!p) {
        ALOGE("updateHardwareInfo is NULL");
        return -1;
    }

    if (id > 8) {
        ALOGE("updateHardwareInfo input Cameraid:%d is too big", id);
        return -1;
    }

    switch(config_get_heigth(id))
    {
    case 480:
        p->mHardwareInfo.cvbs_type = 0;
        break;
    case 576:
        p->mHardwareInfo.cvbs_type = 1;
        break;
    case 960:
        p->mHardwareInfo.cvbs_type = 2;
        break;
    case 1152:
        p->mHardwareInfo.cvbs_type = 3;
        break;
    default:
        p->mHardwareInfo.cvbs_type = 1;
        break;
    }

    return 0;
}

int dvr_factory::add360Hardware()
{
    if (m360Hardware == NULL) {
        m360Hardware = new CameraHardware*[NUM_OF_360CAMERAS];
        if (m360Hardware == NULL) {
            ALOGE("%s: Unable to allocate V4L2Camera array for %d entries",
                 __FUNCTION__, MAX_NUM_OF_CAMERAS);
            return -1;
        }
        memset(m360Hardware, 0, NUM_OF_360CAMERAS * sizeof(CameraHardware*));
    }

    int ret;
    for (int i = 0; i < NUM_OF_360CAMERAS; i++){
        m360Hardware[i] = new CameraHardware();
        if (m360Hardware[i] == NULL) {
            ALOGE("error %s: Unable to instantiate fake camera class", __FUNCTION__);
            return -1;
        }

        sprintf(m360Hardware[i]->mHardwareInfo.device_name, "/dev/video%d", i + TVD_DEV_ID_START);
        m360Hardware[i]->mHardwareInfo.device_id = i + TVD_DEV_ID_START;

        ret = updateHardwareInfo(m360Hardware[i], i + TVD_DEV_ID_START);
        if (ret < 0) {
            return -1;
        }

        m360Hardware[i]->setCameraManager(m360CameraManager);
        m360CameraManager->setCameraHardware(i,m360Hardware[i]);
    }
    return 0;
}

#ifdef ADAS_ENABLE
bool dvr_factory::enableAdas()
{
    ALOGV("enableAdas");
    if (mHardwareCameras == NULL) {
        return false;
    }
    if (mHardwareCameras->sendCommand(CAMERA_CMD_START_ADAS_DETECTION, 0, 0) != NO_ERROR) {
        ALOGE("START_ADAS_DETECTION failed");
        return false;
    }
    usleep(50000);
    return true;
}

bool dvr_factory::disableAdas()
{
    ALOGV("disableAdas");
    if (mHardwareCameras == NULL) {
        return false;
    }

    if (mHardwareCameras->sendCommand(CAMERA_CMD_STOP_ADAS_DETECTION, 0, 0) != NO_ERROR) {
        ALOGE("STOP_ADAS_DETECTION failed");
        return false;
    }
    return true;
}

status_t dvr_factory::setAdasParameters(int key, int value)
{
    if (mHardwareCameras == NULL) {
        return false;
    }
    return mHardwareCameras->setAdasParameters(key, value);
}

bool dvr_factory::setAdasCallbacks(camera_adas_data_callback adas_data_cb)
{
    if (mHardwareCameras == NULL) {
        return false;
    }

    mHardwareCameras->setAdasCallbacks(adas_data_cb);
    return true;
}
#endif

bool dvr_factory::enableWaterMark()
{
    ALOGV("enableWaterMark");
    if (mHardwareCameras == NULL) {
        return false;
    }
    if (mHardwareCameras->sendCommand(CAMERA_CMD_START_WATER_MARK, 0, 0) != NO_ERROR) {
        ALOGE("START_WATER_MARK failed");
        return false;
    }
    usleep(50000);
    return true;
}

bool dvr_factory::disableWaterMark()
{
    ALOGV("disableWaterMark");
    if (mHardwareCameras == NULL) {
        return false;
    }

    if (mHardwareCameras->sendCommand(CAMERA_CMD_STOP_WATER_MARK, 0, 0) != NO_ERROR) {
        ALOGE("STOP_WATER_MARK failed");
        return false;
    }
    return true;
}

status_t dvr_factory::setWaterMarkMultiple(const char *str)
{
    ALOGV("setWaterMarkMultiple");
    if (mHardwareCameras == NULL || str == NULL)
        return BAD_VALUE;

    ALOGV("setWaterMarkMultiple(%s)", str);
    //String8 str8(str);            // = new String8(str)
    return mHardwareCameras->setWaterMarkMultiple((char *)str, WATER_MARK_DISP_MODE_VIDEO_AND_PREVIEW);
}

bool dvr_factory::initializeDev(CameraHardware * pHardware)
{
    if (pHardware == NULL) {
        ALOGE("initializeDev:pHardware is null");
        return -1;
    }

    if (!pHardware->isCameraIdle()) {
        ALOGE("camera[%d] is busy, wait for a moment",pHardware->mHardwareInfo.device_id);
        return -1;
    }

    if (pHardware->connectCamera() != NO_ERROR) {
        ALOGE("%s: Unable to connect camera", __FUNCTION__);
        return -EINVAL;
    }

    if (pHardware->Initialize() != NO_ERROR) {
        ALOGE("%s: Unable to Initialize camera", __FUNCTION__);
        return -EINVAL;
    }

    // Enable error, and metadata messages by default
    pHardware->enableMsgType(CAMERA_MSG_ERROR |
                             /* MOTION_DETECTION_ENABLE */
#ifdef ADAS_ENABLE
                             CAMERA_MSG_ADAS_METADATA |    /* ADAS_ENABLE */
#endif
                             CAMERA_MSG_PREVIEW_METADATA);

    pHardware->setCallbacks(
            __notify_cb,
            __data_cb,
            __data_cb_timestamp,
            (void *) this);

    //for hardware codec
    pHardware->sendCommand(CAMERA_CMD_SET_CEDARX_RECORDER, 0, 0);

    return true;
}

bool dvr_factory::uninitializeDev()
{
    // Release the hardware resources.
    if (360 == mCameraId) {
        if (m360CameraManager != NULL) {
            m360CameraManager->releaseCamera();
        }
    } else {
        if (mHardwareCameras != NULL) {
            mHardwareCameras->releaseCamera();
        }
    }
    //mHardwareCameras.clear();
    return true;
}


dvr_factory::dvr_factory(int cameraId)
  : usrDatCb(NULL),
    mNotifyCb(NULL),
    mDataCb(NULL),
    mDataCbTimestamp(NULL),
    mRecordCamera(NULL),
    mCameraId(cameraId),
    m360CameraManager(NULL),
    m360Hardware(NULL),
    mHardwareCameras(NULL),
    mCbUser(NULL),
    mCbUserDat(NULL),
    mDvrAudioEnc(NULL),
    mAudioCap(NULL),
    mAudioHdl(0),
    mAudioEncType(AUDIO_ENCODER_AAC_TYPE)
{
    //aut_set_disp_rotate_mode(TR_ROT_0);

    bool rt;

    ALOGD("libsdk_camera version:%s", MODULE_VERSION);

    mDvrAudioEnc = new AutAudioEnc();  //encode audio

#ifdef USE_CDX_LOWLEVEL_API_AUDIO
    AudioEncConfig audioEncConfig;
    memset(&audioEncConfig, 0x00, sizeof(AudioEncConfig));
    audioEncConfig.nInChan = 2;
    audioEncConfig.nInSamplerate = 44100;
    audioEncConfig.nOutChan = 2;
    audioEncConfig.nOutSamplerate = 44100;
    audioEncConfig.nSamplerBits = 16;
    audioEncConfig.nType = mAudioEncType;
    audioEncConfig.nFrameStyle = 1;

    mDvrAudioEnc->AutAudioEncInit(&audioEncConfig);
#endif

    int ret = -1;
    if (360 == mCameraId) {
        m360CameraManager = new CameraManager();
        ret = add360Hardware();
        if (ret < 0) {
            return ;
        }

        m360CameraManager->setOviewEnable(false);
        m360CameraManager->setComposeOrder(0,1,2,3); //set position

        for (int i = 0; i < NUM_OF_360CAMERAS; i++) {
            rt = initializeDev(m360Hardware[i]);
            if (!rt) {
                ALOGV("dev init fail repeat");
                return ;
            }
        }
        m360CameraManager->composeBufInit();
        int w,h;
        int id = m360Hardware[0]->mHardwareInfo.device_id;
        if (0 == id) {
            w = 1280;
            h = 720;
        } else {
            if (480 == config_get_heigth(id)) {
                w = 1440;
                h = 960;
            } else {
                w = 2560;
                h = 1440;
            }
        }
        config_set_width(360,w);
        config_set_heigth(360,h);
    } else {
        mHardwareCameras = new CameraHardware();
        if (mHardwareCameras == NULL) {
            ALOGE("%s: Unable to instantiate fake camera class", __FUNCTION__);
            return;
        }

        sprintf(mHardwareCameras->mHardwareInfo.device_name, "/dev/video%d", mCameraId);
        mHardwareCameras->mHardwareInfo.device_id = mCameraId;
        updateHardwareInfo(mHardwareCameras, mCameraId);

        rt = initializeDev(mHardwareCameras);
        if (!rt) {
            ALOGV("initializeDev failed");
            return ;
        }
    }
    mRecordCamera = new RecordCamera(mCameraId);
    mDvrAudioEnc->setAudioEncDataCb(mRecordCamera->audioRecMuxerCb, mRecordCamera);
}

dvr_factory::~dvr_factory()
{
    F_LOG;

    uninitializeDev();
    if (360 == mCameraId) {
        for (int i = 0 ; i < NUM_OF_360CAMERAS; i++) {
            if (m360Hardware[i]!= NULL) {
                delete m360Hardware[i];
                m360Hardware[i] = NULL;
            }
        }

        if (m360CameraManager!= NULL) {
            delete m360CameraManager;
            m360CameraManager = NULL;
        }
    } else {
        if (mHardwareCameras != NULL) {
            delete mHardwareCameras;
            mHardwareCameras = NULL;
            ALOGD("del mHardwareCameras=%p", mHardwareCameras);
        }
    }

#ifdef USE_CDX_LOWLEVEL_API_AUDIO
    mDvrAudioEnc->AutAudioEncDeinit();
    delete mDvrAudioEnc;
#endif

    if (mRecordCamera!=NULL) {
        delete mRecordCamera;
        mRecordCamera = NULL;
    }
}
