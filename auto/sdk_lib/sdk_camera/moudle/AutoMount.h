#ifndef __AUTOMOUNT_H__
#define __AUTOMOUNT_H__

#include "NetlinkManager.h"
#include "NetlinkHandler.h"
#include "NetlinkEvent.h"

#include "DvrFactory.h"

/************Macro*********************/
#define SDCARD_TYPE         "mmcblk1"
#define SDCARD_LEN          7

#define USB_TYPE            "sd"
#define USB_LEN             2

#define SAVE_MAX            10

#define MUTI_PARTS_EN       1
#define RM_PATH_EN          0

extern dvr_factory **ppDvr;

extern dvr_factory *pdvr1;
extern dvr_factory *pdvr2;
extern dvr_factory *pdvr3;
extern dvr_factory *pdvr4;

/************Function******************/
void AutoMountInit(void *usrdata);
void AutoMountCallback(NetlinkEvent * evt, void *usrdata);
void enhanceUsbStability(NetlinkEvent *evt);

#endif