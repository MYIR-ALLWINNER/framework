#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "hwdisp2.h"
#include "sunxiMemInterface.h"

#define LCD_W 1024
#define LCD_H 600
#define PIC_W 800
#define PIC_H 480
#define INPUT_BMP_PATH "./pic_480p"
#define DISP_FMT DISP_FORMAT_BGRA_8888

#define MODULE_VERSION "V2.0.20220506"

#define SCREEN_FB_SIZE (LCD_W * LCD_H * 4)
using namespace android;

typedef struct _disp_param {
    int screen_id;
    int ch_id;
    int lyr_id;
    struct view_info crop = { 0, 0, PIC_W, PIC_H };
    struct view_info sc_win;

    int w;
    int h;
    int zorder;

    int alpha;

    int dmafd;
    int phy;
    int vir;
} disp_param;
disp_param gParam;

/**
 * [releaseDE description]
 * @param param the param of the layer
 */
static void releaseDE(disp_param *param)
{
    android::HwDisplay *gdisp = android::HwDisplay::getInstance();
    if (gdisp == NULL)
    {
        printf("gdisp is NULL");
        return;
    }

    struct view_info frame = {0, 0, param->w, param->h};
    int layer = gdisp->aut_hwd_layer_request(&frame, param->screen_id, param->ch_id, param->lyr_id);
    gdisp->aut_hwd_layer_close(layer);
}

static int freeFb(int sc, int ch, int lyr)
{
    disp_param fb0_param;
    fb0_param.screen_id = sc;
    fb0_param.ch_id = ch;
    fb0_param.lyr_id = lyr;
    fb0_param.w = gParam.w;
    fb0_param.h = gParam.h;
    releaseDE(&fb0_param);
    return 0;
}

int allocPicMem(paramStruct_t* pops, int size)
{
    int iRet = 0;

    iRet = allocOpen(MEM_TYPE_DMA, pops, NULL);
    if (iRet < 0) {
        printf("ion_alloc_open failed\n");
        return iRet;
    }
    pops->size = size;

    iRet = allocAlloc(MEM_TYPE_DMA, pops, NULL);
    if (iRet < 0) {
        printf("allocAlloc failed\n");
        return iRet;
    }
    printf("pops.vir=%p pops.phy=%p dmafd=%d,alloc len=%d\n", pops->vir,
           pops->phy, pops->ion_buffer.fd_data.aw_fd, pops->size);

    return 0;
}

int freePicMem(paramStruct_t* pops)
{
    int iRet = 0;

    allocFree(MEM_TYPE_DMA, pops, NULL);

    return 0;
}

static int fillYuvData(void* ptr, int size)
{
    char yuvfile[64];
    sprintf(yuvfile, INPUT_BMP_PATH);

    FILE* inputfd = fopen(yuvfile, "rb");
    if (NULL == inputfd) {
        printf("fopen %s failed\n", yuvfile);
    } else {
        printf("fopen %s OK\n", yuvfile);
    }
    /* Skip the header if the image is a standard BMP file */
    // fseek(inputfd, 54, SEEK_SET);
    fread(ptr, size, 1, inputfd);
    fclose(inputfd);
    return 0;
}



int main(int argc, char** argv)
{

    printf("alpha test version:%s\n", MODULE_VERSION);

    HwDisplay *mcd = HwDisplay::getInstance();
    paramStruct_t m_DispMemOps;

    freeFb(0,1,0);

    /* alloc memory */
    allocPicMem(&m_DispMemOps, SCREEN_FB_SIZE);
    memset((void*)m_DispMemOps.vir, 0, m_DispMemOps.size);
    fillYuvData((void*)m_DispMemOps.vir, m_DispMemOps.size);
    printf("fill data success!\n");

    /* set the pram of layer0 */
    struct view_info frame = {0, 0, 800, 480};
    struct src_info src = {PIC_W, PIC_H, DISP_FMT};
    int layer = mcd->aut_hwd_layer_request(&frame, 0, 0, 0);
    mcd->aut_hwd_layer_set_src(layer, &src, 0,
                               m_DispMemOps.ion_buffer.fd_data.aw_fd);
    printf("set src success!\n");
    struct view_info rect = {0, 0, 400, 240};
    mcd->aut_hwd_layer_sufaceview(layer, &rect);
    mcd->aut_hwd_layer_set_zorder(layer, 10);
    mcd->aut_hwd_layer_set_alpha(layer, 1, 255);
    mcd->aut_hwd_layer_open(layer);

    /* set the pram of layer0 */
    struct view_info frame1 = { 0, 0, 800, 480 };
    struct src_info src1 = { PIC_W, PIC_H, DISP_FMT };
    int layer1 = mcd->aut_hwd_layer_request(&frame1, 0, 1, 0);
    mcd->aut_hwd_layer_set_src(layer1, &src1, 0,
        m_DispMemOps.ion_buffer.fd_data.aw_fd);
    printf("set src success!\n");
    struct view_info rect1 = { 200, 200, 400, 240 };
    mcd->aut_hwd_layer_sufaceview(layer1, &rect1);
    mcd->aut_hwd_layer_set_zorder(layer1, 50);
    mcd->aut_hwd_layer_set_alpha(layer1, 1 ,100);
    mcd->aut_hwd_layer_open(layer1);

    getchar();

    /* close the layers and release memory */
    mcd->aut_hwd_layer_close(layer);
    mcd->aut_hwd_layer_close(layer1);
    freePicMem(&m_DispMemOps);

    return 0;
}
