

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


	//ʵ�ָ��ඨ���ý��淶�ӿ�
public:
	//����
	
	bool setUrl(const string& strUrl);
	int play();
	
	bool					startPlay(const  string& strUrl, bool bHide = false);

	//��ͣ
		bool					pause();

	//ֹͣ
		bool					stop();

	 uint32_t				getMediaTotalTime();


	// �������ڴ�ͨ��
public:
	// ��Ӧ�����ڴ���������
	static int							handleShareMemControlCmd(int cmd,int val0,char* val1,void* out,void* pdat);

	// ����ʱ�䵽�����ڴ�
	void							updateShareMemTimeInfo();

	// ����״̬�������ڴ�
	void							updateShareMemStatus();

	// �Ƿ���Բ���
	bool							beAbleToPlay();


	//���ߺ���
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


	//״̬����
public:
	//����������
	//AUTPlayer*					m_pAudioPlayerI;
	//AUTPlayer*					m_pAudioPlayerII;
	AUTPlayer*					m_pActivePlayer;

	static uint8_t			m_iAutPlayerStatus;
	static uint8_t			m_iAutPlayerLastStatus;

	//���ſ��Ƶ���������Ĺ����ڴ�
	//CShareMem* m_pCBGShareMemMonitor_Control_Req;
	//char* m_pShareMemControlReq;

	//������״̬�Ĺ����ڴ�
	//CShareMem* m_pCBGShareMemBeater_PlayerStatus;
	//char* m_pShareMemPlayerStatus;

	//����ʱ��Ĺ����ڴ�
	//CShareMem* m_pCBGShareMemBeater_PlayerTimeInfo;
	//char* m_pShareMemPlayerTimeInfo;

	//��Ļ�Ĺ����ڴ�
	static CShareMem* m_pCBGShareMemBeater_Subtitle;
	char* m_pShareMemSubtitle;
	
	//ý����Ϣ�Ĺ����ڴ�
	static CShareMem* m_pCBGShareMemBeater_MediaInfo;
	char* m_pShareMemMediaInfo;
	
	// ��������ʧ�ܵĴ���
	uint32_t m_nPlayFailTimes;
};
#endif

#endif//#ifndef HW_APPS_BG_PROCESS_VIDEO_PLAYER__H