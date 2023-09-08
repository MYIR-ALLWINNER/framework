
#include "CameraDebug.h"
#if DBG_PREVIEW
#define LOG_NDEBUG 0
#endif
#define LOG_TAG "PreviewWindow"
#include <sdklog.h>

#include <ui/Rect.h>
#include "V4L2CameraDevice2.h"
#include "PreviewWindow.h"

#include "G2dApi.h"

#ifndef DMAFD_TEST
// 使用硬件图层显示视频的每一帧
#define USE_DE_LAYER

#else

#include "sunxiMemInterface.h"
extern "C" int info_aframe(int *dmafd);
extern "C" int glReleaseImageKHR(void);
#endif

#define G2D_PROC_ROTATE_FLIP 0
#define USE_DI_INPREVIEW 0
#define USE_VIDEO_PROCESS_BUF 0
#define mMemType MEM_TYPE_CDX_NEW
//#define mMemType MEM_TYPE_DMA

using namespace g2dapi;

namespace android {

#define CAMHAL_GRALLOC_USAGE GRALLOC_USAGE_SW_READ_RARELY | \
                                     GRALLOC_USAGE_SW_WRITE_OFTEN
#define USE_NEW_AUT_DISP 1

void PreviewWindow::PreviewTvOut(HwDisplay* mcd, int screen_id, unsigned int *hlay,
                                    struct view_info *surface,int mode)
{
    if ((NULL == mcd) || (NULL == hlay)) {
        ALOGD("%s input arg error\r\n",__FUNCTION__);
    }

    ALOGD("test_layer%d_tvout_ntsc begin\r\n",screen_id);
    if (mode == DISP_TV_MOD_NTSC) {
        surface->w = 720;
        surface->h = 480;
    } else if(mode == DISP_TV_MOD_PAL) {
        surface->w = 720;
        surface->h = 576;
    }

    mcd->aut_hwd_layer_sufaceview(*hlay, surface);
    mcd->hwd_other_screen(screen_id, DISP_OUTPUT_TYPE_TV, mode);
}

PreviewWindow::PreviewWindow()
  :  mPreviewFrameWidth(0)
    ,mPreviewFrameHeight(0)
    ,mPreviewFrameSize(0)
    ,mDi(NULL)
    ,mDispCnt(0)
    ,mCurPixelFormat(0)
    ,mPreviewEnabled(false)
    ,mShouldAdjustDimensions(true)
    ,isPreviewDispEn(false)
    ,previewSkipCounter(10)
{
    F_LOG;
    mHwDisplay = HwDisplay::getInstance();
    mHwDisplay->aut_hwd_vsync_enable(0, 1);
    memset(&mPreviewMemops, 0, sizeof(dma_mem_des_t));

    int ret = allocOpen(mMemType, &mPreviewMemops, NULL);
    if (ret < 0) {
        ALOGE("ion_alloc_open failed");
    }

    memset(&imgtr, 0, sizeof(tr_obj));

    for (int i = 0; i < DISP_NB_BUFFER; i++) {
        mDispBuff[i].addrPhyY = 0;
        mDispBuff[i].addrVirY = 0;
    }

    mHwDisplay->CameraDispEnableFlag[0] = false;
    mHwDisplay->CameraDispEnableFlag[1] = false;
#if USE_DI_INPREVIEW
    mDi = new DiHandle();
#endif
}
    
PreviewWindow::~PreviewWindow()
{
    F_LOG;

    for (int i = 0; i < DISP_NB_BUFFER; i++) {
        if (mDispBuff[i].addrVirY != 0) {
            mPreviewMemops.vir = mDispBuff[i].addrVirY;
            allocFree(mMemType, &mPreviewMemops, NULL);
            mDispBuff[i].addrPhyY = 0;
            mDispBuff[i].addrVirY = 0;
        }
    }
    mPreviewMemops.size = 0;

    if ((mPreviewMemops.ops != NULL) || (mMemType == mPreviewMemops.memType)){
        int ret = allocClose(mMemType, &mPreviewMemops, NULL);
        if (ret < 0) {
            ALOGE("~PreviewWindow:allocClose MEM_TYPE_CDX_NEW failed");
        }
    }

    if (mDi) {
        delete mDi;
        mDi = NULL;
    }
}

/****************************************************************************
 * Camera API
 ***************************************************************************/
status_t PreviewWindow::setPreviewDisplayOn()
{
    F_LOG
    ALOGD("setPreviewDisplayOn");
    status_t res = NO_ERROR;
    Mutex::Autolock locker(&mObjectLock);
    isPreviewDispEn = true;
    int i;
#if USE_VIDEO_PROCESS_BUF
    mPreviewMemops.size = PBUFFER_SIZE;
    for (i = 0; i < DISP_NB_BUFFER; i++) {
        if (mDispBuff[i].addrVirY == 0) {
            int ret = allocAlloc(mMemType, &mPreviewMemops, NULL);
            if (ret < 0) {
                ALOGE("allocAlloc failed");
            }
            mDispBuff[i].addrVirY  = mPreviewMemops.vir;
            mDispBuff[i].addrPhyY = mPreviewMemops.phy;
            //mDispBuff[i].sharefd = mPreviewMemops.share_data_fd;
            mDispBuff[i].dmafd = mPreviewMemops.ion_buffer.fd_data.aw_fd;
            ALOGD("setPreviewDisplayOn mDispBuff[%d] dmafd:%d vir:0x%lx", i,
                    mDispBuff[i].dmafd, mDispBuff[i].addrVirY);
        }
    }
#endif
    int dmode = 0;//aut_get_disp_rotate_mode();
    if (dmode > 0) {
#if G2D_PROC_ROTATE_FLIP
        imgtr.trfd =g2dInit();
#endif
    }

#ifdef USE_DE_LAYER
    ALOGD("used USE_DE_LAYER");
    mHwDisplay->CameraDispEnableFlag[0] = true;

    HwDisplay* mcd = mHwDisplay;

    mHwlayerScreen0 = mcd->aut_hwd_layer_request(&mvi,0, 0, 0);
    mcd->aut_hwd_layer_set_zorder(mHwlayerScreen0,1);

    mHwlayerScreen1 = mcd->aut_hwd_layer_request(&mvi, 0, 1, 0);
    mcd->aut_hwd_layer_close(mHwlayerScreen1);

    if (mtvout) {
        mHwDisplay->CameraDispEnableFlag[1] = true;

        //----------------------1:video TV OUT CFG-------------------------------
        struct view_info SurfaceTV;

        SurfaceTV.x = 0;
        SurfaceTV.y = 0;
        if (DISP_TV_MOD_NTSC == mtvout) {
            SurfaceTV.w = 720;
            SurfaceTV.h = 480;
        } else {
            SurfaceTV.w = 720;
            SurfaceTV.h = 576;
        }
        mHwlayerScreen1 = mcd->aut_hwd_layer_request(&mcd->Surface[1], 1, 0, 0);

        mcd->aut_hwd_layer_set_zorder(mHwlayerScreen1,1);
        PreviewTvOut(mcd, 1, (unsigned int *)&mHwlayerScreen1, &SurfaceTV, mtvout);

        //----------------------2:ui TV OUT CFG-------------------------------
        //this have a bug,because linux fb have pan display,you must have a timer (10ms eg) in your app to check the base layer crop addr
        // or modify the kernel driver,dor disp pan to swap the base adrr for fb0 layer
        mHwlayerScreen1_ui = mcd->aut_hwd_layer_request(&SurfaceTV, 1, 1, 0);

        disp_layer_config2 fb0Config = mcd->aut_hwd_getLayerConfigWithId(0,1,0);
        mcd->aut_hwd_set_layer_info(mHwlayerScreen1_ui,&fb0Config.info);

        mcd->aut_hwd_layer_set_zorder(mHwlayerScreen1_ui,3);
        PreviewTvOut(mcd, 1, (unsigned int *)&mHwlayerScreen1_ui, &SurfaceTV,DISP_TV_MOD_NTSC);
    }
#endif
    return res;
}

status_t PreviewWindow::setPreviewDisplayOff()
{
    F_LOG;
    ALOGD("setPreviewDisplayOff");
    status_t res = NO_ERROR;
    Mutex::Autolock locker(&mObjectLock);
    isPreviewDispEn = false;

#ifdef USE_DE_LAYER
    mHwDisplay->CameraDispEnableFlag[0] = false;
    if (mHwlayerScreen0 >= 0) {
        mHwDisplay->aut_hwd_layer_close(mHwlayerScreen0);
    }

    if (mtvout) {
        mHwDisplay->CameraDispEnableFlag[1] = false;
        mHwDisplay->aut_hwd_layer_close(mHwlayerScreen1);
        mHwDisplay->aut_hwd_layer_close(mHwlayerScreen1_ui);
    }

#endif

    int dmode = 0;//aut_get_disp_rotate_mode();
    if (dmode > 0) {
#if G2D_PROC_ROTATE_FLIP
        g2dUnit(imgtr.trfd);
#endif
    }
    //heat so guys change the rotate mode during the preview rtime.
    //so check release the buffer out of dmode domain
    int i;
#if USE_VIDEO_PROCESS_BUF
    for (i = 0; i < DISP_NB_BUFFER; i++) {
        if (mDispBuff[i].addrVirY != 0) {
            mPreviewMemops.vir = mDispBuff[i].addrVirY;
            allocFree(mMemType, &mPreviewMemops, NULL);
            //ALOGD("setPreviewDisplayOff mDispBuff[%d]=%d vir=0x%lx",
            //        i,mDispBuff[i].dmafd,mDispBuff[i].addrVirY);
            mDispBuff[i].addrPhyY = 0;
            mDispBuff[i].addrVirY = 0;
            mDispBuff[i].dmafd = 0;
        }
    }
#endif

#ifdef DMAFD_TEST
    //glReleaseImageKHR();
#endif

    mPreviewMemops.size = 0;
    mHwlayerScreen0 = -1;
    mHwlayerScreen1 = -1;

    return res;
}

status_t PreviewWindow::setPreviewParam(struct view_info pvi, struct src_info psi, int tvout,
                                        int tvch)
{
    ALOGD("setPreviewParam view_info(%d,%d,%d,%d), src_info(%d,%d,%d,), tvout:%d, tvch:%d",
            pvi.x, pvi.y, pvi.w, pvi.h,
            psi.w, psi.h, psi.format,
            tvout, tvch);
    mvi = pvi;
    msi = psi;
    mtvout = tvout;
    mtvch = tvch;
}

status_t PreviewWindow::startPreview()
{
    F_LOG;
    Mutex::Autolock locker(&mObjectLock);
    mPreviewEnabled = true;
    return NO_ERROR;
}

void PreviewWindow::stopPreview()
{
    F_LOG;

    Mutex::Autolock locker(&mObjectLock);
    mPreviewEnabled = false;
    mShouldAdjustDimensions = true;
}

#ifdef PREVIRE_SAVEFRAME
static int preview_saveframe(char *str, void *p, int length, int is_oneframe) {
    FILE *fd;

    if (is_oneframe) {
        fd = fopen(str, "wb");
    } else {
        fd = fopen(str, "a");
    }

    if (!fd) {
        ALOGE("Open file error");
        return -1;
    }
    if (fwrite(p, 1, length, fd)) {
        //ALOGD("Write file successfully");
        fclose(fd);
        return 0;
    } else {
        ALOGE("Write file fail");
        fclose(fd);
        return -1;
    }
}
#endif

/****************************************************************************
* Public API
***************************************************************************/
bool PreviewWindow::onNextFrameAvailable(const void *frame, int flipEnable, bool isOview)
{
    //int res;
    Mutex::Autolock locker(&mObjectLock);
    if (!isPreviewDispEn)
        return true;

    V4L2BUF_t *pv4l2_buf = (V4L2BUF_t *) frame;

    // 去掉10帧
    //static int previewSkipCounter = 10;
    if (previewSkipCounter-- > 0) {
        ALOGD("preview start count down:%d", previewSkipCounter);
        return 0;
    }

    //int preview_format = 0;
    //int preview_addr_phy = 0;
    //int preview_addr_vir = 0;
    //int preview_width = 0;
    //int preview_height = 0;
    //RECT_t preview_crop;

    int cur_idx = 0;

    if (!isPreviewEnabled()) {
        return true;
    }


    V4L2BUF_t *pDiBuff = NULL;
    // w>720 is csi camera,csi don't need to do deinterace
    if ((pv4l2_buf->width <= 720) && (mDi)) {
        int ret = mDi->DiHandleInit( pv4l2_buf->width, pv4l2_buf->height);
        if (ret < 0) {
            delete mDi;
            mDi = NULL;
        }
        pDiBuff = mDi->DiProcessLoop(pv4l2_buf,0,0);
        if (NULL == pDiBuff) {
            ALOGD("Dihandle failed,use this origin data cam [%d]w[%d] h[%d]\n",pv4l2_buf->thumbFormat,pv4l2_buf->width, pv4l2_buf->height);
        } else {
            ALOGD("Dihandle success\n");
            pv4l2_buf = pDiBuff;
        }
    }

    struct src_info src;
    src.w = pv4l2_buf->width;
    src.h = pv4l2_buf->height;
    cur_idx = pv4l2_buf->index % DISP_NB_BUFFER;
    struct view_info crop ={ (int)pv4l2_buf->crop_rect.left, (int)pv4l2_buf->crop_rect.top,
                    (int)pv4l2_buf->crop_rect.width,(int)pv4l2_buf->crop_rect.height };

#ifdef PREVIRE_SAVEFRAME
        static int cnt = 0;
        char buf[64];
        cnt++;
        if ((cnt % 4 == 0)&&(cnt < 50)) {
            sprintf(buf, "/tmp/pre_%dx%d_%d.yuv",src.w , src.h, cnt);
            preview_saveframe(buf, (void *) pv4l2_buf->addrVirY, src.w * src.h * 3 / 2, 1);
        }
        if(cnt == 50)
            cnt =0;
#endif

    frm_info_t img;
    int disp_format;
    int ww;
    int hh;
    int addry;
    int addrc;
    int dma_fd;

    //ALOGD("onNextFrameAvailable mDispBuff[%d]=%d",cur_idx,mDispBuff[cur_idx].dmafd);
    int dmode = 0;//aut_get_disp_rotate_mode();
    if (dmode > 0) {
#if G2D_PROC_ROTATE_FLIP   //use /dev/g2d to rotate
        switch(dmode)
        {
        case TR_ROT_0:
            ww = src.w;
            hh = src.h;
            break;
        case TR_ROT_90: //note:dist w*h become h*w
            g2dRotate(imgtr.trfd,G2D_ROTATE90,
                        (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                        (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.h, src.w);
            ww = src.h;
            hh = src.w;
            break;
        case TR_ROT_180:
            g2dRotate(imgtr.trfd,G2D_ROTATE180,
                    (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                    (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.w,src.h);
            ww = src.w;
            hh = src.h;
            break;
        case TR_ROT_270: //note:dist w*h become h*w
            g2dRotate(imgtr.trfd,G2D_ROTATE270,
                        (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                        (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.h, src.w);
            ww = src.h;
            hh = src.w;
            break;
        case TR_HFLIP:
            g2dRotate(imgtr.trfd,G2D_FLIP_VERTICAL,
                    (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                    (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.w,src.h);
            ww = src.w;
            hh = src.h;
            break;
        case TR_HFLIP_ROT_90:  //note:dist w*h become h*w
            g2dRotate(imgtr.trfd,G2D_MIRROR45,
                        (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                        (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.h, src.w);
            ww = src.h;
            hh = src.w;
            break;
        case TR_VFLIP:
            g2dRotate(imgtr.trfd,G2D_FLIP_HORIZONTAL,
                    (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                    (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.w,src.h);
            ww = src.w;
            hh = src.h;
            break;
        case TR_VFLIP_ROT_90:  //note:dist w*h become h*w
            g2dRotate(imgtr.trfd,G2D_MIRROR135,
                        (unsigned char *)pv4l2_buf->addrPhyY, src.w, src.h,
                        (unsigned char *)mDispBuff[cur_idx].addrPhyY, src.h, src.w);
            ww = src.h;
            hh = src.w;
            break;
        }
        disp_format = DISP_FORMAT_YUV420_SP_VUVU;
        addry = mDispBuff[cur_idx].addrPhyY;
        addrc = addry + ww * hh;
        dma_fd = mDispBuff[cur_idx].dmafd;
#endif
    } else {
        ww = src.w;
        hh = src.h;
        disp_format = DISP_FORMAT_YUV420_SP_VUVU;

        addry = pv4l2_buf->addrPhyY;
        addrc = pv4l2_buf->addrPhyC;
        dma_fd = pv4l2_buf->dmafd;
    }

#ifdef USE_DE_LAYER
    src.format = disp_format;
    src.w = ww;
    src.h = hh;
    int ret;

    if (mHwDisplay->CameraDispEnableFlag[0] == true) {
        // ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen0,&src,(unsigned long)&addry);
        ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen0,&src,0,dma_fd);
        if (ret < 0) {
            ALOGE("onNextFrameAvailable set video0 src error");
        }

        mHwDisplay->aut_hwd_layer_open(mHwlayerScreen0);
    }

    if (mHwDisplay->CameraDispEnableFlag[1] == true) {
        // ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen1,&src,(unsigned long)&addry);
        ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen1,&src,0,dma_fd);
        if (ret < 0) {
            ALOGE("onNextFrameAvailable set video1 src error");
        }
        mHwDisplay->aut_hwd_layer_open(mHwlayerScreen1);
    }
#else    //use OPENGLES to display
#if defined(_T507_) || defined(_T7_P1_)
    if(pv4l2_buf->width % 720 == 0)  //720*480  720*576  1440*960  1440*1152
#endif
    {
        mDispCnt++;
        if (mDispCnt >= DISP_NB_BUFFER-1) {
            mDispCnt = 0;
        }

        if (mDispBuff[mDispCnt].addrVirY != NULL) {
            ALOGD("use memcpy");
            memcpy((void *)mDispBuff[mDispCnt].addrVirY, (void *)pv4l2_buf->addrVirY,
                        pv4l2_buf->width * pv4l2_buf->height * 3 / 2);
            mPreviewMemops.ion_buffer.fd_data.aw_fd = mDispBuff[mDispCnt].dmafd;
            flushCache(mMemType, &mPreviewMemops, NULL);
            info_aframe(&mDispBuff[mDispCnt].dmafd);
            //ALOGV("------xx--mDispBuff dmafd----=%d\n", mDispBuff[mDispCnt].dmafd);
        }
        return true;
    }

    int dmafd = 0;
    if (dmode > 0) {
        dmafd = mDispBuff[cur_idx].dmafd;
        ALOGV("------xx-------mDispBuff dmafd----=%d\n", mDispBuff[cur_idx].dmafd);
    } else {
        if (0 == pv4l2_buf->dmafd) {  // 4 csi in,dmafd will be find in   overlay_info->fd_data.aw_fd
            dmafd = ((ion_buffer_node*)pv4l2_buf->overlay_info)->fd_data.aw_fd;
            mPreviewMemops.ion_buffer.fd_data.aw_fd = dmafd;
            flushCache(mMemType, &mPreviewMemops, NULL);
        } else {
            dmafd = pv4l2_buf->dmafd; //normal csi, dmafd will be find in pv4l2_buf->dmafd
            //normal csi's dmafd is from csi-driver,so we don't need to flushCach
        }
    }

    info_aframe(&dmafd);
    //ALOGV("------xx-------dmafd----=%d\n", dmafd);
#endif

    return true;
}

}; /* namespace android */
