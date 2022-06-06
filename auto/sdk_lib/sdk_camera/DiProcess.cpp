#define LOG_TAG "DiProcess"

#include "DiProcess.h"
#include "deinterlace2.h"
#include <unistd.h>
#include <linux/videodev2.h>

#define ALIGN_4K(x) (((x) + (4095)) & ~(4095))
#define ALIGN_32B(x) (((x) + (31)) & ~(31))
#define ALIGN_16B(x) (((x) + (15)) & ~(15))
#define ALIGN_8B(x) (((x) + (7)) & ~(7))

#define ALOGD printf
#define ALOGE printf
#define ALOGV printf

typedef struct
{
	unsigned long      addr[2];  // the address of frame buffer
	__di_rectsz_t       mRectSize;
	__di_pixel_fmt_t    eFormat;
}DiFbT;

typedef struct
{
	DiFbT         mInputFb;	       //current frame fb
	DiFbT         mPreFb;          //previous frame fb
	__di_rectsz_t   mSourceRegion;   //current frame and previous frame process region
	DiFbT         mOutputFb;       //output frame fb
	__di_rectsz_t   mOutRegion;	   //output frame region
	unsigned int  nField;          //process field <0-top field ; 1-bottom field>
	unsigned int  bTopFieldFirst;  //video infomation <0-is not top_field_first; 1-is top_field_first>
}DiParaT;



DiProcess::DiProcess()
    :mDiFd(-1)
    ,mDiReqId(-1)
{
    ALOGD("F:%s,L:%d",__FUNCTION__,__LINE__);
}

DiProcess::~DiProcess()
{
    ALOGD("F:%s,L:%d\n",__FUNCTION__,__LINE__);
    release();
    ALOGD("F:%s ok ,L:%d\n",__FUNCTION__,__LINE__);
}

int DiProcess::init()
{
    int ret = -1;
    if (mDiFd > 0) {
        ALOGE("DiProcess is already init,F:%s,L:%d\n",__FUNCTION__,__LINE__);
        return -1;
    }
    mDiFd = open("/dev/deinterlace", O_RDWR, 0);
    if (mDiFd <= 0) {
        ALOGE("open /dev/deinterlace failed,F:%s,L:%d\n",__FUNCTION__,__LINE__);
        return -1;
    }
    ALOGD("open /dev/deinterlace OK, F:%s,L:%d\n",__FUNCTION__,__LINE__);

    #if defined(_T507_) || defined(_T7_P1_)
    ret = ioctl(mDiFd, DI_REQUEST, &mDiReqId);
    if(ret != 0) {
        ALOGE("DI_REQUEST failed,F:%s,L:%d\n",__FUNCTION__,__LINE__);
        return -1;
    }
    ALOGD("DI_REQUEST OK, F:%s,L:%d, id:%d\n",__FUNCTION__,__LINE__,mDiReqId);
    #endif
    return NO_ERROR;
}

int DiProcess::diProcess2(unsigned char *pre_src, unsigned char *now_src, unsigned char *next_src,
                                int src_width, int src_height, int in_format,
                                unsigned char *dst, int dst_width, int dst_height,
                                int out_format, int nField)
{
    int ret = -1;
    __di_para_t2 di_para;

    if (mDiFd < 0) {
        ALOGE("deinterlace is not init!F:%s,L:%d\n",__FUNCTION__,__LINE__);
        return -1;
    }

    __di_pixel_fmt_t di_in_format;
    switch (in_format) {
        case V4L2_PIX_FMT_NV21:
            di_in_format = DI_FORMAT_NV21;
            break;
        case V4L2_PIX_FMT_NV16:
            di_in_format = DI_FORMAT_YUV422_SP_UVUV;
            break;
        case V4L2_PIX_FMT_NV61:
            di_in_format = DI_FORMAT_YUV422_SP_VUVU;
            break;
        default:
            di_in_format = DI_FORMAT_NV21;
            break;
    }

    __di_pixel_fmt_t di_out_format;
    switch (out_format) {
        case V4L2_PIX_FMT_NV21:
            di_out_format = DI_FORMAT_NV21;
            break;
        case V4L2_PIX_FMT_NV16:
            di_out_format = DI_FORMAT_YUV422_SP_UVUV;
            break;
        case V4L2_PIX_FMT_NV61:
            di_out_format = DI_FORMAT_YUV422_SP_VUVU;
            break;
        default:
            di_out_format = DI_FORMAT_NV21;
            break;
    }

    di_para.pre_fb.addr[0] = (unsigned long long)pre_src;
    di_para.pre_fb.addr[1] = (unsigned long long)(pre_src + ALIGN_16B(src_width)*src_height);
    di_para.pre_fb.addr[2] = 0x0;
    di_para.pre_fb.size.width = src_width;
    di_para.pre_fb.size.height = src_height;
    di_para.pre_fb.format = di_in_format;

    di_para.input_fb.addr[0] = (unsigned long long)now_src;
    di_para.input_fb.addr[1] = (unsigned long long)(now_src + ALIGN_16B(src_width)*src_height);
    di_para.input_fb.addr[2] = 0x0;
    di_para.input_fb.size.width = src_width;
    di_para.input_fb.size.height = src_height;
    di_para.input_fb.format = di_in_format;

    di_para.next_fb.addr[0] = (unsigned long long)next_src;
    di_para.next_fb.addr[1] = (unsigned long long)(next_src + ALIGN_16B(src_width)*src_height);
    di_para.next_fb.addr[2] = 0x0;
    di_para.next_fb.size.width = src_width;
    di_para.next_fb.size.height = src_height;
    di_para.next_fb.format = di_in_format;

    di_para.source_regn.width = src_width;
    di_para.source_regn.height = src_height;

    di_para.output_fb.addr[0] = (unsigned long long)dst;
    di_para.output_fb.addr[1] = (unsigned long long)(dst + ALIGN_16B(dst_width)*dst_height);
    di_para.output_fb.addr[2] = 0x0;
    di_para.output_fb.size.width = dst_width;
    di_para.output_fb.size.height = dst_height;
    di_para.output_fb.format = di_out_format;
    di_para.out_regn.width = dst_width;
    di_para.out_regn.height = dst_height;

    di_para.field = nField;
    di_para.top_field_first = 1;//nField;
    di_para.id = mDiReqId;

    ret = ioctl(mDiFd,DI_IOCSTART2,&di_para);
    if (ret < 0) {
        return -1;
    }

    return NO_ERROR;
}

void DiProcess::diProcess1(unsigned char *presrc, int pre_width, int pre_height,
                unsigned char *src, int src_width, int src_height, 
                unsigned char *dst, int dst_width, int dst_height,int nField)
{
	int ret = 0;
    DiParaT        mDiParaT;
	__di_rectsz_t    mSrcSize;
	__di_rectsz_t    mDstSize;
	__di_pixel_fmt_t eInFormat;
	__di_pixel_fmt_t eOutFormat;
	//eOutFormat = DI_FORMAT_NV21;
	//eInFormat = DI_FORMAT_NV21;
	mSrcSize.width  = src_width;
	mSrcSize.height = src_height;
	mDstSize.width  = dst_width;
	mDstSize.height = dst_height;
	mDiParaT.mInputFb.mRectSize.width= src_width;
	mDiParaT.mInputFb.mRectSize.height= src_height;
	mDiParaT.mInputFb.eFormat	 = DI_FORMAT_NV21;	
	mDiParaT.mPreFb.mRectSize.width = pre_width;
	mDiParaT.mPreFb.mRectSize.height= pre_height;
	mDiParaT.mPreFb.eFormat 	 = DI_FORMAT_NV21;	
	mDiParaT.mOutputFb.mRectSize.width = dst_width;
	mDiParaT.mOutputFb.mRectSize.height= dst_height;
	mDiParaT.mOutputFb.eFormat	 = DI_FORMAT_NV21;
	mDiParaT.mSourceRegion.width= src_width;
	mDiParaT.mSourceRegion.height= src_height;
	mDiParaT.mOutRegion.width = dst_width;
	mDiParaT.mOutRegion.height = dst_height;	
	mDiParaT.nField 			 = nField;
	mDiParaT.bTopFieldFirst 	 = 1;
   	mDiParaT.mInputFb.addr[0]    = (unsigned long)src;
	mDiParaT.mInputFb.addr[1]    = (unsigned long)src + src_width*src_height;
	mDiParaT.mPreFb.addr[0]      = (unsigned long)presrc;
	mDiParaT.mPreFb.addr[1]      = (unsigned long)presrc+pre_width*pre_height;
	mDiParaT.mOutputFb.addr[0]   = (unsigned long)dst;
	mDiParaT.mOutputFb.addr[1]   = (unsigned long)dst+dst_width*dst_height;
	ret = ioctl(mDiFd , DI_IOCSTART, (unsigned long)&mDiParaT);		
	if(ret < 0){
		ALOGE("%s hw di ioctl, DI_IOCSTART failed\n",__FUNCTION__);
		return;
	}
}

int DiProcess::release()
{
    if (mDiFd > 0) {
        if (mDiReqId >= 0) {
            int ret = ioctl(mDiFd, DI_RELEASE, &mDiReqId);
            if(ret < 0){
				ALOGD("DI_RELEASE failed id=%d\n",mDiReqId);
            }
            ALOGD("DI_RELEASE, F:%s,L:%d, id:%d\n",__FUNCTION__,__LINE__,mDiReqId);
            mDiReqId = -1;
        }
        close(mDiFd);
        mDiFd = -1;
        ALOGD("DiProcess,release ok, F:%s,L:%d\n",__FUNCTION__,__LINE__);
    }
    return NO_ERROR;
}



