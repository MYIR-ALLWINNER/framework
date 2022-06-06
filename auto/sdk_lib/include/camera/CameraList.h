#ifndef __CAMERA_LIST_H__
#define __CAMERA_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sdklog.h>

#define CAMERA_LIST_KEY_CONFIG_PATH "/system/etc/cameralist.cfg"

#define KEY_LIST_LENGTH 8192

#define kCAMERA_LIST                    "key_camera_list"
//#define kCAMERA_EXIF_MODEL                    "key_camera_exif_model"

//#define DBG_ENABLE 1

#if  DBG_ENABLE
#define LOGE ALOGE
#define LOGD ALOGD
#define LOGI ALOGI
#define LOGW ALOGW
#define LOGF ALOGW
#define LOGV ALOGV

#else
#ifndef LOGE
#define LOGE(...)				// __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGF(...)
#define LOGV(...)
#endif
#endif

class CameraList {
  public:
	CameraList();
	~CameraList();
	char mCameraDeviceList[KEY_LIST_LENGTH];

  private:
	 bool readKey(char *key, char *value);
	void getValue(char *line, char *value);
	bool usedKey(char *value);

	FILE *mhKeyFile;

};

#endif // __CAMERA_LIST_H__
