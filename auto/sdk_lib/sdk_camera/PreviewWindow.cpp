
#include "CameraDebug.h"
#if DBG_PREVIEW
#define LOG_NDEBUG 0
#endif
#define LOG_TAG "PreviewWindow"
#include <cutils/log.h>

#include <ui/Rect.h>
#include "V4L2CameraDevice2.h"
#include "PreviewWindow.h"

#include "G2dApi.h"

#ifndef DMAFD_TEST
//使用硬件图层显示视频的每一帧
#define USE_DE_LAYER
#endif

#define G2D_PROC_ROTATE_FLIP 1

#ifdef DMAFD_TEST
#include "sunxiMemInterface.h"
extern "C" int info_aframe(int *dmafd);
extern "C" int glReleaseImageKHR(void);
#endif

#define USE_DI_INPREVIEW 1

#define USE_VIDEO_PROCESS_BUF 1
using namespace g2dapi;
namespace android {


#define CAMHAL_GRALLOC_USAGE GRALLOC_USAGE_SW_READ_RARELY | \
                                     GRALLOC_USAGE_SW_WRITE_OFTEN
#define USE_NEW_AUT_DISP 1
	static int calculateFrameSize(int width, int height, uint32_t pix_fmt) {
		int frame_size = 0;
		switch (pix_fmt) {
			case V4L2_PIX_FMT_YVU420:
			case V4L2_PIX_FMT_YUV420:
			case V4L2_PIX_FMT_NV21:
			case V4L2_PIX_FMT_NV12:
				frame_size = (ALIGN_16B(width) * height * 12) / 8;
				break;
				case V4L2_PIX_FMT_YUYV:frame_size = (width * height) << 1;
				break;
				default:ALOGE("%s: Unknown pixel format %d(%.4s)",
							  __FUNCTION__, pix_fmt, reinterpret_cast < const char *>(&pix_fmt));
				 break;
		} return frame_size;
	}

	DBG_TIME_AVG_BEGIN(TAG_CPY);
	DBG_TIME_AVG_BEGIN(TAG_DQBUF);
	DBG_TIME_AVG_BEGIN(TAG_LKBUF);
	DBG_TIME_AVG_BEGIN(TAG_MAPPER);
	DBG_TIME_AVG_BEGIN(TAG_EQBUF);
	DBG_TIME_AVG_BEGIN(TAG_UNLKBUF);


void PreviewWindow::PreviewTvOut(HwDisplay* mcd,int screen_id,unsigned int *hlay,struct view_info *surface,int mode)
{
	if((NULL == mcd)||(NULL == hlay)){
		printf("%s input arg error\r\n",__FUNCTION__);
	}
	
	printf("test_layer%d_tvout_ntsc begin\r\n",screen_id);
	if(mode == DISP_TV_MOD_NTSC){
		surface->w = 720;
		surface->h = 480;
	}else if(mode == DISP_TV_MOD_PAL){
		surface->w = 720;
		surface->h = 576;
	}
	
	mcd->aut_hwd_layer_sufaceview(*hlay,surface);
	mcd->hwd_other_screen(screen_id,DISP_OUTPUT_TYPE_TV,mode);
}

//#define mMemType MEM_TYPE_CDX_NEW
#define mMemType MEM_TYPE_DMA

PreviewWindow::PreviewWindow():
	mPreviewFrameWidth(0),
	mPreviewFrameHeight(0),
	mPreviewFrameSize(0),
    mDi(NULL),
    mDispCnt(0),
	mCurPixelFormat(0), mPreviewEnabled(false), mShouldAdjustDimensions(true)
	, isPreviewDispEn(false),previewSkipCounter(30) {
	F_LOG;
	mHwDisplay = HwDisplay::getInstance();
	mHwDisplay->aut_hwd_vsync_enable(0,1);
	memset(&mPreviewMemops, 0, sizeof(dma_mem_des_t));
	
	int ret = allocOpen(mMemType, &mPreviewMemops, NULL);
	if (ret < 0) {
		LOGE("ion_alloc_open failed");
	}

	memset(&imgtr, 0, sizeof(tr_obj));
	
	int i;
	for (i = 0; i < DISP_NB_BUFFER; i++) {
		mDispBuff[i].addrPhyY = 0;
		mDispBuff[i].addrVirY = 0;
	}

	mHwDisplay->CameraDispEnableFlag[0] = false;
	mHwDisplay->CameraDispEnableFlag[1] = false;
#ifdef USE_DI_INPREVIEW

	mDi = new DiHandle();

#endif	
}
	
PreviewWindow::~PreviewWindow() {
	F_LOG;

	int i;
	for (i = 0; i < DISP_NB_BUFFER; i++) {
		if (mDispBuff[i].addrVirY != 0) {
			mPreviewMemops.vir = mDispBuff[i].addrVirY;
			allocFree(mMemType, &mPreviewMemops, NULL);
			mDispBuff[i].addrPhyY = 0;
			mDispBuff[i].addrVirY = 0;
		}
	}
	mPreviewMemops.size = 0;
	
	if ((mPreviewMemops.ops != NULL)||(mMemType == mPreviewMemops.memType)){
		int ret = allocClose(mMemType,&mPreviewMemops, NULL);
		if(ret < 0){
			ALOGE("~PreviewWindow:allocClose MEM_TYPE_CDX_NEW failed");
		}
	}
    
    if(mDi){
        delete mDi; 
        mDi = NULL;
    }
}

/****************************************************************************
 * Camera API
 ***************************************************************************/
status_t PreviewWindow::setPreviewDisplayOn() {
		//LOGD("%s: current: %p -> new: %p", __FUNCTION__, mPreviewWindow, window);
		F_LOG status_t res = NO_ERROR;
		Mutex::Autolock locker(&mObjectLock);
		isPreviewDispEn = true;
		int i;
		#ifdef USE_VIDEO_PROCESS_BUF
		mPreviewMemops.size = PBUFFER_SIZE;
		for (i = 0; i < DISP_NB_BUFFER; i++) {
			if (mDispBuff[i].addrVirY == 0) {
				int ret = allocAlloc(mMemType, &mPreviewMemops, NULL);
				if(ret < 0){
					ALOGE("allocAlloc failed");
				}
				mDispBuff[i].addrVirY  = mPreviewMemops.vir;
				mDispBuff[i].addrPhyY = mPreviewMemops.phy;
				//mDispBuff[i].sharefd = mPreviewMemops.share_data_fd;
				mDispBuff[i].dmafd = mPreviewMemops.ion_buffer.fd_data.aw_fd;
                printf("setPreviewDisplayOn mDispBuff[%d]=%d vir=0x%lx\n",i,mDispBuff[i].dmafd,mDispBuff[i].addrVirY);
			}
		}
		#endif	
		int dmode = 0;//aut_get_disp_rotate_mode();
		if (dmode > 0) {
			
			#ifdef G2D_PROC_ROTATE_FLIP
				imgtr.trfd =g2dInit();
			#else
				aut_imgtr_init(&imgtr);
			#endif
		}

#ifdef USE_DE_LAYER

	mHwDisplay->CameraDispEnableFlag[0] = true;

	HwDisplay* mcd=mHwDisplay;

	mHwlayerScreen0 = mcd->aut_hwd_layer_request(&mvi,0, 0, 0);
	mcd->aut_hwd_layer_set_zorder(mHwlayerScreen0,1);

	if(mtvout)
	{
		mHwDisplay->CameraDispEnableFlag[1] = true;

		//----------------------1:video TV OUT CFG-------------------------------
		struct view_info SurfaceTV;

		SurfaceTV.x = 0;
		SurfaceTV.y = 0;
		if(DISP_TV_MOD_NTSC == mtvout){
			SurfaceTV.w = 720;
			SurfaceTV.h = 480;
		}else //if(DISP_TV_MOD_NTSC == mtvout)
		{
			SurfaceTV.w = 720;
			SurfaceTV.h = 576;

		}
		mHwlayerScreen1 = mcd->aut_hwd_layer_request(&mcd->Surface[1],
					1, 0, 0);

		mcd->aut_hwd_layer_set_zorder(mHwlayerScreen1,1);
		PreviewTvOut(mcd, 1, (unsigned int *)&mHwlayerScreen1,
							&SurfaceTV,mtvout);
		//----------------------2:ui TV OUT CFG-------------------------------
		//this have a bug,because linux fb have pan display,you must have a timer (10ms eg) in your app to check the base layer crop addr
		// or modify the kernel driver,dor disp pan to swap the base adrr for fb0 layer
		
		mHwlayerScreen1_ui = mcd->aut_hwd_layer_request(&SurfaceTV,
				1, 1, 0);

		disp_layer_config2 fb0Config = mcd->aut_hwd_getLayerConfigWithId(0,1,0);	
		mcd->aut_hwd_set_layer_info(mHwlayerScreen1_ui,&fb0Config.info);

		mcd->aut_hwd_layer_set_zorder(mHwlayerScreen1_ui,3);
		PreviewTvOut(mcd, 1, (unsigned int *)&mHwlayerScreen1_ui,
							&SurfaceTV,DISP_TV_MOD_NTSC);


	}


#endif
		return res;

	}

status_t PreviewWindow::setPreviewParam(struct view_info pvi, struct src_info psi, int tvout,
										int tvch) {
	mvi = pvi;
	msi = psi;
	mtvout = tvout;
	mtvch = tvch;

}

status_t PreviewWindow::setPreviewDisplayOff() {
	F_LOG;
	status_t res = NO_ERROR;
	Mutex::Autolock locker(&mObjectLock);
	isPreviewDispEn = false;

#ifdef USE_DE_LAYER

	mHwDisplay->CameraDispEnableFlag[0] = false;
	if(mHwlayerScreen0 >=0){
		mHwDisplay->aut_hwd_layer_close(mHwlayerScreen0);
	}
	
	if(mtvout){
		mHwDisplay->CameraDispEnableFlag[1] = false;
		mHwDisplay->aut_hwd_layer_close(mHwlayerScreen1);
		mHwDisplay->aut_hwd_layer_close(mHwlayerScreen1_ui);
	}

#endif

	int dmode = 0;//aut_get_disp_rotate_mode();
	if (dmode > 0) {
		
#ifdef G2D_PROC_ROTATE_FLIP
	g2dUnit(imgtr.trfd);

#else
	aut_imgtr_release(&imgtr);
#endif
	}
	//heat so guys change the rotate mode during the preview rtime.
	//so check release the buffer out of dmode domain
	int i;
	#ifdef USE_VIDEO_PROCESS_BUF
	for (i = 0; i < DISP_NB_BUFFER; i++) {
		if (mDispBuff[i].addrVirY != 0) {
			mPreviewMemops.vir = mDispBuff[i].addrVirY;
			allocFree(mMemType, &mPreviewMemops, NULL);
			//printf("setPreviewDisplayOff mDispBuff[%d]=%d vir=0x%lx\n",
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

status_t PreviewWindow::startPreview() {
	F_LOG;

	Mutex::Autolock locker(&mObjectLock);
	mPreviewEnabled = true;

	DBG_TIME_AVG_INIT(TAG_CPY);
	DBG_TIME_AVG_INIT(TAG_DQBUF);
	DBG_TIME_AVG_INIT(TAG_LKBUF);
	DBG_TIME_AVG_INIT(TAG_MAPPER);
	DBG_TIME_AVG_INIT(TAG_EQBUF);
	DBG_TIME_AVG_INIT(TAG_UNLKBUF);
	return NO_ERROR;
}

void PreviewWindow::stopPreview() {
	F_LOG;

	Mutex::Autolock locker(&mObjectLock);
	mPreviewEnabled = false;
	mShouldAdjustDimensions = true;

	DBG_TIME_AVG_END(TAG_CPY, "copy ");
	DBG_TIME_AVG_END(TAG_DQBUF, "deque ");
	DBG_TIME_AVG_END(TAG_LKBUF, "lock ");
	DBG_TIME_AVG_END(TAG_MAPPER, "mapper ");
	DBG_TIME_AVG_END(TAG_EQBUF, "enque ");
	DBG_TIME_AVG_END(TAG_UNLKBUF, "unlock ");
}
static int preview_saveframe(char *str, void *p, int length, int is_oneframe) {
	FILE *fd;

	if (is_oneframe) {
		fd = fopen(str, "wb");
	}
	else {
		fd = fopen(str, "a");
	}

	if (!fd) {
		LOGE("Open file error");
		return -1;
	}
	if (fwrite(p, 1, length, fd)) {
		LOGD("Write file successfully");
		fclose(fd);
		return 0;
	}
	else {
		LOGE("Write file fail");
		fclose(fd);
		return -1;
	}
}

/****************************************************************************
* Public API
***************************************************************************/


bool PreviewWindow::onNextFrameAvailable(const void *frame, int flipEnable, bool isOview) {
	//int res;
	Mutex::Autolock locker(&mObjectLock);
	if (!isPreviewDispEn)
		return true;

	V4L2BUF_t *pv4l2_buf = (V4L2BUF_t *) frame;

	// 去掉30 帧
	//static int previewSkipCounter = 30;
	if( previewSkipCounter-- > 0){
		//ALOGD("preview start count down:%d\n",previewSkipCounter);
		//if(pv4l2_buf)
			//ALOGD("w= [%d] h=[%d] idx=[%d]",pv4l2_buf->width,pv4l2_buf->height,pv4l2_buf->index);
		return 0;
	}

	//int preview_format = 0;
	//int preview_addr_phy = 0;
	//int preview_addr_vir = 0;
	//int preview_width = 0;
	//int preview_height = 0;
	//RECT_t preview_crop;

	int cur_idx = 0;

	if (!isPreviewEnabled())	//|| mPreviewWindow == NULL)
	{
		return true;
	}

    V4L2BUF_t *pDiBuff = NULL;
    if((pv4l2_buf->width <= 720)&&(mDi)){   // w>720 is csi camera,csi don't need to do deinterace
		int ret = mDi->DiHandleInit( pv4l2_buf->width, pv4l2_buf->height );
		if(ret < 0){
			delete mDi;
			mDi = NULL;
		}
    
        pDiBuff = mDi->DiProcessLoop(pv4l2_buf,0,0);
        if(NULL == pDiBuff){
            ALOGD("Dihandle failed,use this origin data cam [%d]w[%d] h[%d]\n",pv4l2_buf->thumbFormat,pv4l2_buf->width, pv4l2_buf->height);
        }else{
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

	#if 0
		static int cnt = 0;
		char buf[64];
		cnt++;
		if ((cnt % 4 == 0)&&(cnt < 50)) {
			sprintf(buf, "/tmp/%dx%d_%d.yuv",src.w , src.h, cnt);
			preview_saveframe(buf, (void *) pv4l2_buf->addrVirY, src.w * src.h * 3 / 2, 1);
		}
	#endif
	
	//frm_info_t img;
	int disp_format;
	int ww;
	int hh;
	int addry;
	int addrc;
	int dma_fd;
	int dmode = 0;//aut_get_disp_rotate_mode();
    //printf("onNextFrameAvailable mDispBuff[%d]=%d\n",cur_idx,mDispBuff[cur_idx].dmafd);

	if (dmode > 0) {
	#ifdef G2D_PROC_ROTATE_FLIP   //use /dev/g2d to rotate
		switch(dmode){
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
	#else               //use /dev/tr to rotate  PS:t7 has no /dev/tr
		img.addr0 = &pv4l2_buf->addrPhyY;
		img.addr1 = &pv4l2_buf->addrPhyC;
		img.format = TR_FORMAT_YUV420_SP_VUVU;
		img.width = src.w;
		img.height = src.h;
		img.mode = (tr_mode) dmode;
		img.outaddr0 = &mDispBuff[cur_idx].addrPhyY;

		aut_imgtr_proc(&imgtr, &img);

		if ((img.mode == TR_ROT_180) || (img.mode == TR_HFLIP) || (img.mode == TR_VFLIP)) {
			ww = ALIGN_32B(src.w);
			hh = src.h;
			crop = {
			pv4l2_buf->crop_rect.left, pv4l2_buf->crop_rect.top, pv4l2_buf->crop_rect.width,
					pv4l2_buf->crop_rect.height};
		}
		else {
			ww = ALIGN_32B(src.h);
			hh = src.w;
			crop = {
			pv4l2_buf->crop_rect.left, pv4l2_buf->crop_rect.top,
					pv4l2_buf->crop_rect.height, pv4l2_buf->crop_rect.width};
		}

		if(mPreviewMemops.ops != NULL){
			mPreviewMemops.vir = mDispBuff[cur_idx].addrVirY;
			mPreviewMemops.size = ww * hh * 3 / 2;
			
			mPreviewMemops.ion_buffer.fd_data.aw_fd = mDispBuff[cur_idx].dmafd;
			flushCache(mMemType, &mPreviewMemops, NULL);
		}

		disp_format = DISP_FORMAT_YUV420_P;

		addry = mDispBuff[cur_idx].addrPhyY;
		addrc = addry + ww * hh;
        dma_fd = mDispBuff[cur_idx].dmafd;
#endif
	}
	else 
	{   //dmode = 0
		ww = src.w;
		hh = src.h;
		disp_format = DISP_FORMAT_YUV420_SP_VUVU;

		addry = pv4l2_buf->addrPhyY;
		addrc = pv4l2_buf->addrPhyC;
        dma_fd = pv4l2_buf->dmafd;
	}

	//return 0;


#ifdef USE_DE_LAYER
	src.format = disp_format;
	src.w = ww;
	src.h = hh;
	int ret;
    
	if(mHwDisplay->CameraDispEnableFlag[0] == true){
	
		ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen0,&src,(unsigned long)&addry);
		if(ret < 0){
			printf("onNextFrameAvailable set video0 src error\n");
		}
		
		mHwDisplay->aut_hwd_layer_open(mHwlayerScreen0);
	}

	if(mHwDisplay->CameraDispEnableFlag[1] == true){
		ret = mHwDisplay->aut_hwd_layer_set_src(mHwlayerScreen1,&src,(unsigned long)&addry);
		if(ret < 0){
			ALOGE("onNextFrameAvailable set video1 src error\n");
		}
		mHwDisplay->aut_hwd_layer_open(mHwlayerScreen1);
	}

#else    //use OPENGLES to display
	#if defined(_T507_) || defined(_T7_P1_)
	if(pv4l2_buf->width%720 == 0)  //720*480  720*576  1440*960  1440*1152
	#endif
	{
		mDispCnt++;
		if(mDispCnt >= DISP_NB_BUFFER-1){
			mDispCnt = 0;
		}
		
		if(mDispBuff[mDispCnt].addrVirY != NULL){
			memcpy((void *)mDispBuff[mDispCnt].addrVirY ,(void *)pv4l2_buf->addrVirY, 
						pv4l2_buf->width*pv4l2_buf->height*3/2);
			mPreviewMemops.ion_buffer.fd_data.aw_fd = mDispBuff[cur_idx].dmafd;
			flushCache(mMemType, &mPreviewMemops, NULL);
			info_aframe(&mDispBuff[mDispCnt].dmafd);
			ALOGV("------xx--mDispBuff dmafd----=%d\n", mDispBuff[mDispCnt].dmafd);
		}
		return true;
	}
	
	int dmafd = 0;
	if(dmode > 0){
		dmafd = mDispBuff[cur_idx].dmafd;
		ALOGV("------xx-------mDispBuff dmafd----=%d\n", mDispBuff[cur_idx].dmafd);
	}else{
		if(0 == pv4l2_buf->dmafd){  // 4 csi in,dmafd will be find in   overlay_info->fd_data.aw_fd
			dmafd = ((ion_buffer_node*)pv4l2_buf->overlay_info)->fd_data.aw_fd;
			mPreviewMemops.ion_buffer.fd_data.aw_fd = dmafd;
			flushCache(mMemType, &mPreviewMemops, NULL);
		}else{
			dmafd = pv4l2_buf->dmafd; //normal csi, dmafd will be find in pv4l2_buf->dmafd
			//normal csi's dmafd is from csi-driver,so we don't need to flushCach
		}
	}

	info_aframe(&dmafd);
	ALOGV("------xx-------dmafd----=%d\n", dmafd);
	
#endif

	return true;
}

};								/* namespace android */
