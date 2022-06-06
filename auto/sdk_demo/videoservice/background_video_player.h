

#ifndef AW_APPS_BG_PROCESS_VIDEO_PLAYER__H
#define AW_APPS_BG_PROCESS_VIDEO_PLAYER__H



#include "CShareMem.h"
#define AW_OS_LINUX_ARM 1
#if defined(AW_OS_LINUX_ARM)
#include "AutPlayer.h"
#include "outputCtrl.h"

#define USE_AUTPLAYER 1
#define AVNCL_VIDEO_WIDTH 800
#define AVNCL_VIDEO_HIGHTH 480

static const  uint8_t VIDEO_STATUS_STOPPED   = 0;
static const  uint8_t VIDEO_STATUS_PREPARING = 1;
static const  uint8_t VIDEO_STATUS_PREPARED  = 2;
static const  uint8_t VIDEO_STATUS_PLAYING   = 3;
static const  uint8_t VIDEO_STATUS_PAUSED    = 4;
static const  uint8_t VIDEO_STATUS_SEEKING   = 5;
static const  uint8_t VIDEO_STATUS_PLAY_COMPLETE   = 6;



class CBackGroundMediaVideo// : public CThread
{

public:
	CBackGroundMediaVideo();
	~CBackGroundMediaVideo();


	//实现父类定义的媒体规范接口
public:
	//播放
	
	bool setUrl(const string& strUrl);
	int play();
	
	bool					startPlay(const  string& strUrl, bool bHide = false);

	//暂停
		bool					pause();

	//停止
		bool					stop();

	 uint32_t				getMediaTotalTime();


	// 处理共享内存通信
public:
	// 响应共享内存命令请求
	static int							handleShareMemControlCmd(int cmd,int val0,char* val1,void* out,void* pdat);

	// 更新时间到共享内存
	void							updateShareMemTimeInfo();

	// 更新状态到共享内存
	void							updateShareMemStatus();

	// 是否可以播放
	bool							beAbleToPlay();


	//工具函数
protected:
	bool							isAllowSeek();

	void									setSeekStatus();

	int									seekwithProtect(uint32_t nTime);

	int32_t							addSubtitleFile(void* pPlayer, const string& strFullName);

#ifdef AW_OS_LINUX_ARM
#if defined(USE_AUTPLAYER)
	static int end(int32_t msgType, void *user);
	static int autCb_func(int32_t msgType, void *user,void*data,int len);
#endif
#endif


	//状态数据
public:
	//播放器对象
	//AUTPlayer*					m_pAudioPlayerI;
	//AUTPlayer*					m_pAudioPlayerII;
	AUTPlayer*					m_pActivePlayer;

	static uint8_t			m_iAutPlayerStatus;
	static uint8_t			m_iAutPlayerLastStatus;

	//播放控制的请求命令的共享内存
	//CShareMem* m_pCBGShareMemMonitor_Control_Req;
	//char* m_pShareMemControlReq;

	//播放器状态的共享内存
	//CShareMem* m_pCBGShareMemBeater_PlayerStatus;
	//char* m_pShareMemPlayerStatus;

	//播放时间的共享内存
	//CShareMem* m_pCBGShareMemBeater_PlayerTimeInfo;
	//char* m_pShareMemPlayerTimeInfo;

	//字幕的共享内存
	static CShareMem* m_pCBGShareMemBeater_Subtitle;
	char* m_pShareMemSubtitle;
	
	//媒体信息的共享内存
	static CShareMem* m_pCBGShareMemBeater_MediaInfo;
	char* m_pShareMemMediaInfo;
	
	// 连续播放失败的次数
	uint32_t m_nPlayFailTimes;
};
#endif

#endif//#ifndef HW_APPS_BG_PROCESS_VIDEO_PLAYER__H