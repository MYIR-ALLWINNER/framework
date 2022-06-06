
#ifndef __HAL_CAMERA_MANAGER_H__
#define __HAL_CAMERA_MANAGER_H__

#include "CameraDebug.h"
#include <fcntl.h>
#include <cutils/list.h>
#include <utils/Mutex.h>
#include <type_camera.h>
#include <utils/Thread.h>
#include "OSAL_Queue.h"

#ifdef SUPPORT_NEW_DRIVER
#include "CameraHardware2.h"
#else
#include "CameraHardware.h"
#endif

#include "DmaIon.h"

//#include "CdxIon.h"

#if 1

#define MAX_NUM_OF_CAMERAS  8
#define NB_COMPOSE_BUFFER 4

//#define USE360_Deinterlace_HW

#ifdef USE360_Deinterlace_HW
#include "DiProcess.h"
#endif

namespace android {

	typedef struct BufManager_t {
		int write_id;
		int read_id;
		int buf_unused;
		pthread_mutex_t mutex;
		pthread_cond_t condition;
		V4L2BUF_t buf[NB_COMPOSE_BUFFER];
	} BufManager;

	enum CaptureState {
		CAPTURE_STATE_PAUSE,
		CAPTURE_STATE_READY,
		CAPTURE_STATE_STARTED,
		CAPTURE_STATE_EXIT,
	};

	class CameraManager {
	  public:
		CameraManager();
		~CameraManager();
		bool composeThread();
		bool commandThread();
		bool previewThread();

		bool setComposeOrder(unsigned int index0, unsigned int index1, unsigned int index2, unsigned int index3);	//index0~3 should be 0~3
		status_t setCameraHardware(int index, CameraHardware * hardware);
		int setFrameSize(int index, int width, int height);
		int setCaptureState(int index, int state);
		int queueCameraBuf(int index, V4L2BUF_t * buffer);
		V4L2BUF_t *dequeueComposeBuf();
		void startPreview();
		void stopPreview();
		void releaseCamera();
		void setAnalogInputColor(int brightness, int contrast, int saturation, int hue = 0);
		int composeBufInit();
		int composeBufDeinit();
		inline void setOviewEnable(bool enable) {
			mIsOview = enable;
		} inline bool isOviewEnable(void) {
			return mIsOview;
		} 
		dma_mem_des_t *mCameraMemops;
		void setScMemOpsS(dma_mem_des_t * p) {
			mCameraMemops = p;
		}
		CaptureState mCaptureState;
	  protected:
		typedef enum CMD_CM_QUEUE_t {
			CMD_CM_START_PREVIEW = 0,
			CMD_CM_STOP_PREVIEW,
			CMD_CM_RELEASE_CAMERA,
			CMD_CM_QUEUE_MAX
		} CMD_CM_QUEUE;

		OSAL_QUEUE mQueueCMCommand;

		typedef struct Queue_CM_Element_t {
			CMD_CM_QUEUE cmd;
			int data;
		} Queue_CM_Element;

		Queue_CM_Element mQueueCMElement[CMD_CM_QUEUE_MAX];

		class DoCommandThread:public Thread {
			CameraManager *mCameraManager;
			bool mRequestExit;
		  public:
			 DoCommandThread(CameraManager * dev):
				Thread(false), mCameraManager(dev), mRequestExit(false) {
			} void startThread() {
				run("DoCommandThread", PRIORITY_URGENT_DISPLAY);
			}
			void stopThread() {
				mRequestExit = true;
			}
			virtual bool threadLoop() {
				if (mRequestExit) {
					return false;
				}
				return mCameraManager->commandThread();
			}
		};
		sp < DoCommandThread > mCommandThread;

		pthread_mutex_t mCommandMutex;
		pthread_cond_t mCommandCond;

		class ComposeThread:public Thread {
			CameraManager *mCameraManager;
			bool mRequestExit;
		  public:
			 ComposeThread(CameraManager * dev):Thread(false),
				mCameraManager(dev), mRequestExit(false) {
			} void startThread() {
				run("ComposeThread", PRIORITY_URGENT_DISPLAY);
			}
			void stopThread() {
				mRequestExit = true;
			}
			virtual bool threadLoop() {
				if (mRequestExit) {
					return false;
				}
				return mCameraManager->composeThread();
			}
		};

		class PreviewThread:public Thread {
			CameraManager *mCameraManager;
			bool mRequestExit;
		  public:
			 PreviewThread(CameraManager * dev):Thread(false),
				mCameraManager(dev), mRequestExit(false) {
			} void startThread() {
				run("PreviewThread", PRIORITY_URGENT_DISPLAY);
			}
			void stopThread() {
				mRequestExit = true;
			}
			bool getThreadStatus() {
				return mRequestExit;
			}
			virtual bool threadLoop() {
				if (mRequestExit) {
					return false;
				}
				return mCameraManager->previewThread();
			}
		};

		int g2d_scale(unsigned char *src, int src_width, int src_height, unsigned char *dst,
					  int dst_width, int dst_height);
		int g2d_clip(void *psrc, int src_w, int src_h, int src_x, int src_y, int width, int height,
					 void *pdst, int dst_w, int dst_h, int dst_x, int dst_y);
		int g2d_compose(void *psrc1, void *psrc2, void *psrc3, void *psrc4, int src_w, int src_h,
						void *pdst);

		void composeBuffer4in1(unsigned char *outBuffer,unsigned char *inBuffer0,unsigned char *inBuffer1,
		    unsigned char *inBuffer2,unsigned char *inBuffer3);

		void composeBuffer2in1(unsigned char *outBuffer,unsigned char *inBuffer0,unsigned char *inBuffer1);

	  private:
		
		int mFrameWidth;
		int mFrameHeight;
		int mIonFd;
		bool mIsOview;
		bool mCameraState[NB_CAMERA];
		BufManager mComposeBuf;
		BufManager mCameraBuf[NB_CAMERA];
		int mAbandonFrameCnt;
		int mManagerIsInited;

		unsigned int mComposeOrderIdx0;
		unsigned int mComposeOrderIdx1;
		unsigned int mComposeOrderIdx2;
		unsigned int mComposeOrderIdx3;

#ifdef USE360_Deinterlace_HW
		int di_select;
		DiProcess                        *mDiProcess;
		V4L2BUF_t mdiBuffer[NB_COMPOSE_BUFFER];

#endif
		CameraHardware *mCameraHardware[NUM_OF_360CAMERAS];
		pthread_mutex_t mComposeMutex;
		pthread_cond_t mComposeCond;
		pthread_mutex_t mCameraMutex;
		pthread_cond_t mCameraCond;
		sp < ComposeThread > mComposeThread;
		sp < PreviewThread > mPreviewThread;

		int mG2DHandle;

		V4L2BUF_t *getAvailableWriteBuf();
		bool canCompose();
		void composeBuffer(unsigned char *outBuffer, unsigned char *inBuffer0,
						   unsigned char *inBuffer1, unsigned char *inBuffer2,
						   unsigned char *inBuffer3);
		int queueComposeBuf();
		bool isSameSize();
	};

};								/* namespace android */

#endif

#endif /* __HAL_CAMERA_MANAGER_H__ */
