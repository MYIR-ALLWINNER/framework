#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "hwdisp2.h"
#include "DvrFactory.h"
#include "CameraFileCfg.h"
#include "CameraHardware2.h"

/************Macro*********************/
#define DISP_GET_CONFIG		0
#define DISP_TV_PAL				1	//720*576
#define DISP_TV_NTSC			2	//720*480
#define DISP_HDMI_1280_720		3	// 720P_60HZ 
#define DISP_HDMI_1920_1080	4	// 1080P_50HZ

#define DISP_TV_ONLY			5	// 1080P_50HZ

#define DISP_YUV_PIC			6	// 

#define DISP_PIC_W 				720
#define DISP_PIC_H 				1280
#define DISP_PIC_NAME 			"test.yuv"

/************Function******************/
void DisplayInit(int mode,int cameraid);
void DisplayShowPic(HwDisplay* mcd);
void DisplayExit(void);

#endif