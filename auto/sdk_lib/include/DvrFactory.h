#ifndef __DVRFACTORY_H__
#define __DVRFACTORY_H__


#define USE_CDX_LOWLEVEL_API 1
#define USE_CDX_LOWLEVEL_API_AUDIO 1
#define USE_RECORD_AUDIO_API 1

//#include "msgq.h"

#include "V4L2CameraDevice2.h"
#include "CallbackNotifier.h"
#include "PreviewWindow.h"
#include "CameraHardware2.h"

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
#include "G2dApi.h"
#include <sdklog.h>

#include "vencoder.h"
#include "CdxMuxer.h"
#include "CdxParser.h"
#include "Rtc.h"
#include "StorageManager.h"
#include "MuxerWriter.h"
#include "sunxiMemInterface.h"
#include "CameraManager.h"

#include "aw_ini_parser.h"
#include "CameraDebug.h"

#ifndef CDX_V27
#include "log.h"
#endif

#ifdef USE_RECORD_AUDIO_API
#include "audio_hal.h"
#endif

#include "RecordCamera.h"
#include "aut_audioenc.h"

using namespace android;

class dvr_factory
{

public:
	dvr_factory(int cameraId);
	~dvr_factory();
	
	int start();
	int stop();
	
	bool initializeDev(CameraHardware * pHardware);
	bool uninitializeDev();


	int recordInit();
	int startRecord();
	int stopRecord();

	int startPriview(struct view_info vv);
	int stopPriview();
	
	int takePicture();
	

	int SetDataCB(usr_data_cb cb,void* user) 
	{
		if(mRecordCamera){
			mRecordCamera->SetDataCB(cb,((dvr_factory*)user)->mRecordCamera);
		}
	    usrDatCb=cb;
	    mCbUserDat=user;
	    return 0;
	}


	void setCallbacks(notify_callback notify_cb,
	                  data_callback data_cb,
	                  data_callback_timestamp data_cb_timestamp,
	                  void* user);


	//water mark
	bool enableWaterMark();
	bool disableWaterMark();
	status_t setWaterMarkMultiple(const char *str);
	
#ifdef ADAS_ENABLE
	bool enableAdas();
	bool disableAdas();
	status_t setAdasParameters(int key,int value);
	bool setAdasCallbacks(camera_adas_data_callback adas_data_cb);
#endif



	int updateHardwareInfo(CameraHardware * p,int id);
	int add360Hardware();

	int getTVINSystemType()
	{
		mHardwareCameras->getTVINSystemType();
	}
	int setGpsData(void *gpsData){
	    return mHardwareCameras->sendCommand(CAMERA_CMD_SET_GPSDATA_RECORDER, (unsigned long)gpsData, 0);
	}

	int setWhiteBlanceData(int32_t Data){
		return mHardwareCameras->sendCommand(CAMERA_CMD_SET_WHITE_BALANCE, Data, 0);
	}

	int setColorEffectData(int32_t Data){
		return mHardwareCameras->sendCommand(CAMERA_CMD_SET_COLOR_EFFECT, Data, 0);
	}

	int setExposureCompensationData(int32_t Data)
	{
		return mHardwareCameras->sendCommand(CAMERA_CMD_SET_EXPOSURE_COMPENSATION, Data, 0);
	}
	
	int mCameraId;
	int recordwith;
	int recordheith;

	sp<AudioCapThread> mAudioCap;
	int mAudioHdl;
	AUDIO_ENCODER_TYPE mAudioEncType;
	int setAudioOps(sp<AudioCapThread> act,int hdl){
		ALOGV("----setAudioOps----hdl=%d-----",hdl);
		mAudioCap=act;
		mAudioHdl=hdl;
		return 0;
	}
	
	static void __dvr_audio_data_cb_timestamp(int32_t msgType,nsecs_t timestamp,int card,int device,
	       char *dataPtr,int dsize,void* user);

    void SetCurRecordStat(int iCurRedStat){ //mod lss
        mCurRecordStat = iCurRedStat;
    }
    int GetCutRecortStat(){
        return mCurRecordStat;
    }

	RecordCamera* mRecordCamera;

	CameraManager * m360CameraManager;
	CameraHardware ** m360Hardware;
	CCameraConfig *m360Config[NUM_OF_360CAMERAS];

	CameraHardware * mHardwareCameras;
	CCameraConfig *mCameraConfig;
private:
	static void notifyCallback(int32_t msgType, int32_t ext1,
	                           int32_t ext2, void* user);
	
	static void __notify_cb(int32_t msg_type, int32_t ext1,
	                        int32_t ext2, void *user);
	
	static void __data_cb(int32_t msg_type,
	                      char *data,
	                      camera_frame_metadata_t *metadata,
	                      void *user);

	static void __data_cb_timestamp(nsecs_t timestamp, int32_t msg_type,
	                               char *data,
	                               void *user);
	
	notify_callback         mNotifyCb;
	data_callback           mDataCb;
	data_callback_timestamp mDataCbTimestamp;
	void *mCbUser;

	//h264 data cb
	usr_data_cb usrDatCb;
	void *mCbUserDat;

	//audio encoder 
	AutAudioEnc *mDvrAudioEnc;

    int mCurRecordStat;
protected:
    /* Locks this instance for parameters, state, etc. change. */
    Mutex                           mObjectLock;
};

//}

#endif
