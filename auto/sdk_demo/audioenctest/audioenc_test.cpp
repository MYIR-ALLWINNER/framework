
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


#include "audio_hal.h"

#ifndef CDX_V27
#include "log.h"
#endif

#include "StorageManager.h"
#include "DvrFactory.h"
#include <sys/socket.h>
#include <sys/un.h>
#include "DvrRecordManager.h"

//#include "moudle/Audio.h"

#include <mcheck.h> 

using namespace android;

#define TEST_CAMERA_ID 0

#define TEST_H264_OUTPUT

status_t audioRecMuxerCb(int32_t msgType,
                                char *dataPtr,int dalen,
                                void *user)
{

media_msg_t  * pmsg = (media_msg_t  *)dataPtr;
        CdxMuxerPacketT *ppkt=(CdxMuxerPacketT *)&pmsg->mesg_data[0];
		ALOGV("audioRecMuxerCb!!! TYPE=%d pmsg=%p ppkt->buf=%p\n",msgType,pmsg,ppkt->buf);
        if(ppkt->buf!=NULL)
            free(ppkt->buf);
        ppkt->buf = NULL;

    if(pmsg!=NULL)
        free(pmsg);
	return 0;
}
int main(int argc, char *argv[])
{
	//setenv("MALLOC_TRACE", "/tmp/output", 1);
	//mtrace(); 
	int ret=0;

AutAudioEnc *mDvrAudioEnc;
mDvrAudioEnc = new AutAudioEnc();  //encode audio
	AudioEncConfig audioEncConfig;
	memset(&audioEncConfig, 0x00, sizeof(AudioEncConfig));
	audioEncConfig.nInChan = 2;
	audioEncConfig.nInSamplerate = 44100;
	audioEncConfig.nOutChan = 2;
	audioEncConfig.nOutSamplerate = 44100;
	audioEncConfig.nSamplerBits = 16;
	audioEncConfig.nType = AUDIO_ENCODER_AAC_TYPE;
	audioEncConfig.nFrameStyle = 1;
	
	mDvrAudioEnc->AutAudioEncInit(&audioEncConfig);
	mDvrAudioEnc->AudioRecStart();		//编码线程启动
	mDvrAudioEnc->setAudioEncDataCb(audioRecMuxerCb,NULL);
	
	char  yuvfile[64];
	int retsize = 0;
	static int s_ppsFlag = 0;
	sprintf(yuvfile,"/tmp/test.wav");
	
	FILE *inputfd = fopen(yuvfile,"rb");
	if(NULL == inputfd){
		printf("fopen %s faile\n",yuvfile);
		return -1;
	}else{
		printf("fopen %s OK\n",yuvfile);
	}

    #ifdef TEST_OUTPUT
	char  outfile[64];
	sprintf(outfile,"/tmp/recode_out.h264");
	FILE *outputfd = fopen(outfile,"a+");
	if(NULL == outputfd){
		printf("fopen %s faile\n",outfile);
	}else{
		printf("fopen %s OK\n",outfile);
	}
    #endif
	char *databuf=(char *)malloc(4096);
	retsize = fread((void *)databuf, 1, 44, inputfd);//remove head
	//sp < AudioCapThread > audiocap = new AudioCapThread();
	retsize = fread((void *)databuf, 1, 4096, inputfd);
	while(1){
/* 		retsize = fread((void *)databuf, 1, 4096, inputfd);
		if(retsize <= 0){
			ALOGD("---------------input close---------------------");
			fclose(inputfd);
			inputfd = NULL;
			break;
		} */
/* 	
		struct timeval lRunTimeEnd;
		gettimeofday(&lRunTimeEnd, NULL);
		long long time1 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
		long long time2 = 0;
		long long time3 = 0 ; */

		mDvrAudioEnc->__audioenc_data_src(0,0,0,0, databuf,4096, mDvrAudioEnc);

/* 		gettimeofday(&lRunTimeEnd, NULL);
		time2 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
		time3 = time2 - time1 ;
		printf("encode use runtime %lldus(%lldms)\n",time3,time3/1000);
		time1 = time2; */
		
		usleep(22*1000);  
	}

	printf("recortTest finish!!!\n");
	
	mDvrAudioEnc->AudioRecStop();
	mDvrAudioEnc->AutAudioEncDeinit();
	delete mDvrAudioEnc;
    
	if(inputfd){
		fclose(inputfd);
		inputfd = NULL;
	}
#ifdef TEST_OUTPUT
	if(outputfd){
		fclose(outputfd);
		outputfd = NULL;
	}
#endif
	if(databuf)
		free(databuf);
	printf("recordTest run finish\n");

	return 0;

}
