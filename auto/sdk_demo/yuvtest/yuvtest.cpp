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

#define MODULE_VERSION "V2.0.20220506"

#define PIC_W 1280
#define PIC_H 720
#define INPUT_BMP_PATH "./bike_1280x720_565"
// #define DISP_FMT DISP_FORMAT_YUV420_P
#define DISP_FMT DISP_FORMAT_RGB_565
// #define DISP_FMT DISP_FORMAT_RGB_888

#define BMP_PIC_SIZE (PIC_W * PIC_H * 4)
using namespace android;

typedef struct _disp_param {
    int screen_id;
    int ch_id;
    int lyr_id;
    /* 裁剪窗口crop */
    struct view_info crop = { 0, 0, PIC_W, PIC_H };

    /* 显示窗口sc_win */
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
    printf("yuvtest version:%s\n", MODULE_VERSION);
    HwDisplay* mcd = HwDisplay::getInstance();

    paramStruct_t m_DispMemOps;

    //申请地址
    allocPicMem(&m_DispMemOps, BMP_PIC_SIZE);

    memset((void*)m_DispMemOps.vir, 0, m_DispMemOps.size);

    fillYuvData((void*)m_DispMemOps.vir, m_DispMemOps.size);
    printf("fill data success!\n");
    //设置相关的显示参数
    // /* cvbs out */
    // mcd->hwd_other_screen(0, DISP_OUTPUT_TYPE_TV, DISP_TV_MOD_NTSC);
    // struct view_info frame = {0, 0, 720, 480};
    // struct src_info src    = {PIC_W, PIC_H, DISP_FMT};
    // int layer0 = mcd->aut_hwd_layer_request(&frame, 0, 0, 0);
    // mcd->aut_hwd_layer_set_src(layer0, &src, 0,
    //                            m_DispMemOps.ion_buffer.fd_data.aw_fd);
    // printf("set src success!\n");
    // // 设置图层的zorder值
    // struct view_info rect = {0, 0, 720, 480};
    // mcd->aut_hwd_layer_sufaceview(layer0, &rect);

    // mcd->aut_hwd_layer_set_zorder(layer0, 10);
    // //显示该图层
    // mcd->aut_hwd_layer_open(layer0);

    // /* HDMI out */
    //  mcd->hwd_other_screen(1, DISP_OUTPUT_TYPE_HDMI, DISP_TV_MOD_1080P_50HZ);
    // struct view_info frame1 = { 0, 0, 1920, 1200 };
    // struct src_info src1 = { PIC_W, PIC_H, DISP_FMT };
    // int layer1 = mcd->aut_hwd_layer_request(&frame1, 1, 0, 0);
    // mcd->aut_hwd_layer_set_src(layer1, &src1, 0,
    //     m_DispMemOps.ion_buffer.fd_data.aw_fd);
    // printf("set src success!\n");
    // /* 配置屏幕显示区域 */
    // struct view_info rect1 = { 0, 0, 1920, 1200 };
    // mcd->aut_hwd_layer_sufaceview(layer1, &rect1);
    // // 设置图层的zorder值
    // mcd->aut_hwd_layer_set_zorder(layer1, 30);
    // //显示该图层
    // mcd->aut_hwd_layer_open(layer1);

    /* LCD out */
 
    struct view_info frame1 = { 0, 0, 800, 480 };
    struct src_info src1 = { PIC_W, PIC_H, DISP_FMT };
    int layer1 = mcd->aut_hwd_layer_request(&frame1, 0, 0, 0);
    mcd->aut_hwd_layer_set_src(layer1, &src1, 0,
        m_DispMemOps.ion_buffer.fd_data.aw_fd);
    printf("set src success!\n");
    /* 配置屏幕显示区域 */
    struct view_info rect1 = { 0, 0, 800, 480 };
    mcd->aut_hwd_layer_sufaceview(layer1, &rect1);
    // 设置图层的zorder值
    mcd->aut_hwd_layer_set_zorder(layer1, 30);
    //显示该图层
    mcd->aut_hwd_layer_open(layer1);
    
    getchar();

    //关闭layer0和layer1
    // mcd->aut_hwd_layer_close(layer0);
    mcd->aut_hwd_layer_close(layer1);
    freePicMem(&m_DispMemOps);
    return 0;
}
