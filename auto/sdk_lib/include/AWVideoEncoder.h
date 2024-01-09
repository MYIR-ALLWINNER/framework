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
#define MAX_ROI_REGION                    4

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

typedef struct AvRoiRegion_t_
{
    int enable;
    int x;           //Left;
    int y;           //Top;
    int w;           //Width;
    int h;           //Height;
    int QPoffset;    //Roi_QP=qp_slice-QPoffset 
    unsigned char absFlag;//0:Roi_QP=qp_slice-QPoffset;  1:Roi_QP = QPoffset 
}AvRoiRegion;
typedef struct AvRoiRegionArray_t_
{
    int  roiNum;        //0-4
    AvRoiRegion region[MAX_ROI_REGION];
}AvRoiRegionArray;

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
    int minQp;                  // QP range [0,51) 
    int maxQp;                  // QP range [0,51) 
    
    int bitRate;
    int frameRate;              //fps
    int maxKeyFrame;            //The max intarval of key frame,for h264 and h265.
    int jpgQuality;             //JpegQuality,0-100.

} EncodeParam;
typedef struct AV_Packet_t_
{
    unsigned long  id;
    long long      pts;
    bool           isKeyframe;

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
    /***********************************************************
     Name:        encoderDataReady
     Description: return data.
                  if id==-1 && pts==-1,means it's pps/sps.
     Return:      0: seccussful.
                  <0:failed!
    ************************************************************/
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
                  AWVideoEncoderDataCallback will return psp&pps immediately.
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
     Name:        setJpgQuality.
     Description: change Jpg Quality.
    ************************************************************/
    virtual int setJpgQuality(int quality) = 0;

    /***********************************************************
     Name:        setRoi.
     Description: set Roi region.
    ************************************************************/
    virtual int setRoi(AvRoiRegionArray* roiRegions) = 0;

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
