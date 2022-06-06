
//#include "CameraDebug.h"
//#if DBG_CAMERA_CONFIG
//#define LOG_NDEBUG 0
//#endif
#define LOG_TAG "CameraList"
#include <cutils/log.h>

#include "CameraList.h"

CameraList::CameraList()
:	mhKeyFile(0)
{
	mhKeyFile =::fopen(CAMERA_LIST_KEY_CONFIG_PATH, "rb");
	if (mhKeyFile == NULL) {
		LOGV("open file %s failed", CAMERA_LIST_KEY_CONFIG_PATH);
		return;
	}
	else {
		LOGV("open file %s OK", CAMERA_LIST_KEY_CONFIG_PATH);
	}

	readKey(kCAMERA_LIST, mCameraDeviceList);
	LOGV("CameraList: %s", mCameraDeviceList);
}

CameraList::~CameraList()
{
	if (mhKeyFile != 0) {
		::fclose(mhKeyFile);
		mhKeyFile = 0;
		LOGD("Close file %s OK", CAMERA_LIST_KEY_CONFIG_PATH);
	}
}

bool CameraList::usedKey(char *value)
{
	return strcmp(value, "1") ? false : true;
}

void CameraList::getValue(char *line, char *value)
{
	char *ptemp = line;
	while (*ptemp) {
		if (*ptemp++ == '=') {
			break;
		}
	}

	char *pval = ptemp;
	char *seps = " \n\r\t";
	int offset = 0;
	//pval = strtok(pval, seps);
	while (pval != NULL) {
		strncpy(value + offset, pval, strlen(pval));
		offset += strlen(pval);
		pval = strtok(NULL, seps);
	}
	*(value + offset) = 0;
}

bool CameraList::readKey(char *key, char *value)
{
	bool bRet = false;
	char str[KEY_LIST_LENGTH];

	if (key == 0 || value == 0) {
		LOGV("error input para");
		return false;
	}

	if (mhKeyFile == 0) {
		//LOGV("error key file handle");
		return false;
	}

	fseek(mhKeyFile, 0L, SEEK_SET);

	memset(str, 0, KEY_LIST_LENGTH);
	while (fgets(str, KEY_LIST_LENGTH, mhKeyFile)) {
		if (!strncmp(key, str, strlen(key))) {
			getValue(str, value);

			bRet = true;
			break;
		}
		memset(str, 0, KEY_LIST_LENGTH);
	}

	return bRet;
}
