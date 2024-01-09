#include "DiHandle.h"
#define LOG_TAG "DiHandle"
#include "sdklog.h"
//namespace android {

#ifndef NO_ERROR
#define NO_ERROR 0L
#endif

/*
echo 8 8 8 8 > /proc/sys/kernel/printk
echo 0xff > /sys/module/deinterlace/parameters/debug_mask
*/

DiHandle::DiHandle()
  :  mDiReadId(0)
    ,mSkipCount(2)
    ,mDiWidth(0)
    ,mDiHeight(0)
    ,mAbandonFrameCnt(0)
    ,mDiProcess(NULL)
{
    mSkipCount = 2;
    mAbandonFrameCnt = 0;

    memset(mCamBuff,0,sizeof(V4L2BUF_t)*DI_HANDLE_BUFFER);
    memset(mdiBuffer,0,sizeof(V4L2BUF_t)*DI_HANDLE_BUFFER);
}

DiHandle::~DiHandle()
{
    DiHandleUnInit();
}

int DiHandle::saveframe(char *str, void *p, int length, int is_oneframe)
{
    FILE *fd;

    if (is_oneframe) {
        fd = fopen(str, "wb");
    } else {
        fd = fopen(str, "a");
    }

    if (!fd) {
        ALOGE("Open file error\n");
        return -1;
    }
    if (fwrite(p, 1, length, fd)) {
        ALOGD("Write file successfully\n");
        fclose(fd);
        return 0;
    } else {
        ALOGE("Write file fail\n");
        fclose(fd);
        return -1;
    }
}

int DiHandle::DiHandleInit(int in_w,int in_h)
{
    if (0 != mCamBuff[0].addrVirY) {
        return 0;
    }

    mBuffInitFlag = 1;

    if ((mDiWidth != 0) && (mDiWidth != in_w)) {
        ALOGE("mDiWidth should not be change twice\n");
        return -1;
    }
    ALOGV("DiHandle::DiHandleInit w=[%d] h=[%d]", in_w,in_h);
    mDiWidth = in_w;
    mDiHeight = in_h;

    paramStruct_t param_in;
    memset(&param_in, 0, sizeof(paramStruct_t));
    int ret = allocOpen(MEM_TYPE_DMA, &param_in,NULL);
    if (ret < 0) {
        ALOGE("open dma_ion failed\n");
        return -1;
    }

    ion_buffer_node ibuf[DI_HANDLE_BUFFER];
    memset(&param_in, 0, sizeof(paramStruct_t));
    param_in.size = mDiWidth * mDiHeight * 3 >> 1;
    for (int i = 0; i < DI_HANDLE_BUFFER; i++) {
        ret = allocAlloc(MEM_TYPE_DMA, &param_in, NULL);
        if (ret < 0) {
            ALOGD("DiBuffInit allocAlloc failed\n\n");
            return -1;
        }

        ibuf[i] = param_in.ion_buffer;
        mCamBuff[i].overlay_info = (void *)malloc(sizeof(ion_buffer_node));
        memcpy(mCamBuff[i].overlay_info,&ibuf[i],sizeof(ion_buffer_node));
        mCamBuff[i].addrVirY = ibuf[i].vir;
        mCamBuff[i].addrPhyY = ibuf[i].phy;

        mCamBuff[i].addrVirC = 0;
        mCamBuff[i].addrPhyC = 0;

        memset((void*)mCamBuff[i].addrVirY, 0x00, mDiWidth*mDiHeight);   //make it black
        memset((void*)mCamBuff[i].addrVirY + mDiWidth*mDiHeight,0x80, mDiWidth*mDiHeight>>1);
        //ALOGV("------USE_DMABUF_API------dmafd----=%d\r\n",((ion_buffer_node*)mCamBuff[i].overlay_info)->fd_data.aw_fd);
        ALOGV("DiHandleInit DiBuffInit---i=%d---vir=%ld\r\n",i,mCamBuff[i].addrVirY);
    }

    memset(&param_in, 0, sizeof(paramStruct_t));
    param_in.size = mDiWidth * mDiHeight * 3 >> 1;
    for (int i = 0;i< DI_HANDLE_BUFFER;i++) {
        //ibuf[i]=dma_ion_alloc(mIonFd,size);
        ret = allocAlloc(MEM_TYPE_DMA, &param_in, NULL);
        if (ret < 0) {
            ALOGE("allocAlloc failed\n");
            return -1;
        }
        ibuf[i] = param_in.ion_buffer;
        mdiBuffer[i].overlay_info=(void *)malloc(sizeof(ion_buffer_node));
        memcpy(mdiBuffer[i].overlay_info,&ibuf[i],sizeof(ion_buffer_node));
        mdiBuffer[i].addrVirY = ibuf[i].vir;
        mdiBuffer[i].addrPhyY = ibuf[i].phy;

        mdiBuffer[i].addrVirC = 0;
        mdiBuffer[i].addrPhyC = 0;

        memset((void*)mdiBuffer[i].addrVirY, 0x00, mDiWidth*mDiHeight);
        memset((void*)(mdiBuffer[i].addrVirY + mDiWidth*mDiHeight),0x80, mDiWidth*mDiHeight>>1);
        ALOGD("mdiBuffer[%d]------allocAlloc dmafd----=%d\r\n",i,((ion_buffer_node*)mdiBuffer[i].overlay_info)->fd_data.aw_fd);
    }

    mDiProcess = new DiProcess();
    if (mDiProcess == NULL) {
        ALOGE("new Diprocess failed\n");
        goto END_ERROR;
    }

    ret = mDiProcess->init();
    if (ret != NO_ERROR) {
        ALOGE("Diprocess init failed\n");
        goto END_ERROR;
    }

   return 0;

END_ERROR:
    DiHandleUnInit();
    return -1;
}

int DiHandle::DiHandleUnInit()
{
    //int ret=0;
    //ion_buffer_node *pibuf;
    //dma_handle_data_t handle_data;
    if (0 == mBuffInitFlag) {
        return 0;
    }

    ALOGV("DiHandle::DiHandleUnInit");
    paramStruct_t param_in;
    memset(&param_in, 0, sizeof(paramStruct_t));
    for (int i = 0; i < DI_HANDLE_BUFFER; i++) {
        if (mCamBuff[i].addrVirY != 0) {
            param_in.vir = mCamBuff[i].addrVirY;
            allocFree(MEM_TYPE_DMA, &param_in, NULL);
            mCamBuff[i].addrVirY = 0;
        }
        
        if (NULL != mCamBuff[i].overlay_info) {
            free(mCamBuff[i].overlay_info);
            mCamBuff[i].overlay_info = NULL;
        }
            
        if (mdiBuffer[i].addrVirY != 0) {
            param_in.vir = mdiBuffer[i].addrVirY;
            allocFree(MEM_TYPE_DMA, &param_in, NULL);
            mdiBuffer[i].addrVirY = 0;
        }

        if (NULL != mdiBuffer[i].overlay_info) {
            free(mdiBuffer[i].overlay_info);
            mdiBuffer[i].overlay_info = NULL;
        }
    }

    allocClose(MEM_TYPE_DMA, &param_in, NULL);

    if (mDiProcess != NULL) {
        delete mDiProcess;
        mDiProcess = NULL;
    }

    mBuffInitFlag = 0;
    return 0;
}


V4L2BUF_t * DiHandle::DiProcessLoop(V4L2BUF_t * camV4l2buf, int savePicBeforeDi, int enableTimeLog)
{
    V4L2BUF_t *buf = NULL;
    V4L2BUF_t *prebuf = NULL;
    V4L2BUF_t *preprebuf = NULL;
    struct timeval lRunTimeEnd;
    long long time1 = 0;
    long long time2 = 0;
    long long time3 = 0 ;
    //int ret;
    paramStruct_t param_in;
    
    mDiReadId++;
    if (mDiReadId >= DI_HANDLE_BUFFER) {
        mDiReadId = 0;
    }
            
    //ALOGD("Dihandle: mDiReadId=%d vir=0x%x buf->width=%d,buf->height=%d\n",
    //        mDiReadId, mCamBuff[mDiReadId].addrVirY,camV4l2buf->width,camV4l2buf->height);
        
    memcpy((void *)mCamBuff[mDiReadId].addrVirY, 
                (void *)camV4l2buf->addrVirY, camV4l2buf->width*camV4l2buf->height*3/2); //only cp data

    if (enableTimeLog) {
        gettimeofday(&lRunTimeEnd, NULL);
        time1 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
        time2 = 0;
        time3 = 0 ;
    }

    buf = &mCamBuff[mDiReadId];
    memset(&param_in,0,sizeof(paramStruct_t));
    param_in.ion_buffer.fd_data.aw_fd = ((ion_buffer_node*)buf->overlay_info)->fd_data.aw_fd;
    flushCache(MEM_TYPE_DMA, &param_in, NULL);
    
    prebuf = (mDiReadId == 0) ?
            (&mCamBuff[DI_HANDLE_BUFFER-1]) : (&mCamBuff[mDiReadId-1]);

    if (mDiReadId == 0 ) {
        preprebuf = &mCamBuff[DI_HANDLE_BUFFER-2] ;
    } else if (mDiReadId == 1 ) {
        preprebuf = &mCamBuff[DI_HANDLE_BUFFER-1] ;
    } else {
        preprebuf = &mCamBuff[mDiReadId-2];
    }

    buf->width = camV4l2buf->width;
    buf->height = camV4l2buf->height;
    buf->crop_rect.left        = 0;
    buf->crop_rect.top        = 0;
    buf->crop_rect.width    = camV4l2buf->width -1;
    buf->crop_rect.height    = camV4l2buf->height - 1;
    buf->timeStamp = camV4l2buf->timeStamp;
    buf->format = camV4l2buf->format;
    buf->isThumbAvailable = 0;
    buf->bytesused=camV4l2buf->width * camV4l2buf->height*3/2;  

    buf->addrVirC = buf->addrVirY + buf->width*buf->height;
    buf->addrPhyC = buf->addrPhyY + buf->width*buf->height;

    if (mAbandonFrameCnt > 0) {
        mAbandonFrameCnt--;
        return NULL;
    }

    //int frame_size = buf->width * buf->height* 3 /2;   
    if (mSkipCount <= 0) {
        memset(&param_in,0,sizeof(paramStruct_t));
        param_in.ion_buffer.fd_data.aw_fd = ((ion_buffer_node*)mdiBuffer[mDiReadId].overlay_info)->fd_data.aw_fd;
        flushCache(MEM_TYPE_DMA, &param_in, NULL);
        if (savePicBeforeDi == 1) {
            static int saveCnt = 0;
            char filebuf[64];
            saveCnt++;
            if ((saveCnt % 4 == 0)&&(saveCnt < 50)) {
                sprintf(filebuf, "/tmp/%dx%d_%d_bf.yuv",buf->width , buf->height, saveCnt);
                saveframe(filebuf, (void *) buf->addrVirY, buf->width * buf->height * 3 / 2, 1);
            }
        }
#if defined(_T507_) || defined(_T7_P1_)
        mDiProcess->diProcess2((unsigned char*)preprebuf->addrPhyY,
              (unsigned char*)prebuf->addrPhyY,
              (unsigned char *)buf->addrPhyY,
              buf->width, buf->height, buf->format,
              (unsigned char *)mdiBuffer[mDiReadId].addrPhyY,
              buf->width, buf->height, buf->format, 0);
                      
        mDiProcess->diProcess2((unsigned char*)preprebuf->addrPhyY,
              (unsigned char*)prebuf->addrPhyY,
              (unsigned char *)buf->addrPhyY,
              buf->width, buf->height, buf->format,
              (unsigned char *)mdiBuffer[mDiReadId].addrPhyY,
              buf->width, buf->height, buf->format, 1);
#else
        mDiProcess->diProcess1((unsigned char *)prebuf->addrPhyY,prebuf->width,prebuf->height,
              (unsigned char *)buf->addrPhyY,buf->width,buf->height,
              (unsigned char *)mdiBuffer[mDiReadId].addrPhyY,buf->width,buf->height,0);
        usleep(1);
        mDiProcess->diProcess1((unsigned char *)prebuf->addrPhyY,prebuf->width,prebuf->height,
              (unsigned char *)buf->addrPhyY,buf->width,buf->height,
              (unsigned char *)mdiBuffer[mDiReadId].addrPhyY,buf->width,buf->height,1);
#endif
        
        mdiBuffer[mDiReadId].width = buf->width;
        mdiBuffer[mDiReadId].height = buf->height;
        mdiBuffer[mDiReadId].index = buf->index;
        mdiBuffer[mDiReadId].timeStamp = buf->timeStamp;
        mdiBuffer[mDiReadId].crop_rect = buf->crop_rect;
        mdiBuffer[mDiReadId].format = buf->format;

        mdiBuffer[mDiReadId].addrVirC = mdiBuffer[mDiReadId].addrVirY + buf->width*buf->height;
        mdiBuffer[mDiReadId].addrPhyC = buf->addrPhyY + buf->width*buf->height;

        memset(&param_in,0,sizeof(paramStruct_t));
        param_in.ion_buffer.fd_data.aw_fd = ((ion_buffer_node*)buf->overlay_info)->fd_data.aw_fd;
        flushCache(MEM_TYPE_DMA, &param_in, NULL);
    } else {
        mSkipCount--;
        return NULL;
    }
    
    static unsigned char s_printcnt = 0;
    if (enableTimeLog) {
        gettimeofday(&lRunTimeEnd, NULL);
        time2 = lRunTimeEnd.tv_sec * 1000000 + lRunTimeEnd.tv_usec;
        time3 = time2 - time1 ;
        if (s_printcnt++ > 50) {
            ALOGD("Dihandle use %lldus(%lldms)\n",time3,time3/1000);
            s_printcnt = 0;
        }
        time1 = time2;
    }

    return &mdiBuffer[mDiReadId];
}

//}
