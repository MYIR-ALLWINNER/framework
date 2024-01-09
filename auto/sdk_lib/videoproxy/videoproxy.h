#ifndef _VIDEO_PROSY_H_
#define  _VIDEO_PROSY_H_

#include <cdx_log.h>

#include "xplayer.h"

#include "CdxTypes.h"

#include "mediaInfo.h"
#include "CShareMem.h"

typedef int (*autCallback_func)(int32_t msgType, void *user,void*data,int len);

class AUTPlayerProxy
{
public:
    AUTPlayerProxy();
    ~AUTPlayerProxy();
    int setUrl(char *url);
    int play();
    int stop();
    int seekto(int sec);

    int pause();
	int connectSrv();
	static int CallbackForAwPlayer(int msg,int ext1,int val1,void* pUserData);
    int setUserCb(autCallback_func cb,void *dat)
    {
        cbUser=cb;
        datUser=dat;
        return 0;
    }  
	MediaInfo * getMediaInfo();
    int getDuration();
    int getCurrentPosition();
    autCallback_func cbUser;
    void *datUser;
	string m_url;
	
	CShareMem* m_pCBGShareMemBeater_Subtitle;
	
	CShareMem* m_pCBGShareMemBeater_MediaInfo;
};
#endif

