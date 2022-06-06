#ifdef BGVIDEO_SER

#include "background_video_player.h"
#include "AutPlayer.h"
#include "media_video_interface.h"
#define AUDIO_PCM_OUTPUT 128


#include "dbusmediavideoserver.h"
#include "dbusmediavideoCommon.h"
#include "dbusmediavideotype.h"
#define		BG_MEDIAMP3_TIME_INFO_TIMER	500
#define		BG_MEDIAMP3_CONTROL_CHECK_TIMER	20
#define		BG_MEDIAVIDEO_STATUS_TIMER	50

#define MEMTYPE_MEDIA_INFO 0xaa550001
#define MEMTYPE_MEDIA_STAT 0xaa550002
#define MEMTYPE_MEDIA_SUBTITILE 0xaa550003
#if 1
uint8_t			CBackGroundMediaVideo::m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
uint8_t			CBackGroundMediaVideo::m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
CShareMem* CBackGroundMediaVideo::m_pCBGShareMemBeater_Subtitle = new CShareMem(MEMTYPE_MEDIA_SUBTITILE, sizeof(uint32_t) *3 + 1920*360*4);

CShareMem* CBackGroundMediaVideo::m_pCBGShareMemBeater_MediaInfo= new CShareMem(MEMTYPE_MEDIA_INFO, sizeof(uint32_t) *3 + sizeof(MediaInfo));
CBackGroundMediaVideo::CBackGroundMediaVideo()
{
	//m_pActivePlayer = new AUTPlayer(44100,2,"plug:audio_media");
	m_pActivePlayer = NULL;
	m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
	m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
	m_nPlayFailTimes = 0;

	m_pCBGShareMemBeater_Subtitle->createMemory();
	m_pCBGShareMemBeater_MediaInfo->createMemory();

}


CBackGroundMediaVideo::~CBackGroundMediaVideo()
{
	if (NULL != m_pActivePlayer)
	{
		delete m_pActivePlayer;
		m_pActivePlayer = NULL;
	}
}

bool		CBackGroundMediaVideo::startPlay(const string& strUrl, bool bHide)
{
	int32_t iRet = -1;

	//if ((m_iAutPlayerStatus == VIDEO_STATUS_PAUSED) || (m_iAutPlayerStatus == VIDEO_STATUS_PLAYING) || (m_iAutPlayerStatus == VIDEO_STATUS_SEEKING))
	{
		if(m_pActivePlayer!=NULL)
		{
			m_pActivePlayer->stop();
		}
		m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
	}

	if(m_pActivePlayer!=NULL)
	{
		delete m_pActivePlayer;
		m_pActivePlayer = NULL;
	}

	m_pActivePlayer = new AUTPlayer();//44100,2,"plug:audio_media");
	if(m_pActivePlayer == NULL)
	{
		printf("new AutPlayer error");
		iRet = -1;
	}
	else
	{
		iRet = 0;
	}
	
	if (iRet >= 0)
		{
			iRet = m_pActivePlayer->setUserCb(autCb_func, this);
			if (iRet < 0)
			{
				printf("\n\n\n\nm_pActivePlayer->setUserCb() =====failed======%d\n\n\n\n", iRet);
				iRet = -1;
			}
		}

	if (iRet >= 0)
	{
		iRet = m_pActivePlayer->setUrl((char*)strUrl.c_str());
		if (iRet < 0)
		{
			printf("\n\n\n\nm_pActivePlayer->setUrl() =====failed======%d, strUrl=%s\n\n\n\n", iRet, strUrl.c_str());
			iRet = -1;
		}
		else
		{
			printf("\n\n\n\nm_pActivePlayer->setUrl() =====success======%d, strUrl=%s\n\n\n\n", iRet, strUrl.c_str());
		}
	}

	
	if (iRet >= 0)
	{
		int32_t iSubtiletRet = addSubtitleFile((void*)m_pActivePlayer, strUrl);
		printf("iSubtiletRet ret : %d====================================\n", iSubtiletRet);

		if (true == bHide)
		{
			iRet = m_pActivePlayer->setViewWindow(800, 0, AVNCL_VIDEO_WIDTH, AVNCL_VIDEO_HIGHTH); 
		} 
		else
		{
			iRet = m_pActivePlayer->setViewWindow(0, 0, AVNCL_VIDEO_WIDTH, AVNCL_VIDEO_HIGHTH); 
		}
		if (iRet < 0)
		{
			printf("\n\n\n\npVideoFilter->play() =====failed======%d\n\n\n\n", iRet);
			iRet = -1;
		}
	}

	if (iRet >= 0)
	{
		iRet = m_pActivePlayer->play();
		if (iRet < 0)
		{
			printf("\n\n\n\nm_pActivePlayer->play() =====failed======%d\n\n\n\n", iRet);
			iRet = -1;
		}
	}

	if (iRet >= 0)
	{
		m_iAutPlayerStatus = VIDEO_STATUS_PLAYING;
		m_iAutPlayerLastStatus = VIDEO_STATUS_PLAYING;
		m_nPlayFailTimes = 0;
	} 
	else
	{
		m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
		m_nPlayFailTimes++;

		return false;
	}
	return true;
}

#if 1
bool		CBackGroundMediaVideo::setUrl(const string& strUrl)
{
	int32_t iRet = -1;

	//if ((m_iAutPlayerStatus == VIDEO_STATUS_PAUSED) || (m_iAutPlayerStatus == VIDEO_STATUS_PLAYING) || (m_iAutPlayerStatus == VIDEO_STATUS_SEEKING))
	{
		if(m_pActivePlayer!=NULL)
		{
			m_pActivePlayer->stop();
		}
		m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
	}

	if(m_pActivePlayer!=NULL)
	{
		delete m_pActivePlayer;
		m_pActivePlayer = NULL;
	}

	m_pActivePlayer = new AUTPlayer();//44100,2,"plug:audio_media");
	if(m_pActivePlayer == NULL)
	{
		printf("new AutPlayer error");
		iRet = -1;
	}
	else
	{
		iRet = 0;
	}
	
	if (iRet >= 0)
		{
			iRet = m_pActivePlayer->setUserCb(autCb_func, this);
			if (iRet < 0)
			{
				printf("\n\n\n\nm_pActivePlayer->setUserCb() =====failed======%d\n\n\n\n", iRet);
				iRet = -1;
			}
		}

	if (iRet >= 0)
	{
		iRet = m_pActivePlayer->setUrl((char*)strUrl.c_str());
		if (iRet < 0)
		{
			printf("\n\n\n\nm_pActivePlayer->setUrl() =====failed======%d, strUrl=%s\n\n\n\n", iRet, strUrl.c_str());
			iRet = -1;
		}
		else
		{
			printf("\n\n\n\nm_pActivePlayer->setUrl() =====success======%d, strUrl=%s\n\n\n\n", iRet, strUrl.c_str());
		}
	}
	
	int32_t iSubtiletRet = addSubtitleFile((void*)m_pActivePlayer, strUrl);
	printf("iSubtiletRet ret : %d====================================\n", iSubtiletRet);

	int	iRet2 = m_pActivePlayer->setViewWindow(0, 0, AVNCL_VIDEO_WIDTH, AVNCL_VIDEO_HIGHTH); 

	if (iRet2 < 0)
	{
		printf("\n\n\n\npVideoFilter->play() =====failed======%d\n\n\n\n", iRet);
		iRet2 = -1;
	}
	

	if (iRet < 0)
	{
		m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
		m_nPlayFailTimes++;

		return false;
	}
	return true;
}
int CBackGroundMediaVideo::play(){




	int iRet = m_pActivePlayer->play();
	if (iRet < 0)
	{
		printf("\n\n\n\nm_pActivePlayer->play() =====failed======%d\n\n\n\n", iRet);
		iRet = -1;
	}

	if (iRet >= 0)
	{
		m_iAutPlayerStatus = VIDEO_STATUS_PLAYING;
		m_iAutPlayerLastStatus = VIDEO_STATUS_PLAYING;
		m_nPlayFailTimes = 0;
	} 
	else
	{
		m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;
		m_nPlayFailTimes++;

		return false;
	}
	return true;
}
#endif
bool					CBackGroundMediaVideo::pause()
{
	//只有在播放状态下才能执行暂停操作
	if (m_iAutPlayerStatus != VIDEO_STATUS_PLAYING && m_iAutPlayerStatus != VIDEO_STATUS_PAUSED)
	{
		return false;
	}

	//暂停媒体播放
	if (NULL == m_pActivePlayer || m_pActivePlayer->pause() < 0)
	{
		return false;
	}

	//更新媒体状态
	if (m_iAutPlayerStatus == VIDEO_STATUS_PLAYING)
	{
		m_iAutPlayerStatus = VIDEO_STATUS_PAUSED;
		m_iAutPlayerLastStatus = VIDEO_STATUS_PAUSED;
	} 
	else if (m_iAutPlayerStatus == VIDEO_STATUS_PAUSED)
	{
		m_iAutPlayerStatus = VIDEO_STATUS_PLAYING;
		m_iAutPlayerLastStatus = VIDEO_STATUS_PLAYING;
	}

	return true;
}


bool	CBackGroundMediaVideo::stop()
{
	//已经是停止状态，则不需要再进行处理
	if (m_iAutPlayerStatus == VIDEO_STATUS_STOPPED)
	{
		//printf("CBackGroundMediaVideo::stop() ------ 22222----------\n");
		return true;
	}
	//printf("CBackGroundMediaVideo::stop() ------ 33333----------\n");

	//只有在播放和暂停状态下才能执行暂停操作
	if (m_iAutPlayerStatus != VIDEO_STATUS_PLAYING &&
		m_iAutPlayerStatus != VIDEO_STATUS_PAUSED)
	{
		//printf("CBackGroundMediaVideo::stop() ------ 444444----------\n");
		return false;
	}
	//printf("CBackGroundMediaVideo::stop() ------ 5555555----------\n");

	//更新媒体状态
	m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
	m_iAutPlayerLastStatus = VIDEO_STATUS_STOPPED;

	if (NULL == m_pActivePlayer)
	{
		return false;
	}

	//停止媒体播放
	m_pActivePlayer->stop();

	//由于需要AutPlayer只能实例一个，切换SD-Video和USB-Video，AutPlayer在stop后需要delete
	delete m_pActivePlayer;
	m_pActivePlayer = NULL;

	return true;
}

// 响应共享内存命令请求
int					CBackGroundMediaVideo::handleShareMemControlCmd(int cmd,int val0,char* val1,void* out,void* pdat)
{
	// 接收播放控制请求

	int32_t ret = 0;

	CBackGroundMediaVideo *pthis=(CBackGroundMediaVideo *)pdat;
	soutval_t *pout =(soutval_t *)out;
	
	switch(cmd)
	{

	case MEDIA_VIDEO_CMD_SETURL:
		{
			string strMedia(val1);
			if (strMedia.length() > 0)
			{
				pout->val0 = pthis->setUrl(strMedia)==true?0:-1;
				
			}
			//pthis->updateShareMemStatus();
			
			pout->val1 = m_iAutPlayerStatus;
			
			break;
		}
	case MEDIA_VIDEO_CMD_PLAY:
		{
			string strMedia(val1);
			if (strMedia.length() > 0)
			{
				pout->val0 =pthis->play()==true?0:-1;
			}
			//pthis->updateShareMemStatus();
			
			pout->val1 = m_iAutPlayerStatus;
			
			break;
		}

	case MEDIA_VIDEO_CMD_PAUSE:
		{
			pout->val0=pthis->pause()==true?0:-1;
			//pthis->updateShareMemStatus();
			pout->val1 = m_iAutPlayerStatus;
			break;
		}
	case MEDIA_VIDEO_CMD_STOP:
		{
			pout->val0=pthis->stop()==true?0:-1;
			pout->val1 = m_iAutPlayerStatus;
			//pthis->updateShareMemStatus();
			break;
		}
	case MEDIA_VIDEO_CMD_SEEKTO:
		{
			uint32_t uSeekTime = val0;
			printf("video bgThread---------uSeekTime=%d-----------\n", uSeekTime);
			
			pout->val0 = pthis->seekwithProtect(uSeekTime);
			pout->val1 = m_iAutPlayerStatus;
			//pthis->updateShareMemStatus();
			break;
		}
	
	case MEDIA_VIDEO_CMD_GETPOS:
		{
			pout->val0 = (int32_t)pthis->m_pActivePlayer->getCurrentPosition();
			break;
		}
	case MEDIA_VIDEO_CMD_GETDUR:
		{
			pout->val0 = (int32_t)pthis->getMediaTotalTime();
			break;
		}
	case MEDIA_VIDEO_CMD_GETSTATUS:
		{
			pout->val0 = pthis->m_iAutPlayerStatus;
			break;
		}
	case MEDIA_VIDEO_CMD_GETMEDIAINFO:
		{
			pout->val0 = (unsigned long)pthis->m_pActivePlayer->getMediaInfo();
			if(pout->val0 != NULL)
				memcpy(m_pCBGShareMemBeater_MediaInfo->getShareMem()+sizeof(uint32_t) *3, (void *)pout->val0,sizeof(MediaInfo));
			else
				memset(m_pCBGShareMemBeater_MediaInfo->getShareMem()+sizeof(uint32_t) *3, 0,sizeof(MediaInfo));
			break;
		}				
	#if 0
	case enumPlayerShareMemControlType_PlayAndHideVideo:
		{
			string strMedia;
			strMedia.format("%s", m_pShareMemControlReq);
			if (strMedia.getLength() > 0)
			{
				startPlay(strMedia, true);
			}
			updateShareMemStatus();
			break;
		}
	case enumPlayerShareMemControlType_ShowVideo:
		{
			string strSeekTime;
			strSeekTime.format("%s", m_pShareMemControlReq);
			uint32 uSeekTime = strSeekTime.getUint32();
			if (0 < uSeekTime)
			{
				printf("video bgThread---------strSeekTime=%s, uSeekTime=%d-----------\n", strSeekTime.getString(), uSeekTime);
				seekwithProtect(uSeekTime);
			}

			if (NULL != m_pActivePlayer)
			{
				m_pActivePlayer->setViewWindow(0, 0, AVNCL_VIDEO_WIDTH, AVNCL_VIDEO_HIGHTH); 
			}
			updateShareMemStatus();
			break;
		}
	case enumPlayerShareMemControlType_DeletePlayer:
		{
			if (NULL != m_pActivePlayer)
			{
				m_pActivePlayer->stop();
				delete m_pActivePlayer;
				m_pActivePlayer = NULL;

				m_iAutPlayerStatus = VIDEO_STATUS_STOPPED;
			}
			updateShareMemStatus();
			break;
		}
#endif
	default:
		break;
	}
	printf("video bgThread getShareMem Control_Req, done! %d \n",cmd);
	return ret;
}

// 更新时间到共享内存
void					CBackGroundMediaVideo::updateShareMemTimeInfo()
{
	int32_t	iTotalTime;
	int32_t	iCurTime;
	if (NULL != m_pActivePlayer && (m_iAutPlayerStatus == VIDEO_STATUS_PAUSED || m_iAutPlayerStatus == VIDEO_STATUS_PLAYING))
	{
		iTotalTime	= (int32_t)m_pActivePlayer->getDuration();
		//printf("CBackGroundMediaVideo::updateShareMemTimeInfo  Player-Time-Info iTotalTime=%d---------------\n", iTotalTime);
		if (iTotalTime < 0 || (1 << 30) < iTotalTime)
		{
			iTotalTime = 0;
		}

		iCurTime	= (int32_t)m_pActivePlayer->getCurrentPosition();
		//printf("CBackGroundMediaVideo::updateShareMemTimeInfo  Player-Time-Info iCurTime=%d---------------\n", iCurTime);
		if (iCurTime < 0)
		{
			iCurTime = 0;
		}

	} 
	else
	{
		iTotalTime	= 0;
		iCurTime	= 0;
		//printf("CBackGroundMediaVideo::updateShareMemTimeInfo  Player-Time-Info Not play 000---------------\n");
	}
	//printf("CBackGroundMediaVideo::updateShareMemTimeInfo  Player-Time-Info iCurTime=%d---------------\n", iCurTime);

	// 发送时间信息
	//m_pCBGShareMemBeater_PlayerTimeInfo->activeShareMemPlayerTimeInfo(false, (int32)iCurTime, (int32)iTotalTime);
}

// 更新状态到共享内存
void					CBackGroundMediaVideo::updateShareMemStatus()
{
	//printf("CBackGroundMediaVideo::updateShareMemStatus    m_iAutPlayerStatus=%d---------------\n", m_iAutPlayerStatus);
	sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_STAT,m_iAutPlayerStatus,m_iAutPlayerStatus);
}

uint32_t	CBackGroundMediaVideo::getMediaTotalTime()
{

	if (NULL == m_pActivePlayer)
	{
		return 0;
	}

	int32_t nTotalTime = m_pActivePlayer->getDuration();
	if (nTotalTime < 0)
	{
		nTotalTime = 0;
	}

	return (uint32_t)nTotalTime;
}


bool	CBackGroundMediaVideo::isAllowSeek()
{
	if (m_iAutPlayerStatus == VIDEO_STATUS_PLAYING || m_iAutPlayerStatus == VIDEO_STATUS_PAUSED)
	{
		return true;
	}
	return false;
}

void	CBackGroundMediaVideo::setSeekStatus()
{
	//m_iAutPlayerLastStatus = m_iAutPlayerStatus;
	m_iAutPlayerStatus = VIDEO_STATUS_SEEKING;
}

int	CBackGroundMediaVideo::seekwithProtect(uint32_t nTime)
{
	int ret = -1;
	//AutPlayer的seek必须先判断底层回调的seek完成状态，防止重入，并加sleep保护
	if (isAllowSeek())
	{
		printf("CMediaMP3::setMediaItemPlayTime = %d ====================\n", nTime);
		if (NULL != m_pActivePlayer)
		{
			ret = m_pActivePlayer->seekto(nTime);
			if(ret>=0)
				setSeekStatus();
		}
	}

	return ret;
}

#ifdef AW_OS_LINUX_ARM
#if defined(USE_AUTPLAYER)
int CBackGroundMediaVideo::autCb_func(int32_t msgType, void *user,void*data,int len)
{
	//printf("CBackGroundMediaVideo::autCb_func  begin, msgType= %d================================\r\n", msgType);

	switch(msgType)
	{
	case AUDIO_PCM_OUTPUT: //128
		{
			//printf("CBackGroundMediaVideo::autCb_func  AUDIO_PCM_OUTPUT ========================\n");
			break;
		}
	case SUBCTRL_SUBTITLE_AVAILABLE: //1600
		{
			printf("CBackGroundMediaVideo::autCb_func  SUBCTRL_SUBTITLE_AVAILABLE = %d================================\r\n", msgType);

			SubtitleItem* pItem = (SubtitleItem*)data;

			if(pItem == NULL)
			{
				loge("error pItem == NULL");
				return -1;
			}
			if(pItem->bText==1)
				printf("autCb_func, text=%s\n",pItem->pText);

			printf("subtitle show\n");
			memcpy(m_pCBGShareMemBeater_Subtitle->getShareMem()+sizeof(uint32_t) *3,pItem,sizeof(SubtitleItem));
			if(pItem->bText==0)
				memcpy(m_pCBGShareMemBeater_Subtitle->getShareMem()+sizeof(SubtitleItem)+sizeof(uint32_t) *3, pItem->pBitmapData,pItem->nBitmapWidth*pItem->nBitmapHeight*4);
			else
				memcpy(m_pCBGShareMemBeater_Subtitle->getShareMem()+sizeof(SubtitleItem)+sizeof(uint32_t) *3, pItem->pText,pItem->nTextLength);
			
			sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_PLAYERCB,msgType,m_iAutPlayerStatus);
			break;
		}

	case SUBCTRL_SUBTITLE_EXPIRED: //1601
		{
			printf("subtitle hide\n");
			sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_PLAYERCB,msgType,m_iAutPlayerStatus);
			break;
		}


	case AWPLAYER_MEDIA_PREPARED:
		printf("CBackGroundMediaVideo::autCb_func  AWPLAYER_MEDIA_PREPARED================================\r\n");
		break;
	case AWPLAYER_MEDIA_PLAYBACK_COMPLETE:
		{
			printf("CBackGroundMediaVideo::autCb_func  AWPLAYER_MEDIA_PLAYBACK_COMPLETE================================\r\n");
			m_iAutPlayerStatus = VIDEO_STATUS_PLAY_COMPLETE;
			m_iAutPlayerLastStatus = VIDEO_STATUS_PLAY_COMPLETE;
			sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_PLAYERCB,msgType,m_iAutPlayerStatus);
			break;
		}
	case AWPLAYER_MEDIA_SEEK_COMPLETE:
		{
			//AutPlayer的seek必须先判断底层回调的seek完成状态，防止重入，并加sleep保护
			printf("CBackGroundMediaVideo::autCb_func  AWPLAYER_MEDIA_SEEK_COMPLETE================================\r\n");
			m_iAutPlayerStatus = m_iAutPlayerLastStatus;
			sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_PLAYERCB,msgType,m_iAutPlayerStatus);
			break;
		}

	case AWPLAYER_MEDIA_LOG_RECORDER:
	case AWPLAYER_MEDIA_BUFFERING_UPDATE:
	case AWPLAYER_MEDIA_ERROR:
	case AWPLAYER_MEDIA_INFO:
	case AWPLAYER_MEDIA_SET_VIDEO_SIZE:
		sMediaVideoEmitSignal(MEDIA_VIDEO_TYPE_PLAYERCB,msgType,m_iAutPlayerStatus);
		break;
	default:
		{
			//logw("CMediaMP3 message 0x%x not handled.", messageId);
			break;
		}
	}

	return 0;
}
#endif
#endif

int32_t	CBackGroundMediaVideo::addSubtitleFile(void* pPlayer, const string& strFullName)
{
#ifdef AW_OS_LINUX_ARM
#if defined(USE_AUTPLAYER)
	AUTPlayer* ap = (AUTPlayer*)pPlayer;
	if (NULL == ap)
	{
		return -1;
	}

	int32_t iPos = (int32_t)strFullName.find(".", strFullName.length() - 1, false);
	if (iPos <= 0)
	{
		return -1;
	}

	string strTrimMediaName = "";
	strTrimMediaName = strFullName.substr(0, (uint32_t)iPos);

	string suffix_idx = ".idx";
	string suffix[11] = {".sub", ".dvdsub", ".pgs", ".divx", ".dvbsub", ".txt", ".timedtext", ".ssa", ".smi", ".srt", ".ass"};

	for (uint8_t i = 0; i < 11; i++)
	{
		string strFile;
		strFile = strTrimMediaName + suffix[i];
		printf("CMediaFilter::addSubtitleFile -----strFile= %s -------\n", strFile.c_str());

		//CFile file(strFile);
		//bool bRet = file.exists();
		int bRet = access((char*)strFile.c_str(), F_OK);
		if (bRet == 0)
		{
			printf("CMediaFilter::addSubtitleFile -----strFile= %s -------find!!!!!!!!!!!!!!!!!!!!!!---------\n", strFile.c_str());
			int apRet = -999;
			if (0 == i)
			{
				string strIdxFile;
				strIdxFile = strTrimMediaName + suffix_idx;
				//CFile idxFile(strIdxFile);
				//bool bHasIdx = idxFile.exists();
				int bHasIdx = access((char*)strIdxFile.c_str(), F_OK);
			
				if (bHasIdx == 0)
				{
					apRet = ap->setsubtitleUrlFd((char*)strFile.c_str(), (char*)strIdxFile.c_str());
				} 
				else
				{
					apRet = ap->setsubtitleUrl((char*)strFile.c_str());
				}
			}
			else
			{
				apRet = ap->setsubtitleUrl((char*)strFile.c_str());
			}
			return (int32_t)apRet;
		}
	}

#endif
#endif
	return -1;
}


// 是否可以播放
bool	CBackGroundMediaVideo::beAbleToPlay()
{
	if (20 <= m_nPlayFailTimes)
	{
		return false;
	}

	return true;
}
#endif
#endif
