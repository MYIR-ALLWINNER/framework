#ifndef __AUT_AUDIOENC_H__
#define __AUT_AUDIOENC_H__

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
#include <time.h>
//#include "OSAL_Mutex.h"
//#include "OSAL_Queue.h"
//#include "CdxMuxer.h"
//#include "CdxParser.h"
//#include "MuxerWriter.h"

#include "audio_hal.h"


#include "RecordCamera.h"
//#include "V4L2CameraDevice2.h"
//#include "CallbackNotifier.h"
//#include "PreviewWindow.h"
//#include "CameraHardware2.h"

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
#include <time.h>
#include <g2d_driver_enh.h>
#include <sdklog.h>

#include "vencoder.h"
//#include "CdxMuxer.h"
//#include "CdxParser.h"
#include "Rtc.h"
#include "StorageManager.h"
#include "MuxerWriter.h"
#include "sunxiMemInterface.h"
#include "CameraManager.h"

#include "aw_ini_parser.h"
#include "CameraDebug.h"



#include <sdklog.h>

#include "aencoder.h"

using namespace android;

typedef struct AudioEncOutBuffer
{
    char       *pBuf;
    unsigned int        len;
    long long  pts;
    int        bufId;
} AudioEncOutBuffer;

class AutAudioEnc
{
	
public:
	AutAudioEnc();
	~AutAudioEnc();
	int setAudioEncDataCb(usr_data_cb cb,void* user);

	static void __audioenc_data_src(int32_t msgType,nsecs_t timestamp,int card,int device,
	                        char *dataPtr,int dsize,
	                        void* user /*must class AutAudioEnc */);
	
	int AudioRecStart();
	int AudioRecStop();

	int AutAudioEncInit(AudioEncConfig* pconfig);
	int AutAudioEncDeinit();
	bool AutAudioEncThread();

	class AudioEncThread : public Thread
	{
		AutAudioEnc* cam;
		bool mRequestExit;
	public:

		AudioEncThread(AutAudioEnc* hw)
			: Thread(false), cam(hw),mRequestExit(false) { }

		void stopThread()
		{
			mRequestExit = true;
		}

		void startThread()
		{
			run("AudioEncThread", PRIORITY_URGENT_DISPLAY);
		}

		virtual bool threadLoop()
		{
			if (mRequestExit)
			{
				cam->dropQueue();
				return false;
			}

			return cam->AutAudioEncThread();
		}
	};
	enum RecordThreadState mAudioThreadState;
	void dropQueue();
	sp<AudioEncThread>			mAudioEncThread;
	pthread_mutex_t 				mAudioEncMutex;
	pthread_cond_t					mAudioEncCond;
	OSAL_QUEUE						mQueueBufferAudioEnc; //cmd queue
	AudioEncConfig aencconfig;
	usr_data_cb usrDatCb;
	void *mCbUserDat;
	int mAudioRecordQueueErr;
	AudioEncoder*	pAudioEncode;

};
#endif
