
/*
 * \file        CameraFileCfg.cpp
 * \brief
 *
 * \version     1.0.0
 * \date        2017
 * \author       
 *
 * Copyright (c) 2012 Allwinner Technology. All Rights Reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CameraFileCfg.h"
#include "aw_ini_parser.h"
#include <sdklog.h>

int config_get_curfiledir(int section, char *obuf)
{
	if (obuf == NULL) {
		ALOGE("config_get_curfiledir obuf err\n");
		return -1;
	}
	ALOGV("config_get_curfiledir\n");

	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);
	if (get_ini_value(sectbuf, CAMERA_KEY_DIR, &val) == -1) {
		ALOGE("config_get_curfiledir get value err\n");
		return -2;
	}
	else {
		if (val.type == VALUE_TYPE_STR) {
			//printf("get a ini value str:%s\n", val.val.str);
			strcpy(obuf, val.val.str);
			ALOGV("get a ini value ostr:%s\n", obuf);
		}
		else if (val.type == VALUE_TYPE_NUM) {
			ALOGV("config_get_curfiledir value num:%d\n", val.val.num);
			return -3;
		}
		else {
			ALOGV("config_get_curfiledir unknown:%d\n", val.type);

			strcpy(obuf, val.val.str);
			ALOGV("get a ini value ostr:%s\n", obuf);
			return -4;
		}
	}

	return 0;
}

int config_get_camfileidx(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_IDX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("get a ini value num:%d\n", val.val.num);

	}

	return ret;
}

int config_get_startup(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_AUTOSTART, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_startup value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_weith(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_X, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_weith value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_heigth(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_Y, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_heigth value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_cyctime(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_TIME, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_cyctime value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_tvout(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_TVOUT, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_tvout value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_adas(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_ADAS, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_adas value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_gsensor(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_GSEN, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_gsensor value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_sound(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_SND, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_sound value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_shutdowntime(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_SHUTDOWNTIME, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_sound value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_timefmt(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_TIMEFMT, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_sound value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_lcdbr(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_LCDBR, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_sound value num:%d\n", val.val.num);

	}
	return ret;
}

int config_get_cambr(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_CAMBR, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_sound value num:%d\n", val.val.num);

	}
	return ret;
}

int config_set(const char *section, const char *key, char *ibuf)
{
	struct val_st val;

	val.type = VALUE_TYPE_STR;
	snprintf(val.val.str, ASCIILINESZ + 1, "%s", ibuf);
	ALOGV("val.val.str:%s\n", val.val.str);

	return set_ini_value(section, key, &val);
}

int config_set_camfileidx(int section, int idx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", idx);
	return config_set(sectbuf, CAMERA_KEY_IDX, buf);

}

int config_get_recfileidx(int section, int camno)
{
	struct val_st val;
	char buf2[32];

	sprintf(buf2, "%s,%d", CAMERA_KEY_IDX, camno);
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, buf2, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("get a ini value num:%d\n", val.val.num);

	}

	return ret;
}


//NORMAL_PIC_IDX
int config_get_normalpicidx(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_NORMAL_PIC_IDX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_normalpicidx value num:%d\n", val.val.num);

	}
	return ret;
}

//LOCK_PIC_IDX
int config_get_lockpicidx(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_LOCK_PIC_IDX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_lockpicidx value num:%d\n", val.val.num);

	}
	return ret;
}

//LOCK_VIDEO_IDX
int config_get_lockvideoidx(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_LOCK_VIDEO_IDX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_lockvideoidx value num:%d\n", val.val.num);

	}
	return ret;
}

//MAX_NORMAL_PIC
int config_get_normalpicmax(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_NORMAL_PIC_MAX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxnormalpicidx value num:%d\n", val.val.num);

	}
	return ret;
}

//MAX_LOCK_PIC
int config_get_lockpicmax(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_LOCK_PIC_MAX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxlockpicidx value num:%d\n", val.val.num);

	}
	return ret;
}

//MAX_NORMAL_VIDEO
int config_get_normalvideomax(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_NORMAL_VIDEO_MAX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxnormalvideoidx value num:%d\n", val.val.num);

	}
	return ret;
}

//MAX_LOCK_VIDEO
int config_get_lockvideomax(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_LOCK_VIDEO_MAX, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxlockvideoidx value num:%d\n", val.val.num);

	}
	return ret;
}

//BUILD_ID
int config_get_buildid(int section, char *buf)
{
	if (NULL == buf)
		return -1;
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_BUILD_ID, &val) == -1) {
		return -1;
	}
	if (val.type == VALUE_TYPE_STR) {
		sprintf(buf, "%s", val.val.str);
		ALOGV("config_get_build_id value str:%s\n", val.val.str);
		return 0;
	}
	return -1;
}

//UI_RGB
int config_get_uirgb(int section, char *buf)
{
	if (NULL == buf)
		return -1;
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_UI_RGB, &val) == -1) {
		return -1;
	}
	if (val.type == VALUE_TYPE_STR) {
		sprintf(buf, "%s", val.val.str);
		ALOGV("config_get_ui_rgb value str:%s\n", val.val.str);
		return 0;
	}
	return -1;
}

//UI_COLOR
int config_get_uicolor(int section, int *buf)
{
	if (NULL == buf)
		return -1;
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_UI_RED, &val) == -1) {
		return -1;
	}
	if (val.type == VALUE_TYPE_NUM) {
		//sprintf(buf, "%s",val.val.str);
		buf[0] = val.val.num;
		ALOGV("config_get_ui_color red value:%d\n", val.val.num);
	}

	if (get_ini_value(sectbuf, CAMERA_KEY_UI_GREEN, &val) == -1) {
		return 1;
	}
	if (val.type == VALUE_TYPE_NUM) {
		//sprintf(buf, "%s",val.val.str);
		buf[1] = val.val.num;
		ALOGV("config_get_ui_color green value:%d\n", val.val.num);
	}

	if (get_ini_value(sectbuf, CAMERA_KEY_UI_BLUE, &val) == -1) {
		return 2;
	}
	if (val.type == VALUE_TYPE_NUM) {
		//sprintf(buf, "%s",val.val.str);
		buf[2] = val.val.num;
		ALOGV("config_get_ui_color blue value:%d\n", val.val.num);
		return 3;
	}

	return -1;
}

//DREAM_ON
int config_get_dreamon(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_DREAM_ON, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxlockvideoidx value num:%d\n", val.val.num);

	}
	return ret;
}

//DREAM_TIME
int config_get_dreamtime(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, CAMERA_KEY_DREAM_TIME, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_maxlockvideoidx value num:%d\n", val.val.num);

	}
	return ret;
}

//LCD_AUTO
int config_get_lcd_auto(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, SYSTEM_LCD_AUTO, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_lcd_auto value num:%d\n", val.val.num);

	}
	return ret;
}

//LCD_BRIGHTNESS
int config_get_lcd_brightness(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, SYSTEM_LCD_BRIGHTNESS, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_lcd_brightness value num:%d\n", val.val.num);

	}
	return ret;
}

//SYSTEM_VOLUME
int config_get_system_volume(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, SYSTEM_VOLUME, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_system_volume value num:%d\n", val.val.num);

	}
	return ret;
}

//SYSTEM_MUTE
int config_get_system_mute(int section)
{
	struct val_st val;
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	if (get_ini_value(sectbuf, SYSTEM_MUTE_ON, &val) == -1) {
		return 0;
	}
	int ret;
	if (val.type == VALUE_TYPE_NUM) {
		ret = val.val.num;
		ALOGV("config_get_system_mute_on value num:%d\n", val.val.num);

	}
	return ret;
}

/********************set config**********************/

//SET LCD_AUTO
int config_set_lcd_auto(int section, int value)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", value);
	return config_set(sectbuf, SYSTEM_LCD_AUTO, buf);
}

//SET LCD_BRIGHTNESS
int config_set_lcd_brightness(int section, int value)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", value);
	return config_set(sectbuf, SYSTEM_LCD_BRIGHTNESS, buf);
}

//SET SYSTEM_VOLUME 
int config_set_system_volume(int section, int value)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", value);
	return config_set(sectbuf, SYSTEM_VOLUME, buf);
}

//SET SYSTEM_MUTE
int config_set_system_mute(int section, int value)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", value);
	return config_set(sectbuf, SYSTEM_MUTE_ON, buf);
}

//SET DREAM_ON
int config_set_dreamon(int section, int flag)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", flag);
	return config_set(sectbuf, CAMERA_KEY_DREAM_ON, buf);

}

//SET DREAM_TIME
int config_set_dreamtime(int section, int sec)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", sec);
	return config_set(sectbuf, CAMERA_KEY_DREAM_TIME, buf);

}

//SET NORMAL_PIC_IDX
int config_set_normalpicidx(int section, int idx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", idx);
	return config_set(sectbuf, CAMERA_KEY_NORMAL_PIC_IDX, buf);

}

//SET NORMAL_PIC_MAX
int config_set_normalpicmax(int section, int maxidx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", maxidx);
	return config_set(sectbuf, CAMERA_KEY_NORMAL_PIC_MAX, buf);

}

//SET LOCK_PIC_IDX
int config_set_lockpicidx(int section, int idx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", idx);
	return config_set(sectbuf, CAMERA_KEY_LOCK_PIC_IDX, buf);

}

//SET LOCK_PIC_MAX
int config_set_lockpicmax(int section, int maxidx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", maxidx);
	return config_set(sectbuf, CAMERA_KEY_LOCK_PIC_MAX, buf);

}

//SET LOCK_VIDEO_IDX
int config_set_lockvideoidx(int section, int idx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", idx);
	//ALOGW("config_set_lockvideoidx value %d\n", idx);
	return config_set(sectbuf, CAMERA_KEY_LOCK_VIDEO_IDX, buf);

}

//SET LOCK_VIDEO_MAX
int config_set_lockvideomax(int section, int maxidx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", maxidx);
	return config_set(sectbuf, CAMERA_KEY_LOCK_VIDEO_MAX, buf);

}

//SET NORMAL_VIDEO_MAX
int config_set_normalvideomax(int section, int maxidx)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", maxidx);
	return config_set(sectbuf, CAMERA_KEY_NORMAL_VIDEO_MAX, buf);

}

//SET BUILD_ID
int config_set_buildid(int section, char *build_id)
{
	if (NULL == build_id)
		return -1;

	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%s", build_id);
	return config_set(sectbuf, CAMERA_KEY_BUILD_ID, buf);

}

//SET UI_RGB
int config_set_uirgb(int section, char *ui_rgb)
{
	if (NULL == ui_rgb)
		return -1;

	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%s", ui_rgb);
	return config_set(sectbuf, CAMERA_KEY_UI_RGB, buf);

}


int config_set_recfileidx(int section, int camno, int idx)
{
	char buf[32];
	char buf2[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", idx);
	sprintf(buf2, "%s,%d", CAMERA_KEY_IDX, camno);
	return config_set(sectbuf, buf2, buf);

}

int config_set_curfiledir(int section, char *buf)
{
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	return config_set(sectbuf, CAMERA_KEY_DIR, buf);
}

int config_set_startup(int section, int bootstart)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", bootstart);
	return config_set(sectbuf, CAMERA_KEY_AUTOSTART, buf);

}

int config_set_weith(int section, int with)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", with);
	return config_set(sectbuf, CAMERA_KEY_X, buf);

}

int config_set_heigth(int section, int heith)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", heith);
	return config_set(sectbuf, CAMERA_KEY_Y, buf);

}

int config_set_cyctime(int section, int sec)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", sec);
	return config_set(sectbuf, CAMERA_KEY_TIME, buf);

}

int config_set_tvout(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_TVOUT, buf);

}

int config_set_adas(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_ADAS, buf);

}

int config_set_gsensor(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_GSEN, buf);

}

int config_set_sound(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_SND, buf);

}

int config_set_shutdowntime(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_SHUTDOWNTIME, buf);

}

int config_set_timefmt(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_TIMEFMT, buf);

}

int config_set_lcdbr(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_LCDBR, buf);

}

int config_set_cambr(int section, int type)
{
	char buf[32];
	char sectbuf[32];
	sprintf(sectbuf, "%s%d", SECTION_CAMERA_PREFIX, section);

	sprintf(buf, "%d", type);
	return config_set(sectbuf, CAMERA_KEY_CAMBR, buf);

}
