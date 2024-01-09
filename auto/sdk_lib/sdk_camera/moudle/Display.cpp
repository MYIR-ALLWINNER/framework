/***************************************
FileName:
Copyright:
Author:
Description:
***************************************/
#define LOG_TAG "Display"
#include <sdklog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/time.h>
#include "Display.h"

/************Macro*********************/

/************Variable******************/

/************Function******************/
#ifdef DMAFD_TEST
int egl_param[4];
extern "C" int create_textture(void *param);
extern "C" int info_aframe(int *dmafd);
//extern "C" int infoGlExit();
#endif


/**************************************
Function:
Description:
***************************************/
void DisplayInit(int mode,int cameraid)
{
    HwDisplay *mcd = NULL;
    int screen = 0;
    int vsync_enable =1;

    mcd = HwDisplay::getInstance();
    mcd->aut_hwd_vsync_enable(screen, vsync_enable);

    switch (mode)
    {
    case DISP_GET_CONFIG:
        mode = config_get_tvout(cameraid);
        mcd->hwd_screen1_mode(mode);
        break;
    case DISP_TV_ONLY:
        mcd->hwd_tvout();
        break;
    case DISP_YUV_PIC:
        mode = config_get_tvout(cameraid);
        mcd->hwd_screen1_mode(mode);
        DisplayShowPic(mcd);
        break;
    default:
        mcd->hwd_screen1_mode(mode);
        break;
    }
    //tvmode:0x0b~pal_TV  0x0e~ntsc_TV   0x05~720pHDMI  0x09~1080pHDMI
    ALOGD("tvmode =%d", mode);

#ifdef DMAFD_TEST
    egl_param[0] = 1280;
    egl_param[1] = 800;
    if (360 == cameraid) {
        egl_param[2] = config_get_width(cameraid);
        egl_param[3] = config_get_heigth(cameraid);
    } else {
        egl_param[2] = config_get_width(cameraid);
        egl_param[3] = config_get_heigth(cameraid);
    }
    create_textture((void *)&egl_param);
#endif
}

/**************************************
Function:
Description: show pic
***************************************/
void DisplayShowPic(HwDisplay* mcd)
{
    struct ScMemOpsS* dispmemops = MemAdapterGetOpsS();
    int video_layer0=0;

    int ret = CdcMemOpen(dispmemops);

    if (ret < 0) {
        ALOGE("ion_alloc_open failed");
        return ;
    }
    unsigned long disp_vaddr= (unsigned long)CdcMemPalloc(dispmemops, (DISP_PIC_W*DISP_PIC_H*4+0xfff) & ~0xfff, NULL, NULL);
    unsigned long disp_paddr=(unsigned long)CdcMemGetPhysicAddressCpu(dispmemops,(void*)disp_vaddr);
    char  filename[64];
    //sprintf(filename,"/mnt/sdcard/mmcblk1p1/%s",PIC_NAME);
    sprintf(filename,"/tmp/%s",DISP_PIC_NAME);

    FILE *fpff = fopen(filename,"rb");
    if (NULL == fpff) {
        fpff = fopen(filename,"rb");
        if (NULL == fpff) {
            ALOGE("fopen %s ERR ",filename);
        } else {
            ALOGE("fopen %s OK ",filename);
            fread((void *)disp_vaddr, 1, DISP_PIC_W*DISP_PIC_H*3/2, fpff);
            fclose(fpff);
        }
    } else {
        ALOGD("fopen %s OK ",filename);
        fread((void *)disp_vaddr, 1, DISP_PIC_W*DISP_PIC_H*3/2, fpff);
        fclose(fpff);
    }

    struct view_info surface0={0,0,1024,600};
    struct src_info src={DISP_PIC_W,DISP_PIC_H,DISP_FORMAT_YUV420_SP_VUVU};
    ALOGD("layer_request  layer0 ");
    video_layer0=mcd->aut_hwd_layer_request(&surface0,0,0,0);

    mcd->aut_hwd_layer_set_src(video_layer0,&src,(unsigned long)&disp_paddr);
    mcd->aut_hwd_layer_set_zorder(video_layer0,4);

    mcd->aut_hwd_layer_set_alpha(video_layer0,1,0xff);

    mcd->aut_hwd_layer_sufaceview(video_layer0,&surface0);

    mcd->aut_hwd_layer_open(video_layer0);

    mcd->aut_hwd_layer_render(video_layer0, (void *)&disp_paddr,0);
    ALOGD("aut_hwd_layer_render video_layer0");
    sleep(3000);
    CdcMemPfree(dispmemops, (void *)disp_vaddr,NULL,NULL);
    CdcMemClose(dispmemops);
    while(1);
}

void DisplayExit(void)
{
#ifdef DMAFD_TEST
    //infoGlExit();
#endif
}

/**************************************
end
***************************************/
