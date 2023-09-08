
#ifndef __HAL_CALLBACK_NOTIFIER_H__
#define __HAL_CALLBACK_NOTIFIER_H__

#include "camera.h"
#include "sunxiMemInterface.h"

/*
 * Contains declaration of a class CallbackNotifier that manages callbacks set
 * via set_callbacks, enable_msg_type, and disable_msg_type camera HAL API.
 */

enum ThreadState {
    THREAD_STATE_NULL,            // The thread has not been created.
    THREAD_STATE_PAUSED,        // The thread is paused for waiting some signal.
    THREAD_STATE_RUNNING,        // The thread is in running.
    THREAD_STATE_EXIT,            // The thread will exit.
};

namespace android {

    class V4L2CameraDevice;

/* Manages callbacks set via set_callbacks, enable_msg_type, and disable_msg_type
 * camera HAL API.
 *
 * Objects of this class are contained in CameraHardware objects, and handle
 * relevant camera API callbacks.
 * Locking considerations. Apparently, it's not allowed to call callbacks
 * registered in this class, while holding a lock: recursion is quite possible,
 * which will cause a deadlock.
 */
    class CallbackNotifier {
      public:
        /* Constructs CallbackNotifier instance. */
        CallbackNotifier();

        /* Destructs CallbackNotifier instance. */
        ~CallbackNotifier();

    /****************************************************************************
     * Camera API
     ***************************************************************************/

      public:
        /* Actual handler for camera_device_ops_t::set_callbacks callback.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::set_callbacks callback.
         */
        void setCallbacks(camera_notify_callback notify_cb,
                          camera_data_callback data_cb,
                          camera_data_timestamp_callback data_cb_timestamp,
                          void *user);
#ifdef ADAS_ENABLE
        void setAdasCallbacks(camera_adas_data_callback adas_data_cb);
#endif

        /* Actual handler for camera_device_ops_t::enable_msg_type callback.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::enable_msg_type callback.
         */
        void enableMessage(uint msg_type);

        /* Actual handler for camera_device_ops_t::disable_msg_type callback.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::disable_msg_type callback.
         */
        void disableMessage(uint msg_type);

        /* Actual handler for camera_device_ops_t::store_meta_data_in_buffers
         * callback. This method is called by the containing V4L2Camera object
         * when it is handing the camera_device_ops_t::store_meta_data_in_buffers
         * callback.
         * Return:
         *  NO_ERROR on success, or an appropriate error status.
         */
        status_t storeMetaDataInBuffers(bool enable);

        /* Enables video recording.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::start_recording callback.
         * Return:
         *  NO_ERROR on success, or an appropriate error status.
         */
        status_t enableVideoRecording();

        /* Disables video recording.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::stop_recording callback.
         */
        void disableVideoRecording();

        /* Actual handler for camera_device_ops_t::msg_type_enabled callback.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::msg_type_enabled callback.
         * Note: this method doesn't grab a lock while checking message status, since
         * upon exit the status would be undefined anyway. So, grab a lock before
         * calling this method if you care about persisting a defined message status.
         * Return:
         *  0 if message is disabled, or non-zero value, if message is enabled.
         */
        inline int isMessageEnabled(uint msg_type) {
            return mMessageEnabler & msg_type;
        }
        /* Checks id video recording is enabled.
         * This method is called by the containing V4L2Camera object when it is
         * handing the camera_device_ops_t::recording_enabled callback.
         * Note: this method doesn't grab a lock while checking video recordin status,
         * since upon exit the status would be undefined anyway. So, grab a lock
         * before calling this method if you care about persisting of a defined video
         * recording status.
         * Return:
         *  true if video recording is enabled, or false if it is disabled.
         */
        inline bool isVideoRecordingEnabled() {
            return mVideoRecEnabled;
        }

    /****************************************************************************
     * Public API
          ***************************************************************************/
      public:
        /* Resets the callback notifier. */
        void cleanupCBNotifier();

        /* Next frame is available in the camera device.
         * This is a notification callback that is invoked by the camera device when
         * a new frame is available.
         * Note that most likely this method is called in context of a worker thread
         * that camera device has created for frame capturing.
         * Param:
         *  frame - Captured frame, or NULL if camera device didn't pull the frame
         *      yet. If NULL is passed in this parameter use GetCurrentFrame method
         *      of the camera device class to obtain the next frame. Also note that
         *      the size of the frame that is passed here (as well as the frame
         *      returned from the GetCurrentFrame method) is defined by the current
         *      frame settings (width + height + pixel format) for the camera device.
         * timestamp - Frame's timestamp.
         * camera_dev - Camera device instance that delivered the frame.
         */
        void onNextFrameAvailable(const void *frame, bool hw, int channel);

        void onNextFrameHW(const void *frame, int channel);

        void onNextFrameSW(const void *frame, int channel);
        /* Entry point for notifications that occur in camera device.
         * Param:
         *  err - CAMERA_ERROR_XXX error code.
         */
        void onCameraDeviceError(int err);

        /* Sets JPEG quality used to compress frame during picture taking. */
        void setJpegQuality(int jpeg_quality) {
            mJpegQuality = jpeg_quality;
        }


    /****************************************************************************
     * Private API
     ***************************************************************************/

    /****************************************************************************
     * Data members
     ***************************************************************************/

      protected:
        /* Locks this instance for data change. */
        Mutex mObjectLock;
        /*
         * Callbacks, registered in set_callbacks.
         */
        camera_notify_callback mNotifyCB;
        camera_data_callback mDataCB;
#ifdef ADAS_ENABLE
        camera_adas_data_callback mAdasDataCB;
        float mADASCarSpeed;
        int mLaneLineOffsetSensity;
#endif
        camera_data_timestamp_callback mDataCBTimestamp;
        void *mCallbackCookie;

        /* Message enabler. */
        uint32_t mMessageEnabler;

        /* Video recording status. */
        bool mVideoRecEnabled;

      public:
        inline void setPictureSize(int w, int h) {
            mPictureWidth = w;
            mPictureHeight = h;
        }

        inline void setExifMake(char *make) {
            strcpy(mExifMake, make);
        }

        inline void setExifModel(char *model) {
            strcpy(mExifModel, model);
        }

        // Sets JPEG rotate used to compress frame during picture taking.
        inline void setJpegRotate(int jpeg_rotate) {
            mJpegRotate = jpeg_rotate;
        }

        inline void setGPSLatitude(double gpsLatitude) {
            mGpsLatitude = gpsLatitude;
        }

        inline void setGPSLongitude(double gpsLongitude) {
            mGpsLongitude = gpsLongitude;
        }

        inline void setGPSAltitude(long gpsAltitude) {
            mGpsAltitude = gpsAltitude;
        }

        inline void setGPSTimestamp(long gpsTimestamp) {
            mGpsTimestamp = gpsTimestamp;
        }

        inline void setGPSMethod(const char *gpsMethod) {
            strcpy(mGpsMethod, gpsMethod);
        }

        inline void setJpegThumbnailSize(int w, int h) {
            mThumbWidth = w;
            mThumbHeight = h;
        }

#ifdef ADAS_ENABLE
        inline void setAdasDistanceDetectLevel(int mDetectLevel) {
            mDistanceDetectLevel = mDetectLevel;
        }
        inline int getAdasDistanceDetectLevel() {
            return mDistanceDetectLevel;
        }
#endif
        inline void setSaveFolderPath(const char *str) {
            strcpy(mFolderPath, str);
        }

        inline void setSnapPath(const char *str) {
            strcpy(mSnapPath, str);
        }

#ifdef WATERMARK
        void setWaterMarkMultiple(char *mWaterMark);
        void getWaterMarkMultiple(char *mWaterMark);
#endif

#ifdef ADAS_ENABLE
        status_t adasResultMsg(void *adas);
        float getADASCarSpeed() {
            return mADASCarSpeed;
        }
        int getLaneLineOffsetSensity() {
            return mLaneLineOffsetSensity;
        }
#endif
        bool takePicture(const void *frame, bool is_continuous = false);

        void notifyPictureMsg(const void *frame);

        void getCurrentDateTime();

      protected:
        // JPEG quality used to compress frame during picture taking.
        int mJpegQuality;

        // JPEG rotate used to compress frame during picture taking.
        int mJpegRotate;

        // JPEG size
        int mPictureWidth;
        int mPictureHeight;

        // thumb size
        int mThumbWidth;
        int mThumbHeight;
#ifdef ADAS_ENABLE
        //for adas
        int mDistanceDetectLevel;
#endif
        // gps exif
        double mGpsLatitude;
        double mGpsLongitude;
        long mGpsAltitude;
        long mGpsTimestamp;
        char mGpsMethod[100];

        char mExifMake[64];         //for the cameraMake name
        char mExifModel[64];        //for the cameraMode
        char mDateTime[64];         //for the data and time
        char mFolderPath[128];
        char mSnapPath[128];
#ifdef WATERMARK
        char mWaterMarkMultiple[128];
#endif
    };

};  /* namespace android */

#endif /* __HAL_CALLBACK_NOTIFIER_H__ */
