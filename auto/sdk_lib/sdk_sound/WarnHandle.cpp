#include <sys/socket.h>
#include <sys/un.h>
#include <utils/Thread.h>
#include <type_compat.h>
#include<sys/ioctl.h>
#include <signal.h>
#include <pthread.h>
#include "WarnHandle.h"

WarnHandle::WarnHandle():
		Thread(false),
		playType(0),
		mRequestExit(false)
{
	pthread_mutex_init(&mWarnhandleMutex, NULL);
	pthread_cond_init(&mWarnhandleCond, NULL);
	startThread();
}

WarnHandle::~WarnHandle()
{
	
}


void WarnHandle::startThread() {
	run("WarnHandle", PRIORITY_NORMAL);
}


bool WarnHandle::threadLoop() {
	if (mRequestExit)
	{
		return false;
	}

	return warnCapThread();
} 

bool WarnHandle::warnCapThread()
{
	while(1){
		pthread_mutex_lock(&mWarnhandleMutex);
		pthread_cond_wait(&mWarnhandleCond, &mWarnhandleMutex);
		pthread_mutex_unlock(&mWarnhandleMutex);
		
		//printf(">>>> WarnCapThread >>> \n");
		
		playWarnSound(playType);
	}
}


void WarnHandle::extPlayWarnSound(int type)
{
	//printf(">>>> extPlayWarnSound >>> \n");
	
	playType=type;
	pthread_mutex_lock(&mWarnhandleMutex);
	pthread_cond_signal(&mWarnhandleCond);
	pthread_mutex_unlock(&mWarnhandleMutex);
}



void WarnHandle::playWarnSound(int type)
{
	switch(type){
		case 0:
			if(WarnPlayType.flag0==0){
				WarnPlayType.flag0=1;

				//printf(">>>> flag0 >>> \n");
				system("tinyplay  /wave/yanwu.wav -D 0 -d 0 -p 1280 -n 4");
			}
			break;
		case 1:
			if(WarnPlayType.flag1==0){
				WarnPlayType.flag1=1;
				//printf(">>>> flag1 >>> \n");
				system("tinyplay  /wave/didi.wav -D 0 -d 0 -p 1280 -n 4");
			}	
			break;
		default:
			break;
	}
	
	cleanWarnTypeFlag();
	
}


void WarnHandle::cleanWarnTypeFlag()
{
	WarnPlayType.flag0=0;	
	WarnPlayType.flag1=0;
	WarnPlayType.flag2=0;
	WarnPlayType.flag3=0;
	
	WarnPlayType.flag4=0;
	WarnPlayType.flag5=0;
	WarnPlayType.flag6=0;
	WarnPlayType.flag7=0;
}
		
		
		
