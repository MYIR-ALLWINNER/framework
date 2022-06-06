
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
//#include "moudle/Audio.h"

#include <mcheck.h> 

using namespace android;

#define TEST_CAMERA_ID 0

#define TEST_H264_OUTPUT

void Rec_usernotifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void *user)
{
	LOGE("msgType =%d-----data=%p-----%d)", msgType, user);

	if ((msgType & CAMERA_MSG_ERROR) == CAMERA_MSG_ERROR) {
		LOGE("(msgType =CAMERA_MSG_ERROR)");

	}
	#if 0
	if ((msgType & CAMERA_MSG_DVR_NEW_FILE) == CAMERA_MSG_DVR_NEW_FILE) {
		dvr_factory *p_dvr = (dvr_factory *) user;
		LOGE("(msgType =CAMERA_MSG_DVR_NEW_FILE camera %d idx =%d)", p_dvr->mCameraId, ext1);
	}

	if ((msgType & CAMERA_MSG_DVR_STORE_ERR) == CAMERA_MSG_DVR_STORE_ERR) {
		LOGE("msgType =CAMERA_MSG_DVR_STORE_ERR)");
		dvr_factory *p_dvr = (dvr_factory *) user;
		p_dvr->mRecordCamera->storage_state = 0;
		p_dvr->stopRecord();
	}
	#endif
}

void Rec_userdataCallback(int32_t msgType, char *dataPtr, camera_frame_metadata_t * metadata,void *user)
{
    
}

void Rec_userdataCallbackTimestamp(nsecs_t timestamp, int32_t msgType, char *dataPtr, void *user)
{
	V4L2BUF_t *pbuf = (V4L2BUF_t *) (dataPtr );
}

int main(int argc, char *argv[])
{
	//setenv("MALLOC_TRACE", "/tmp/output", 1);
	//mtrace(); 
	int ret=0;
	V4L2BUF_t v4l2_buf;
	unsigned int memtype = MEM_TYPE_CDX_NEW;   //dont use  MEM_TYPE_DMA in t5
	sdk_log_setlevel(6);
	
	DvrRecordManagerInit(); 
	int mCameraId  = 0;
	int recordwith = config_get_weith(mCameraId);
	int recordheith = config_get_heigth(mCameraId);
	
	RecordCamera *pRecordCamera = new RecordCamera(mCameraId);
	pRecordCamera->videoEncParmInit(recordwith, recordheith, 
								recordwith, recordheith, 8, 25, VENC_CODEC_H264);
								
	pRecordCamera->setCallbacks(Rec_usernotifyCallback,pRecordCamera);
	
	pRecordCamera->setDuration(1 * 60);

	pRecordCamera->start();
	pRecordCamera->startRecord();
	

	dma_mem_des_t recordMem;
	memset(&recordMem, 0, sizeof(dma_mem_des_t));
	ret = allocOpen(memtype, &recordMem, NULL);  
	if (ret < 0) {
		LOGE("ion_alloc_open failed");
	}
	recordMem.size = recordwith*recordheith*3/2;
	ret = allocAlloc(memtype, &recordMem, NULL);
	if(ret < 0){
		ALOGE("allocAlloc failed");
	}

	char  yuvfile[64];
	int retsize = 0;
	static int s_ppsFlag = 0;
	sprintf(yuvfile,"/tmp/720p_recordTest.yuv");
	
	FILE *inputfd = fopen(yuvfile,"rb");
	if(NULL == inputfd){
		printf("fopen %s faile\n",yuvfile);
	}else{
		printf("fopen %s OK\n",yuvfile);
	}

    #ifdef TEST_H264_OUTPUT
	char  outfile[64];
	sprintf(outfile,"/tmp/recode_out.h264");
	FILE *outputfd = fopen(outfile,"a+");
	if(NULL == outputfd){
		printf("fopen %s faile\n",outfile);
	}else{
		printf("fopen %s OK\n",outfile);
	}
    #endif

	while(1){
		retsize = fread((void *)recordMem.vir, 1, recordMem.size, inputfd);
		if(retsize <= 0){
			ALOGD("---------------input close---------------------");
			fclose(inputfd);
			inputfd = NULL;
			break;
		}
		flushCache(memtype, &recordMem, NULL);
		v4l2_buf.width = 1280;
		v4l2_buf.height = 720;
		v4l2_buf.addrPhyY = recordMem.phy;
		v4l2_buf.addrPhyC = recordMem.phy + v4l2_buf.width*v4l2_buf.height;
		v4l2_buf.addrVirY = recordMem.vir;
		v4l2_buf.addrVirC = recordMem.vir + v4l2_buf.width*v4l2_buf.height;
		v4l2_buf.dmafd = recordMem.ion_buffer.fd_data.aw_fd;
		v4l2_buf.timeStamp =  (int64_t) systemTime();

		
		CdxMuxerPacketT pkt;
		
		struct timeval lRunTimeEnd;
		gettimeofday(&lRunTimeEnd, NULL);
		long long time1 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
		long long time2 = 0;
		long long time3 = 0 ;

#ifdef TEST_H264_OUTPUT
		//encode will malloc pkt.buflen size buf to pkt.buf!we need to free it at h264 test
		ret = pRecordCamera->encode(&v4l2_buf, (char *) &pkt, NULL, NULL);
		if (ret < 0) {
			LOGW("encode fail");
			return -1;
		}

		if(s_ppsFlag == 0){
			s_ppsFlag = 1;
			VencHeaderData sps_pps_data;
			VideoEncGetParameter(pRecordCamera->pRecVideoEnc, VENC_IndexParamH264SPSPPS, &sps_pps_data);
			if(outputfd){
				fwrite(sps_pps_data.pBuffer, 1, sps_pps_data.nLength, outputfd);
			}
		}
		
		if(outputfd){
			fwrite((void *)pkt.buf,1,pkt.buflen,outputfd);
		}
		free(pkt.buf);
		pkt.buf = NULL;
#else
        //output is mp4 in /mnt/sdcard/mmcblk1p1/ dir
		pRecordCamera->dataCallbackTimestamp(v4l2_buf.timeStamp,CAMERA_MSG_VIDEO_FRAME, 
									(char *)&v4l2_buf, NULL);
#endif

		gettimeofday(&lRunTimeEnd, NULL);
		time2 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
		time3 = time2 - time1 ;
		printf("encode use runtime %lldus(%lldms)\n",time3,time3/1000);
		time1 = time2;
		
		usleep(30*1000);  
	}

	allocFree(memtype, &recordMem, NULL);
	printf("recortTest finish!!!\n");

    pRecordCamera->stopRecord();
    pRecordCamera->stop();
    pRecordCamera->videoEncDeinit();
    delete pRecordCamera;
    pRecordCamera = NULL;
    
	if(inputfd){
		fclose(inputfd);
		inputfd = NULL;
	}
#ifdef TEST_H264_OUTPUT
	if(outputfd){
		fclose(outputfd);
		outputfd = NULL;
	}
#endif
	
	printf("recordTest run finish\n");
    #ifdef TEST_H264_OUTPUT
        printf("please check /tmp/recode_out.h264 file\n");
    #else
        printf("please check /mnt/sdcard/mmcblk1p1/ dir to find *.mp4\n");
    #endif
	return 0;

}
