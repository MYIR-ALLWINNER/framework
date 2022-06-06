#ifndef __CAMERAFILECFG_H__
#define __CAMERAFILECFG_H__

#define SECTION_CAMERA_PREFIX "camera"

#define CAMERA_KEY_IDX "cur-fileidx"
#define CAMERA_KEY_AUTOSTART "startup"
#define CAMERA_KEY_X 	"horizontal"
#define CAMERA_KEY_Y 	"vertical"
#define CAMERA_KEY_TIME "cycle-time"
#define CAMERA_KEY_DIR  "cur_filedir"

#define CAMERA_KEY_TVOUT  "tvout"

#define CAMERA_KEY_ADAS  "adas_en"
#define CAMERA_KEY_GSEN  "g-sensor"
#define CAMERA_KEY_SND  "sound"
#define CAMERA_KEY_SHUTDOWNTIME  "shutdowntime"
#define CAMERA_KEY_TIMEFMT  "timefmt"

#define CAMERA_KEY_LCDBR  "lcdbr"
#define CAMERA_KEY_CAMBR  "cambr"

#define CAMERA_KEY_LOCK_VIDEO_IDX       "cur-lock-video-idx"
#define CAMERA_KEY_LOCK_VIDEO_MAX       "max-lock-video-idx"
#define CAMERA_KEY_NORMAL_VIDEO_MAX     "max-normal-video-idx"
#define CAMERA_KEY_NORMAL_PIC_IDX       "cur-normal-pic-idx"
#define CAMERA_KEY_NORMAL_PIC_MAX       "max-normal-pic-idx"
#define CAMERA_KEY_LOCK_PIC_IDX         "cur-lock-pic-idx"
#define CAMERA_KEY_LOCK_PIC_MAX         "max-lock-pic-idx"
#define CAMERA_KEY_MONITOR_VIDEO_IDX    "cur-monitor-video-idx"
#define CAMERA_KEY_MOBITOR_VIDEO_MAX    "max-monitor-video-idx"
#define CAMERA_KEY_BUILD_ID             "build-id"
#define CAMERA_KEY_UI_RGB               "ui-rgb"
#define CAMERA_KEY_UI_RED               "ui-red"
#define CAMERA_KEY_UI_GREEN             "ui-green"
#define CAMERA_KEY_UI_BLUE              "ui-blue"
#define CAMERA_KEY_DREAM_ON             "dream-on"
#define CAMERA_KEY_DREAM_TIME           "dream-time"
#define SYSTEM_LCD_BRIGHTNESS           "lcd-brightness"
#define SYSTEM_LCD_AUTO           	"lcd-auto"
#define SYSTEM_MUTE_ON           	"mute-on"
#define SYSTEM_VOLUME           	"volume"
#define CM_MAX_PICTURE_NUM              1024

int config_get_startup(int section);
int config_get_weith(int section);
int config_get_heigth(int section);
int config_get_cyctime(int section);
int config_get_adas(int section);
int config_get_tvout(int section);
int config_get_curfiledir(int section,char* obuf);
int config_get_sound(int section);
int config_get_gsensor(int section);
int config_get_shutdowntime(int section);
int config_get_timefmt(int section);

int config_get_normalpicidx(int section);
int config_get_normalpicmax(int section);
int config_get_normalvideomax(int section);
int config_get_lockpicmax(int section);
int config_get_lockpicidx(int section);
int config_get_lockvideoidx(int section);
int config_get_lockvideomax(int section);
int config_get_buildid(int section, char *buf);
int config_get_uirgb(int section, char *buf);
int config_get_uicolor(int section, int *buf);
int config_get_dreamon(int section);
int config_get_dreamtime(int section);
int config_get_lcd_auto(int section);
int config_get_lcd_brightness(int section);
int config_get_system_mute(int section);
int config_get_system_volume(int section);
int config_get_lcdbr(int section);
int config_set_camfileidx(int section,int idx);
int config_get_cambr(int section);

int config_set_normalpicmax(int section, int maxidx);
int config_set_normalvideomax(int section, int maxidx);
int config_set_lockpicmax(int section, int maxidx);
int config_set_lockvideomax(int section, int maxidx);
int config_set_normalpicidx(int section, int idx);
int config_set_lockpicidx(int section, int  idx);
int config_set_lockvideoidx(int section, int idx);
int config_set_buildid(int section, char *build_id);
int config_set_ui_rgb(int section, char *ui_rgb);
int config_set_dreamon(int section, int flag);
int config_set_dreamtime(int section, int sec);
int config_set_camfileidx(int section, int idx);
int config_set_lcd_auto(int section, int value);
int config_set_lcd_brightness(int section, int value);
int config_set_system_mute(int section, int value);
int config_set_system_volume(int section, int value);
int scan_picture(const char *path, int mCameraId);
int config_get_camfileidx(int section);
int config_set_weith(int section,int with);
int config_set_heigth(int section,int heith);
int config_set_cyctime(int section,int sec);
int config_set_startup(int section,int bootstart);
int config_set_curfiledir(int section,char *buf);
int config_set_tvout(int section,int type);
int config_set_adas(int section,int type);
int config_set_sound(int section,int type);
int config_set_gsensor(int section,int type);

int config_set_shutdowntime(int section,int type);
int config_set_timefmt(int section,int type);
int config_set_lcdbr(int section,int type);
int config_set_cambr(int section,int type);

//}

#endif
