#ifndef TINA_SOUND_CONTROL_H
#define TINA_SOUND_CONTROL_H

#include <alsa/asoundlib.h>
#include <soundControl.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum SoundStatus_t
{
    STATUS_START = 0,
    STATUS_PAUSE ,
    STATUS_STOP
}SoundStatus;
typedef int (*autCallback_func)(int32_t msgType, void *user,void*data,int len);

//IMPORTANT:do not modify this sequence,unless you want to change the stream priorities.
typedef enum audio_stream_type_t
{
    STREAM_BTCALL = 0,
    STREAM_NAVI,
    STREAM_SYSTEM,
    STREAM_MUSIC,
    STREAM_BTMUSIC,
    STREAM_DEFAULT,
    STREAM_MAX
}audio_stream_type;

typedef enum stream_control_t
{
    ST_NULL = -1,
    ST_NONE = 0,
    ST_MUTE ,
    ST_DECREASE,
    ST_PAUSE,
}stream_control;

typedef struct vol_ctl_shm_t{
    audio_stream_type type[STREAM_MAX];
    int isplaying;
}vol_ctl_shm;

typedef struct SoundCtrlContext_t
{
    SoundCtrl                   base;
    snd_pcm_uframes_t           chunk_size;
    snd_pcm_format_t            alsa_format;
    snd_pcm_hw_params_t         *alsa_hwparams;
    snd_pcm_t                   *alsa_handler;
    struct mixer             *mixer;
    struct mixer_ctl           *ctl[STREAM_MAX];
    vol_ctl_shm           *p_map;
    int             shmid;
    snd_pcm_access_t            alsa_access_type;
    snd_pcm_stream_t            alsa_open_mode;
    unsigned int                nSampleRate;
    unsigned int                nChannelNum;
    int                         alsa_fragcount;
    int                         alsa_can_pause;
    size_t                      bytes_per_sample;
    SoundStatus                 sound_status;
    int                         mVolume;
    int                  vol_left;
    int                  vol_right;
    audio_stream_type      stream_type;
    stream_control        control_type;
    pthread_mutex_t             mutex;
	autCallback_func *msndCallback;
	void ** msndCallbackDat;
	char mSoundDevName[64];
}SoundCtrlContext;

typedef struct pcm_hw_params_t
{
    unsigned int samplerate;
    unsigned int channels;
    int format;
} pcm_hw_params;

//SoundCtrl* TinaSoundDeviceInit(int srates,int chnum,int alsa_format,char *devname);
SoundCtrl* TinaSoundDeviceInit(audio_stream_type type);
void TinaSoundDeviceDestroy(SoundCtrl* s);

void TinaSoundDeviceSetFormat(SoundCtrl* s,CdxPlaybkCfg* cfg);

int TinaSoundDeviceStart(SoundCtrl* s);

int TinaSoundDeviceStop(SoundCtrl* s);

int TinaSoundDevicePause(SoundCtrl* s);

int TinaSoundDeviceWrite(SoundCtrl* s, void* pData, int nDataSize);

int TinaSoundDeviceReset(SoundCtrl* s);

int TinaSoundDeviceGetCachedTime(SoundCtrl* s);
int TinaSoundDeviceGetFrameCount(SoundCtrl* s);
int TinaSoundDeviceSetPlaybackRate(SoundCtrl* s,const XAudioPlaybackRate *rate);

int TinaSoundDeviceControl(SoundCtrl* s, int cmd, void* para);

void TinaSoundDeviceSetVol(SoundCtrl* s, int left, int right);
void TinaSoundDeviceGetVol(SoundCtrl* s, int *left, int *right);

int TinaSoundDeviceSetCallback(SoundCtrl* s, void *callback, void **pUserData);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
