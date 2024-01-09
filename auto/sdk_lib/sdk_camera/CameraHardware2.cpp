
#if DBG_CAMERA_HARDWARE
#define LOG_NDEBUG 0
#endif
#define LOG_TAG "CameraHardware"
#include <sdklog.h>
#include "CameraDebug.h"

#include <cutils/properties.h>

#include "CameraHardware2.h"
#include "V4L2CameraDevice2.h"
#include "vencoder.h"
#include "MetadataBufferType.h"
#include "CameraManager.h"
#include <sys/syscall.h>
#include "CameraFileCfg.h"

#define BASE_ZOOM    0

namespace android {

#define GET_CALLING_PID    (syscall(__NR_gettid))

void getCallingProcessName(char *name) {
    char proc_node[128];

    if (name == 0) {
        ALOGE("error in params");
        return;
    }
    memset(proc_node, 0, sizeof(proc_node));
    sprintf(proc_node, "/proc/%ld/cmdline", GET_CALLING_PID);
    int fp =::open(proc_node, O_RDONLY);
    if (fp > 0) {
        memset(name, 0, 128);
        ::read(fp, name, 128);
        ::close(fp);
        fp = 0;
        ALOGD("Calling process is: %s", name);
    } else {
        ALOGE("Obtain calling process failed %s", proc_node);
    }
}

#if DEBUG_PARAM
/* Calculates and logs parameter changes.
 * Param:
 *  current - Current set of camera parameters.
 *  new_par - String representation of new parameters.
 */
    static void PrintParamDiff(const CameraParameters & current, const char *new_par);
#else
    #define PrintParamDiff(current, new_par)   (void(0))
#endif /* DEBUG_PARAM */

/* A helper routine that adds a value to the camera parameter.
 * Param:
 *  param - Camera parameter to add a value to.
 *  val - Value to add.
 * Return:
 *  A new string containing parameter with the added value on success, or NULL on
 *  a failure. If non-NULL string is returned, the caller is responsible for
 *  freeing it with 'free'.
 */
static char *AddValue(const char *param, const char *val);

// Parse string like "640x480" or "10000,20000"
static int parse_pair(const char *str, int *first, int *second, char delim,
                  char **endptr = NULL)
{
    // Find the first integer.
    char *end;
    int w = (int) strtol(str, &end, 10);
    // If a delimeter does not immediately follow, give up.
    if (*end != delim) {
        ALOGE("Cannot find delimeter (%c) in str=%s", delim, str);
        return -1;
    }

    // Find the second integer, immediately after the delimeter.
    int h = (int) strtol(end + 1, &end, 10);

    *first = w;
    *second = h;

    if (endptr) {
        *endptr = end;
    }

    return 0;
}

CameraHardware::CameraHardware()
    :
    mPreviewWindow(),
    mCallbackNotifier(),
    mIsCameraIdle(true),
    mFirstSetParameters(true),
    mFullSizeWidth(0),
    mFullSizeHeight(0),
    mCaptureWidth(0),
    mCaptureHeight(0),
    mVideoCaptureWidth(0),
    mVideoCaptureHeight(0),
    mUseHwEncoder(false),
    mZoomRatio(0),
    mOriention(0),
    mIsImageCaptureIntent(false),
    mCameraManager(NULL)
{
    /*
     * Initialize camera_device descriptor for this object.
     */
    ALOGV("CameraHardware2 construct");
    // instance V4L2CameraDevice object
    mV4L2CameraDevice = new V4L2CameraDevice(this, &mPreviewWindow, &mCallbackNotifier);
    if (mV4L2CameraDevice == NULL) {
        ALOGE("Failed to create V4L2Camera instance");
        return;
    }

    memset(&mHardwareInfo, 0, sizeof(mHardwareInfo));
    // init command queue
    OSAL_QueueCreate(&mQueueCommand, CMD_QUEUE_MAX);
    memset((void *) mQueueElement, 0, sizeof(mQueueElement));

    // init command thread
    pthread_mutex_init(&mCommandMutex, NULL);
    pthread_cond_init(&mCommandCond, NULL);
    mCommandThread = new DoCommandThread(this);
    mCommandThread->startThread();
}

CameraHardware::~CameraHardware()
{
    releaseCamera();

    if (mV4L2CameraDevice != NULL) {
        delete mV4L2CameraDevice;
        mV4L2CameraDevice = NULL;
    }

    if (mCommandThread != NULL) {
        mCommandThread->stopThread();
        pthread_mutex_lock(&mCommandMutex);
        pthread_cond_signal(&mCommandCond);
        pthread_mutex_unlock(&mCommandMutex);
        mCommandThread->join();
        ALOGV("singal mCommandThread quit");
        mCommandThread.clear();
        mCommandThread = 0;
    }

    pthread_mutex_destroy(&mCommandMutex);
    pthread_cond_destroy(&mCommandCond);

    OSAL_QueueTerminate(&mQueueCommand);
}

bool CameraHardware::commandThread()
{
    pthread_mutex_lock(&mCommandMutex);
    if (mCommandThread->getThreadStatus() == THREAD_STATE_EXIT) {
        ALOGD("commandThread exited");
        pthread_mutex_unlock(&mCommandMutex);
        return false;
    }

    Queue_Element *queue = (Queue_Element *) OSAL_Dequeue(&mQueueCommand);
    if (queue == NULL) {
        ALOGV("wait commond queue ......");
        pthread_cond_wait(&mCommandCond, &mCommandMutex);
        pthread_mutex_unlock(&mCommandMutex);
        return true;
    }
    pthread_mutex_unlock(&mCommandMutex);

    V4L2CameraDevice *pV4L2Device = mV4L2CameraDevice;
    int cmd = queue->cmd;
    switch (cmd) {
        case CMD_QUEUE_SET_COLOR_EFFECT:
        {
            int new_image_effect = queue->data;
            ALOGV("CMD_QUEUE_SET_COLOR_EFFECT: %d", new_image_effect);

            if (pV4L2Device->setImageEffect(new_image_effect) < 0) {
                ALOGE("ERR(%s):Fail on mV4L2Camera->setImageEffect(effect(%d))",
                             __FUNCTION__, new_image_effect);
            }
            break;
        }
        case CMD_QUEUE_SET_WHITE_BALANCE:
        {
            int new_white = queue->data;
            ALOGV("CMD_QUEUE_SET_WHITE_BALANCE: %d", new_white);

            if (pV4L2Device->setWhiteBalance(new_white) < 0) {
                ALOGE("ERR(%s):Fail on mV4L2Camera->setWhiteBalance(white(%d))",
                             __FUNCTION__, new_white);
            }
            break;
        }
        case CMD_QUEUE_SET_EXPOSURE_COMPENSATION:
        {
            int new_exposure_compensation = queue->data;
            ALOGV("CMD_QUEUE_SET_EXPOSURE_COMPENSATION: %d", new_exposure_compensation);

            if (pV4L2Device->setExposureCompensation(new_exposure_compensation) < 0) {
                ALOGE("ERR(%s):Fail on mV4L2Camera->setBrightness(brightness(%d))",
                             __FUNCTION__, new_exposure_compensation);
            }
            break;
        }
        case CMD_QUEUE_SET_FLASH_MODE:
        {
            int new_flash = queue->data;
            ALOGV("CMD_QUEUE_SET_FLASH_MODE: %d", new_flash);

            if (pV4L2Device->setFlashMode(new_flash) < 0) {
                ALOGE("ERR(%s):Fail on mV4L2Camera->setFlashMode(flash(%d))", __FUNCTION__,
                             new_flash);
            }
            break;
        }
        case CMD_QUEUE_SET_FOCUS_MODE:
        {
            break;
        }
        case CMD_QUEUE_SET_FOCUS_AREA:
        {
            break;
        }
        case CMD_QUEUE_START_FACE_DETECTE:
        {
            break;
        }
        case CMD_QUEUE_STOP_FACE_DETECTE:
        {
            break;
        }
#ifdef ADAS_ENABLE
        case CMD_QUEUE_START_ADAS_DETECTE:
        {
            ALOGV("CMD_QUEUE_START_ADAS_DETECTE");
            mV4L2CameraDevice->adasInitialize();
            break;
        }
        case CMD_QUEUE_STOP_ADAS_DETECTE:
        {
            ALOGV("CMD_QUEUE_STOP_ADAS_DETECTE");
            mV4L2CameraDevice->adasDestroy();
            break;
        }
#endif
#ifdef WATERMARK
        case CMD_QUEUE_START_WATER_MARK:
        {
            ALOGV("CMD_QUEUE_START_WATER_MARK");
            mV4L2CameraDevice->waterMarkinit();
            break;
        }
        case CMD_QUEUE_STOP_WATER_MARK:
        {
            ALOGV("CMD_QUEUE_STOP_WATER_MARK");
            mV4L2CameraDevice->waterMarkDestroy();
            break;
        }
#endif
#ifdef START_STOP_RENDER
        case CMD_QUEUE_START_RENDER:
        {
            ALOGV("CMD_QUEUE_START_RENDER");
            mPreviewWindow.startPreview();
            break;
        }
        case CMD_QUEUE_STOP_RENDER:
        {
            ALOGV("CMD_QUEUE_STOP_RENDER");
            if (mPreviewWindow.isPreviewEnabled()) {
                mPreviewWindow.stopPreview();
            }
            break;
        }
#endif
        case CMD_QUEUE_TAKE_PICTURE:
        {
            ALOGV("CMD_QUEUE_TAKE_PICTURE");
            break;
        }
        case CMD_QUEUE_PICTURE_MSG:
        {
            ALOGV("CMD_QUEUE_PICTURE_MSG");
            void *frame = (void *) queue->data;
            mCallbackNotifier.notifyPictureMsg(frame);
            break;
        }
        case CMD_QUEUE_STOP_CONTINUOUSSNAP:
        {
            break;
        }
        case CMD_QUEUE_SET_FOCUS_STATUS:
        {
            break;
        }
        default:
        {
            ALOGW("unknown queue command: %d", cmd);
            break;
        }
    }
    return true;
}

/****************************************************************************
 * Public API
 ***************************************************************************/

status_t CameraHardware::Initialize()
{
    F_LOG;

    initDefaultParameters();

    return NO_ERROR;
}

void CameraHardware::initDefaultParameters()
{
    CameraParameters p = mParameters;
    String8 parameterString;
    char value[20];

    ALOGV("initDefaultParameters");

    mCaptureWidth = config_get_width(mHardwareInfo.device_id);
    mCaptureHeight = config_get_heigth(mHardwareInfo.device_id);
    ALOGV("default preview size: %dx%d", mCaptureWidth, mCaptureHeight);
    // check video size support
    mV4L2CameraDevice->tryFmtSize(&mCaptureWidth, &mCaptureHeight);

    // version
    p.set(KEY_CAMERA_HAL_VERSION, CAMERA_HAL_VERSION);

    p.set(CameraHardware::FACING_KEY, CameraHardware::FACING_BACK);

    p.set(CameraHardware::ORIENTATION_KEY, mHardwareInfo.orientation);

    mCallbackNotifier.setExifMake("Allwinner");
    mCallbackNotifier.setExifModel("T113");

    // preview size
    sprintf(value, "%dx%d", mCaptureWidth, mCaptureHeight);
    p.set(CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES, value);
    p.set(CameraParameters::KEY_PREVIEW_SIZE, value);
    p.set(CameraParameters::KEY_VIDEO_SIZE, value);
    ALOGV("[%s]:%s", CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES, value);

    // picture size
    p.set(CameraParameters::KEY_SUPPORTED_PICTURE_SIZES, value);
    p.set(CameraParameters::KEY_PICTURE_SIZE, value);
    mCallbackNotifier.setPictureSize(mCaptureWidth, mCaptureHeight);
    ALOGV("[%s]:%s", CameraParameters::KEY_SUPPORTED_PICTURE_SIZES, value);

    // frame rate
    p.set(CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES, "25");
    p.set(CameraParameters::KEY_PREVIEW_FRAME_RATE, "25");
    ALOGV("[%s]:%s", CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES, "25");
    mV4L2CameraDevice->setFrameRate(25);

    mVideoCaptureWidth = mCaptureWidth;
    mVideoCaptureHeight = mCaptureHeight;

    p.set(KEY_CAPTURE_SIZE_WIDTH, mCaptureWidth);
    p.set(KEY_CAPTURE_SIZE_HEIGHT, mCaptureHeight);
    p.set(KEY_PREVIEW_CAPTURE_SIZE_WIDTH, mCaptureWidth);
    p.set(KEY_PREVIEW_CAPTURE_SIZE_HEIGHT, mCaptureHeight);

    // preview formats
    parameterString = CameraParameters::PIXEL_FORMAT_YUV420SP;    // NV21, default
    parameterString.append(",");
    parameterString.append(CameraParameters::PIXEL_FORMAT_YUV420P);    // YV12
    p.set(CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS, parameterString.string());

    p.set(CameraParameters::KEY_VIDEO_FRAME_FORMAT, CameraParameters::PIXEL_FORMAT_YUV420SP);
    p.set(CameraParameters::KEY_PREVIEW_FORMAT, CameraParameters::PIXEL_FORMAT_YUV420SP);

    p.set(CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS, CameraParameters::PIXEL_FORMAT_JPEG);
    p.set(CameraParameters::KEY_JPEG_QUALITY, "95");    // maximum quality
    p.set(CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES, "320x240,0x0");
    p.set(CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH, "320");
    p.set(CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT, "240");
    p.set(CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY, "90");
    p.setPictureFormat(CameraParameters::PIXEL_FORMAT_JPEG);

    mCallbackNotifier.setJpegRotate(0);
    mCallbackNotifier.setJpegQuality(95);
    mCallbackNotifier.setJpegThumbnailSize(320, 240);

    // record hint
    p.set(CameraParameters::KEY_RECORDING_HINT, "false");

    // rotation
    p.set(CameraParameters::KEY_ROTATION, 0);

    //init keys added for AWGallery
    p.set("snap-path", "");
    p.set("picture-mode", "normal");

    mParameters = p;

    mFirstSetParameters = true;
    ALOGV("CameraHardware::initDefaultParameters ok");
}

void CameraHardware::onCameraDeviceError(int err)
{
    F_LOG;
    /* Errors are reported through the callback notifier */
    mCallbackNotifier.onCameraDeviceError(err);
}

/****************************************************************************
 * Camera API implementation.
 ***************************************************************************/
status_t CameraHardware::setCameraHardwareInfo(HALCameraInfo * halInfo)
{
    // check input params
    if (halInfo == NULL) {
        ALOGE("ERROR camera info");
        return EINVAL;
    }

    memcpy((void *) &mHardwareInfo, (void *) halInfo, sizeof(HALCameraInfo));

    return NO_ERROR;
}

void CameraHardware::setCameraManager(CameraManager * manager)
{
    mCameraManager = manager;
    mV4L2CameraDevice->setCameraManager(mCameraManager);
}

bool CameraHardware::isCameraIdle()
{
    Mutex::Autolock locker(&mCameraIdleLock);
    return mIsCameraIdle;
}

status_t CameraHardware::connectCamera()
{
    F_LOG;
    status_t res = EINVAL;

    {
        Mutex::Autolock locker(&mCameraIdleLock);
        mIsCameraIdle = false;
    }

    if (mV4L2CameraDevice != NULL) {
        res = mV4L2CameraDevice->connectDevice(&mHardwareInfo);
        if (res == NO_ERROR) {
            int format = mV4L2CameraDevice->getCaptureFormat();
            mParameters.set(KEY_CAPTURE_FORMAT, format);
            if (format == V4L2_PIX_FMT_H264) {
                mUseHwEncoder = true;
                mV4L2CameraDevice->setHwEncoder(true);
            }
        } else {
            Mutex::Autolock locker(&mCameraIdleLock);
            mIsCameraIdle = true;
        }
    }
    return -res;
}

void CameraHardware::setCallbacks(notify_callback notify_cb,
                          data_callback data_cb,
                          data_callback_timestamp data_cb_timestamp,
                          void *user)
{
    F_LOG;
    mCallbackNotifier.setCallbacks(
                (camera_notify_callback)notify_cb,
                (camera_data_callback)data_cb,
                (camera_data_timestamp_callback)data_cb_timestamp,
                (void *)user);
}

#ifdef ADAS_ENABLE
void CameraHardware::setAdasCallbacks(camera_adas_data_callback adas_data_cb)
{
    F_LOG;
    mCallbackNotifier.setAdasCallbacks(adas_data_cb);
}

status_t CameraHardware::setAdasParameters(int key, int value)
{
    mV4L2CameraDevice->setAdasParameters(key, value);
    return NO_ERROR;
}
#endif

void CameraHardware::enableMsgType(int32_t msg_type)
{
    if (msg_type & CAMERA_MSG_PREVIEW_FRAME) {
        //HwDisplay* mcd=NULL;
        //mcd=HwDisplay::getInstance();
        //struct view_info vv={0,0,mcd->lcdxres,mcd->lcdyres};
        //struct src_info srcinfo={mCaptureWidth,mCaptureHeight,HWC_FORMAT_YUV420UVC};
        //ALOGV("vx=%d vy=%d sx=%d sy%d",mcd->lcdxres,mcd->lcdyres,mCaptureWidth,mCaptureHeight);
        mPreviewWindow.setPreviewDisplayOn();
    }

    mCallbackNotifier.enableMessage(msg_type);
}

void CameraHardware::disableMsgType(int32_t msg_type)
{
    if (msg_type & CAMERA_MSG_PREVIEW_FRAME) {
        mPreviewWindow.setPreviewDisplayOff();
    }
    mCallbackNotifier.disableMessage(msg_type);
}

int CameraHardware::isMsgTypeEnabled(int32_t msg_type)
{
    return mCallbackNotifier.isMessageEnabled(msg_type);
}

status_t CameraHardware::startPreview()
{
    F_LOG;
    //enableMsgType(CAMERA_MSG_PREVIEW_FRAME);
    Mutex::Autolock locker(&mObjectLock);
    /* Callback should return a negative errno. */
    return -doStartPreview();
}

void CameraHardware::stopPreview()
{
    F_LOG;
    pthread_mutex_lock(&mCommandMutex);
#ifdef ADAS_ENABLE
    mQueueElement[CMD_QUEUE_STOP_ADAS_DETECTE].cmd = CMD_QUEUE_STOP_ADAS_DETECTE;
    OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_STOP_ADAS_DETECTE]);
#endif
#ifdef WATERMARK
    mQueueElement[CMD_QUEUE_STOP_WATER_MARK].cmd = CMD_QUEUE_STOP_WATER_MARK;
    OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_STOP_WATER_MARK]);
#endif
    pthread_mutex_unlock(&mCommandMutex);
    pthread_cond_signal(&mCommandCond);
    ALOGD("stopPreview send mCommandCond");
    Mutex::Autolock locker(&mObjectLock);
    doStopPreview();
}

int CameraHardware::isPreviewEnabled()
{
    F_LOG;
    return mPreviewWindow.isPreviewEnabled();
}

status_t CameraHardware::storeMetaDataInBuffers(int enable)
{
    F_LOG;

    if (enable == false) {
        mUseHwEncoder = false;
        mV4L2CameraDevice->setHwEncoder(false);
    } else {
        mUseHwEncoder = true;
        mV4L2CameraDevice->setHwEncoder(true);
    }
    return OK;
}

status_t CameraHardware::startRecording()
{
    F_LOG;
    ALOGD("startRecording start");
    // video hint
    const char *valstr = mParameters.get(CameraParameters::KEY_RECORDING_HINT);
    if (valstr) {
        ALOGV("KEY_RECORDING_HINT: %s -> true", valstr);
    }

    mParameters.set(KEY_SNAP_PATH, "/tmp/");

    mParameters.set(CameraParameters::KEY_RECORDING_HINT, CameraParameters::TRUE);

    if (mVideoCaptureWidth != mCaptureWidth || mVideoCaptureHeight != mCaptureHeight) {
        doStopPreview();
        doStartPreview();
    }

    /* Callback should return a negative errno. */
    return -mCallbackNotifier.enableVideoRecording();
}

void CameraHardware::stopRecording()
{
    F_LOG;

    mCallbackNotifier.disableVideoRecording();
    ALOGD("F:%s,L:%d", __FUNCTION__, __LINE__);
    //mV4L2CameraDevice->setHwEncoder(false);
}

int CameraHardware::isRecordingEnabled()
{
    F_LOG;
    return mCallbackNotifier.isVideoRecordingEnabled();
}

void CameraHardware::releaseRecordingFrame(const void *opaque)
{
    if (mUseHwEncoder) {
        int buffer_type = *(int *) (opaque);

        if (buffer_type != kMetadataBufferTypeCameraSource) {
            //ALOGE("releaseRecordingFrame,error buffer type: %d", buffer_type);
        }

        if ((mCameraManager != NULL) && (mCameraManager->isOviewEnable())) {

        } else {
            mV4L2CameraDevice->releasePreviewFrame(((VencInputBuffer *) (opaque + 4))->nID);
        }
    }
}

int CameraHardware::getTVINSystemType()
{
    return mV4L2CameraDevice->getTVINSystemType();
}

int CameraHardware::getFrameWidth()
{
    return mV4L2CameraDevice->getFrameWidth();
}

int CameraHardware::getFrameHeight()
{
    return mV4L2CameraDevice->getFrameHeight();
}

void CameraHardware::releasePreviewFrame(int index)
{
    mV4L2CameraDevice->releasePreviewFrame(index);
}

void CameraHardware::setAnalogInputColor(int brightness, int contrast, int saturation)
{
    F_LOG;
    //mV4L2CameraDevice->setAnalogInputColor(brightness, contrast, saturation);
}

/****************************************************************************
 * Focus
 ***************************************************************************/
status_t CameraHardware::setAutoFocus()
{
    F_LOG;
    return OK;
}

status_t CameraHardware::cancelAutoFocus()
{
    F_LOG;
    return OK;
}

/****************************************************************************
 * take picture management
 ***************************************************************************/
status_t CameraHardware::takePicture()
{
    F_LOG;
    Mutex::Autolock locker(&mObjectLock);

    /* Get JPEG quality. */
    int jpeg_quality = mParameters.getInt(CameraParameters::KEY_JPEG_QUALITY);
    if (jpeg_quality <= 0) {
        jpeg_quality = 90;
    }

    /* Get JPEG rotate. */
    int jpeg_rotate = mParameters.getInt(CameraParameters::KEY_ROTATION);
    if (jpeg_rotate <= 0) {
        jpeg_rotate = 0;    /* Fall back to default. */
    }

    /* Get JPEG size. */
    int pic_width, pic_height;
    mParameters.getPictureSize(&pic_width, &pic_height);

    mCallbackNotifier.setJpegQuality(jpeg_quality);
    mCallbackNotifier.setJpegRotate(jpeg_rotate);
    mCallbackNotifier.setPictureSize(pic_width, pic_height);

    // if in recording mode
    const char *valstr = mParameters.get(CameraParameters::KEY_RECORDING_HINT);
    bool video_hint = (strcmp(valstr, CameraParameters::TRUE) == 0);
    if (video_hint) {
        mV4L2CameraDevice->setTakePictureState(TAKE_PICTURE_RECORD);
    } else {
        mV4L2CameraDevice->setTakePictureState(TAKE_PICTURE_NORMAL);
    }

    return OK;
}

status_t CameraHardware::cancelPicture()
{
    F_LOG;
    mV4L2CameraDevice->setTakePictureState(TAKE_PICTURE_NULL);

    return NO_ERROR;
}

void CameraHardware::notifyPictureMsg(const void *frame)
{
    pthread_mutex_lock(&mCommandMutex);
    mQueueElement[CMD_QUEUE_PICTURE_MSG].cmd = CMD_QUEUE_PICTURE_MSG;
    mQueueElement[CMD_QUEUE_PICTURE_MSG].data = (unsigned long) frame;
    OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_PICTURE_MSG]);
    pthread_cond_signal(&mCommandCond);
    pthread_mutex_unlock(&mCommandMutex);
}

/****************************************************************************
 * set and get parameters
 ***************************************************************************/
void CameraHardware::setVideoCaptureSize(int video_w, int video_h)
{
    ALOGD("setVideoCaptureSize next version to do ......");

    // video size is video_w x video_h, capture size may be different
    // now the same
    mVideoCaptureWidth = video_w;
    mVideoCaptureHeight = video_h;

    int videoCaptureWidth = mVideoCaptureWidth;
    int videoCaptureHeight = mVideoCaptureHeight;

    int ret = mV4L2CameraDevice->tryFmtSize(&videoCaptureWidth, &videoCaptureHeight);
    if (ret < 0) {
        ALOGE("setVideoCaptureSize tryFmtSize failed");
        return;
    }

    float widthRate = (float) videoCaptureWidth / (float) mVideoCaptureWidth;
    float heightRate = (float) videoCaptureHeight / (float) mVideoCaptureHeight;

    if ((widthRate > 4.0) && (heightRate > 4.0)) {
        mV4L2CameraDevice->setThumbUsedForVideo(true);
        mV4L2CameraDevice->setVideoSize(video_w, video_h);
        mVideoCaptureWidth = videoCaptureWidth;
        mVideoCaptureHeight = videoCaptureHeight;
        mParameters.set(KEY_CAPTURE_SIZE_WIDTH, videoCaptureWidth / 2);
        mParameters.set(KEY_CAPTURE_SIZE_HEIGHT, videoCaptureHeight / 2);
    } else {
        mV4L2CameraDevice->setThumbUsedForVideo(false);
        mVideoCaptureWidth = videoCaptureWidth;
        mVideoCaptureHeight = videoCaptureHeight;
        mParameters.set(KEY_CAPTURE_SIZE_WIDTH, videoCaptureWidth);
        mParameters.set(KEY_CAPTURE_SIZE_HEIGHT, videoCaptureHeight);
    }
}

void CameraHardware::getCurrentOriention(int *oriention)
{
    *oriention = mOriention;
}

status_t CameraHardware::setParameters(const char *p)
{
    F_LOG;
    int ret = UNKNOWN_ERROR;

    PrintParamDiff(mParameters, p);

    CameraParameters params;
    String8 str8_param(p);
    params.unflatten(str8_param);

    V4L2CameraDevice *pV4L2Device = mV4L2CameraDevice;
    if (pV4L2Device == NULL) {
        ALOGE("%s : getCameraDevice failed", __FUNCTION__);
        return UNKNOWN_ERROR;
    }

    // picture mode
    const char *new_path = params.get(KEY_SNAP_PATH);
    ALOGV("%s : snap new_path : %s", __FUNCTION__, new_path);
    if (new_path != NULL) {
        mParameters.set(KEY_SNAP_PATH, new_path);
        mCallbackNotifier.setSnapPath(new_path);
    }

    // preview format
    const char *new_preview_format = params.getPreviewFormat();
    ALOGV("%s : new_preview_format : %s", __FUNCTION__, new_preview_format);
    if (new_preview_format != NULL
            && (strcmp(new_preview_format, CameraParameters::PIXEL_FORMAT_YUV420SP) == 0
                || strcmp(new_preview_format, CameraParameters::PIXEL_FORMAT_YUV420P) == 0)) {
        mParameters.setPreviewFormat(new_preview_format);
    } else {
        ALOGE("%s : Only yuv420sp or yuv420p preview is supported", __FUNCTION__);
        return -EINVAL;
    }

    // picture size
    int new_picture_width = 0;
    int new_picture_height = 0;
    params.getPictureSize(&new_picture_width, &new_picture_height);
    ALOGV("%s : new_picture_width x new_picture_height = %dx%d", __FUNCTION__, new_picture_width,
             new_picture_height);
    if (0 < new_picture_width && 0 < new_picture_height) {
        mCallbackNotifier.setPictureSize(new_picture_width, new_picture_height);
        mParameters.setPictureSize(new_picture_width, new_picture_height);
    } else {
        ALOGE("%s : error picture size", __FUNCTION__);
        return -EINVAL;
    }

    // video hint
    const char *valstr = params.get(CameraParameters::KEY_RECORDING_HINT);
    if (valstr) {
        ALOGV("%s : KEY_RECORDING_HINT: %s", __FUNCTION__, valstr);
        mParameters.set(CameraParameters::KEY_RECORDING_HINT, valstr);
    }

    // frame rate
    int new_preview_frame_rate = params.getPreviewFrameRate();
    if (0 < new_preview_frame_rate) {
        int preview_frame_rate = mParameters.getPreviewFrameRate();
        if (preview_frame_rate != new_preview_frame_rate) {
            mParameters.setPreviewFrameRate(new_preview_frame_rate);
            pV4L2Device->setFrameRate(new_preview_frame_rate);
        }
    }

    // JPEG image quality
    int new_jpeg_quality = params.getInt(CameraParameters::KEY_JPEG_QUALITY);
    ALOGV("%s : new_jpeg_quality %d", __FUNCTION__, new_jpeg_quality);
    if (new_jpeg_quality >= 1 && new_jpeg_quality <= 100) {
        mCallbackNotifier.setJpegQuality(new_jpeg_quality);
        mParameters.set(CameraParameters::KEY_JPEG_QUALITY, new_jpeg_quality);
    }

    // gps latitude
    const char *new_gps_latitude_str = params.get(CameraParameters::KEY_GPS_LATITUDE);
    if (new_gps_latitude_str) {
        mCallbackNotifier.setGPSLatitude(atof(new_gps_latitude_str));
        mParameters.set(CameraParameters::KEY_GPS_LATITUDE, new_gps_latitude_str);
    } else {
        mCallbackNotifier.setGPSLatitude(0.0);
        mParameters.remove(CameraParameters::KEY_GPS_LATITUDE);
    }

    // gps longitude
    const char *new_gps_longitude_str = params.get(CameraParameters::KEY_GPS_LONGITUDE);
    if (new_gps_longitude_str) {
        mCallbackNotifier.setGPSLongitude(atof(new_gps_longitude_str));
        mParameters.set(CameraParameters::KEY_GPS_LONGITUDE, new_gps_longitude_str);
    } else {
        mCallbackNotifier.setGPSLongitude(0.0);
        mParameters.remove(CameraParameters::KEY_GPS_LONGITUDE);
    }

    // gps altitude
    const char *new_gps_altitude_str = params.get(CameraParameters::KEY_GPS_ALTITUDE);
    if (new_gps_altitude_str) {
        mCallbackNotifier.setGPSAltitude(atol(new_gps_altitude_str));
        mParameters.set(CameraParameters::KEY_GPS_ALTITUDE, new_gps_altitude_str);
    } else {
        mCallbackNotifier.setGPSAltitude(0);
        mParameters.remove(CameraParameters::KEY_GPS_ALTITUDE);
    }

    // gps timestamp
    const char *new_gps_timestamp_str = params.get(CameraParameters::KEY_GPS_TIMESTAMP);
    if (new_gps_timestamp_str) {
        mCallbackNotifier.setGPSTimestamp(atol(new_gps_timestamp_str));
        mParameters.set(CameraParameters::KEY_GPS_TIMESTAMP, new_gps_timestamp_str);
    } else {
        mCallbackNotifier.setGPSTimestamp(0);
        mParameters.remove(CameraParameters::KEY_GPS_TIMESTAMP);
    }

    // gps processing method
    const char *new_gps_processing_method_str =
            params.get(CameraParameters::KEY_GPS_PROCESSING_METHOD);
    if (new_gps_processing_method_str) {
        mCallbackNotifier.setGPSMethod(new_gps_processing_method_str);
        mParameters.set(CameraParameters::KEY_GPS_PROCESSING_METHOD,
                            new_gps_processing_method_str);
    } else {
        mCallbackNotifier.setGPSMethod("");
        mParameters.remove(CameraParameters::KEY_GPS_PROCESSING_METHOD);
    }

    mFirstSetParameters = false;
    pthread_cond_signal(&mCommandCond);

    return NO_ERROR;
}

/* A dumb variable indicating "no params" / error on the exit from
 * CameraHardware::getParameters(). */
static char lNoParam = '\0';
char *CameraHardware::getParameters()
{
    F_LOG;
    String8 params(mParameters.flatten());
    char *ret_str = reinterpret_cast < char *>(malloc(sizeof(char) * (params.length() + 1)));
    if (ret_str != NULL) {
        memset(ret_str, 0, params.length() + 1);
        strncpy(ret_str, params.string(), params.length() + 1);
        return ret_str;
    } else {
        ALOGE("%s: Unable to allocate string for %s", __FUNCTION__, params.string());
        /* Apparently, we can't return NULL fron this routine. */
        return &lNoParam;
    }
}

void CameraHardware::putParameters(char *params)
{
    F_LOG;
    /* This method simply frees parameters allocated in getParameters(). */
    if (params != NULL && params != &lNoParam) {
        free(params);
    }
}

#ifdef WATERMARK
status_t CameraHardware::setWaterMarkMultiple(char *mWaterMark, int dispMode)
{
    mCallbackNotifier.setWaterMarkMultiple(mWaterMark);
    mV4L2CameraDevice->setWaterMarkDispMode(dispMode);
    return NO_ERROR;
}
#endif

//public flip setting
status_t CameraHardware::setCameraFlipStatus(int flipEnable)
{
    mV4L2CameraDevice->setCameraFlipStatus(flipEnable);
    ALOGV("%s : flipEnable = %d", __FUNCTION__, flipEnable);
    return NO_ERROR;
}
//end

status_t CameraHardware::setFd(int fd)
{
    return NO_ERROR;
}

void CameraHardware::setNewCrop(Rect * rect)
{
    F_LOG;
}

status_t CameraHardware::sendCommand(int32_t cmd, unsigned long arg1, int32_t arg2)
{
    ALOGV("%s: cmd = 0x%x, arg1 = %d, arg2 = %d", __FUNCTION__, cmd, arg1, arg2);

    /* TODO: Future enhancements. */
    switch (cmd) {
        case CAMERA_CMD_SET_WHITE_BALANCE:
            ALOGD("sendCommand --- CAMERA_CMD_SET_WHITE_BALANCE");
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_SET_WHITE_BALANCE].cmd = CMD_QUEUE_SET_WHITE_BALANCE;
            mQueueElement[CMD_QUEUE_SET_WHITE_BALANCE].data = arg1;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_SET_WHITE_BALANCE]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_SET_EXPOSURE_COMPENSATION:
            ALOGD("sendCommand --- CAMERA_CMD_SET_EXPOSURE_COMPENSATION");
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_SET_EXPOSURE_COMPENSATION].cmd =
                    CMD_QUEUE_SET_EXPOSURE_COMPENSATION;
            mQueueElement[CMD_QUEUE_SET_EXPOSURE_COMPENSATION].data = arg1;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_SET_EXPOSURE_COMPENSATION]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_SET_COLOR_EFFECT:
            ALOGD("sendCommand --- CAMERA_CMD_SET_COLOR_EFFECT");
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_SET_COLOR_EFFECT].cmd = CMD_QUEUE_SET_COLOR_EFFECT;
            mQueueElement[CMD_QUEUE_SET_COLOR_EFFECT].data = arg1;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_SET_COLOR_EFFECT]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_SET_GPSDATA_RECORDER:
            mV4L2CameraDevice->setGpsData((void *) arg1);
            return OK;
        case CAMERA_CMD_SET_CEDARX_RECORDER:
            mUseHwEncoder = true;
            mV4L2CameraDevice->setHwEncoder(true);
            return OK;
        case CAMERA_CMD_START_FACE_DETECTION:
            ALOGD("CMD_START_FACE_DETECTION not support!");
            return OK;
        case CAMERA_CMD_STOP_FACE_DETECTION:
            ALOGD("CMD_STOP_FACE_DETECTION not support!");
            return OK;
#ifdef WATERMARK
        case CAMERA_CMD_START_WATER_MARK:
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_START_WATER_MARK].cmd = CMD_QUEUE_START_WATER_MARK;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_START_WATER_MARK]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_STOP_WATER_MARK:
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_STOP_WATER_MARK].cmd = CMD_QUEUE_STOP_WATER_MARK;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_STOP_WATER_MARK]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
#endif
#ifdef START_STOP_RENDER
        case CAMERA_CMD_STOP_RENDER:
            ALOGV("CAMERA_CMD_STOP_RENDER");
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_STOP_RENDER].cmd = CMD_QUEUE_STOP_RENDER;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_STOP_RENDER]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_START_RENDER:
            ALOGV("CAMERA_CMD_START_RENDER");
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_START_RENDER].cmd = CMD_QUEUE_START_RENDER;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_START_RENDER]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
#endif
#ifdef ADAS_ENABLE
        case CAMERA_CMD_START_ADAS_DETECTION:
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_START_ADAS_DETECTE].cmd = CMD_QUEUE_START_ADAS_DETECTE;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_START_ADAS_DETECTE]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
        case CAMERA_CMD_STOP_ADAS_DETECTION:
            pthread_mutex_lock(&mCommandMutex);
            mQueueElement[CMD_QUEUE_STOP_ADAS_DETECTE].cmd = CMD_QUEUE_STOP_ADAS_DETECTE;
            OSAL_Queue(&mQueueCommand, &mQueueElement[CMD_QUEUE_STOP_ADAS_DETECTE]);
            pthread_cond_signal(&mCommandCond);
            pthread_mutex_unlock(&mCommandMutex);
            return OK;
#endif
        case CAMERA_CMD_PING:
            ALOGD("CMD_PING not support!");
            return OK;
        case CAMERA_CMD_ENABLE_FOCUS_MOVE_MSG:
            ALOGD("CMD_ENABLE_FOCUS_MOVE_MSG not support!");
            return OK;
        case CAMERA_CMD_SET_DISPLAY_ORIENTATION:
            ALOGD("CMD_SET_DISPLAY_ORIENTATION not support!");
            return OK;
        default:
            break;
    }
    return -EINVAL;
}

status_t CameraHardware::setPreviewParam(struct view_info pvi, struct src_info psi, int tvout,
                             int tvch)
{
    ALOGV("%s", __FUNCTION__);
    mPreviewWindow.setPreviewParam(pvi, psi, tvout, tvch);

    return NO_ERROR;
}

void CameraHardware::releaseCamera()
{
    ALOGV("%s", __FUNCTION__);
    cleanupCamera();
}

status_t CameraHardware::dumpCamera(int fd)
{
    ALOGV("%s", __FUNCTION__);

    /* TODO: Future enhancements. */
    return -EINVAL;
}

/****************************************************************************
 * Preview management.
 ***************************************************************************/
status_t CameraHardware::doStartPreview()
{
    F_LOG;

    V4L2CameraDevice *const camera_dev = mV4L2CameraDevice;

    if (camera_dev->isStarted()
            && mPreviewWindow.isPreviewEnabled()) {
        ALOGD("CameraHardware::doStartPreview has been already started");
        return NO_ERROR;
    }

    if (camera_dev->isStarted()) {
        camera_dev->stopDeliveringFrames();
        camera_dev->stopDevice();
    }

    ALOGD("doStartPreview start");
    status_t res = mPreviewWindow.startPreview();
    if (res != NO_ERROR) {
        return res;
    }

    // Make sure camera device is connected.
    if (!camera_dev->isConnected()) {
        res = camera_dev->connectDevice(&mHardwareInfo);
        if (res != NO_ERROR) {
            mPreviewWindow.stopPreview();
            return res;
        }
    }

    mVideoCaptureWidth = mCaptureWidth;
    mVideoCaptureHeight = mCaptureHeight;
    uint32_t org_fmt = V4L2_PIX_FMT_NV21;
    ALOGD("CameraID[%d] mVideoCapture(%dx%d)", mHardwareInfo.device_id,
                mVideoCaptureWidth, mVideoCaptureHeight);
    res = camera_dev->startDevice(mCaptureWidth, mCaptureHeight, org_fmt, 1);
    if (res != NO_ERROR) {
        mPreviewWindow.stopPreview();
        return res;
    }
    F_LOG;

    res = camera_dev->startDeliveringFrames();
    if (res != NO_ERROR) {
        camera_dev->stopDevice();
        mPreviewWindow.stopPreview();
    }
    F_LOG;

    return res;
}

status_t CameraHardware::doStopPreview()
{
    F_LOG;

    status_t res = NO_ERROR;
    if (mPreviewWindow.isPreviewEnabled()) {
        /* Stop the camera. */
        if (mV4L2CameraDevice->isStarted()) {
            mV4L2CameraDevice->stopDeliveringFrames();
            res = mV4L2CameraDevice->stopDevice();
        }

        if (res == NO_ERROR) {
            /* Disable preview as well. */
            mPreviewWindow.stopPreview();
        }
    }

    return NO_ERROR;
}

/****************************************************************************
 * Private API.
 ***************************************************************************/
status_t CameraHardware::cleanupCamera()
{
    F_LOG;

    status_t res = NO_ERROR;

    mParameters.set(KEY_SNAP_PATH, "");
    mCallbackNotifier.setSnapPath("");

    mParameters.set(KEY_PICTURE_MODE, "normal");

    // reset preview format to yuv420sp
    mParameters.set(CameraParameters::KEY_PREVIEW_FORMAT,
                CameraParameters::PIXEL_FORMAT_YUV420SP);

    mV4L2CameraDevice->setHwEncoder(false);

    mParameters.set(CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH, 320);
    mParameters.set(CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT, 240);

    mParameters.set(CameraParameters::KEY_ZOOM, 0);

    mVideoCaptureWidth = 0;
    mVideoCaptureHeight = 0;
    mUseHwEncoder = false;

    /* If preview is running - stop it. */
    res = doStopPreview();
    if (res != NO_ERROR) {
        return -res;
    }
    F_LOG
    /* Stop and disconnect the camera device. */
    V4L2CameraDevice * const camera_dev = mV4L2CameraDevice;
    if (camera_dev != NULL) {
        if (camera_dev->isStarted()) {
            camera_dev->stopDeliveringFrames();
            F_LOG
            res = camera_dev->stopDevice();
            F_LOG
            if (res != NO_ERROR) {
                return -res;
            }
            F_LOG
        }

        if (camera_dev->isConnected()) {
            F_LOG
            res = camera_dev->disconnectDevice();
            if (res != NO_ERROR) {
                return -res;
            }
        }
    }
    F_LOG

    mCallbackNotifier.cleanupCBNotifier();

    {
        Mutex::Autolock locker(&mCameraIdleLock);
        mIsCameraIdle = true;
    }
    F_LOG
    return NO_ERROR;
}

/****************************************************************************
 * Common keys
 ***************************************************************************/
const char CameraHardware::FACING_KEY[] = "prop-facing";
const char CameraHardware::ORIENTATION_KEY[] = "prop-orientation";
const char CameraHardware::RECORDING_HINT_KEY[] = "recording-hint";

/****************************************************************************
 * Common string values
 ***************************************************************************/

const char CameraHardware::FACING_BACK[] = "back";
const char CameraHardware::FACING_FRONT[] = "front";

/****************************************************************************
 * Helper routines
 ***************************************************************************/

static char *AddValue(const char *param, const char *val) {
    const size_t len1 = strlen(param);
    const size_t len2 = strlen(val);
    char *ret = reinterpret_cast < char *>(malloc(len1 + len2 + 2));
    //LOGE_IF(ret == NULL, "%s: Memory failure", __FUNCTION__);
    if (ret != NULL) {
        memcpy(ret, param, len1);
        ret[len1] = ',';
        memcpy(ret + len1 + 1, val, len2);
        ret[len1 + len2 + 1] = '\0';
    }
    return ret;
}

/****************************************************************************
 * Parameter debugging helpers
 ***************************************************************************/

#if DEBUG_PARAM
    static void PrintParamDiff(const CameraParameters & current, const char *new_par) {
        char tmp[2048];
        const char *wrk = new_par;

        /* Divided with ';' */
        const char *next = strchr(wrk, ';');
        while (next != NULL) {
            snprintf(tmp, sizeof(tmp), "%.*s", next - wrk, wrk);
            /* in the form key=value */
            char *val = strchr(tmp, '=');
            if (val != NULL) {
                *val = '\0';
                val++;
                const char *in_current = current.get(tmp);
                if (in_current != NULL) {
                    if (strcmp(in_current, val)) {
                        ALOGD("=== Value changed: %s: %s -> %s", tmp, in_current, val);
                    }
                }
                else {
                    ALOGD("+++ New parameter: %s=%s", tmp, val);
                }
            }
            else {
                ALOGW("No value separator in %s", tmp);
            }
            wrk = next + 1;
            next = strchr(wrk, ';');
        }
    }
#endif /* DEBUG_PARAM */

};    /* namespace android */
