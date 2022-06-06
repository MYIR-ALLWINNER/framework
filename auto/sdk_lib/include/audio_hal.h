#ifndef __AUDIO_HAL_H__
#define __AUDIO_HAL_H__
#include <ui/Rect.h>
#include <fcntl.h>
#include <utils/Thread.h>

#include<sys/stat.h>
#include "sdklog.h"

#define USE_TINYALSA_INTERFACE
//#define USE_ALSA_INTERFACE

#define USE_AHUB_CAP 1

#define F_LOG ALOGV("%s, line: %d", __FUNCTION__, __LINE__);

#ifdef  USE_TINYALSA_INTERFACE
#include "tinyalsasoundlib.h"
#endif

#ifdef USE_ALSA_INTERFACE
#include "alsa/asoundlib.h"
//#include "aconfig.h"
//#include "formats.h"
typedef struct _InputHWparams{
	snd_pcm_format_t format;
	unsigned int channels;
	unsigned int rate;
}InputHWparams;
#endif
using namespace android;
typedef void (*audiodata_callback)(int32_t msgType,nsecs_t timestamp,int card,int device,
                                   char *dataPtr,int dsize,
                                   void* user);
enum AudioCapThreadState
{
    /* Do not capture frame. */
    AUDIO_CAP_STATE_NULL =0,
    AUDIO_CAP_STATE_INIT,
    /* Do not capture frame. */
    AUDIO_CAP_STATE_PAUSED,
    /* Start capture frame. */
    AUDIO_CAP_STATE_STARTED,
    /* exit thread*/
    AUDIO_CAP_STATE_EXIT,
};



#define MAX_AUDIO_DATA_CB_NUM 4
#define AUDIO_SINK_STAT_OPEN 1
#define AUDIO_SINK_STAT_OPEN_MUTE 2

#define AUDIO_SINK_STAT_CLOSE 0
typedef struct AudioSouce
{
    audiodata_callback mDataCb;
    void *mUsrDat;
    int cbStat;
    int isUsed;

} AudioSouce_t;

class AudioCapThread : public Thread
{
    AudioSouce_t AudioSrc[MAX_AUDIO_DATA_CB_NUM];
    int mNewCbCnt;
    int64_t mCurFrameTimestamp;

    int refCnt;
    bool mRequestExit;

public:

    AudioCapThread(int device,int card);
    

    AudioCapThread();
     
    ~AudioCapThread()
    {
		stopThread();
    }
    void stopThread()
    {
        mRequestExit = true;
    }

    void startThread()
    {
        run("AudioCapThread", PRIORITY_URGENT_DISPLAY);
    }
    bool AutAudioCapThread();
    int reqAudioSource(audiodata_callback cb,void *UsrDat);
    int releaseAudioSource(int hdl);
    #ifdef USE_TINYALSA_INTERFACE
	#ifdef USE_AHUB_CAP
	struct pcm *ahub_pcm;
	#endif
    struct pcm *pcm;
    struct pcm_config config;
    #endif
    char *buffer;
    char *buffer_zero;


    unsigned int buf_size;
    unsigned int bytes_read ;

    virtual bool threadLoop()
    {
        if (mRequestExit)
        {
            return false;
        }

        return AutAudioCapThread();
    }
    int setCaptureStat(int hdl,int stat);
    

    int startCapture(int hdl);
    

    int stopCapture(int hdl);
    
    int stopAudio();
    
private:
    enum AudioCapThreadState mAudioCapThreadState;

    pthread_mutex_t 				mAudioCapMutex;
    pthread_cond_t					mAudioCapCond;
    
    
    #ifdef USE_TINYALSA_INTERFACE
    bool tinyalsa_audio_init();
    bool tinyalsa_audio_cap();
    bool tinyalsa_audio_free();    
    #endif
    
    #ifdef USE_ALSA_INTERFACE
    snd_pcm_t *mAlsaPcmHandle;
    snd_pcm_hw_params_t *gAlsaHWparams; //pcm hardware
    snd_pcm_uframes_t mAlsaChunkSize;
    size_t mAlsaBitsPerFrame;
    
    void alsa_pcm_exit(snd_pcm_t *handle,int code);
    int alsa_recovery(snd_pcm_t *handle, int err);
    ssize_t alsa_pcm_read(snd_pcm_t *handle, char *data, size_t chunk_size);
    void alsa_initHwParams(snd_pcm_t *handle, snd_pcm_hw_params_t *params,InputHWparams *pInputParam);
    bool alsa_audio_init(char *pcm_name, unsigned int ch,unsigned int rate);
    bool alsa_audio_cap(void);
    bool alsa_audio_free(void);
    #endif
};
#endif
