//SDKLIB_TEST have already defined by Makefile
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sdklog.h>
#include <time.h>
#include <cutils/log.h>
#include "aw_ini_parser.h"

#include "CameraDebug.h"
#include "hwdisp2.h"

#include "V4L2CameraDevice2.h"
#include "CallbackNotifier.h"
#include "PreviewWindow.h"
#include "CameraHardware2.h"

#include "audio_hal.h"

#ifndef CDX_V27
#include "log.h"
#endif

#include "vencoder.h"
#include "CdxMuxer.h"
#include "Rtc.h"
#include "StorageManager.h"
#include "DvrFactory.h"
#include "CameraFileCfg.h"
#include <sys/socket.h>
#include <sys/un.h>
#include "Fat.h"
#include "DebugLevelThread.h"
#include "DvrRecordManager.h"

#include "moudle/AutoMount.h"
#include "moudle/Display.h"
#include "moudle/Audio.h"

#include "sdktest.h"
#include <mcheck.h> 
#include "AutoMount.h"
#include <ls_ctrl.h>
#include "G2dApi.h"

using namespace android;

#define TEST_CAMERA_ID 0

void testStop(int signo)
{
    ALOGD("oops! stop!!! %d\n",signo);
    _exit(0);
}

#define MAX_TEST_CAMERA 14
dvr_factory *dvrs[MAX_TEST_CAMERA];
static int g360idx = 0;
typedef struct {
	int record;
	int preview;
}dvrstat_t;

dvrstat_t test_dvrstat[MAX_TEST_CAMERA];

/**************************************
Function:usr_datacb
Description:dataPtr has encoded data such as H264 or jpeg data
***************************************/
static FILE *pfileH264 = NULL;
static int cameranums = 0;
static int cameraId[MAX_TEST_CAMERA] = {0};

status_t usr_datacb(int32_t msgType, char *dataPtr, int dalen, void *user)
{
	dvr_factory *p_dvr = (dvr_factory *) user;
	
	return 0;
}
/**************************************
Function:
Description:
***************************************/
void usernotifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void *user)
{
	LOGE("msgType =%x-----data=%p-----%d)", msgType, user);
	RecordCamera *p_dvr = (RecordCamera*) user;

	if ((msgType & CAMERA_MSG_ERROR) == CAMERA_MSG_ERROR) {
		LOGE("(msgType =CAMERA_MSG_ERROR  code=%d)",ext1);

	}
	if ((msgType & CAMERA_MSG_DVR_NEW_FILE) == CAMERA_MSG_DVR_NEW_FILE) {
		//dvr_factory *p_dvr = (dvr_factory *) user;
		LOGE("(msgType =CAMERA_MSG_DVR_NEW_FILE camera %d idx =%d)", p_dvr->mCameraId, ext1);
	}

	if ((msgType & CAMERA_MSG_DVR_STORE_ERR) == CAMERA_MSG_DVR_STORE_ERR) {
		LOGE("msgType =CAMERA_MSG_DVR_STORE_ERR)");
		//dvr_factory *p_dvr = (dvr_factory *) user;
		if(p_dvr){
			p_dvr->storage_state = 0;
			test_dvrstat[g360idx].record =0;
			dvrs[g360idx]->stopRecord();
		}
	}
}

/**************************************
Function:
Description:
***************************************/
void userdataCallback(int32_t msgType, char *dataPtr, camera_frame_metadata_t * metadata,void *user)
{
	int i;
	
	dvr_factory *p_dvr = (dvr_factory *) user;
	V4L2BUF_t *pv4l2_buf = (V4L2BUF_t *) dataPtr;
	
	if(CAMERA_MSG_PREVIEW_FRAME == msgType){

	}
}

/**************************************
Function:
Description:data is from V4l2 captureThread,it's NV21 format YUV
***************************************/
void userdataCallbackTimestamp(nsecs_t timestamp, int32_t msgType, char *dataPtr, void *user)
{
	V4L2BUF_t *pbuf = (V4L2BUF_t *) (dataPtr );
}

void argsAnalysis(int argc, char *argv[], int *cameraId)
{
//======Analysis argv=========
	printf("argc = %d \r\n", argc);
	int i = 0;
	if (argc > 2) {

		cameranums = atoi(argv[1]);
		if((cameranums > MAX_TEST_CAMERA)||((cameranums < 1)))
		{
			printf("can not support %d,max support camera numbers %d \r\n",cameranums,MAX_TEST_CAMERA);
			exit(-1);
		}
		if(argc<cameranums+2)
		{
			printf("bad parm num %d can not support %d,max support camera numbers %d \r\n",argc,cameranums,MAX_TEST_CAMERA);
			exit(-1);
		}
		for(i=0;i<cameranums;i++){
			cameraId[i]  = atoi(argv[2+i]);
		}
		int j;
		for(i=0;i<cameranums;i++){
			if(cameraId[i]==360)
			{
				for(j=0;j<cameranums;j++){
					if((cameraId[j]==2)||(cameraId[j]==3)||(cameraId[j]==4)||(cameraId[j]==5))
					{
						printf("when use camera 360,can not use csi camera %d \r\n",cameraId[j]);
						exit(-1);
					}
				}
			}
			
			if(cameraId[i]==8)
			{
				for(j=0;j<cameranums;j++){
					if((cameraId[j]==4)||(cameraId[j]==5)||(cameraId[j]==6)||(cameraId[j]==7))
					{
						printf("when use camera 8,can not use cvbs camera %d \r\n",cameraId[j]);
						exit(-1);
					}
					
				}
			}
		}			

		
		printf("argv[1] =%s \r\n", argv[1]);
	}else
	{
			printf(" ---------------sdktest-------------------------\r\n"
			"cameraId:	0,1,2,3,4,5,6,7,8,360"
			"if cameraId is 360,dont open /dev/video2~5 \r\n"
			"arg1:camera number x \r\n"
			"arg2->arg(x+1):cameraid1 ... cameraidx \r\n"
			"for example:"
			"\r\n");
			printf("/sdktest 1	0    	//for test video 0\r\n");
			printf("/sdktest 3  0 1 2 	//for test video 0,1,2 \r\n");
			printf("/sdktest 2  0  2 	//for test video 0,2 \r\n");
			printf("/sdktest 1	360  	//for test video 360(4 csi in)\r\n");
			printf("/sdktest 3 0 1 360  //for test video 0 1 and 360 \r\n");
			printf(" ---------------sdktest-------------------------\r\n");
			exit(-1);
	}
}

#define HAVAAUDIO 1
#define RECORD_TEST 1

void testaudiocb(int32_t msgType,nsecs_t timestamp,int card,int device,
                                   char *dataPtr,int dsize,
                                   void* user)
{
	ALOGD("testaudiocb date=%p ,len=%d ,usrp=%p",dataPtr,dsize,user);
}

static void terminate(int sig_no)
{
	printf("Got signal %d, exiting ...\n", sig_no);
    for(int i=0;i<cameranums;i++)
    {
		if(test_dvrstat[i].preview ==1){
			dvrs[i]->stopPriview();
			test_dvrstat[i].preview =0;
		}
		
		if(test_dvrstat[i].record == 1){
			test_dvrstat[i].record =0;
			dvrs[i]->stopRecord();
		}
		dvrs[i]->stop();
        
		delete dvrs[i];
		dvrs[i] = NULL;
    }
	system("cat /sys/class/disp/disp/attr/sys");
   exit(1);
}

static void install_sig_handler(void)
{
	signal(SIGBUS, terminate);
	signal(SIGFPE, terminate);
	signal(SIGHUP, terminate);
	signal(SIGILL, terminate);
	signal(SIGKILL, terminate);
	signal(SIGINT, terminate);
	signal(SIGIOT, terminate);
	//signal(SIGPIPE, terminate);
	signal(SIGQUIT, terminate);
	//signal(SIGSEGV, terminate);
	signal(SIGSYS, terminate);
	signal(SIGTERM, terminate);
	signal(SIGTRAP, terminate);
	signal(SIGUSR1, terminate);
	signal(SIGUSR2, terminate);
}

int main(int argc, char *argv[])
{
	//setenv("MALLOC_TRACE", "/tmp/output", 1);
	//mtrace(); 
	sigset_t set1;
	sigemptyset(&set1);
	sigaddset(&set1 , SIGIO);   //block SIGIO signal in main thread,SIGIO will wakeup sleep
	pthread_sigmask(SIG_BLOCK , &set1 , NULL);
	sigpending(&set1);
	
	signal(SIGINT, testStop);
    install_sig_handler();
	int rt=0;

	sdk_log_setlevel(6);
	int mode;
	//======moudle init===========
	int i;
	for(i=0;i<MAX_TEST_CAMERA;i++){
		cameraId[i] = -1;
	}

	argsAnalysis(argc, argv, cameraId);  //cameraId[i] will be: 0/1/2/3/4/5/6/7/360
	cameranums = atoi(argv[1]);

	//start audio capture thread
	#ifdef HAVAAUDIO
	sp < AudioCapThread > audiocap = new AudioCapThread();
	#endif
	int hdl;
	int ret;

	DvrRecordManagerInit();
	int testcnt=0;
retry:

	dvr_factory *tmp_dvr;
	for(i=0;i<cameranums;i++){
		test_dvrstat[i].record =0;
		test_dvrstat[i].preview =0;
		printf("cameraId[%d]=%d\n",i,cameraId[i]);
		if(360 == cameraId[i])
			g360idx = i;
		dvrs[i] = new dvr_factory(cameraId[i]);
		tmp_dvr = dvrs[i];
#ifdef HAVAAUDIO		
		hdl= audiocap->reqAudioSource(tmp_dvr->__dvr_audio_data_cb_timestamp,(void *)tmp_dvr);
		tmp_dvr->setAudioOps(audiocap, hdl);
#endif
		tmp_dvr->SetDataCB(usr_datacb, tmp_dvr);
		tmp_dvr->setCallbacks(usernotifyCallback, userdataCallback, userdataCallbackTimestamp, tmp_dvr);
			int rt=0;
#ifdef 	RECORD_TEST
		rt = tmp_dvr->recordInit();
		if (0 != rt) {
			ALOGE("pdvr->recordInit error\n");
			return -1;
		}
		else {
			ALOGD("pdvr->recordInit success\n");
		}	
		tmp_dvr->startRecord();
		test_dvrstat[i].record = 1;
#endif
	}

	DisplayInit(DISP_GET_CONFIG,dvrs[0]->mCameraId); 

	for(i=0;i<cameranums;i++){
		rt = dvrs[i]->start();
		if (rt < 0) {
			ALOGE("dvrs[%d]->start() error\n",i);
			return -1;
		}
	}

	//dvrs[0]->takePicture();   
	
	//======preview===========
	struct view_info vv = { 0, 0, 1280, 800 };
	int recordcnt=0;

	#ifdef 	RECORD_TEST
	while (1) 
	#endif
	{
		for(i=0;i<cameranums;i++){   //show 7sec then sleep 3set, switch video
			ret = dvrs[i]->startPriview(vv);
			if(ret != 0){
				ALOGE("dvr startPreview error,maybe cam isn't inline");
				return -1;
			}
			ALOGV("preview camera %d for 7 sec",cameraId[i]);

			sleep(7);
			dvrs[i]->stopPriview();
			sleep(3);
		}
	}
	
	for(i=0;i<cameranums;i++){
		if(test_dvrstat[i].preview ==1){
			rt = dvrs[i]->stopPriview();
			test_dvrstat[i].preview =0;
		}
		
		if(test_dvrstat[i].record == 1){
			test_dvrstat[i].record =0;
			dvrs[i]->stopRecord();
		}
		sleep(2);
		rt = dvrs[i]->stop();
		#ifdef HAVAAUDIO
		dvrs[i]->mAudioCap->releaseAudioSource(dvrs[i]->mAudioHdl);
		#endif
	}
	
	sleep(1);
	for(i=0;i<cameranums;i++){
		delete dvrs[i];
		dvrs[i] = NULL;
	}
	
	sleep(2);
	if(pfileH264){
		fclose(pfileH264);
	}
	{
		printf("\n\n\n\n\n\n\n\n----------test---%d end \n\n\n\n\n\n\n\n",testcnt);
		ALOGV("\n\n\n\n\n\n\n\n----------test---%d end \n\n\n\n\n\n\n\n",testcnt);
		testcnt++;
        //if(testcnt<10)
		goto retry;
	}
#ifdef HAVAAUDIO
	audiocap->stopAudio();
#endif
	while(1){
		LOGE("sleep forever");
		sleep(1000);
	}
	return 0;
}
