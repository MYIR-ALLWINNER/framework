#ifndef AW_VIDEO_ENCORDER_H
#define AW_VIDEO_ENCORDER_H
/***********************************************************
    Copyright (c) 2018 by Allwinnertech Co., Ltd.

            http://www.allwinnertech.com

************************************************************
File Name           :
Version             :   release 0.1
Author              :   yuanguochao

Description         :   This file is depend on Tinyalsa with cerdaX
                        for AllWinner Socs system.
                        plz read Makefile for more information.


History Information Description
Date                    Author                  Modification
2018.10.31             yuanguochao               Created file
************************************************************/
#define DPRCT_W __attribute__((deprecated("plz use [init] and [AWVideoEncoderDataCallback].")))

namespace awvideoencoder
{

#define MAX_OVERLAY_SIZE                  64

typedef enum CodecType_
{
    CODEC_H264,
    CODEC_JPEG,
    CODEC_H264_VER2,
    CODEC_H265,
    CODEC_VP8,
} CodecType;

typedef enum PixelFmt_
{
    PIXEL_YUV420SP,//0 nv12
    PIXEL_YVU420SP,//1 nv21
    PIXEL_YUV420P, //2 i420
    PIXEL_YVU420P, //3 yv12
} PixelFmt;

typedef enum FrameCount_
{
    ONLY_ONE_FRAME = 1,
    MULTI_FRAMES,
} FrameCount;

typedef enum RotationAngle_
{
    Angle_0 = 0,
    Angle_90 = 90,
    Angle_180 = 180,
    Angle_270 = 270,
} RotationAngle;

typedef enum RcMode_
{
    CBR = 0,
    VBR = 1,
    AVBR = 2,
} RcMode;

typedef enum   OVERLAY_ARGB_TYPE_
{
    OVERLAY_ARGB_MIN    = -1,
    OVERLAY_ARGB8888    = 0,
    OVERLAY_ARGB4444   = 1,
    OVERLAY_ARGB1555   = 2,
    OVERLAY_ARGB_MAX    = 3,
}  OVERLAY_ARGB_TYPE;

typedef enum   OVERLAY_TYPE_
{
    NORMAL_OVERLAY          = 0,    //normal overlay
    COVER_OVERLAY           = 1,    //use the setting yuv to cover region
    LUMA_REVERSE_OVERLAY    = 2,    //normal overlay and luma reverse
}  OVERLAY_TYPE;

typedef struct   OverlayCoverYuvS_
{
    //1:use the cover yuv; 0:transform the argb data to yuv ,then cover
    unsigned char       use_cover_yuv_flag;
    unsigned char       cover_y; //the value of cover y
    unsigned char       cover_u; //the value of cover u
    unsigned char       cover_v; //the value of cover v
}  OverlayCoverYuvS;

typedef struct   OverlayHeaderS_
{
    unsigned short      start_mb_x;         //horizonal value of  start points divided by 16
    unsigned short      end_mb_x;           //horizonal value of  end points divided by 16
    unsigned short      start_mb_y;         //vertical value of  start points divided by 16
    unsigned short      end_mb_y;           //vertical value of  end points divided by 16
    unsigned char       extra_alpha_flag;   //0:no use extra_alpha; 1:use extra_alpha
    unsigned char       extra_alpha;        //use user set extra_alpha, range is [0, 15]
    OverlayCoverYuvS    cover_yuv;          //when use COVER_OVERLAY should set the cover yuv
    OVERLAY_TYPE        overlay_type;       //reference define of   OVERLAY_TYPE
    unsigned char*      overlay_blk_addr;   //the vir addr of overlay block
    unsigned int        bitmap_size;        //the size of bitmap

    //* for v5v200 and newer ic
    unsigned int        bforce_reverse_flag;
    unsigned int        reverse_unit_mb_w_minus1;
    unsigned int        reverse_unit_mb_h_minus1;
    //* end

}  OverlayHeaderS;

typedef struct   OverlayInfoS_
{
    unsigned char               blk_num; //num of overlay region
    OVERLAY_ARGB_TYPE           argb_type;//reference define of   ARGB_TYPE
    OverlayHeaderS              overlayHeaderList[MAX_OVERLAY_SIZE];

    //* for v5v200 and newer ic
    unsigned int                invert_mode;
    unsigned int                invert_threshold;
    //* end

}  OverlayInfoS;

typedef struct encode_param_t_
{

    PixelFmt    pixelFormat;
    FrameCount  frameCount;     //one for a picture,MULTI for a stream.
    CodecType   codecType;

    unsigned int srcW;          //the src size.
    unsigned int srcH;
    unsigned int dstW;          //the dst size.
    unsigned int dstH;
    RotationAngle rotation;     //Clockwise,invalid for jpeg.

    RcMode rcMode;              //CBR VBR AVBR
    int bitRate;
    int frameRate;              //fps
    int maxKeyFrame;            //The max intarval of key frame,for h264 and h265.
    int jpgQuality;             //JpegQuality,0-100.

    OverlayInfoS* overlayInfoS; //OverlayInfo,default is NULL.
} EncodeParam;
typedef struct AV_Packet_t_
{
    unsigned long  id;
    long long      pts;

    unsigned char* pAddrPhy0;   //input:YUV -> Y buf phyAddr
    unsigned char* pAddrPhy1;   //input:YUV -> C buf phyAddr
    unsigned char* pAddrVir0;   //input:YUV -> Y buf virAddr | output:encode data0 virAddr
    unsigned char* pAddrVir1;   //input:YUV -> C buf virAddr | output:encode data1 virAddr(It's usually jpg)

    unsigned int   dataLen0;    //input:YUV -> Y buf length | output:encode data0 length
    unsigned int   dataLen1;    //input:YUV -> C buf length | output:encode data1 length(It's usually jpg)
} AVPacket;
class AWVideoEncoderDataCallback
{
public:
    virtual int encoderDataReady(AVPacket* packet) = 0;
};

class AWVideoEncoder
{
public:
    DPRCT_W static AWVideoEncoder* create(EncodeParam* param);
    static AWVideoEncoder* create();
    static void destroy(AWVideoEncoder* encoder);

    /***********************************************************
     Name:        init
     Description: initial the encoder.
     Return:      0: seccussful.
                  <0:failed!
    ************************************************************/
    virtual int init(EncodeParam* param, AWVideoEncoderDataCallback* cbk) = 0;

    /***********************************************************
     Name:        getSpsHeader
     Description: get h264 and h265 pps & sps data.Deprecated.
     Return:      Actual length of Header.
    ************************************************************/
    DPRCT_W virtual int getHeader(void* header) = 0;

    /***********************************************************
     Name:        setVBR in bytes.
     Description: change Bitrate.
    ************************************************************/
    virtual int setVBR(unsigned int bitrate) = 0;
    /***********************************************************
     Name:        setOverlayInfoS.
     Description: change OverlayInfoS when encoding.
    ************************************************************/
    virtual int setOverlayInfoS(OverlayInfoS* overlayInfoS) = 0;
    /***********************************************************
     Name:        encode
     Description: encode the input data and copy to outputBuf.Deprecated.
     Return:      >0:Actual length of output data.
                  <0:encode failed!
    ************************************************************/
    DPRCT_W virtual int encode(const void* inputBuf, unsigned int inputLen,
                               void* outputBuf, unsigned int outputLen) = 0;

    /***********************************************************
     Name:        encode
     Description: encode the input packet,
                  the encoded data will be output from AWVideoEncoderDataCallback.
     Return:      >0:Actual length of output data.
                  <0:encode failed!
    ************************************************************/
    virtual int encode(AVPacket* inPacket) = 0;

    virtual ~AWVideoEncoder() {};
};

}

#endif
