#ifndef _WARNHANDLE_H_
#define _WARNHANDLE_H_

using namespace android;
#include <math.h>


struct WarnPlayTypeStr{
	int flag0;
	int flag1;
	int flag2;
	int flag3;
	int flag4;
	int flag5;
	int flag6;
	int flag7;
};



class WarnHandle:public Thread {
public:
	int playType;
	bool mRequestExit;
	pthread_mutex_t 				mWarnhandleMutex;
	pthread_cond_t					mWarnhandleCond;
	
	WarnHandle();
	~WarnHandle();
	
	void startThread();
	bool threadLoop();
	bool warnCapThread();
	void extPlayWarnSound(int type);
	
	
private:
	struct WarnPlayTypeStr WarnPlayType;
	void playWarnSound(int type);
	void cleanWarnTypeFlag();
	
};



#endif
