//#include "media_video_interface.h"


#include "videoproxy.h"
#include "dbusmediavideoCommon.h"
#include "dbusmediavideoclient.h"
#include "libgdbusmediavideo.h"
#include "dbusmediavideotype.h"
#include "outputCtrl.h"


#define MEMTYPE_MEDIA_INFO 0xaa550001
#define MEMTYPE_MEDIA_STAT 0xaa550002
#define MEMTYPE_MEDIA_SUBTITILE 0xaa550003

AUTPlayerProxy::AUTPlayerProxy()
{
	cMediaVideoClientInit(this);
	cMediaVideoClientRegSingalHandl((void *)CallbackForAwPlayer);
	m_pCBGShareMemBeater_Subtitle = new CShareMem(MEMTYPE_MEDIA_SUBTITILE, sizeof(uint32_t) *3 + 1920*360*4);
	m_pCBGShareMemBeater_MediaInfo= new CShareMem(MEMTYPE_MEDIA_INFO, sizeof(uint32_t) *3 + sizeof(MediaInfo));
	m_pCBGShareMemBeater_Subtitle->createMemory();
	m_pCBGShareMemBeater_MediaInfo->createMemory();
	
	//int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_INIT, 0,0, (const char*) m_url.c_str(), (int *)&res);
}
int AUTPlayerProxy::connectSrv()
{
	int ret = cMediaVideoClientInit(this);
	cMediaVideoClientRegSingalHandl((void *)CallbackForAwPlayer);
	return ret;
}

AUTPlayerProxy::~AUTPlayerProxy(){
	m_pCBGShareMemBeater_Subtitle->destroyMemory();
	m_pCBGShareMemBeater_MediaInfo->destroyMemory();
}
int AUTPlayerProxy::setUrl(char *url){
	soutval_t res;
	m_url = url;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_SETURL, 0,0, (const char*) url, (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{
		usleep(100000);
		connectSrv();
		return -1;
	}
	
}
int AUTPlayerProxy::play(){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_PLAY, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}

}
int AUTPlayerProxy::stop(){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_STOP, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}
}
int AUTPlayerProxy::seekto(int sec){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_SEEKTO, sec,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}

}
MediaInfo * AUTPlayerProxy::getMediaInfo(){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_GETMEDIAINFO, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		if(res.val0>0)
			return (MediaInfo *)(m_pCBGShareMemBeater_MediaInfo->getShareMem()+sizeof(uint32_t) *3);
			
	}else
	{		usleep(100000);
		connectSrv();
		return NULL;
	}


}
int AUTPlayerProxy::getDuration(){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_GETDUR, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}


}
int AUTPlayerProxy::getCurrentPosition(){
	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_GETPOS, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}

}
int AUTPlayerProxy::pause()
{

	soutval_t res;
	int ret = cMediaVideoClientSetCmd( MEDIA_VIDEO_CMD_PAUSE, 0,0, (const char*) m_url.c_str(), (int *)&res);
	if(ret >= 0)
	{
		return res.val0;
	}else
	{		usleep(100000);
		connectSrv();
		return -1;
	}

}

int AUTPlayerProxy::CallbackForAwPlayer(int type,int msg,int ext1,void* pself)//(void* pUserData, int msg, int ext1, void* param)
{
	if(!pself){
		printf("AUTPlayer CallbackForAwPlayer error,pUserData=null\n");
		return -1;
	}

    AUTPlayerProxy *p=(AUTPlayerProxy*)pself;

    autCallback_func cbUser=p->cbUser;
    switch(msg)
    {
    	case AWPLAYER_MEDIA_INFO:
        {
            switch(ext1)
            {
                case AW_MEDIA_INFO_NOT_SEEKABLE:
                {
                    printf("AUTPlayer info: media source is unseekable.\n");
			        if(cbUser!=0)
			        {
			            cbUser(msg,p->datUser,0,0);
			        }
                    break;
                }
                case AW_MEDIA_INFO_RENDERING_START:
                {
                    printf("info: start to show pictures.\n");
                    break;
                }
            }
            break;
        }
		
		case SUBCTRL_SUBTITLE_AVAILABLE: //1600
			{
				printf("CBackGroundMediaVideo::autCb_func  SUBCTRL_SUBTITLE_AVAILABLE = %d================================\r\n", msg);
		
				SubtitleItem* pItem = (SubtitleItem*)(p->m_pCBGShareMemBeater_Subtitle->getShareMem()+sizeof(uint32_t) *3);
		
				if(pItem == NULL)
				{
					printf("error pItem == NULL");
					return -1;
				}
				if(pItem->bText==1)
					printf("autCb_func, text=%s\n",pItem->pText);
		
				int dataoffset = (unsigned long)p->m_pCBGShareMemBeater_Subtitle->getShareMem()+sizeof(SubtitleItem)+sizeof(uint32_t) *3;
				if(pItem->bText==0)
					{
						pItem->pBitmapData = (char *)dataoffset;
					}
				else
					{
						pItem->pText  = (char *) dataoffset;
					}
				 cbUser(msg,p->datUser,pItem,sizeof(SubtitleItem));
				 
				break;
			}
		
		default:
			if(cbUser!=0)
			{
			    cbUser(msg,p->datUser,0,0);
			}
            break;
	}
}

