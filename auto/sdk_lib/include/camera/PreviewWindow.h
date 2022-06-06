
#ifndef __HAL_PREVIEW_WINDOW_H__
#define __HAL_PREVIEW_WINDOW_H__

#include "hwdisp2.h"
#include "DiHandle.h"
/*
 * Contains declaration of a class PreviewWindow that encapsulates functionality
 * of a preview window set via set_preview_window camera HAL API.
 */

#include "aut_tr.h"
#include "sunxiMemInterface.h"
namespace android {

	enum FlipStatus {
		NO_FLIP = 0,
		FLIP_MIRROR = 1
	};
#define DISP_NB_BUFFER 5

class V4L2CameraDevice;
#define PBUFFER_SIZE (1920*1088*3/2)

/* Encapsulates functionality of a preview window set via set_preview_window
 * camera HAL API.
 *
 * Objects of this class are contained in CameraHardware objects, and handle
 * relevant camera API callbacks.
 */
	class PreviewWindow {
	  public:
		/* Constructs PreviewWindow instance. */
		PreviewWindow();
		dma_mem_des_t mPreviewMemops;

		/* Destructs PreviewWindow instance. */
		~PreviewWindow();

	/***************************************************************************
     * Camera API
     **************************************************************************/

	  public:
		/* Actual handler for camera_device_ops_t::set_preview_window callback.
		 * This method is called by the containing V4L2Camera object when it is
		 * handing the camera_device_ops_t::set_preview_window callback.
		 * Param:
		 *  window - Preview window to set. This parameter might be NULL, which
		 *      indicates preview window reset.
		 *  preview_fps - Preview's frame frequency. This parameter determins when
		 *      a frame received via onNextFrameAvailable call will be pushed to
		 *      the preview window. If 'window' parameter passed to this method is
		 *      NULL, this parameter is ignored.
		 * Return:
		 *  NO_ERROR on success, or an appropriate error status.
		 */

		//status_t setPreviewWindow(struct preview_stream_ops* window);

		/* Starts the preview.
		 * This method is called by the containing V4L2Camera object when it is
		 * handing the camera_device_ops_t::start_preview callback.
		 */
		 status_t startPreview();

		/* Stops the preview.
		 * This method is called by the containing V4L2Camera object when it is
		 * handing the camera_device_ops_t::start_preview callback.
		 */
		void stopPreview();
        DiHandle * mDi;
		int mDispCnt;
		/* Checks if preview is enabled. */
		inline bool isPreviewEnabled() {
			return mPreviewEnabled;
		}

	/****************************************************************************
     * Public API
	      ***************************************************************************/ public:
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
		 bool onNextFrameAvailable(const void *frame, int flipEnable, bool isOview);
		status_t setPreviewDisplayOff();
		status_t setPreviewDisplayOn();
		status_t setPreviewParam(struct view_info pvi, struct src_info psi, int tvout, int tvch);
		void PreviewTvOut(HwDisplay* mcd,int screen_id,unsigned int *hlay,struct view_info *surface,int mode);

		struct view_info mvi;
		struct src_info msi;
		int mtvout;
		int mtvch;
		bool isPreviewDispEn;


		int previewSkipCounter;

	/***************************************************************************
     * Private API
     **************************************************************************/

	  protected:
		 V4L2BUF_t mDispBuff[DISP_NB_BUFFER];

	/***************************************************************************
     * Data members
     **************************************************************************/

	  protected:
		/* Locks this instance for data changes. */
		 Mutex mObjectLock;

		/*
		 * Cached preview window frame dimensions.
		 */
		int mPreviewFrameWidth;
		int mPreviewFrameHeight;
		int mPreviewFrameSize;
		int mCurPixelFormat;

		/* Preview status. */
		bool mPreviewEnabled;

		// -------------------------------------------------------------------------
		// extended interfaces here <***** star *****>
		// -------------------------------------------------------------------------
		int mHwlayerScreen0;
		int mHwlayerScreen1;
		int mHwlayerScreen1_ui;
		HwDisplay *mHwDisplay;
	  protected:
		 bool mShouldAdjustDimensions;
	  private:
		 tr_obj imgtr;
	};

};								/* namespace android */

#endif /* __HAL_PREVIEW_WINDOW_H__ */
