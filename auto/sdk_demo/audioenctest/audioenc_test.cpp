#include "DvrFactory.h"

using namespace android;

#define MODULE_VERSION "V2.0.20220506"

FILE *inputfd = NULL;
FILE *outputfd = NULL;

status_t audioRecMuxerCbXF(int32_t msgType,
                                char *dataPtr,int dalen,
                                void *user)
{

		media_msg_t  * pmsg = (media_msg_t  *)dataPtr;
        CdxMuxerPacketT *ppkt=(CdxMuxerPacketT *)&pmsg->mesg_data[0];
		//printf("audioRecMuxerCb!!! TYPE=%d pmsg=%p ppkt->buf=%p\n",msgType,pmsg,ppkt->buf);
		fwrite(ppkt->buf,ppkt->buflen,1,outputfd);
        if(ppkt->buf!=NULL)
            free(ppkt->buf);
        ppkt->buf = NULL;

    if(pmsg!=NULL)
        free(pmsg);
	return 0;
}
int main(int argc, char *argv[])
{
    printf("audioenc test version:%s\n", MODULE_VERSION);

	//setenv("MALLOC_TRACE", "/tmp/output", 1);
    //mtrace();
	int ret=0;

	AutAudioEnc *mDvrAudioEnc;
	mDvrAudioEnc = new AutAudioEnc();  //encode audio
	AudioEncConfig audioEncConfig;
	memset(&audioEncConfig, 0x00, sizeof(AudioEncConfig));
	audioEncConfig.nInChan = 2;
	audioEncConfig.nInSamplerate = 48000;
	audioEncConfig.nOutChan = 2;
	audioEncConfig.nOutSamplerate = 48000;
	audioEncConfig.nSamplerBits = 16;
	audioEncConfig.nType = AUDIO_ENCODER_MP3_TYPE;
	audioEncConfig.nFrameStyle = 1;

	mDvrAudioEnc->AutAudioEncInit(&audioEncConfig);
	mDvrAudioEnc->AudioRecStart();		//编码线程启动
	mDvrAudioEnc->setAudioEncDataCb(audioRecMuxerCbXF,NULL);

	char  wavfile[64];
	int retsize = 0;
	static int s_ppsFlag = 0;
	sprintf(wavfile,"/tmp/test.wav");

	inputfd = fopen(wavfile,"rb");
	if(NULL == inputfd){
		printf("fopen %s faile\n",wavfile);
		return -1;
	}else{
		printf("fopen %s OK\n",wavfile);
	}

	sprintf(wavfile,"/tmp/test.mp3");
	outputfd = fopen(wavfile,"ab+");
	if(NULL == outputfd){
		printf("fopen %s faile\n",wavfile);
		return -1;
	}else{
		printf("fopen %s ok \n",wavfile);
	}

	char *databuf=(char *)malloc(4096);
	retsize = fread((void *)databuf, 1, 44, inputfd);//remove head
	//sp < AudioCapThread > audiocap = new AudioCapThread();
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
		retsize = fread((void *)databuf, 1, 4096, inputfd);
		if(retsize<4096){
			printf("file end exit.\n");
			break;}
		mDvrAudioEnc->__audioenc_data_src(0,0,0,0, databuf,4096, mDvrAudioEnc);

/* 		gettimeofday(&lRunTimeEnd, NULL);
		time2 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
		time3 = time2 - time1 ;
		printf("encode use runtime %lldus(%lldms)\n",time3,time3/1000);
		time1 = time2; */

        usleep(5*1000);
	}


	mDvrAudioEnc->AudioRecStop();
	mDvrAudioEnc->AutAudioEncDeinit();
	delete mDvrAudioEnc;

	if(inputfd){
		fclose(inputfd);
		inputfd = NULL;
	}
	if(outputfd){
		fclose(outputfd);
		outputfd = NULL;
	}
	if(databuf)
		free(databuf);
	printf("audioenc test run finish\n");

	return 0;

}
