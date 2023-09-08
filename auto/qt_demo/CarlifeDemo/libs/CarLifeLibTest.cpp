/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@8th-December-2016@

	CarLife Protocol version:
		@V1.2.4@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CCarLifeLibWrapper.h"
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <string.h>


using namespace CCarLifeLibH;

static int g_isConnected = -1;
static int g_isReadFinished = 0;

/*************************************************
 MACRO
 *************************************************/
//connection pattern setting
#define ADB_CONNECTION 0
#define IOS_WIFI_CONNECTION 1
#define CONNECTION_PATTERN ADB_CONNECTION

/****************************************
CALLBACK FUNCTIONS DECLARE
*****************************************/
// Video channel
void videoDataReceive(u8 *data, u32 len);
void videoHeartBeat();

// Media channel
void mediaInit(S_AUDIO_INIT_PARAMETER *initParam);
void mediaNormalData(u8 *data, u32 len);
void mediaStop();
void mediaPause();
void mediaResume();
void mediaSeek();

// Navi TTS channel
void ttsInit(S_AUDIO_INIT_PARAMETER *initParam);
void ttsNormalData(u8 *data, u32 len);
void ttsStop();

//Vr channel
void vrInit(S_AUDIO_INIT_PARAMETER *initParam);
void vrNormalData(u8 *data, u32 len);
void vrStop();

// CMD channel
void *cmdReceiveThread(void *arg);
void *videoReceiveThread(void *arg);
void *mediaReceiveThread(void *arg);
void *ttsReceiveThread(void *arg);
void *vrReceiveThread(void *arg);

void cmdProtocolVersionMatchStatus(S_PROTOCOL_VERSION_MATCH_SATUS* status);
void cmdMDInfro(S_MD_INFO*);
void cmdMDBTPairInfro(BTPairInfo*);
void cmdVideoEncoderInitDone(S_VIDEO_ENCODER_INIT_DONE*);
void cmdVideoEncoderFrameRateChangeDone(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*);
void cmdTelStateChangeIncoming();
void cmdTelStateChangeOutGoing();
void cmdTelStateChangeIdle();
void cmdTelStateChangeInCalling();
void cmdScreenOn();
void cmdScreenOff();
void cmdScreenUserPresent();
void cmdForeground();
void cmdBackground();
void cmdGoToDeskTop();
void cmdMicRecordWakeupStart();
void cmdMicRecordEnd();
void cmdMicRecordRecogStart();
//0x00010026
void cmdModuleStatus(S_MODULE_STATUS_LIST_MOBILE*);
//0x00010030
void cmdNaviNextTurnInfo(S_NAVI_NEXT_TURN_INFO*);
//0x00010031
void cmdCarDataSubscribe(S_VEHICLE_INFO_LIST*);	
//0x00010033
void cmdCarDataSubscribeStart(S_VEHICLE_INFO_LIST*);
//0x00010034
void cmdCarDataSubscribeStop(S_VEHICLE_INFO_LIST*);
//0x00010035
void cmdMediaInfo(S_MEDIA_INFO*);
//0x00010036
void cmdMediaProgressBar(S_MEDIA_PROGRESS_BAR*);
//0x00010037
void cmdRegisterConnectException(S_CONNECTION_EXCEPTION*);
//0x00010038
void cmdRegisterRequestGoToForeground(void);
//0x00010039
void cmdRegisterUIActionSound(void);

//0x00010049
void cmdRegisterMdAuthenResponse(S_AUTHEN_RESPONSE* response);

//0x00010051
void cmdRegisterFeatureConfigRequest();

//0x00010057
void cmdRegisterVideoEncoderJPEGAck();

//0x00010058(Deprecated)

//0x00010059
void cmdRegisterMdExit();

int checkVideoReceive();


/******************************************
INIT PARAMETER
*******************************************/
S_HU_PROTOCOL_VERSION huProtocolVersion={1,0};

S_VIDEO_ENCODER_INIT initVideoParam={768, 480,30};

u8 vrData[1024]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};

S_TOUCH_ACTION touchAction={1, 12 ,34};

//S_TOUCH_CAR_HARD_KEY_CODE touchCarHardKeyCode={0x00000010};//next song
S_TOUCH_CAR_HARD_KEY_CODE touchCarHardKeyCode={0x00000008};//next song

//anthorization
S_AUTHEN_REQUEST authenRequest={"CarLife_1.0.0"};

S_FEATURE_CONFIG_LIST configList;
S_FEATURE_CONFIG featureConfigFocusUI;

void setFocusUIConfig(int val){
	configList.cnt=1;
	configList.pFeatureConfig=&featureConfigFocusUI;
	featureConfigFocusUI.key="FOCUS_UI";
	featureConfigFocusUI.value=val;
	featureConfigFocusUI.pNext=NULL;
}


#if 0

#define  BUF_SIZE  5
unsigned char fifo_arr[BUF_SIZE] = {}; 
unsigned int readops = 0;
unsigned int writeops = 0;
unsigned int empty = 0;
unsigned int full = 0;

/*
* 初始化函数，读写下标readops，writeops指向
* empty = 1，fifo为空；full = 0，fifo不满
*/
int init_fifo(void)
{

    memset(fifo_arr,0, sizeof(fifo_arr));
    readops = 0;
    writeops = 0;
    empty = 1;
    full = 0;
    return 0;

}

int read_fifo(char* arr,int len)
{

    int can_readlen = 0; //可以读的长度

    int readlen = 0;

    int nextreadops = 0;

    int i = 0;

    readlen = len;

    if(1 == empty)//为空则返回

    {

        return  -1;

    }

    if(readlen == 0)

    {

        return 0;

    }

    if(writeops > readops)

    {

        can_readlen = writeops - readops;

    }

    else if(writeops == readops)

    {

        can_readlen = BUF_SIZE;

    }

    else

    {

        can_readlen = BUF_SIZE - (readops - writeops);

    }


    if(readlen > can_readlen)

    {

        readlen = can_readlen;

    }


    nextreadops = (readops + readlen)%BUF_SIZE;

    if(nextreadops == (readops + readlen))

    {

        for(i = 0; i < readlen ; i++)

        {

            arr[i]=fifo_arr[readops + i];

        }

    }

    else

    {

        for(i = 0; i < readlen - nextreadops ; i++)

        {

            arr[i]=fifo_arr[readops + i];

        }

        for(i = 0; i < nextreadops ; i++)

        {

            arr[readlen - nextreadops + i]=fifo_arr[i];

        }

    }

    readops = nextreadops;

    if(writeops = readops)

    {

        empty = 1;// empty = 1，fifo为空；

    }

    full = 0;  //full = 0，fifo不满

    return readlen;

}


int write_fifo(char* arr,int len)
{

    int can_writelen = 0; //可以写的长度

    int writelen = 0;

    int nextwriteops = 0;

    int i = 0;

    writelen = len;

    if(1 == full)//为满则返回

    { 

        return  -1;

    }


    if(writelen == 0)

    {

        return 0;

    }


    if(writeops > readops)

    {

        can_writelen = BUF_SIZE - (writeops - readops);

    }

    else if(writeops == readops)

    {

        can_writelen = BUF_SIZE;

    }

    else

    {

        can_writelen = readops - writeops;

    }



    if(writelen > can_writelen)

    {

        writelen = can_writelen;

    }


    nextwriteops = (writeops + writelen)%BUF_SIZE;

    if(nextwriteops == (readops + writelen))

    {

        for(i = 0; i < writelen ; i++)

        {

            fifo_arr[readops + i]=arr[i];

        }

    }

    else

    {

        for(i = 0; i < writelen -nextwriteops ; i++)

        {

            fifo_arr[writeops + i] = arr[i];

        }

        for(i = 0; i <nextwriteops ; i++)

        {

            fifo_arr[i] = arr[writelen - nextwriteops + i];

        }

    }


    writeops = nextwriteops;

    if(writeops == readops)

    {

        full = 1; //full = 1，fifo满

    }

    empty = 0;//empty = 0，fifo不为空；

    return writelen;

}
#endif


#include "RingQueue.h"
#define RX_BUF_MAX_SIZE     (1000*1000)        // 定义缓冲区的最大大小为200
static unsigned char RxBuffer[RX_BUF_MAX_SIZE];   // 定义缓冲区
static RING_QUEUE RxRingQ;             // 定义环形缓冲区的控制块
   
#if 0
int main()
{
	int ret;
	char szBuf[6]={'1', '2', '3', '4', '5', '6'};
	char szBuf2[10];
	int i;
	
	unsigned char err;
   // 初始化缓冲区
    RingQueueInit(&RxRingQ,RxBuffer,RX_BUF_MAX_SIZE,&err);
    if(err != RQ_ERR_NONE){
        //初始化缓冲区失败的处理
        printf("init failed\n", err);
    }

	printf("write 123456 to ring\n");
	for(i = 0; i < 6; i++)
	{
   		RingQueueIn(&RxRingQ,szBuf[i],RQ_OPTION_WHEN_FULL_DONT_IN,&err); 
	}

	for(i = 0; i < 6; i++)
	{
		szBuf2[i] = RingQueueOut(&RxRingQ,&err);
		if(err != RQ_ERR_NONE)
		{
			 printf("read %d failed\n", i);
			 break;
		}
	}
	szBuf2[5]= 0;
	
	printf("read %d, buf is %s\n", i, szBuf2);


	szBuf2[0] = RingQueueOut(&RxRingQ,&err);

	printf("read 1 again, ret should be 4, %d\n", err);


	printf("write 3456 to ring\n");
	for(i = 0; i < 4; i++)
	{
   		RingQueueIn(&RxRingQ,szBuf[i+2],RQ_OPTION_WHEN_FULL_DONT_IN,&err); 
	}
	
	memset(szBuf2, 0x0, sizeof(szBuf2));
	for(i = 0; i < 3; i++)
	{
		szBuf2[i] = RingQueueOut(&RxRingQ,&err);
		if(err != RQ_ERR_NONE)
		{
			 printf("read %d failed\n", i);
			 break;
		}
	}
	szBuf2[3] = 0;
	printf("read 3 , ret should be 3, %d, buf should be 345, is %s\n", i, szBuf2);


	printf("write 123 to ring\n");
	for(i = 0; i < 3; i++)
	{
   		RingQueueIn(&RxRingQ,szBuf[i],RQ_OPTION_WHEN_FULL_DONT_IN,&err); 
	}

	memset(szBuf2, 0x0, sizeof(szBuf2));
	for(i = 0; i < 5; i++)
	{
		szBuf2[i] = RingQueueOut(&RxRingQ,&err);
		if(err != RQ_ERR_NONE)
		{
			 printf("read %d failed\n", i);
			 break;
		}
	}
	szBuf2[4] = 0;
	printf("read 5 , ret should be 4, %d, buf should be 6123, is %s\n", i, szBuf2);
	

	return 0;
	
	
	
}

#endif


extern "C" {
       int init_XPlayer(int (*read_fifo)(char*, int));
	   int read_fifo(char* arr,int len);
	   int destroy_XPlayer();
}


#include<pthread.h>
#include <semaphore.h> 

static pthread_mutex_t testlock;
sem_t bin_sem;


int init_fifo()
{
	unsigned char err;
   // 初始化缓冲区
    RingQueueInit(&RxRingQ,RxBuffer,RX_BUF_MAX_SIZE,&err);
    if(err != RQ_ERR_NONE){
        //初始化缓冲区失败的处理
        printf("init failed\n");
		return -1;
    }
	pthread_mutex_init(&testlock, NULL);
	sem_init(&bin_sem,0,0);
}



int read_fifo(char* arr,int len)
{
	int i;
	unsigned char err;
	static int total1 = 0;
	static int total2 = 0;

	
	pthread_mutex_lock(&testlock); 
	
	for(i = 0; i < len; i++)
	{
		arr[i] = RingQueueOut(&RxRingQ,&err);
		if(err != RQ_ERR_NONE)
		{
			 //printf("read %d failed\n", i);
			 break;
		}
	}
	
	pthread_mutex_unlock(&testlock); 
	
	total1+=i;
	if(total1 % (1000*1000) == 10)
	{
		cout<< "read_fifo read"<<total1<<"\n";
	}
	if(i == 0 && g_isReadFinished == 0)
		sem_wait(&bin_sem);
	//if(i == 0 && g_isReadFinished == 1)
	//	printf("wfd read_fifo finished now\n");
	
	return i;
	
}


int write_fifo(char* arr,int len)
{
	int i;
	unsigned char err;
	
	for(i = 0; i < len; i++)
	{
		pthread_mutex_lock(&testlock); 
		RingQueueIn(&RxRingQ,arr[i],RQ_OPTION_WHEN_FULL_DONT_IN,&err);
		pthread_mutex_unlock(&testlock); 
		sem_post(&bin_sem);
		if(err != RQ_ERR_NONE)
			break;
	}
	
	
	
	return i;
}

int carlife_service_is_connected()
{
	if(1 == g_isConnected)
		return 1;

	return 0;
}
int carlife_service_init()
{
	init_fifo();
	cout << "init xplayer\n";
	g_isReadFinished = 0;
	g_isConnected = -1;
	
	init_XPlayer(read_fifo);
	return 0;
}
int carlife_service_destroy()
{
	g_isReadFinished = 1;
	sem_post(&bin_sem);
	destroy_XPlayer();
	return 0;
}
int carlife_service_connect_to_app()
{
	int ret;
	pthread_t id;

	if(1 == g_isConnected)
	{
		cout << "has connected\n";
		return 0;
	}
	cout << "destroy old first\n";

	g_isConnected = -1;
	
	CCarLifeLib::getInstance()->carLifeLibDestory();
	sleep(2);
	cout << "init new now\n";
	// prepare for connectionSetup;
	CCarLifeLib::getInstance()->carLifeLibInit();
	sleep(2);
	cout << "begin to connect\n";
	if(0 != CCarLifeLib::getInstance()->connectionSetup())
	{
		cout << "connect to md failed\n";
		return -1;
	}
	cout << "connect to md sucessfully\n";
	
	//create receive thread for cmd, video, media, navi tts, vr, control channels
	ret=pthread_create(&id, NULL, cmdReceiveThread, NULL);
	if(ret!=0){
		cout<<"cmdReceiveThread create failed!"<<endl;
	}else{
	cout<<"cmdReceiveThread create!"<<endl;
	}
	sleep(2);
	if(0  == g_isConnected)
	{
		cout << "connect to app failed\n";
		return -1;
	}

	g_isConnected = 1;
	cout << "connect to app sucessfully\n";


	

	
	ret=pthread_create(&id, NULL, videoReceiveThread, NULL);
	if(ret!=0){
		cout<<"videoReceivThread create failed!"<<endl;
	}else{
	cout<<"videoReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, mediaReceiveThread, NULL);
	if(ret!=0){
		cout<<"mediaReceivThread create failed!"<<endl;
	}else{
	cout<<"mediaReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, ttsReceiveThread, NULL);
	if(ret!=0){
		cout<<"ttsReceivThread create failed!"<<endl;
	}else{
	cout<<"ttsReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, vrReceiveThread, NULL);
	if(ret!=0){
		cout<<"vrReceivThread create failed!"<<endl;
	}else{
	cout<<"vrReceivThread create !"<<endl;
	}
	{
		//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
		CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
		//S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};
		S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};

		CCarLifeLib::getInstance()->cmdStatisticInfo(&huStatisticsInfo);

		CCarLifeLib::getInstance()->cmdVideoEncoderInit(&initVideoParam);
		sleep(2);//sleep 2s
		CCarLifeLib::getInstance()->cmdVideoEncoderStart();
					
	}
	return 0;
	
}
int main(int argc, char *const argv[]){
	static int count=0;
	
	while(1)
	{
		if(carlife_service_is_connected() != 1)
		{
			printf("2 carlife_service_destroy\n");
			carlife_service_destroy();
			//sleep(1);
			printf("carlife_service_init\n");
			carlife_service_init();
			
			carlife_service_connect_to_app();
		}
		else
		{
			while(1)
			{
				int time=2000*1000;

				touchCarHardKeyCode.keycode = 0x1e;
				CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);
				usleep(time);
				
				touchCarHardKeyCode.keycode = 0x1d;
				CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);
				usleep(time);
			

				touchCarHardKeyCode.keycode = 0x0b;
				CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);
				usleep(time);
				touchCarHardKeyCode.keycode = 0x09;
				CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);
				usleep(time);
				
				
				if(count++ % 40 == 0)
					printf("test video date rate %d\n", count);
				if(carlife_service_is_connected() != 1)
				{
					printf("connection lost, reconnect\n");
					break;
				}
			}
			
		}
		sleep(1);
	}
}

#if 0
/****************************************
 FUNCTIONS
 ****************************************/
int main(int argc, char *const argv[]){
	int ret;
	pthread_t id;
	int item;



	init_fifo();
		
	cout << "init xplayer\n";

	init_XPlayer(read_fifo);
	
	//parameter check
   if(CONNECTION_PATTERN==IOS_WIFI_CONNECTION){
	   if(argc!=2){
			cout<<"use method:"<<endl;
			cout<<"\t ./libtest IPAddress"<<endl;
			return -1;
	   }
   }


	cout<<"CarLife library test"<<endl;

	cout<<"CarLifeLib initialization && connection set up test:"<<endl;
	//initialize CarLife libaray
	CCarLifeLib::getInstance()->carLifeLibInit();

	//set up connection between head unit and mobile device
	//support WI-FI connection
	if(CONNECTION_PATTERN==IOS_WIFI_CONNECTION){
		if(0==CCarLifeLib::getInstance()->connectionSetup(argv[1])){
			cout<<"command/video/media/tts/vr/control channel connection have been set up!"<<endl;
		}else{
				cout<<"connection set up failed!"<<endl;
		}
	}

	//support ADB connection
	if(CONNECTION_PATTERN==ADB_CONNECTION){
		if(0==CCarLifeLib::getInstance()->connectionSetup()){
			cout<<"command/video/media/tts/vr/control channel connection have been set up!"<<endl;
		}else{
				cout<<"connection set up failed!"<<endl;
		}

//		//carLifeLibDestory() test
//		sleep(2);//sleep 2s
//		cout<<"carLifeLibDestory()"<<endl;
//		CCarLifeLib::getInstance()->carLifeLibDestory();
//
//		sleep(2);//sleep 2s
//		cout<<"connectionSetup()"<<endl;
//		CCarLifeLib::getInstance()->connectionSetup();
//
//		//carLifeLibDestory() test
//		sleep(2);//sleep 2s
//		cout<<"carLifeLibDestory()"<<endl;
//		CCarLifeLib::getInstance()->carLifeLibDestory();
//
//		sleep(2);//sleep 2s
//		cout<<"connectionSetup()"<<endl;
//		CCarLifeLib::getInstance()->connectionSetup();
//
//		//disconnect() test
//		sleep(2);//sleep 2s
//		cout<<"disconnect()"<<endl;
//		CCarLifeLib::getInstance()->disconnect();
//		sleep(2);//sleep 2s
//		cout<<"connectionSetup()"<<endl;
//		CCarLifeLib::getInstance()->connectionSetup();
	}
	
	//create receive thread for cmd, video, media, navi tts, vr, control channels
	ret=pthread_create(&id, NULL, cmdReceiveThread, NULL);
	if(ret!=0){
		cout<<"cmdReceiveThread create failed!"<<endl;
	}else{
	cout<<"cmdReceiveThread create!"<<endl;
	}

	ret=pthread_create(&id, NULL, videoReceiveThread, NULL);
	if(ret!=0){
		cout<<"videoReceivThread create failed!"<<endl;
	}else{
	cout<<"videoReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, mediaReceiveThread, NULL);
	if(ret!=0){
		cout<<"mediaReceivThread create failed!"<<endl;
	}else{
	cout<<"mediaReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, ttsReceiveThread, NULL);
	if(ret!=0){
		cout<<"ttsReceivThread create failed!"<<endl;
	}else{
	cout<<"ttsReceivThread create !"<<endl;
	}

	ret=pthread_create(&id, NULL, vrReceiveThread, NULL);
	if(ret!=0){
		cout<<"vrReceivThread create failed!"<<endl;
	}else{
	cout<<"vrReceivThread create !"<<endl;
	}

	//channel test
	cout<<"CarLifeLib test item: "<<endl;
	cout<<"\t1. command channel test;"<<endl;
	cout<<"\t2. video channel test;"<<endl;
	cout<<"\t3. media channel test;"<<endl;
	cout<<"\t4. tts channel test;"<<endl;
	cout<<"\t5. vr channel test;"<<endl;
	cout<<"\t6. control channel test;"<<endl;
	cout<<">>";
	
	//cin>>item;
	//wufude added
	if(argc == 2)
	item = atoi(argv[1]);
	else
		cin>>item;
	switch(item){
		//cmd channel test
		case 1:
			//head unit send protocol version information to mobile device
			CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);

			//0x00018048 
			//CCarLifeLib::getInstance()->cmdHuAuthenRequest(&authenRequest);

			//setFocusUIConfig(1);
			//0x00018052
			//CCarLifeLib::getInstance()->cmdFeatureConfigResponse(&configList);

			//0x00018056
//			CCarLifeLib::getInstance()->cmdVideoEncoderJPEG();
			break;
		//video channel test
		case 2:
			//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
			CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
			
			CCarLifeLib::getInstance()->cmdVideoEncoderInit(&initVideoParam);
			sleep(2);//sleep 2s
			CCarLifeLib::getInstance()->cmdVideoEncoderStart();
			break;
		//media channel test
		case 3:
			{
				//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
				CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
				//S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};
				S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};

				CCarLifeLib::getInstance()->cmdStatisticInfo(&huStatisticsInfo);
			}
			//receive media data
			break;
		//navi tts channel test
		case 4:
			//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
			//CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
				{
				//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
				CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
				//S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};
				S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};

				CCarLifeLib::getInstance()->cmdStatisticInfo(&huStatisticsInfo);
			}
			
			//receive tts data
			break;
		//vr channel test
		case 5:
			//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
			CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);

			CCarLifeLib::getInstance()->sendVRRecordData(vrData, 1024, 0);
			break;
		//control channel test
		case 6:
			//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
			CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);

				{
				int i = 0; 
				//it is necessary to send MSG_CMD_HU_PROTOCOL_VERSION(0x00018001) message
				CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);
				//S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};
				S_STATISTICS_INFO huStatisticsInfo = {"", "", 1, "20312104", 0, 0, 0, ""};

				CCarLifeLib::getInstance()->cmdStatisticInfo(&huStatisticsInfo);

				CCarLifeLib::getInstance()->cmdVideoEncoderInit(&initVideoParam);
				sleep(2);//sleep 2s
				CCarLifeLib::getInstance()->cmdVideoEncoderStart();

			
				//CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);//next song
				while(++i)
				{
					cout << "wufude test hard key "<< i<<endl;
					S_TOUCH_ACTION_DOWN sd;
					S_TOUCH_ACTION_MOVE sm;
					S_TOUCH_ACTION_UP su;
					sd.x = 100+i*5;
					sd.y=100+i*5;

					sm.x=200+i*5;
					sm.y=200+i*5;
					#if 0
					CCarLifeLib::getInstance()->ctrlTouchActionDown(&sd);
					CCarLifeLib::getInstance()->ctrlTouchActionMove(&sm);
					#else
					if(i % 2 == 0)
						touchCarHardKeyCode.keycode = 0x1f;
					else
						touchCarHardKeyCode.keycode = 0x20;
						CCarLifeLib::getInstance()->ctrlTouchCarHardKeyCode(&touchCarHardKeyCode);
					#endif
					
						sleep(5);
				}
			}
			
			break;
		default:
			break;
	}
	
	while(1){
		sleep(1);
	}

	//release CarLifeVehicleLib resources
	CCarLifeLib *pCCarLifeLib=CCarLifeLib::getInstance();
	pCCarLifeLib->carLifeLibDestory();
	
	return 0;
}

#endif



//cmd channel receive thread
void *cmdReceiveThread(void *arg){
	//register call back
	CCarLifeLib::getInstance()->cmdRegisterProtocolVersionMatchStatus(cmdProtocolVersionMatchStatus);
	CCarLifeLib::getInstance()->cmdRegisterMDInfro(cmdMDInfro);
	CCarLifeLib::getInstance()->cmdRegisterMDBTPairInfro(cmdMDBTPairInfro);
	CCarLifeLib::getInstance()->cmdRegisterVideoEncoderInitDone(cmdVideoEncoderInitDone);
	CCarLifeLib::getInstance()->cmdRegisterVideoEncoderFrameRateChangeDone(cmdVideoEncoderFrameRateChangeDone);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeIncoming(cmdTelStateChangeIncoming);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeOutGoing(cmdTelStateChangeOutGoing);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeIdle(cmdTelStateChangeIdle);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeInCalling(cmdTelStateChangeInCalling);
	CCarLifeLib::getInstance()->cmdRegisterScreenOn(cmdScreenOn);
	CCarLifeLib::getInstance()->cmdRegisterScreenOff(cmdScreenOff);
	CCarLifeLib::getInstance()->cmdRegisterScreenUserPresent(cmdScreenUserPresent);
	CCarLifeLib::getInstance()->cmdRegisterForeground(cmdForeground);
	CCarLifeLib::getInstance()->cmdRegisterBackground(cmdBackground);
	CCarLifeLib::getInstance()->cmdRegisterGoToDeskTop(cmdGoToDeskTop);
	CCarLifeLib::getInstance()->cmdRegisterMicRecordWakeupStart(cmdMicRecordWakeupStart);
	CCarLifeLib::getInstance()->cmdRegisterMicRecordEnd(cmdMicRecordEnd);
	CCarLifeLib::getInstance()->cmdRegisterMicRecordRecogStart(cmdMicRecordRecogStart);
	//0x00010026
	CCarLifeLib::getInstance()->cmdRegisterModuleStatus(cmdModuleStatus);
	//0x00010030
	CCarLifeLib::getInstance()->cmdRegisterNaviNextTurnInfo(cmdNaviNextTurnInfo);
	//0x00010031
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribe(cmdCarDataSubscribe);	
	//0x00010033
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribeStart(cmdCarDataSubscribeStart);
	//0x00010034
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribeStop(cmdCarDataSubscribeStop);
	//0x00010035
	CCarLifeLib::getInstance()->cmdRegisterMediaInfo(cmdMediaInfo);
	//0x00010036
	CCarLifeLib::getInstance()->cmdRegisterMediaProgressBar(cmdMediaProgressBar);
	//0x00010037
	CCarLifeLib::getInstance()->cmdRegisterConnectException(cmdRegisterConnectException);
	//0x00010038
	CCarLifeLib::getInstance()->cmdRegisterRequestGoToForeground(cmdRegisterRequestGoToForeground);
	//0x00010039
	CCarLifeLib::getInstance()->cmdRegisterUIActionSound(cmdRegisterUIActionSound);

	//0x00010049 
	CCarLifeLib::getInstance()->cmdRegisterMdAuthenResponse(cmdRegisterMdAuthenResponse);

	//0x00010051
	CCarLifeLib::getInstance()->cmdRegisterFeatureConfigRequest(cmdRegisterFeatureConfigRequest);

	//0x00010057
	CCarLifeLib::getInstance()->cmdRegisterVideoEncoderJPEGAck(cmdRegisterVideoEncoderJPEGAck);

	//0x00010058(Deprecated)

	//0x00010059
	CCarLifeLib::getInstance()->cmdRegisterMdExit(cmdRegisterMdExit);

	while(1){
		//receive data from command channel
		if(-1==CCarLifeLib::getInstance()->cmdReceiveOperation()){

			cout<<"command channel receive thread exit!"<<endl;
			g_isConnected = 0;	
			break;
			}
	}
}

//video channel receive thread



void *videoReceiveThread(void *arg){
	CCarLifeLib::getInstance()->videoRegisterDataReceive(videoDataReceive);
	CCarLifeLib::getInstance()->videoRegisterHeartBeat(videoHeartBeat);

	while(1){
		if(-1==CCarLifeLib::getInstance()->videoReceiveOperation()){
			g_isConnected = 0;
			cout<<"video channel receive thread exit!"<<endl;
			break;
		}
	}
}

//media channel receive tread
void *mediaReceiveThread(void *arg){
	CCarLifeLib::getInstance()->mediaRegisterInit(mediaInit);
	CCarLifeLib::getInstance()->mediaRegisterNormalData(mediaNormalData);
	CCarLifeLib::getInstance()->mediaRegisterStop(mediaStop);
	CCarLifeLib::getInstance()->mediaRegisterPause(mediaPause);
	CCarLifeLib::getInstance()->mediaRegisterResume(mediaResume);
	CCarLifeLib::getInstance()->mediaRegisterSeek(mediaSeek);

	while(1){
		if(-1==CCarLifeLib::getInstance()->mediaReceiveOperation()){
			g_isConnected = 0;
			cout<<"media channel thread exit!"<<endl;
			break;
		}
	}
}

//tts channel receive thread
void *ttsReceiveThread(void *arg){
	CCarLifeLib::getInstance()->ttsRegisterInit(ttsInit);
	CCarLifeLib::getInstance()->ttsRegisterNormalData(ttsNormalData);
	CCarLifeLib::getInstance()->ttsRegisterStop(ttsStop);

	while(1){
		if(-1==CCarLifeLib::getInstance()->ttsReceiveOperation()){
			g_isConnected = 0;
			cout<<"tts channel thread exit!"<<endl;
			break;
		}
	}
}

//vr channel receive thread
void *vrReceiveThread(void *arg){
	CCarLifeLib::getInstance()->vrRegisterInit(vrInit);
	CCarLifeLib::getInstance()->vrRegisterNormalData(vrNormalData);
	CCarLifeLib::getInstance()->vrRegisterStop(vrStop);

	while(1){
		if(-1==CCarLifeLib::getInstance()->vrReceiveOperation()){
			g_isConnected = 0;
			cout<<"vr channel thread exit!"<<endl;
			break;
		}
	}
}

/**
 CALLBACK FUNCTION IMPLEMENT
 */
//video channel callback functions

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int write_data_to_file(u8 * data, int len)
{
    #define FILE_PATH    "/tmp/saima.pcm"
	static int total1=0;
	static int total2 = 0;
	static int first = 0;
	static int last = 0;
	static int fd = 0;
	if(0 == first)
	{
		fd = open(FILE_PATH,O_WRONLY|O_CREAT ,077);
		if(fd == -1)
		{
		     cout<<"ERROR opening %s"<<FILE_PATH;
			 total2++;
		     return -1;
		}
		first = 1;
	}

    ssize_t ret = write(fd, data, len);
    if(ret <= 0)
    {
        cout<<"ERROR writing %s"<<FILE_PATH;
		total2++;
        return -1;
    }
	else
	{
		total1 += ret;
		if(total1 / 100000 > last)
		{
			sync();
			last = total1 / 100000;
		}
		cout<<"\write data: "<<total1<<":"<<total2<<" bytes to files"<<endl;
	}
   	//close(fd);
	
	return 0;
	
}
	

void videoDataReceive(u8 *data, u32 len){
	//cout<<"videoDataReceive() is invoked"<<endl;
	//cout<<"\treceive video data: "<<len<<" bytes"<<endl;
	//write_vedio_data(data,len);
	write_fifo((char *)data,len);
/*
	for(int i=0;i<len;i++){
		cout<<data[i]<<" ";
	}

	cout<<endl;
*/
}

void videoHeartBeat(){
	cout<<"videoHeartBeat() is invoked"<<endl;
	cout<<"\tvideo heart beat received!";
}






//media channel callback functions
void mediaInit(S_AUDIO_INIT_PARAMETER *initParam){
	cout<<"mediaInit() is invoked"<<endl;
	cout<<"\tsampleRate: "<<initParam->sampleRate<<endl;
	cout<<"\tchannelConfig: "<<initParam->channelConfig<<endl;
	cout<<"\tsampleFormat: "<<initParam->sampleFormat<<endl;
}

void mediaNormalData(u8 *data, u32 len){
//	cout<<"mediaNormalData() is invoked"<<endl;
//	cout<<"\t wfd receive media data: "<<len<<" bytes"<<endl;

	//write_data_to_file(data, len);
/*
	for(int i=0;i<len;i++){
		cout<<data[i]<<" ";
	}

	cout<<endl;
*/
}

void mediaStop(){
	cout<<"mediaStop() is invoked"<<endl;
	cout<<"\tmedia stop status received!"<<endl;
}

void mediaPause(){
	cout<<"mediaPause() is invoked"<<endl;
	cout<<" \tmedia pause status received!"<<endl;
}

void mediaResume(){
	cout<<"mediaResume() is invoked"<<endl;
	cout<<"\tmedia resume status received!"<<endl;
}

void mediaSeek(){
	cout<<"mediaSeek() is invoked"<<endl;
	cout<<"\tmedia seek status received!"<<endl;
}




//tts channel callback functions
void ttsInit(S_AUDIO_INIT_PARAMETER *initParam){
	cout<<"ttsInit() is invoked"<<endl;
	cout<<"\tsampleRate: "<<initParam->sampleRate<<endl;
	cout<<"\tchannelConfig: "<<initParam->channelConfig<<endl;
	cout<<"\tsampleFormat: "<<initParam->sampleFormat<<endl;
}

void ttsNormalData(u8 *data, u32 len){
	cout<<"ttsNormalData() is invoked"<<endl;
	cout<<"\treceive tts data: "<<len<<" bytes"<<endl;
/*
	for(int i=0;i<len;i++){
		cout<<data[i]<<" ";
	}

	cout<<endl;
*/
}

void ttsStop(){
	cout<<"ttsStop() is invoked"<<endl;
	cout<<"\ttts stop status received!"<<endl;
}


//vr channel callback functions
void vrInit(S_AUDIO_INIT_PARAMETER *initParam){
	cout<<"vrInit() is invoked"<<endl;
	cout<<"\tsampleRate: "<<initParam->sampleRate<<endl;
	cout<<"\tchannelConfig: "<<initParam->channelConfig<<endl;
	cout<<"\tsampleFormat: "<<initParam->sampleFormat<<endl;
}

void vrNormalData(u8 *data, u32 len){
	cout<<"vrNormalData() is invoked"<<endl;
	cout<<"\treceive vr data: "<<len<<" bytes"<<endl;
/*
	for(int i=0;i<len;i++){
		cout<<data[i]<<" ";
	}

	cout<<endl;
*/
}

void vrStop(){
	cout<<"vrStop() is invoked"<<endl;
	cout<<"\tvr stop status received!"<<endl;
}

//cmd channel
void cmdProtocolVersionMatchStatus(S_PROTOCOL_VERSION_MATCH_SATUS* status){
	cout<<"cmdProtocolVersionMatchStatus() is invoked"<<endl;
	cout<<"\tprotocol version match status: "<<status->matchStatus<<endl;
}

void cmdMDInfro(S_MD_INFO* mdInfro){
	cout<<"cmdMDInfro() is invoked"<<endl;
	cout<<"\tos: "<<mdInfro->os<<endl;
	cout<<"\tboard: "<<mdInfro->board<<endl;
	cout<<"\tbootloader: "<<mdInfro->bootloader<<endl;
	cout<<"\tbrand: "<<mdInfro->brand<<endl;
	cout<<"\tcpu_abi: "<<mdInfro->cpu_abi<<endl;
	cout<<"\tcpu_abi2: "<<mdInfro->cpu_abi2<<endl;
	cout<<"\tdevice: "<<mdInfro->device<<endl;
	cout<<"\tdisplay: "<<mdInfro->display<<endl;
	cout<<"\tfingerprint: "<<mdInfro->fingerprint<<endl;
	cout<<"\thardware: "<<mdInfro->hardware<<endl;
	cout<<"\thost: "<<mdInfro->host<<endl;
	cout<<"\tcid: "<<mdInfro->cid<<endl;
	cout<<"\tmanufacturer: "<<mdInfro->manufacturer<<endl;
	cout<<"\tmodel: "<<mdInfro->model<<endl;
	cout<<"\tproduct: "<<mdInfro->product<<endl;
	cout<<"\tserial: "<<mdInfro->serial<<endl;
	cout<<"\tcodename: "<<mdInfro->codename<<endl;
	cout<<"\tincremental: "<<mdInfro->incremental<<endl;
	cout<<"\trelease: "<<mdInfro->release<<endl;
	cout<<"\tsdk: "<<mdInfro->sdk<<endl;
	cout<<"\tsdk_int: "<<mdInfro->sdk_int<<endl;
	
}

void cmdMDBTPairInfro(BTPairInfo* info){
	cout<<"cmdMDBTPairInfro() is invoked"<<endl;
	cout<<"/taddress: "<<info->address<<endl;
	cout<<"/tpassKey: "<<info->passKey<<endl;
	cout<<"/thash: "<<info->hash<<endl;
	cout<<"/trandomizer: "<<info->randomizer<<endl;
	cout<<"/tuuid: "<<info->uuid<<endl;
	cout<<"/tname: "<<info->name<<endl;
	cout<<"/tstatus: "<<info->status<<endl;
}

void cmdVideoEncoderInitDone(S_VIDEO_ENCODER_INIT_DONE* videoEncoderInitDone){
	cout<<"cmdVideoEncoderInitDone() is invoked"<<endl;
	cout<<"\twidth: "<<videoEncoderInitDone->width<<endl;
	cout<<"\theight: "<<videoEncoderInitDone->height<<endl;
	cout<<"\tframeRate: "<<videoEncoderInitDone->frameRate<<endl;
}

void cmdVideoEncoderFrameRateChangeDone(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE* videoEncoderFrameRateChangeDone){
	cout<<"cmdVideoEncoderFrameRateChangeDone() is invoked"<<endl;
	cout<<"\tframeRate: "<<videoEncoderFrameRateChangeDone->frameRate<<endl;
}

void cmdTelStateChangeIncoming(){
	cout<<"cmdTelStateChangeIncoming() is invoked"<<endl;
}

void cmdTelStateChangeOutGoing(){
	cout<<"cmdTelStateChangeOutGoing() is invoked"<<endl;
}

void cmdTelStateChangeIdle(){
	cout<<"cmdTelStateChangeIdle() is invoked"<<endl;
}
void cmdTelStateChangeInCalling(){
	cout<<"cmdTelStateChangeInCalling() is invoked"<<endl;
}

void cmdScreenOn(){
	cout<<"cmdScreenOn() is invoked"<<endl;
}
void cmdScreenOff(){
	cout<<"cmdScreenOff() is invoked"<<endl;
}
void cmdScreenUserPresent(){
	cout<<"cmdScreenUserPresent() is invoked"<<endl;
}

void cmdForeground(){
	cout<<"cmdForeground() is invoked"<<endl;
}

void cmdBackground(){
	cout<<"cmdBackground() is invoked"<<endl;
}

void cmdGoToDeskTop(){
	cout<<"cmdGoToDeskTop() is invoked"<<endl;
}

void cmdMicRecordWakeupStart(){
	cout<<"cmdMicRecordWakeupStart() is invoked"<<endl;
}
void cmdMicRecordEnd(){
	cout<<"cmdMicRecordEnd() is invoked"<<endl;
}

void cmdMicRecordRecogStart(){
	cout<<"cmdMicRecordRecogStart() is invoked"<<endl;
}

//0x00010026
void cmdModuleStatus(S_MODULE_STATUS_LIST_MOBILE*){
	cout<<"cmdModuleStatus is invoked"<<endl;
}

//0x00010030
void cmdNaviNextTurnInfo(S_NAVI_NEXT_TURN_INFO*){
	cout<<"cmdNaviNextTurnInfo is invoked"<<endl;
}

//0x00010031
void cmdCarDataSubscribe(S_VEHICLE_INFO_LIST*){
	cout<<"cmdCarDataSubscribe is invoked"<<endl;
}

//0x00010033
void cmdCarDataSubscribeStart(S_VEHICLE_INFO_LIST*){	
	cout<<"cmdCarDataSubscribeStart is invoked"<<endl;
}

//0x00010034
void cmdCarDataSubscribeStop(S_VEHICLE_INFO_LIST*){
	cout<<"cmdCarDataSubscribeStop is invoked"<<endl;
}

//0x00010035
void cmdMediaInfo(S_MEDIA_INFO* info){
	cout<<"cmdMediaInfo is invoked"<<endl;
	
	cout<<"source= "<<info->source<<endl;
	cout<<"song= "<<info->song<<endl;
	cout<<"artist= "<<info->artist<<endl;
	cout<<"album= "<<info->album<<endl;
	//cout<<"albumArt= "<<info->albumArt<<endl;
	cout<<"duration= "<<info->duration<<endl;
	cout<<"playlistNum= "<<info->playlistNum<<endl;
	cout<<"songId= "<<info->songId<<endl;
	cout<<"mode= "<<info->mode<<endl;
	
	
}

//0x00010036
void cmdMediaProgressBar(S_MEDIA_PROGRESS_BAR*){
	cout<<"cmdMediaProgressBar is invoked"<<endl;
}

//0x00010037
void cmdRegisterConnectException(S_CONNECTION_EXCEPTION*){
	cout<<"cmdRegisterConnectException is invoked"<<endl;
}

//0x00010038
void cmdRegisterRequestGoToForeground(void){
	cout<<"cmdRegisterRequestGoToForeground is invoked"<<endl;
}

//0x00010039
void cmdRegisterUIActionSound(void){
	cout<<"cmdRegisterUIActionSound is invoked"<<endl;
}

//0x00010049
void cmdRegisterMdAuthenResponse(S_AUTHEN_RESPONSE* response){
	cout<<"cmdRegisterMdAuthenResponse is invoked"<<endl;
	cout<<"encryptValue= "<<response->encryptValue<<endl;
}

//0x00010051
void cmdRegisterFeatureConfigRequest(){
	cout<<"cmdRegisterFeatureConfigRequest is invoked"<<endl;

	setFocusUIConfig(1);
	//0x00018052
	CCarLifeLib::getInstance()->cmdFeatureConfigResponse(&configList);
}

//0x00010057
void cmdRegisterVideoEncoderJPEGAck(){
	cout<<"cmdRegisterVideoEncoderJPEGAck is invoked"<<endl;
}

//0x00010058(Deprecated)

//0x00010059
void cmdRegisterMdExit(){
	cout<<"cmdRegisterMdExit is invoked"<<endl;
}






