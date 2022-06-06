#ifndef __CONNECTMSG_H__
#define __CONNECTMSG_H__

#ifdef __cplusplus
extern "C" {
#endif



typedef enum CARBIT_EVENT_{
	ON_PHONE_CONED,
	ON_PHONE_DISCONED,
    ON_MIRROR_DISCONED,
    ON_MIRROR_START,
    ON_MIRROR_STOP,
    ON_ECStatusMessage,
	ON_PhoneAppHUD,
	ON_PhoneAppInfo,
	ON_CallAction,
	ON_LicenseAuthFail,
	ON_PhoneAppExited,
	ON_SyncPhoneStat,
	ON_ServiceDie,
	ON_AppNotSTARTED,
}CARBIT_EVENT;

typedef enum CARBIT_CMD_{
	CMD_START_MIRROR,
	CMD_STOP_MIRROR,
	CMD_TOUCH_EVENT,
	CMD_SYNC_PHONE_STAT,
	CMD_KEY_EVENT,
	CMD_YL_OPEN_PAGE,
}CARBIT_CMD;
typedef enum CARBIT_ST_{
PHONE_DISCONED,	
PHONE_CONED,
MIRROR_START,
MIRROR_STOP,
}CARBIT_ST;


typedef struct EconMsg {
    int msg;
	int val;
}EconMsg_t;


#define ECON_MSGQ_NAME "/conMsgQ"

#ifdef __cplusplus
}
#endif


#endif //__CONNECTMSG_H__
