
/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/mount.h>
#include <cutils/log.h>
#include "Fat.h"

/**
*
*return:    0~ok  1~not ok
***/
int Fat::format(const char *devPath, const char *fsPath)
{
	int result;
	if ((NULL == fsPath) || (NULL == devPath)) {
		ALOGE("fsPath or devPath is null,%s format error\n", fsPath);
		return -1;
	}
	ALOGV("\nformat devpath is %s, fspath is %s\n", devPath, fsPath);

	char tmp[512];
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "umount -l %s", fsPath);
	result = system(tmp);
	if (0 != result) {
		ALOGE("no SD card is mount. fat umount error\n", result);
		return -1;
	}

	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "mkfs.vfat %s", devPath);
	result = system(tmp);
	if (0 != result) {
		ALOGE("%s format err = %d \n", fsPath, result);
		return -1;
	}

	result = mount(devPath, fsPath, "vfat", 0, 0);	//result=0~success
	if (0 != result) {
		ALOGE("fat mount error!!!\n");
		return -1;
	}

	ALOGV("%s format ok\n", fsPath);
	return 0;
}
