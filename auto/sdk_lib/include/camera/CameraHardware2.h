
#ifndef __HAL_CAMERA_HARDWARE_H__
#define __HAL_CAMERA_HARDWARE_H__

/*
 * Contains declaration of a class CameraHardware that encapsulates functionality
 * common to all V4L2Cameras ("fake", "webcam", "video file", etc.).
 * Instances of this class (for each V4L2Camera) are created during the
 * construction of the HALCameraFactory instance.
 * This class serves as an entry point for all camera API calls that defined
 * by camera_device_ops_t API.
 */

#include <utils/Mutex.h>
#include "videodev2_new.h"
#include "CameraParameters.h"
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include "hardware.h"

#include "V4L2CameraDevice2.h"
#include "PreviewWindow.h"
#include "CallbackNotifier.h"
#include "CCameraConfig.h"

namespace android {
typedef void (*notify_callback)(int32_t msgType,
                            int32_t ext1,
                            int32_t ext2,
                            void* user);

typedef void (*data_callback)(int32_t msgType,
                            char *dataPtr,
                            camera_frame_metadata_t *metadata,
                            void* user);

typedef void (*data_callback_timestamp)(nsecs_t timestamp,
                            int32_t msgType,
                            char *dataPtr,
                            void *user);
typedef  unsigned int uint_t;
#ifdef ADAS_ENABLE
	typedef void (*adas_data_callback)(int32_t msgType,
                            char *dataPtr,
                            void *metadata,
                            void* user);
#endif

class CameraManager;

#define NUM_OF_360CAMERAS  4
#define MAX_NUM_OF_CAMERAS  8

#define KEY_CAMERA_HAL_VERSION          "camera-hal-version"
#define KEY_CAPTURE_SIZE_WIDTH          "capture-size-width"
#define KEY_CAPTURE_SIZE_HEIGHT         "capture-size-height"
#define KEY_PREVIEW_CAPTURE_SIZE_WIDTH  "preview_capture-size-width"
#define KEY_PREVIEW_CAPTURE_SIZE_HEIGHT "preview_capture-size-height"

#define KEY_PICTURE_MODE                "picture-mode"
#define PICTURE_MODE_NORMAL             "normal"
#define PICTURE_MODE_BLINK              "blink"
#define PICTURE_MODE_SMILE              "smile"
#define PICTURE_MODE_CONTINUOUS         "continuous"
#define PICTURE_MODE_CONTINUOUS_FAST    "continuous-fast"
#define KEY_CANCEL_CONTINUOUS_PICTURE   "cancel_continuous_picture"	// "true" for stopping
#define KEY_CONTINUOUS_PICTURE_PATH     "continuous-picture-path"

#define KEY_SNAP_PATH                   "snap-path"

#define KEY_IS_IMAGECAPTURE_INTENT      "is-imagecapture-intent"
#define KEY_CAPTURE_FORMAT              "capture-format"

	typedef enum face_detection_states_t {
		FACE_DETECTION_UNINITIALIZED = 0,
		FACE_DETECTION_INITIALIZED = 1 << 0,
		FACE_DETECTION_STARTED = 1 << 1,
		FACE_DETECTION_PREPARED = 1 << 2,
		FACE_DETECTION_IDLE = 1 << 3,
		FACE_DETECTION_STOPPED = 1 << 4,
		FACE_DETECTION_STATE_ERROR = 1 << 5,
	} face_detection_states;

typedef  unsigned int uint_t;

/* Encapsulates functionality common to all V4L2Cameras.
 *
 * Note that HALCameraFactory instantiates object of this class just once,
 * when HALCameraFactory instance gets constructed. Connection to /
 * disconnection from the actual camera device is handled by calls to connectDevice(),
 * and closeCamera() methods of this class that are ivoked in response to
 * hw_module_methods_t::open, and camera_device::close callbacks.
 */
	class CameraHardware{
	  public:
		/* Constructs CameraHardware instance.
		 * Param:
		 *  module - V4L2Camera HAL module descriptor.
		 */
		//CameraHardware(struct hw_module_t *module, CCameraConfig * pCameraCfg);

		CameraHardware(CCameraConfig * pCameraCfg);
		/* Destructs CameraHardware instance. */
		 virtual ~ CameraHardware();

	/****************************************************************************
     * Public API
     ***************************************************************************/

	  public:
		/* Initializes CameraHardware instance.
		 * Return:
		 *  NO_ERROR on success, or an appropriate error status on failure.
		 */
		 virtual status_t Initialize();

		/* Entry point for notifications that occur in camera device.
		 * Param:
		 *  err - CAMERA_ERROR_XXX error code.
		 */
		virtual void onCameraDeviceError(int err);

	/****************************************************************************
     * Camera API implementation
     ***************************************************************************/

	  public:
		/* Creates connection to the V4L2Camera device.
		 * This method is called in response to hw_module_methods_t::open callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		 virtual status_t connectCamera();

		/* Closes connection to the V4L2Camera.
		 * This method is called in response to camera_device::close callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */

	/****************************************************************************
     * Camera API implementation.
     * These methods are called from the camera API callback routines.
     ***************************************************************************/
		/* Actual handler for camera_device_ops_t::release_recording_frame callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void releaseRecordingFrame(const void *opaque);

		/* Actual handler for camera_device_ops_t::send_command callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t sendCommand(int32_t cmd, unsigned long arg1, int32_t arg2);

	 // protected:
		/* Actual handler for camera_device_ops_t::set_preview_window callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		//virtual status_t setPreviewWindow(struct preview_stream_ops *window);

		/* Actual handler for camera_device_ops_t::set_callbacks callback.
		 * NOTE: When this method is called the object is locked.
		 */
								   
		virtual void setCallbacks(notify_callback notify_cb,
									  data_callback data_cb,
									  data_callback_timestamp data_cb_timestamp,
									  void *user);

#ifdef ADAS_ENABLE
		void setAdasCallbacks(camera_adas_data_callback adas_data_cb);

		virtual status_t setAdasParameters(int key, int value);

#endif

		virtual void setAnalogInputColor(int brightness, int contrast, int saturation);

		/* Actual handler for camera_device_ops_t::enable_msg_type callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void enableMsgType(int32_t msg_type);

		/* Actual handler for camera_device_ops_t::disable_msg_type callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void disableMsgType(int32_t msg_type);

		/* Actual handler for camera_device_ops_t::msg_type_enabled callback.
		 * NOTE: When this method is called the object is locked.
		 * Return:
		 *  0 if message(s) is (are) disabled, != 0 if enabled.
		 */
		virtual int isMsgTypeEnabled(int32_t msg_type);

		/* Actual handler for camera_device_ops_t::start_preview callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t startPreview();

		/* Actual handler for camera_device_ops_t::stop_preview callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void stopPreview();

		/* Actual handler for camera_device_ops_t::preview_enabled callback.
		 * NOTE: When this method is called the object is locked.
		 * Return:
		 *  0 if preview is disabled, != 0 if enabled.
		 */
		virtual int isPreviewEnabled();

		/* Actual handler for camera_device_ops_t::store_meta_data_in_buffers callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t storeMetaDataInBuffers(int enable);

		/* Actual handler for camera_device_ops_t::start_recording callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t startRecording();

		/* Actual handler for camera_device_ops_t::stop_recording callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void stopRecording();

		/* Actual handler for camera_device_ops_t::recording_enabled callback.
		 * NOTE: When this method is called the object is locked.
		 * Return:
		 *  0 if recording is disabled, != 0 if enabled.
		 */
		virtual int isRecordingEnabled();


		/* Actual handler for camera_device_ops_t::auto_focus callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t setAutoFocus();

		/* Actual handler for camera_device_ops_t::cancel_auto_focus callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t cancelAutoFocus();

		/* Actual handler for camera_device_ops_t::take_picture callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t takePicture();

		/* Actual handler for camera_device_ops_t::cancel_picture callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t cancelPicture();

		/* Actual handler for camera_device_ops_t::set_parameters callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t setParameters(const char *parms);
#ifdef WATERMARK
		//for watermark setting
		virtual status_t setWaterMarkMultiple(char *mWaterMark, int dispMode);
		//end
#endif
		//for flip setting
		virtual status_t setCameraFlipStatus(int flipEnable);
		//end
		virtual status_t setFd(int fd);

		/* Actual handler for camera_device_ops_t::get_parameters callback.
		 * NOTE: When this method is called the object is locked.
		 * Return:
		 *  Flattened parameters string. The caller will free the buffer allocated
		 *  for the string by calling camera_device_ops_t::put_parameters callback.
		 */
		virtual char *getParameters();

		/* Actual handler for camera_device_ops_t::put_parameters callback.
		 * Called to free the string returned from camera_device_ops_t::get_parameters
		 * callback. There is nothing more to it: the name of the callback is just
		 * misleading.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void putParameters(char *params);

		status_t setPreviewParam(struct view_info pvi, struct src_info psi, int tvout, int tvch);

		/* Actual handler for camera_device_ops_t::release callback.
		 * NOTE: When this method is called the object is locked.
		 */
		virtual void releaseCamera();

		/* Actual handler for camera_device_ops_t::dump callback.
		 * NOTE: When this method is called the object is locked.
		 * Note that failures in this method are reported as negave EXXX statuses.
		 */
		virtual status_t dumpCamera(int fd);

	/****************************************************************************
     * Preview management.
     ***************************************************************************/

	  protected:
	  public:
		/* Starts preview.
		 * Note that when this method is called mPreviewWindow may be NULL,
		 * indicating that framework has an intention to start displaying video
		 * frames, but didn't create the preview window yet.
		 * Return:
		 *  NO_ERROR on success, or an appropriate error status on failure.
		 */
		 virtual status_t doStartPreview();

		/* Stops preview.
		 * This method reverts DoStartPreview.
		 * Return:
		 *  NO_ERROR on success, or an appropriate error status on failure.
		 */
		virtual status_t doStopPreview();

		status_t doTakePicture();
		status_t doTakePictureEnd();

	/****************************************************************************
     * Private API.
     ***************************************************************************/

	  protected:
		/* Cleans up camera when released. */
		 virtual status_t cleanupCamera();

	/****************************************************************************
     * Data members
     ***************************************************************************/
	  public:
		/* Preview window. */
		 PreviewWindow mPreviewWindow;
		CallbackNotifier mCallbackNotifier;

	  protected:
		/* Locks this instance for parameters, state, etc. change. */
		 Mutex mObjectLock;

		/* Camera parameters. */
		CameraParameters mParameters;

		V4L2CameraDevice *mV4L2CameraDevice;

	  private:
		/* Registered callbacks implementing camera API. */
		CameraManager *mCameraManager;

	/****************************************************************************
     * Common keys
     ***************************************************************************/

	  public:
		static const char FACING_KEY[];
		static const char ORIENTATION_KEY[];
		static const char RECORDING_HINT_KEY[];

	 /****************************************************************************
     * Common string values
     ***************************************************************************/

		/* Possible values for FACING_KEY */
		static const char FACING_BACK[];
		static const char FACING_FRONT[];

		unsigned char *mFrameData;

		int mPreviewRotation;
		int mPreviewWidth;
		int mPreviewHeight;

		bool mSmileDetectionCmdEnable;
		bool mBlinkDetectionCmdEnable;

		bool mSmileDetectionEnable;
		bool mBlinkDetectionEnable;


		bool mBlinkPictureStarted;
		bool mBlinkPictureResult;
		bool mSmilePictureResult;

		// -------------------------------------------------------------------------
		// extended interfaces here <***** star *****>
		// -------------------------------------------------------------------------
	  public:
		 status_t setCameraHardwareInfo(HALCameraInfo * halInfo);

		void setCameraManager(CameraManager * manager);
		void releasePreviewFrame(int index);
		int getTVINSystemType();
		int getFrameWidth();
		int getFrameHeight();
		status_t startPreview_h();
		void stopPreview_h();
		void releaseCamera_h();
		void setAnalogInputColor_h(int brightness, int contrast, int saturation);

		void initDefaultParameters();

		void notifyPictureMsg(const void *frame);

		void setNewCrop(Rect * rect);
		int setAutoFocusRange();
		int getCurrentFaceFrame(void *frame);
		int faceDetection(camera_frame_metadata_t * face);
		int smileDetection(camera_face_smile_status_t * smile);
		int blinkDetection(camera_face_blink_status_t * blink);
		int parse_focus_areas(const char *str, bool is_face = false);
		bool checkFocusArea(const char *area);
		bool checkFocusMode(const char *mode);

		bool commandThread();
		bool autoFocusThread();
		bool faceDetectionThread();

		void setVideoCaptureSize(int video_w, int video_h);
		void getCurrentOriention(int *oriention);

		bool isCameraIdle();

		HALCameraInfo mHardwareInfo;
		int mCaptureWidth;
		int mCaptureHeight;
		int mVideoCaptureWidth;
		int mVideoCaptureHeight;
	  protected:
		CCameraConfig * mCameraConfig;

		Mutex mCameraIdleLock;
		bool mIsCameraIdle;

		bool mFirstSetParameters;
		bool mIsSupportFocus;
		bool mIsSupportEffect;
		bool mIsSupportFlash;
		bool mIsSupportScene;
		bool mIsSupportWhiteBlance;
		bool mIsSupportExposure;

		int mFullSizeWidth;
		int mFullSizeHeight;

		bool mUseHwEncoder;

		int mCaptureFormat;

		char mCallingProcessName[128];

		Rect mFrameRectCrop;	// current frame buffer crop for focus
		char mFocusAreasStr[32];
		/* Add windows coordinates struct by raymonxiu */
		struct v4l2_win_coordinate {
			__s32 x1;
			__s32 y1;
			__s32 x2;
			__s32 y2;
		};
		struct v4l2_win_coordinate mLastFocusAreas;

		typedef enum CMD_QUEUE_t {
			CMD_QUEUE_SET_COLOR_EFFECT = 0,
			CMD_QUEUE_SET_WHITE_BALANCE,
			CMD_QUEUE_SET_FLASH_MODE,
			CMD_QUEUE_SET_FOCUS_MODE,
			CMD_QUEUE_SET_FOCUS_AREA,
			CMD_QUEUE_SET_EXPOSURE_COMPENSATION,

			CMD_QUEUE_START_FACE_DETECTE,
			CMD_QUEUE_STOP_FACE_DETECTE,

			CMD_QUEUE_START_SMILE_DETECTE,
			CMD_QUEUE_STOP_SMILE_DETECTE,

			CMD_QUEUE_START_BLINK_DETECTE,
			CMD_QUEUE_STOP_BLINK_DETECTE,

			CMD_QUEUE_TAKE_PICTURE,
			CMD_QUEUE_PICTURE_MSG,
			CMD_QUEUE_STOP_CONTINUOUSSNAP,

			CMD_QUEUE_SET_FOCUS_STATUS,
#ifdef ADAS_ENABLE
			CMD_QUEUE_START_ADAS_DETECTE,
			CMD_QUEUE_STOP_ADAS_DETECTE,
#endif

#ifdef WATERMARK
			CMD_QUEUE_START_WATER_MARK,
			CMD_QUEUE_STOP_WATER_MARK,
#endif
#ifdef START_STOP_RENDER
			CMD_QUEUE_START_RENDER,
			CMD_QUEUE_STOP_RENDER,
#endif
			CMD_QUEUE_MAX
		} CMD_QUEUE;

		OSAL_QUEUE mQueueCommand;

		typedef struct Queue_Element_t {
			CMD_QUEUE cmd;
			unsigned long data;
		} Queue_Element;

		Queue_Element mQueueElement[CMD_QUEUE_MAX];

		class DoCommandThread:public Thread {
			CameraHardware *mCameraHardware;
			ThreadState mThreadStatus;
		  public:
			 DoCommandThread(CameraHardware * hw):
				Thread(false), mCameraHardware(hw), mThreadStatus(THREAD_STATE_NULL) {
			} void startThread() {
				mThreadStatus = THREAD_STATE_RUNNING;
				run("CameraCommandThread", PRIORITY_NORMAL);
			} void stopThread() {
				ALOGV("DoCommandThread stopThread");
				mThreadStatus = THREAD_STATE_EXIT;
			} ThreadState getThreadStatus() {
				return mThreadStatus;
			}
			bool isThreadStarted() {
				return (mThreadStatus == THREAD_STATE_PAUSED)
					|| (mThreadStatus == THREAD_STATE_RUNNING);
			}
			virtual bool threadLoop() {
				return mCameraHardware->commandThread();
			}
		};
		sp < DoCommandThread > mCommandThread;

		pthread_mutex_t mCommandMutex;
		pthread_cond_t mCommandCond;

		class DoAutoFocusThread:public Thread {
			CameraHardware *mCameraHardware;
			ThreadState mThreadStatus;
		  public:
			 DoAutoFocusThread(CameraHardware * hw):Thread(false),
				mCameraHardware(hw), mThreadStatus(THREAD_STATE_NULL) {
			} void startThread() {
				mThreadStatus = THREAD_STATE_RUNNING;
				run("CameraAutoFocusThread", PRIORITY_NORMAL);
			}
			void stopThread() {
				mThreadStatus = THREAD_STATE_EXIT;
			}
			ThreadState getThreadStatus() {
				return mThreadStatus;
			}
			bool isThreadStarted() {
				return (mThreadStatus == THREAD_STATE_PAUSED)
					|| (mThreadStatus == THREAD_STATE_RUNNING);
			}
			virtual bool threadLoop() {
				return mCameraHardware->autoFocusThread();
			}
		};
		sp < DoAutoFocusThread > mAutoFocusThread;

		pthread_mutex_t mAutoFocusMutex;
		pthread_cond_t mAutoFocusCond;
		bool mAutoFocusThreadExit;

	  public:
		typedef enum FocusStatus_t {
			FOCUS_STATUS_IDLE = 0x0,
			FOCUS_STATUS_SUCCESS = 0x1,
			FOCUS_STATUS_FAIL = 0x2,
			FOCUS_STATUS_DONE = FOCUS_STATUS_SUCCESS | FOCUS_STATUS_FAIL,
			FOCUS_STATUS_BUSY = 0x4,
		} FocusStatus;

	  protected:
		FocusStatus mFocusStatus;
		bool mIsSingleFocus;

		int mOriention;

		int mZoomRatio;

		bool mIsImageCaptureIntent;

private:

	 
#ifdef ADAS_ENABLE
	adas_data_callback   mAdasDataCB;
#endif
   
#ifdef ADAS_ENABLE
	static void __adas_data_cb(int32_t msg_type,
                          const char *data, unsigned int index,
                          void *metadata,
                          void *user)
	{
        //ALOGV("%s", __FUNCTION__);

	if(data == NULL ) {
		ALOGE("camera memory data or handle is NULL");
		return;
	}

        CameraHardware *__this =
                static_cast<CameraHardware *>(user);
	

       // __this->mAdasDataCB(msg_type, data, metadata, user);
	}
#endif

};
};							/* namespace android */

#endif /* __HAL_CAMERA_HARDWARE_H__ */
