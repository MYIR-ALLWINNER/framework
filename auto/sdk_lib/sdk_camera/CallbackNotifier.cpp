
#include "CameraDebug.h"
#if DBG_CALLBACK
#define LOG_NDEBUG 0
#endif
#define LOG_TAG "CallbackNotifier"
#include <sdklog.h>

#include "V4L2CameraDevice2.h"
#include "CallbackNotifier.h"

#ifdef ADAS_ENABLE
#include "AdasProcess.h"
#include "Adas_interface.h"
#endif

#include "vencoder.h"
#include "MetadataBufferType.h"
#include <stdio.h>
#include <stdlib.h>
#include "vencoder.h"

#ifndef CDX_V27
#include "log.h"
#endif

#include <unistd.h>
using namespace std;

static long long GetNowUs()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000 + now.tv_usec;
}

extern int JpegEnc(void *pBufOut, int *bufSize, JPEG_ENC_t * jpeg_enc);

namespace android {

/* String representation of camera messages. */
static const char *lCameraMessages[] = {
    "CAMERA_MSG_ERROR",
    "CAMERA_MSG_SHUTTER",
    "CAMERA_MSG_FOCUS",
    "CAMERA_MSG_ZOOM",
    "CAMERA_MSG_PREVIEW_FRAME",
    "CAMERA_MSG_VIDEO_FRAME",
    "CAMERA_MSG_POSTVIEW_FRAME",
    "CAMERA_MSG_RAW_IMAGE",
    "CAMERA_MSG_COMPRESSED_IMAGE",
    "CAMERA_MSG_RAW_IMAGE_NOTIFY",
    "CAMERA_MSG_PREVIEW_METADATA",
    "CAMERA_MSG_CONTINUOUSSNAP",
    "CAMERA_MSG_SNAP",
    "CAMERA_MSG_SNAP_THUMB",
    "CAMERA_MSG_SNAP_FD",
#ifdef ADAS_ENABLE
    "CAMERA_MSG_ADAS_METADATA"
#endif
};
static const int lCameraMessagesNum = sizeof(lCameraMessages) / sizeof(char *);

/* Builds an array of strings for the given set of messages.
 * Param:
 *  msg - Messages to get strings for,
 *  strings - Array where to save strings
 *  max - Maximum number of entries in the array.
 * Return:
 *  Number of strings saved into the 'strings' array.
 */
static int GetMessageStrings(uint32_t msg, const char **strings, int max) {
    int index = 0;
    int out = 0;
    while (msg != 0 && out < max && index < lCameraMessagesNum) {
        while ((msg & 0x1) == 0 && index < lCameraMessagesNum) {
            msg >>= 1;
            index++;
        }
        if ((msg & 0x1) != 0 && index < lCameraMessagesNum) {
            strings[out] = lCameraMessages[index];
            out++;
            msg >>= 1;
            index++;
        }
    }
    return out;
}

/* Logs messages, enabled by the mask. */
#if DEBUG_MSG
    static void PrintMessages(uint32_t msg) {
        const char *strs[lCameraMessagesNum];
        const int translated = GetMessageStrings(msg, strs, lCameraMessagesNum);
        for (int n = 0; n < translated; n++) {
            ALOGV("    %s", strs[n]);
        }
    }
#else
    #define PrintMessages(msg)   (void(0))
#endif

CallbackNotifier::CallbackNotifier()
    : mNotifyCB(NULL),
        mDataCB(NULL),
        mDataCBTimestamp(NULL),
        mCallbackCookie(NULL),
        mMessageEnabler(0),
        mVideoRecEnabled(false),
        mJpegQuality(90),
        mJpegRotate(0),
        mPictureWidth(640),
        mPictureHeight(480),
        mThumbWidth(0),
        mThumbHeight(0),
        mGpsLatitude(0.0),
        mGpsLongitude(0.0),
        mGpsAltitude(0),
        mGpsTimestamp(0)
{
    ALOGV("CallbackNotifier construct");

    memset(mGpsMethod, 0, sizeof(mGpsMethod));

    strcpy(mExifMake, "Allwinner");
    strcpy(mExifModel, "T113");
    memset(mDateTime, 0, sizeof(mDateTime));
    strcpy(mDateTime, "2012:10:24 17:30:00");

    memset(mFolderPath, 0, sizeof(mFolderPath));
    memset(mSnapPath, 0, sizeof(mSnapPath));
#ifdef WATERMARK
    strcpy(mWaterMarkMultiple, "NULL VALUE");
#endif
}

CallbackNotifier::~CallbackNotifier()
{
    ALOGV("CallbackNotifier disconstruct");
}

/****************************************************************************
 * Camera API
 ***************************************************************************/

void CallbackNotifier::setCallbacks(camera_notify_callback notify_cb,
                            camera_data_callback data_cb,
                            camera_data_timestamp_callback data_cb_timestamp,
                             void *user)
{
    ALOGV("%s: %p, %p, %p (%p)",
             __FUNCTION__, notify_cb, data_cb, data_cb_timestamp, user);

    Mutex::Autolock locker(&mObjectLock);
    mNotifyCB = notify_cb;
    // takepicture data cb
    mDataCB = data_cb;
    // record data cb
    mDataCBTimestamp = data_cb_timestamp;
    mCallbackCookie = user;
}

#ifdef ADAS_ENABLE
void CallbackNotifier::setAdasCallbacks(camera_adas_data_callback adas_data_cb)
{
    mAdasDataCB = adas_data_cb;
}
#endif

void CallbackNotifier::enableMessage(uint msg_type)
{
    ALOGV("%s: msg_type = 0x%x", __FUNCTION__, msg_type);
    PrintMessages(msg_type);

    Mutex::Autolock locker(&mObjectLock);
    mMessageEnabler |= msg_type;
    ALOGV("**** Currently enabled messages:");
    PrintMessages(mMessageEnabler);
}

void CallbackNotifier::disableMessage(uint msg_type)
{
    ALOGV("%s: msg_type = 0x%x", __FUNCTION__, msg_type);
    PrintMessages(msg_type);

    Mutex::Autolock locker(&mObjectLock);
    mMessageEnabler &= ~msg_type;
    ALOGV("**** Currently disable messages:");
    PrintMessages(mMessageEnabler);
}

status_t CallbackNotifier::enableVideoRecording()
{
    F_LOG;

    Mutex::Autolock locker(&mObjectLock);
    mVideoRecEnabled = true;

    return NO_ERROR;
}

void CallbackNotifier::disableVideoRecording()
{
    F_LOG;

    Mutex::Autolock locker(&mObjectLock);
    mVideoRecEnabled = false;
}

status_t CallbackNotifier::storeMetaDataInBuffers(bool enable)
{
    /* Return INVALID_OPERATION means HAL does not support metadata. So HAL will
     * return actual frame data with CAMERA_MSG_VIDEO_FRAME. Return
     * INVALID_OPERATION to mean metadata is not supported.
     */
    return UNKNOWN_ERROR;
}

/****************************************************************************
 * Public API
 ***************************************************************************/

void CallbackNotifier::cleanupCBNotifier()
{
    F_LOG
    Mutex::Autolock locker(&mObjectLock);
    mMessageEnabler = 0;
    mNotifyCB = NULL;
    mDataCB = NULL;
    mDataCBTimestamp = NULL;
    mCallbackCookie = NULL;
    mVideoRecEnabled = false;
    mJpegQuality = 90;
    mJpegRotate = 0;
    mPictureWidth = 640;
    mPictureHeight = 480;
    mThumbWidth = 0;
    mThumbHeight = 0;
    mGpsLatitude = 0.0;
    mGpsLongitude = 0.0;
    mGpsAltitude = 0;
    mGpsTimestamp = 0;
    F_LOG
}

void CallbackNotifier::onNextFrameAvailable(const void *frame, bool hw, int channel)
{
    if (hw) {
        onNextFrameHW(frame, channel);
    } else {
        onNextFrameSW(frame, channel);
    }
}

#ifdef ADAS_ENABLE
status_t CallbackNotifier::adasResultMsg(void *adas)
{
    ADASOUT_IF *pbuffer = (ADASOUT_IF *) adas;
    if (isMessageEnabled(CAMERA_MSG_ADAS_METADATA)) {
        char *cam_buff = (char *)malloc(sizeof(ADASOUT_IF));
        if (NULL == cam_buff) {
            ALOGE("%s: Memory failure in CAMERA_MSG_ADAS_METADATA", __FUNCTION__);
            return NO_MEMORY;
        }
        mAdasDataCB(CAMERA_MSG_ADAS_METADATA, (const char *)cam_buff, 0, adas, mCallbackCookie);
        if(!cam_buff)
            free(cam_buff);
    }
    return NO_ERROR;
}
#endif

void CallbackNotifier::onNextFrameHW(const void *frame, int channel)
{
    V4L2BUF_t *pbuf = (V4L2BUF_t *) frame;
#if 0
    VencInputBuffer sInputBuffer;

    //int buffer_type = kMetadataBufferTypeCameraSource;    //matadataType
    memset(&sInputBuffer, 0, sizeof(VencInputBuffer));

    sInputBuffer.pAddrVirY = (unsigned char *) pbuf->addrVirY;
    sInputBuffer.pAddrVirC = (unsigned char *) pbuf->addrVirC;
    sInputBuffer.pAddrPhyY = (unsigned char *) pbuf->addrPhyY;
    sInputBuffer.pAddrPhyC = (unsigned char *) pbuf->addrPhyC;
    sInputBuffer.nID = pbuf->index;
    sInputBuffer.nPts = pbuf->timeStamp;

    if ((pbuf->bytesused > 0) && (SONIX_CAMERA_H264 == 1)) {
        sInputBuffer.nFlag = pbuf->bytesused;
    }

    if (pbuf->width == (unsigned int)pbuf->crop_rect.width || pbuf->height == (unsigned int)pbuf->crop_rect.height) {
        sInputBuffer.bEnableCorp = 0;
    } else {
        //sInputBuffer.bEnableCorp = 1;
        sInputBuffer.sCropInfo.nLeft = pbuf->crop_rect.left;
        sInputBuffer.sCropInfo.nTop = pbuf->crop_rect.top;
        sInputBuffer.sCropInfo.nWidth = pbuf->crop_rect.width;
        sInputBuffer.sCropInfo.nHeight = pbuf->crop_rect.height;
    }
#endif

    //char * cam_buff = (char *)malloc(sizeof(VencInputBuffer) );
    if (isMessageEnabled(CAMERA_MSG_VIDEO_FRAME) && isVideoRecordingEnabled()) {
        mDataCBTimestamp(pbuf->timeStamp, CAMERA_MSG_VIDEO_FRAME,
                     (const char *)pbuf, mCallbackCookie);
    }
}

void CallbackNotifier::onNextFrameSW(const void *frame, int channel)
{
    return ;
}

void CallbackNotifier::notifyPictureMsg(const void *frame)
{
    F_LOG;

    V4L2BUF_t *pbuf = (V4L2BUF_t *) frame;
    int framesize = pbuf->width * pbuf->height * 3 / 2;

    // shutter msg
    if (isMessageEnabled(CAMERA_MSG_SHUTTER)) {
        F_LOG;
        mNotifyCB(CAMERA_MSG_SHUTTER, 0, 0, mCallbackCookie);
    }

    // raw image msg
    if (isMessageEnabled(CAMERA_MSG_RAW_IMAGE)) {
        char *dummyRaw = (char*)malloc(1);
        if (NULL == dummyRaw) {
            ALOGE("%s: Memory failure in CAMERA_MSG_PREVIEW_FRAME", __FUNCTION__);
            return;
        }
        mDataCB(CAMERA_MSG_RAW_IMAGE, dummyRaw, NULL, mCallbackCookie);
        if(!dummyRaw)
            free(dummyRaw);
    } else if (isMessageEnabled(CAMERA_MSG_RAW_IMAGE_NOTIFY)) {
        mNotifyCB(CAMERA_MSG_RAW_IMAGE_NOTIFY, 0, 0, mCallbackCookie);
    }

    // postview msg
    if (0 && isMessageEnabled(CAMERA_MSG_POSTVIEW_FRAME)) {
        F_LOG;
        char *cam_buff = (char*)malloc(framesize);
        if (NULL != cam_buff ) {
            memset(cam_buff, 0xff, framesize);
            mDataCB(CAMERA_MSG_POSTVIEW_FRAME, (const char *)cam_buff, NULL, mCallbackCookie);
            free(cam_buff);
        } else {
            ALOGE("%s: Memory failure in CAMERA_MSG_PREVIEW_FRAME", __FUNCTION__);
            return;
        }
    }
}

bool CallbackNotifier::takePicture(const void *frame, bool is_continuous)
{
    V4L2BUF_t *pbuf = (V4L2BUF_t *) frame;
    void *pOutBuf = NULL;
    int bufSize = 0;

    int src_format = 0;
    unsigned long src_addr_phy = 0;
    unsigned long src_addr_vir = 0;
    int src_width = 0;
    int src_height = 0;
    RECT_t src_crop;

    if ((pbuf->isThumbAvailable == 1)
            && (pbuf->thumbUsedForPhoto == 1)) {
        src_format = pbuf->thumbFormat;
        src_addr_phy = pbuf->thumbAddrPhyY;
        src_addr_vir = pbuf->thumbAddrVirY;
        src_width = pbuf->thumbWidth;
        src_height = pbuf->thumbHeight;
        memcpy((void *) &src_crop, (void *) &pbuf->thumb_crop_rect, sizeof(RECT_t));
    } else {
        src_format = pbuf->format;
        src_addr_phy = pbuf->addrPhyY;
        src_addr_vir = pbuf->addrVirY;
        src_width = pbuf->width;
        src_height = pbuf->height;
        memcpy((void *) &src_crop, (void *) &pbuf->crop_rect, sizeof(RECT_t));
    }

    JPEG_ENC_t jpeg_enc;
    memset(&jpeg_enc, 0, sizeof(jpeg_enc));
    jpeg_enc.addrY = src_addr_vir;    //src_addr_phy;
    jpeg_enc.addrC = src_addr_vir + ALIGN_16B(src_width) * src_height;;    //src_addr_phy + ALIGN_16B(src_width) * src_height;
    jpeg_enc.src_w = src_width;
    jpeg_enc.src_h = src_height;
    jpeg_enc.pic_w = mPictureWidth;
    jpeg_enc.pic_h = mPictureHeight;
    jpeg_enc.colorFormat =
        (src_format == V4L2_PIX_FMT_NV21) ? JPEG_COLOR_YUV420_NV21 : JPEG_COLOR_YUV420_NV12;
    jpeg_enc.quality = mJpegQuality;
    jpeg_enc.rotate = mJpegRotate;
    getCurrentDateTime();

    strcpy(jpeg_enc.CameraMake, mExifMake);
    strcpy(jpeg_enc.CameraModel, mExifModel);
    strcpy(jpeg_enc.DateTime, mDateTime);

    jpeg_enc.thumbWidth = mThumbWidth;
    jpeg_enc.thumbHeight = mThumbHeight;
    jpeg_enc.whitebalance = 0;
    jpeg_enc.focal_length = 0;

    if (0 != strlen(mGpsMethod)) {
        jpeg_enc.enable_gps = 1;
        jpeg_enc.gps_latitude = mGpsLatitude;
        jpeg_enc.gps_longitude = mGpsLongitude;
        jpeg_enc.gps_altitude = mGpsAltitude;
        jpeg_enc.gps_timestamp = mGpsTimestamp;
        strcpy(jpeg_enc.gps_processing_method, mGpsMethod);
        memset(mGpsMethod, 0, sizeof(mGpsMethod));
    } else {
        jpeg_enc.enable_gps = 0;
    }

    if ((src_crop.width != jpeg_enc.src_w)
            || (src_crop.height != jpeg_enc.src_h)) {
        jpeg_enc.enable_crop = 1;
        jpeg_enc.crop_x = src_crop.left;
        jpeg_enc.crop_y = src_crop.top;
        jpeg_enc.crop_w = src_crop.width;
        jpeg_enc.crop_h = src_crop.height;
    } else {
        jpeg_enc.enable_crop = 0;
    }

    ALOGV("addrY: %x, pic: %dx%d, quality: %d, rotate: %d",
                jpeg_enc.addrY, jpeg_enc.pic_w, jpeg_enc.pic_h, jpeg_enc.quality, jpeg_enc.rotate);

    pOutBuf = (void *) malloc(mPictureWidth * mPictureHeight);
    int ret = JpegEnc(pOutBuf, &bufSize, &jpeg_enc);
    if (ret < 0) {
        ALOGE("JpegEnc failed");
        return false;
    }
    //ALOGV("hw enc time: %lld(ms), size: %d", (systemTime() - lasttime)/1000000, bufSize);

    char *jpeg_buff = (char*)malloc(bufSize);
    if (NULL != jpeg_buff ) {
        memcpy(jpeg_buff, (uint8_t *) pOutBuf, bufSize);
        camera_frame_metadata_t metadata;
        metadata.number_of_faces = bufSize;
        mDataCB(CAMERA_MSG_COMPRESSED_IMAGE, jpeg_buff, &metadata, mCallbackCookie);
        if(!jpeg_buff)
            free(jpeg_buff);
    } else {
        ALOGE("%s: Memory failure in CAMERA_MSG_COMPRESSED_IMAGE", __FUNCTION__);
    }

    ALOGV("taking photo end");
    return true;
}


#ifdef WATERMARK

/*
* Allwinnertech
* watemark set and get string
* 20160114
*/
void CallbackNotifier::setWaterMarkMultiple(char *mWaterMark)
{
    ALOGV("%s***********%s", __FUNCTION__, mWaterMark);
    strcpy(mWaterMarkMultiple, mWaterMark);
}

void CallbackNotifier::getWaterMarkMultiple(char *mWaterMark)
{
    sprintf(mWaterMark, "%s", mWaterMarkMultiple);
}
//end
#endif

void CallbackNotifier::getCurrentDateTime()
{
    time_t t;
    struct tm *tm_t;
    time(&t);
    tm_t = localtime(&t);
    sprintf(mDateTime, "%4d:%02d:%02d %02d:%02d:%02d",
            tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday,
            tm_t->tm_hour, tm_t->tm_min, tm_t->tm_sec);
}

void CallbackNotifier::onCameraDeviceError(int err)
{
    if (isMessageEnabled(CAMERA_MSG_ERROR) && mNotifyCB != NULL) {
        mNotifyCB(CAMERA_MSG_ERROR, err, 0, mCallbackCookie);
    }
}

}; /* namespace android */
