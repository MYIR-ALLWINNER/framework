#define LOG_TAG "audio_hal"

#include "audio_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#ifdef USE_ALSA_INTERFACE
#include <malloc.h>
#include <ctype.h>
#include <errno.h>
//#include <alsa/asoundlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

char* AudioCapThreadStateString[]
{
    /* Do not capture frame. */
    "AUDIO_CAP_STATE_NULL",
    "AUDIO_CAP_STATE_INIT",
    /* Do not capture frame. */
    "AUDIO_CAP_STATE_PAUSED",
    /* Start capture frame. */
    "AUDIO_CAP_STATE_STARTED",
    /* exit thread*/
    "AUDIO_CAP_STATE_EXIT",
};

//  /t7arecord -D plug:mic-dvr -r 16000 -f S16_LE -c 2 /tmp/dvr.wav
void AudioCapThread::alsa_pcm_exit(snd_pcm_t* handle, int code)
{
    ALOGW("alsa_pcm_exit\n");
    if (handle)
        snd_pcm_close(handle);
}

/*
 *  当读写音频节点出现问题时，用此函数来恢复
 */
int AudioCapThread::alsa_recovery(snd_pcm_t* handle, int err)
{
    if (err == -EPIPE)      /* under-run */
    {
        err = snd_pcm_prepare(handle);

        if (err < 0)
            ALOGW("Can't recovery from underrun, prepare failed: %s\n",
                  snd_strerror(err));
        return 0;
    }
    else if (err == -ESTRPIPE)
    {
        while ((err = snd_pcm_resume(handle)) == -EAGAIN)
            sleep(1);       /* wait until the suspend flag is released */
        if (err < 0)
        {
            err = snd_pcm_prepare(handle);
            if (err < 0)
                ALOGW("Can't recovery from suspend, prepare failed: %s\n",
                      snd_strerror(err));
        }
        return 0;
    }
    else
    {
        ALOGW("alsa_recovery snd_pcm_prepare() return %s\n", snd_strerror(err));
    }
    return err;
}

/*
 *  read function
 *  从音频节点读chunk_size大小的数据，放到以data为开始的缓存中
 *  如果能按要求填满data，则返回0,否则返回-1
 */
ssize_t AudioCapThread::alsa_pcm_read(snd_pcm_t* handle, char* data, size_t chunk_size)
{
    ssize_t r;
    size_t result = 0;
    size_t count = chunk_size;

    while (count > 0)
    {
        r = snd_pcm_readi(handle, data, count);
        if (r == -EAGAIN || (r >= 0 && (size_t)r < count))   //haven't finish or r is in normal zone
        {
            snd_pcm_wait(handle, 100);
        }
        else if (r < 0)
        {
            ALOGW(("alsa_pcm_read error: %s\n"), snd_strerror(r));
            alsa_recovery(handle, r);
            break;
        }
        if (r > 0)
        {
            result += r;
            count -= r;
            data += r * mAlsaBitsPerFrame / 8;
        }
    }

    if (result == chunk_size)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void AudioCapThread::alsa_initHwParams(snd_pcm_t* handle, snd_pcm_hw_params_t* params, InputHWparams* pInputParam)
{
    int err = snd_pcm_hw_params_any(handle, params);
    if (err < 0)
    {
        ALOGW("Broken configuration for this PCM: no configurations available\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }

    err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED); //SND_PCM_ACCESS_RW_NONINTERLEAVED
    if (err < 0)
    {
        ALOGW("Access type not available\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }

    err = snd_pcm_hw_params_set_format(handle, params, pInputParam->format);
    if (err < 0)
    {
        ALOGW("Sample format non available\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }

    err = snd_pcm_hw_params_set_channels(handle, params, pInputParam->channels);
    if (err < 0)
    {
        ALOGW("Channels count non available\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }

    err = snd_pcm_hw_params_set_rate_near(handle, params, &pInputParam->rate, 0);
    if (err < 0)
    {
        ALOGW("snd_pcm_hw_params_set_rate_near error\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }

    err = snd_pcm_hw_params(handle, params);   //start to set hardware acturly
    if (err < 0)
    {
        ALOGW("Unable to install hw params:\n");
        alsa_pcm_exit(handle, EXIT_FAILURE);
    }
    return ;
}

bool AudioCapThread::alsa_audio_init(char* pcm_name,    unsigned int ch, unsigned int rate)
//bool AudioCapThread::alsa_audio_init(void)
{
    //char *pcm_name = "plug:mic-dvr";      //argv[1];  ////pcm_name="plug:mic-dvr";
    //char *SaveFilePath = "/tmp/dvr.wav";  //argv[2];
    int err;
    int i;

    InputHWparams paramIn;
    paramIn.channels = ch;
    paramIn.format = SND_PCM_FORMAT_S16_LE;
    paramIn.rate = rate;

    err = snd_pcm_open(&mAlsaPcmHandle, pcm_name, SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0)
    {
        ALOGW("snd_pcm_open error: %s", snd_strerror(err));
        return false;
    }

    /* setup sound hardware */
    snd_pcm_hw_params_alloca(&gAlsaHWparams);  //how to release it???
    alsa_initHwParams(mAlsaPcmHandle, gAlsaHWparams, &paramIn); //init hardware param

    //snd_pcm_hw_params_get_period_size(gAlsaHWparams, &mAlsaChunkSize, 0);
    mAlsaChunkSize = 1024;
    size_t gBitsPerSample = snd_pcm_format_physical_width(paramIn.format);
    mAlsaBitsPerFrame = gBitsPerSample * paramIn.channels;

    buf_size = mAlsaChunkSize * mAlsaBitsPerFrame / 8;
    //ALOGV("buf_size=%d",buf_size);

    buffer = (char*)malloc(buf_size);
    if (!buffer)
    {
        fprintf(stderr, "Unable to allocate %d bytes\n", buf_size);
        free(buffer);
        alsa_pcm_exit(mAlsaPcmHandle, EXIT_FAILURE);
        return false;
    }

    buffer_zero = (char*)malloc(buf_size);
    if (!buffer_zero)
    {
        ALOGW("  buffer_zero fail size =%d==-----------", buf_size);
    }
    else
    {
        memset(buffer_zero, 0, buf_size);
    }
    return true;
}

bool AudioCapThread::alsa_audio_cap(void)
{
    return alsa_pcm_read(mAlsaPcmHandle, buffer, mAlsaChunkSize);
}

bool AudioCapThread::alsa_audio_free(void)
{
    // if(gAlsaHWparams){
    //     snd_pcm_hw_params_free(gAlsaHWparams);
    // }
    if (mAlsaPcmHandle)
        snd_pcm_close(mAlsaPcmHandle);
    mAlsaPcmHandle = NULL;
    snd_config_update_free_global();
    return true;
}
//---------------------alsa interface end--------------------------------------

#endif


#ifdef USE_TINYALSA_INTERFACE

bool AudioCapThread::tinyalsa_audio_init()
{
    unsigned int card = 3;
    unsigned int device = 0;
    unsigned int channels = 2;
    unsigned int rate = 48000;
#ifdef USE_AHUB_CAP
    unsigned int ahub_card = 1;
    unsigned int ahub_device = 0;
#endif
    //unsigned int bits = 16;
    unsigned int period_size = 256;
    unsigned int period_count = 4;
    enum pcm_format format;

    format = PCM_FORMAT_S16_LE;

    //format = PCM_FORMAT_S32_LE;
    config.channels = channels;
    config.rate = rate;
    config.period_size = period_size;
    config.period_count = period_count;
    config.format = format;
    config.start_threshold = 0;
    config.stop_threshold = 0;
    config.silence_threshold = 0;


    pcm = pcm_open(card, device, PCM_IN, &config);
    if (!pcm || !pcm_is_ready(pcm))
    {
        fprintf(stderr, "Unable to open PCM device (%s)\n",
                pcm_get_error(pcm));
        return false;
    }

#ifdef USE_AHUB_CAP
    pcm_start(pcm);
    ahub_pcm = pcm_open(ahub_card, ahub_device, PCM_IN, &config);
    int ret = pcm_is_ready(ahub_pcm);
    if (!ahub_pcm || !ret)
    {
        fprintf(stderr, "Unable to open AHub device %d (%s)\n",
                ahub_device, pcm_get_error(ahub_pcm));
        pcm_close(pcm);
        return false;
    }
    buf_size = pcm_frames_to_bytes(ahub_pcm, pcm_get_buffer_size(ahub_pcm));
    ALOGV("buf_size=%d", buf_size);
    buffer = (char*)malloc(buf_size);
    if (!buffer)
    {
        fprintf(stderr, "Unable to allocate %d bytes\n", buf_size);
        free(buffer);
        pcm_close(ahub_pcm);
        pcm_close(pcm);
        return false;
    }
#else
    buf_size = pcm_frames_to_bytes(pcm, pcm_get_buffer_size(pcm));
    ALOGV("buf_size=%d", buf_size);
    buffer = (char*)malloc(buf_size);

    if (!buffer)
    {
        fprintf(stderr, "Unable to allocate %d bytes\n", buf_size);
        free(buffer);
        pcm_close(pcm);
        return false;
    }
#endif


    buffer_zero = (char*)malloc(buf_size);
    if (!buffer_zero)
    {
        ALOGW("  buffer_zero fail size =%d==-----------", buf_size);
    }
    else
    {
        memset(buffer_zero, 0, buf_size);
    }
    return true;
}

bool AudioCapThread::tinyalsa_audio_cap()
{
#ifdef USE_AHUB_CAP
    if ((NULL != ahub_pcm) && (NULL != buffer))
        return pcm_read(ahub_pcm, buffer, buf_size);
#else
    if ((NULL != pcm) && (NULL != buffer))
        return pcm_read(pcm, buffer, buf_size);
#endif
}

bool AudioCapThread::tinyalsa_audio_free()
{
#ifdef USE_AHUB_CAP
    if (ahub_pcm)
    {
        pcm_close(ahub_pcm);
        ahub_pcm = NULL;
    }
#endif

    if (pcm)
    {
        pcm_close(pcm);
        pcm = NULL;
    }
    return 0;
}
#endif
AudioCapThread::AudioCapThread(int device, int card)
    : Thread(false), mRequestExit(false)
{
    mNewCbCnt = 0;
    refCnt = 0;
#ifdef USE_TINYALSA_INTERFACE
#ifdef USE_AHUB_CAP
    ahub_pcm = NULL;;
#endif
    pcm = NULL;;
#endif
    buffer = NULL;;
    buffer_zero = NULL;
    mCurFrameTimestamp = 0;
    int i;
    for (i = 0; i < MAX_AUDIO_DATA_CB_NUM; i++)
    {
        AudioSrc[i].mDataCb = 0;
        AudioSrc[i].mUsrDat = 0;
        AudioSrc[i].cbStat = AUDIO_SINK_STAT_CLOSE;
        AudioSrc[i].isUsed = 0;
    }
    pthread_mutex_init(&mAudioCapMutex, NULL);
    pthread_cond_init(&mAudioCapCond, NULL);
    mAudioCapThreadState = AUDIO_CAP_STATE_NULL;
    startThread();
}

AudioCapThread::AudioCapThread()
    : Thread(false), mRequestExit(false)
{
    mNewCbCnt = 0;
    refCnt = 0;
#ifdef USE_TINYALSA_INTERFACE
#ifdef USE_AHUB_CAP
    ahub_pcm = NULL;;
#endif
    pcm = NULL;;
#endif
    buffer = NULL;;
    buffer_zero = NULL;

    int i;
    for (i = 0; i < MAX_AUDIO_DATA_CB_NUM; i++)
    {
        AudioSrc[i].mDataCb = 0;
        AudioSrc[i].mUsrDat = 0;
        AudioSrc[i].cbStat = AUDIO_SINK_STAT_CLOSE;
        AudioSrc[i].isUsed = 0;
    }
    pthread_mutex_init(&mAudioCapMutex, NULL);
    pthread_cond_init(&mAudioCapCond, NULL);
    mAudioCapThreadState = AUDIO_CAP_STATE_NULL;
    startThread();
}

int AudioCapThread::reqAudioSource(audiodata_callback cb, void* UsrDat)
{
    int i;
    if (mNewCbCnt + 1 >= MAX_AUDIO_DATA_CB_NUM)
    {
        ALOGE("%s mNewCbCnt MAX", __FUNCTION__);
        return -1;
    }

    if (cb == NULL)
    {
        ALOGE("%s cb NULL", __FUNCTION__);
        return -1;
    }

    for (i = 0; i < MAX_AUDIO_DATA_CB_NUM; i++)
    {
        ALOGV("reqAudioSource idx=%d isuded=%d", i, AudioSrc[i].isUsed);
        if (AudioSrc[i].isUsed == 0)
        {
            AudioSrc[i].mDataCb = cb;
            AudioSrc[i].mUsrDat = UsrDat;
            AudioSrc[i].cbStat = AUDIO_SINK_STAT_CLOSE;
            AudioSrc[i].isUsed = 1;

            mNewCbCnt++;
            break;
        }
    }
    if (MAX_AUDIO_DATA_CB_NUM == i)
        return -1;

    return i;
}
int AudioCapThread::releaseAudioSource(int hdl)
{
    if (hdl + 1 >= MAX_AUDIO_DATA_CB_NUM)
        return -1;

    if (AudioSrc[hdl].isUsed == 1)
    {
        AudioSrc[hdl].isUsed = 0;
        AudioSrc[hdl].mDataCb = 0;
        AudioSrc[hdl].mUsrDat = 0;
        AudioSrc[hdl].cbStat = AUDIO_SINK_STAT_CLOSE;
        mNewCbCnt--;
    }
    return 0;
}


int AudioCapThread::startCapture(int hdl)
{
    F_LOG;
    ALOGV("audio startCapture hdl=%d", hdl);
    if (hdl >= MAX_AUDIO_DATA_CB_NUM)
    {
        ALOGE("hdl=%d>MAX_AUDIO_DATA_CB_NUM", hdl);
        return -1;
    }
    if (AudioSrc[hdl].mDataCb == NULL)
    {
        ALOGE("hdl=%d mDataCb NULL", hdl);
        return -1;
    }

    if (mAudioCapThreadState == AUDIO_CAP_STATE_NULL)
    {
        ALOGE("hdl=%d mAudioCapThreadState NULL", hdl);
        return -1;
    }
    //default is open
    //but if setcapturestat other mode etc.AUDIO_SINK_STAT_OPEN_mute before this function ,
    //we psuh zero data to audio endode queue
    if (AudioSrc[hdl].cbStat == AUDIO_SINK_STAT_CLOSE)
        AudioSrc[hdl].cbStat = AUDIO_SINK_STAT_OPEN;
    else
        ALOGW("now audio cap mode =%d", AudioSrc[hdl].cbStat);
    refCnt++;

    if ((mAudioCapThreadState == AUDIO_CAP_STATE_INIT) || (mAudioCapThreadState == AUDIO_CAP_STATE_PAUSED))
    {
        pthread_mutex_lock(&mAudioCapMutex);
        mAudioCapThreadState = AUDIO_CAP_STATE_STARTED;
        mCurFrameTimestamp = (int64_t)systemTime();
        // singal to start capture thread
        pthread_cond_signal(&mAudioCapCond);
        pthread_mutex_unlock(&mAudioCapMutex);
    }

    return 0;

}
int AudioCapThread::stopCapture(int hdl)
{
    F_LOG;
    if (hdl >= MAX_AUDIO_DATA_CB_NUM)
    {
        ALOGE("stopCapture over MAX hdl=%d ", hdl);
        return -1;
    }
    refCnt--;
    AudioSrc[hdl].cbStat = AUDIO_SINK_STAT_CLOSE;
    if (refCnt <= 0)
    {
        if (mAudioCapThreadState == AUDIO_CAP_STATE_STARTED)
        {
            pthread_mutex_lock(&mAudioCapMutex);
            mAudioCapThreadState = AUDIO_CAP_STATE_PAUSED;
            // singal to start capture thread
            pthread_mutex_unlock(&mAudioCapMutex);
        }
    }
    return 0;
}

int AudioCapThread::stopAudio()
{
    if ((mAudioCapThreadState == AUDIO_CAP_STATE_PAUSED) || (mAudioCapThreadState == AUDIO_CAP_STATE_INIT))
    {
        pthread_mutex_lock(&mAudioCapMutex);
        mAudioCapThreadState = AUDIO_CAP_STATE_EXIT;
        // singal to start capture thread
        pthread_cond_signal(&mAudioCapCond);
        pthread_mutex_unlock(&mAudioCapMutex);
        //stopThread();
    }
    return 0;
#if 0
    //for force quit condition
    if (mAudioCapThreadState == AUDIO_CAP_STATE_STARTED)
    {
        stopThread();

        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }

        if (buffer_zero)
        {
            free(buffer_zero);
            buffer_zero = NULL;
        }

#ifdef USE_TINYALSA_INTERFACE
        tinyalsa_audio_free();
#endif

#ifdef USE_ALSA_INTERFACE
        alsa_audio_free();
#endif
    }
#endif
}

int  AudioCapThread::setCaptureStat(int hdl, int stat)
{
    F_LOG;
    ALOGV("audio startCapture hdl=%d", hdl);
    if (hdl >= MAX_AUDIO_DATA_CB_NUM)
    {
        ALOGE("hdl=%d>MAX_AUDIO_DATA_CB_NUM", hdl);
        return -1;
    }

    if (stat > AUDIO_SINK_STAT_OPEN_MUTE)
    {
        ALOGE("stat=%d>AUDIO_SINK_STAT_OPEN_MUTE stat=%d", hdl, stat);
        return -1;
    }

    if (AudioSrc[hdl].mDataCb == NULL)
    {
        ALOGE("hdl=%d mDataCb NULL", hdl);
        return -1;
    }

    if (mAudioCapThreadState == AUDIO_CAP_STATE_NULL)
    {
        ALOGE("hdl=%d mAudioCapThreadState NULL", hdl);
        return -1;
    }

    AudioSrc[hdl].cbStat = stat;
    return 0;
}


bool AudioCapThread::AutAudioCapThread()
{
    bool ret = true;
    //null state
    if (mAudioCapThreadState == AUDIO_CAP_STATE_NULL)
    {
#ifdef USE_ALSA_INTERFACE
        ret = alsa_audio_init("plug:mic-dvr", 2, 44100);
#else
        ret = tinyalsa_audio_init();
#endif

        if (false == ret)
        {
            ALOGE("  audio_init failed!");
            return ret;
        }
        ALOGW("  mAudioCapThreadState==AUDIO_CAP_STATE_INIT-----------");
        mAudioCapThreadState = AUDIO_CAP_STATE_INIT;
        pthread_mutex_lock(&mAudioCapMutex);
        pthread_cond_wait(&mAudioCapCond, &mAudioCapMutex);
        pthread_mutex_unlock(&mAudioCapMutex);

        //ALOGW("  mAudioCapThreadState==AUDIO_CAP_STATE_INIT----change =%s-------",AudioCapThreadStateString[mAudioCapThreadState]);
        //mAudioCapThreadState=AUDIO_CAP_STATE_INIT;
        return true;
    }

    if (mAudioCapThreadState == AUDIO_CAP_STATE_STARTED)
    {
        //start state
        //ALOGE("mAudioCapThreadState==AUDIO_CAP_STATE_STARTED-------%p-ize=%d---",buffer,buf_size);
        int read_ret;
#ifdef USE_ALSA_INTERFACE
        read_ret = alsa_audio_cap();
#else
        read_ret = tinyalsa_audio_cap();
#endif
        if (!read_ret)
        {
            //ALOGV("pcm_read ok---%p----%d---%x %x %x-",buffer,buf_size,buffer[0],buffer[10],buffer[20]);
            int i;
            for (i = 0; i < MAX_AUDIO_DATA_CB_NUM; i++)
            {
                if ((AudioSrc[i].isUsed == 1) && (AudioSrc[i].cbStat == AUDIO_SINK_STAT_OPEN) && (AudioSrc[i].mDataCb != NULL))
                {
                    int64_t curtime = (int64_t)systemTime();
                    int64_t nowpts = curtime;
                    mCurFrameTimestamp = (int64_t)systemTime();
                    AudioSrc[i].mDataCb(1, nowpts, 0, 0,
                                        buffer, buf_size,
                                        (void* )AudioSrc[i].mUsrDat);
                }
                if ((AudioSrc[i].isUsed == 1) && (AudioSrc[i].cbStat == AUDIO_SINK_STAT_OPEN_MUTE) && (AudioSrc[i].mDataCb != NULL))
                {
                    int64_t curtime = (int64_t)systemTime();
                    int64_t nowpts = curtime;
                    mCurFrameTimestamp = (int64_t)systemTime();
                    AudioSrc[i].mDataCb(1, nowpts, 0, 0,
                                        buffer_zero, buf_size,
                                        (void* )AudioSrc[i].mUsrDat);
                }
            }
            bytes_read += buf_size;
        }
        else
        {
            ALOGE("read pcm fail---%d(%s)--------", errno, strerror(errno));
            usleep(22000);
            int i;
            for (i = 0; i < MAX_AUDIO_DATA_CB_NUM; i++)
            {
                if ((AudioSrc[i].isUsed == 1) && (AudioSrc[i].cbStat == AUDIO_SINK_STAT_OPEN_MUTE) && (AudioSrc[i].mDataCb != NULL))
                {
                    int64_t curtime = (int64_t)systemTime();
                    int64_t nowpts = curtime;
                    mCurFrameTimestamp = (int64_t)systemTime();
                    AudioSrc[i].mDataCb(1, nowpts, 0, 0,
                                        buffer_zero, buf_size,
                                        (void* )AudioSrc[i].mUsrDat);
                }
            }
        }
    }
    //stop state

    if (mAudioCapThreadState == AUDIO_CAP_STATE_PAUSED)
    {

        ALOGE("  mAudioCapThreadState==AUDIO_CAP_STATE_PAUSED-----------");
        pthread_mutex_lock(&mAudioCapMutex);
        pthread_cond_wait(&mAudioCapCond, &mAudioCapMutex);
        pthread_mutex_unlock(&mAudioCapMutex);

        //ALOGW("  mAudioCapThreadState==AUDIO_CAP_STATE_PAUSED----change =%s-------",AudioCapThreadStateString[mAudioCapThreadState]);
        return true;
    }

    if (mAudioCapThreadState == AUDIO_CAP_STATE_EXIT)
    {
        ALOGE("  mAudioCapThreadState==AUDIO_CAP_STATE_EXIT-----------");
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }
        if (buffer_zero)
        {
            free(buffer_zero);
            buffer_zero = NULL;
        }

#ifdef USE_TINYALSA_INTERFACE
        tinyalsa_audio_free();
#endif

#ifdef USE_ALSA_INTERFACE
        alsa_audio_free();
#endif
        stopThread();

    }
    return true;

}


