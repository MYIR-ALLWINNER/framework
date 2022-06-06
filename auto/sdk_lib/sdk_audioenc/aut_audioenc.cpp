#include "aut_audioenc.h"
using namespace android;
#define LOG_TAG "AudioEnc"

AutAudioEnc::AutAudioEnc():usrDatCb(NULL),mCbUserDat(NULL),mAudioRecordQueueErr(0){


	OSAL_QueueCreate(&mQueueBufferAudioEnc, 96);
	mAudioEncThread = new AudioEncThread(this);
	pthread_mutex_init(&mAudioEncMutex, NULL);
	pthread_cond_init(&mAudioEncCond, NULL);
	mAudioThreadState = RECORD_STATE_PAUSED;
	mAudioEncThread->startThread();
}
AutAudioEnc::~AutAudioEnc()

{
	if (mAudioEncThread != NULL) {
		mAudioEncThread->stopThread();
		pthread_mutex_lock(&mAudioEncMutex);
        pthread_cond_signal(&mAudioEncCond);
        pthread_mutex_unlock(&mAudioEncMutex);
		mAudioThreadState = RECORD_STATE_NULL;
		mAudioEncThread.clear();
		mAudioEncThread = 0;
	}

	pthread_mutex_destroy(&mAudioEncMutex);
	pthread_cond_destroy(&mAudioEncCond);
	OSAL_QueueTerminate(&mQueueBufferAudioEnc);

}
int AutAudioEnc::AutAudioEncInit(AudioEncConfig* pconfig)
{
    int ret=0;
    pAudioEncode = CreateAudioEncoder();

    if(!pAudioEncode)
    {
        ALOGE("AudioEncInit failed");
        return -1;
    }

    if(InitializeAudioEncoder(pAudioEncode, pconfig) < 0)
    {
        ALOGE("AudioEncInit init failed");
        return -1;
    }
    ALOGW("AudioEncInit success");

	memcpy(&aencconfig,pconfig,sizeof(AudioEncConfig));

    return ret;
}

int AutAudioEnc::AutAudioEncDeinit()
{
    int ret=0;
    if(pAudioEncode)
    {
        DestroyAudioEncoder(pAudioEncode);
        pAudioEncode=NULL;
    }

    return ret;
}

#define USE_AUDIO_ENC 1
void AutAudioEnc::dropQueue()
{
	media_msg_t * datmsg=NULL;

	int qcnt = OSAL_GetElemNum(&mQueueBufferAudioEnc);
	LOGV("audio record dropQueue cnt %d sleep...",qcnt);
	if(qcnt>0)
	{
		while(qcnt>0)
		{
			datmsg = (media_msg_t *)OSAL_Dequeue(&mQueueBufferAudioEnc);
			if(datmsg!=NULL)
			{
				free(datmsg->extradata);
				free(datmsg);
			}
			qcnt--;
		}
	
	}

}

bool AutAudioEnc::AutAudioEncThread()
{
    int ret=0;
    bool rt=false;
    media_msg_t * datmsg=NULL;


    CdxMuxerPacketT pkt;
    int pcm_size = 0;
    char *pcm_buf = NULL;
    if(mAudioThreadState==RECORD_STATE_STARTED)
    {
        datmsg = (media_msg_t *)OSAL_Dequeue(&mQueueBufferAudioEnc);
        if(datmsg==NULL)
        {
            //ALOGW("--AutAudioEncThread----pop---%p",pamsg);
            pthread_mutex_lock(&mAudioEncMutex);
            pthread_cond_wait(&mAudioEncCond, &mAudioEncMutex);
            pthread_mutex_unlock(&mAudioEncMutex);

            return true;
        }
		if((datmsg!=NULL)&&(datmsg->extradata==NULL))
		{
            //ALOGW("--AutAudioEncThread----pop---%p",pamsg);
            free(datmsg);
            pthread_mutex_lock(&mAudioEncMutex);
            pthread_cond_wait(&mAudioEncCond, &mAudioEncMutex);
            pthread_mutex_unlock(&mAudioEncMutex);

            return true;
        }	

        pcm_size = datmsg->mesg_len;

        pcm_buf  = datmsg->extradata;
        //for test
        #if 0
       ALOGV("--AutAudioEncThread----pop-%p--msgp=%p pcmp=%p size=%d",&mQueueBufferAudioEnc,datmsg,pcm_buf,pcm_size);
        if(datmsg!=NULL){
        	free(datmsg->extradata);
       	free(datmsg);
        }
       return true;
	   #endif
		//test end
		
        memset(&pkt, 0, sizeof(CdxMuxerPacketT));
#ifdef USE_AUDIO_ENC 
		AudioEncOutBuffer bufInfo;

        ret =WriteAudioStreamBuffer(pAudioEncode, pcm_buf , pcm_size);
        if(ret<0)
        {
            ALOGE("-ERROR--WriteAudioStreamBuffer--ret=%d",ret);
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
	        return true;
	    }

        ret = EncodeAudioStream(pAudioEncode);

        if(ret == ERR_AUDIO_ENC_NONE)
        {
            //logd("audio encode ok");
            rt=true;
        }
        else if(ret == ERR_AUDIO_ENC_ABSEND)
        {
            ALOGE("audio encode ERR_AUDIO_ENC_ABSEND");
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            return true;
        }
        else if (ret == ERR_AUDIO_ENC_UNKNOWN)
        {
            ALOGE("audio encode ERR_AUDIO_ENC_UNKNOWN");
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            return true;
        }
        else if (ret == ERR_AUDIO_ENC_PCMUNDERFLOW || ret == ERR_AUDIO_ENC_OUTFRAME_UNDERFLOW)
        {
            ALOGE("audio encode ERR_AUDIO_ENC_PCMUNDERFLOW");
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            usleep(10*1000); // it is not a good idea to do this
            return true;
        }
        else //ERR_AUDIO_ENC_NONE
        {
            ALOGE("unkown ret(%d)", ret);
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            return true;
        }
        ret = RequestAudioFrameBuffer(pAudioEncode, &bufInfo.pBuf, &bufInfo.len, &bufInfo.pts, &bufInfo.bufId);
        if(ret<0)
        {
            ALOGE("-ERROR--RequestAudioFrameBuffer--ret=%d",ret);
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            return true;
        }
        if(bufInfo.len > pcm_size)
        {
            ALOGE("-ERROR----outlen=%d outp=%p pkt.buf=%p inlen=%d ret=%d",bufInfo.len,bufInfo.pBuf,pkt.buf,pcm_size,ret);
            ReturnAudioFrameBuffer(pAudioEncode, bufInfo.pBuf, bufInfo.len, bufInfo.pts, bufInfo.bufId);
            if(datmsg!=NULL)
	        {
	            free(datmsg->extradata);
	            free(datmsg);
	        }
            return true;

        }
        
        pkt.buflen = bufInfo.len;
        pkt.length = bufInfo.len;
        pkt.buf = malloc(bufInfo.len);
        memcpy(pkt.buf, bufInfo.pBuf, pkt.buflen);
        pkt.pts = bufInfo.pts;
        pkt.type = CDX_MEDIA_AUDIO;
        pkt.streamIndex = 1;

        ReturnAudioFrameBuffer(pAudioEncode, bufInfo.pBuf, bufInfo.len, bufInfo.pts, bufInfo.bufId);
#else
		pkt.buflen = pcm_size;
        pkt.length = pcm_size;
        pkt.buf = malloc(pcm_size);
        memcpy(pkt.buf, pcm_buf, pcm_size);
        pkt.pts = datmsg->timestamp;
        pkt.type = CDX_MEDIA_AUDIO;
        pkt.streamIndex = 1;
#endif
		
        media_msg_t *pkmsg;

		pkmsg=(media_msg_t *)malloc(sizeof(media_msg_t));
		if(pkmsg==NULL)
		{
		    LOGW("AutAudioEncThread malloc fail");
		    if(datmsg!=NULL)
		    {
		        free(datmsg->extradata);
		        free(datmsg);
		    }
		    return true;
		}
				
	    memcpy(&pkmsg->mesg_data[0],&pkt,sizeof(CdxMuxerPacketT));//blank
	    pkmsg->timestamp = datmsg->timestamp;

	    if(datmsg!=NULL)
	    {
	        free(datmsg->extradata);
	        free(datmsg);
	    }

	    pkmsg->mesg_len = sizeof(CdxMuxerPacketT);
	    pkmsg->mesg_type = CDX_MEDIA_AUDIO;

	    if(usrDatCb!=NULL)
	    {
	        ret=usrDatCb(CDX_MEDIA_AUDIO,(char*)pkmsg,sizeof(media_msg_t),mCbUserDat);
	        if (ret != 0)
	        {
	            mAudioRecordQueueErr++;
	            if((mAudioRecordQueueErr%30)==1)//FIRST AND 30ERROR REPORT
	                LOGW("audio record queue full msgQSend %d",1);
	            free(pkt.buf);
	            free(pkmsg);
	        }
		}else
		{
			free(pkt.buf);
			free(pkmsg);

		}
		return true;
    }
    if(mAudioThreadState==RECORD_STATE_PAUSED)
    {
		dropQueue();
        pthread_mutex_lock(&mAudioEncMutex);
        pthread_cond_wait(&mAudioEncCond, &mAudioEncMutex);
        ALOGV("--AutAudioEncThread----change to---%d",mAudioThreadState);
        pthread_mutex_unlock(&mAudioEncMutex);
        return true;
    }

    return rt;
}


int AutAudioEnc::AudioRecStop()
{

	pthread_mutex_lock(&mAudioEncMutex);

	if (mAudioThreadState == RECORD_STATE_NULL) {
		LOGE("error state of capture thread, %s", __FUNCTION__);
		pthread_mutex_unlock(&mAudioEncMutex);
		return EINVAL;
	}

	if (mAudioThreadState == RECORD_STATE_PAUSED) {
		LOGW("capture thread has already paused");
		pthread_mutex_unlock(&mAudioEncMutex);
		return NO_ERROR;
	}

	mAudioThreadState = RECORD_STATE_PAUSED;
	pthread_cond_signal(&mAudioEncCond);

	pthread_mutex_unlock(&mAudioEncMutex);
	return NO_ERROR;
}

int AutAudioEnc::AudioRecStart()
{
	F_LOG pthread_mutex_lock(&mAudioEncMutex);

	if (mAudioThreadState == RECORD_STATE_NULL) {
		LOGE("error state of capture thread, %s", __FUNCTION__);
		pthread_mutex_unlock(&mAudioEncMutex);
		return EINVAL;
	}

	if (mAudioThreadState == RECORD_STATE_STARTED) {
		LOGW("capture thread has already started");
		pthread_mutex_unlock(&mAudioEncMutex);
		return NO_ERROR;
	}
	F_LOG
	// singal to start capture thread
	mAudioThreadState = RECORD_STATE_STARTED;
	pthread_cond_signal(&mAudioEncCond);
	pthread_mutex_unlock(&mAudioEncMutex);

	return NO_ERROR;

}
int AutAudioEnc::setAudioEncDataCb(usr_data_cb cb,void* user)
{
	usrDatCb=cb;
	mCbUserDat=user;
	return 0;
}
void AutAudioEnc::__audioenc_data_src(int32_t msgType,nsecs_t timestamp,int card,int device,
						char *dataPtr,int dsize,void* user)
{
    if(user==NULL)
    {
        LOGW("__audioenc_data_src user null");
        return ;
    }
	
	 //cmd queue
	media_msg_t *datmsg=(media_msg_t *)malloc(sizeof(media_msg_t));
	 
    if(datmsg==NULL)
    {
        LOGW("__audioenc_data_src mesg fail");
        return ;
    }
	datmsg->extradata=(char *)malloc(dsize);
	if(datmsg->extradata==NULL)
    {
        LOGW("__audioenc_data_src extradata fail");
		free(datmsg);
        return ;
    }
    memcpy(datmsg->extradata,dataPtr,dsize);//blank
    datmsg->timestamp = timestamp;
    datmsg->user=user;
    datmsg->mesg_len = dsize;
    datmsg->mesg_type = msgType;
	//ALOGV("--__audioenc_data_cb_timestamp----PUSH---%p",mesg);
	int ret = OSAL_Queue(&((AutAudioEnc*)user)->mQueueBufferAudioEnc, datmsg);
	if (ret != 0)
	{
		free(datmsg->extradata);
		free(datmsg);
		ALOGV("--__audioenc_data_src----OSAL_Queue=%p---msg=%p fail",&((AutAudioEnc*)user)->mQueueBufferAudioEnc,datmsg);
	}
	
	pthread_mutex_lock(&((AutAudioEnc*)user)->mAudioEncMutex);
	pthread_cond_signal(&((AutAudioEnc*)user)->mAudioEncCond);
	pthread_mutex_unlock(&((AutAudioEnc*)user)->mAudioEncMutex);
	return;

}


