#ifndef _AUTPLAYER_H_
#define _AUTPLAYER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <linux/videodev2.h>
#ifndef CDX_V27
#include "cdx_config.h"
#include "log.h"
#include "awplayer.h"
#else
#include "cdx_config.h"
#include <cdx_log.h>
#include "xplayer.h"

#endif

#include "CdxTypes.h"

#include "hwdisp2.h"

#include "mediaInfo.h"
using namespace android;
static const int STATUS_STOPPED   = 0;
static const int STATUS_PREPARING = 1;
static const int STATUS_PREPARED  = 2;
static const int STATUS_PLAYING   = 3;
static const int STATUS_PAUSED    = 4;
static const int STATUS_SEEKING   = 5;

struct size
{
    int width;
    int height;
};
typedef struct AUTPlayerContext
{
#ifndef CDX_V27

    AwPlayer*       mAwPlayer;
#else
    XPlayer*       mAwPlayer;
#endif
    int             mPreStatus;
    int             mStatus;
    int             mSeekable;
    int             mError;
    pthread_mutex_t mMutex;
    int             mVideoFrameNum;
    char *disp_vaddr;
    int disp_paddr;
    int disp_memlen;
} AUTPlayerContext;


//* define commands for user control.
typedef struct Command
{
    const char* strCommand;
    int         nCommandId;
    const char* strHelpMsg;
} Command;



#define COMMAND_HELP            0x1     //* show help message.
#define COMMAND_QUIT            0x2     //* quit this program.

#define COMMAND_SET_SOURCE      0x101   //* set url of media file.
#define COMMAND_PLAY            0x102   //* start playback.
#define COMMAND_PAUSE           0x103   //* pause the playback.
#define COMMAND_STOP            0x104   //* stop the playback.
#define COMMAND_SEEKTO          0x105   //* seek to posion, in unit of second.
#define COMMAND_SHOW_MEDIAINFO  0x106   //* show media information.
#define COMMAND_SHOW_DURATION   0x107   //* show media duration, in unit of second.
#define COMMAND_SHOW_POSITION   0x108   //* show current play position, in unit of second.
#define COMMAND_SWITCH_AUDIO    0x109   //* switch autio track.

typedef int (*autCallback_func)(int32_t msgType, void *user,void*data,int len);
#define MEDIA_TYPE_AUDIO 1
#define MEDIA_TYPE_VIDEO 2

class AUTPlayer
{
public:
    AUTPlayer();
	AUTPlayer(int srates,int chnum);
	AUTPlayer(int srates,int chnum,char * snd_devname);
    ~AUTPlayer();
    int setUrl(char *url);
	int setsubtitleUrl(char *suburl);
	int setsubtitleUrlFd(char *suburl,char *idxurl);
	
	int switchSubtitle(int index);  //begin with 1,not 0
	int switchAudio(int index);
	
    int play();
    int stop();
	int setSpeed(int nSpeed);
    int seekto(int sec);
    MediaInfo * getMediaInfo();
    int getDuration();
    int getCurrentPosition();
    int pause();
    int setViewWindow(int x,int y,int w,int h);//user view win size on screen if not call use lcd full scn
    int setVideoSrcCrop(int x,int y,int w,int h); //orginal Video disp crop size if not call use video default
    int  getCurBuffInfo(int *with,int*height,unsigned int* vir_y );
    int  getDispwidth();
    int  getDispheigth();
	int setVolume(int, int);
	int getVolume(int*, int*);
	int  setWindowZorder(int z);
    int setUserCb(autCallback_func cb,void *dat)
    {

        cbUser=cb;
        datUser=dat;
        return 0;
    }    

    void initSoundControlOpsT();
    static int CallbackForAwPlayer(void* pUserData, int msg, int param0, void* param1);

    AUTPlayerContext mPlayer;
    struct size input_size;
    HwDisplay* mcd;
	SoundCtrl* sound;
    int layer;
    autCallback_func cbUser;
    void *datUser;
    struct view_info vv;
    struct view_info src_crop;
    struct ScMemOpsS* dispmemops;
    int mMediaType;
	int mSampRates;
	int mAudioChNum;
	int mAlsaFormat;
	char mSndDevName[64];//  for "default" or for "plug:dmix" or others
};

#ifdef __cplusplus
}
#endif

#endif

