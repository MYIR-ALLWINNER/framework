#ifndef AW_VIDEO_DECORDER_H
#define AW_VIDEO_DECORDER_H

/************************************************************
    Copyright (c) 2018 by Allwinnertech Co., Ltd.

            http://www.allwinnertech.com

************************************************************
File Name           :
Version             :   release 0.1
Author              :   yuanguochao

Description         :   This decord is depend on Tinyalsa with cerdaX
                        for AllWinner Socs system.
                        It will be build with cerdaX,
                        plz read Makefile for more information.

History Information Description
Date                    Author                  Modification
2018.10.31             yuanguochao               Created file
************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define DPRCT_W __attribute__((deprecated("plz use [init] and [AWVideoDecoderDataCallback].")))

namespace awvideodecoder
{

typedef enum CodecType_
{
    CODEC_UNKNOWN          = 0,
    CODEC_MJPEG            = 0x101,
    CODEC_MPEG1            = 0x102,
    CODEC_MPEG2            = 0x103,
    CODEC_MPEG4            = 0x104,
    CODEC_MSMPEG4V1        = 0x105,
    CODEC_MSMPEG4V2        = 0x106,
    CODEC_DIVX3            = 0x107,
    CODEC_DIVX4            = 0x108,
    CODEC_DIVX5            = 0x109,
    CODEC_XVID             = 0x10a,
    CODEC_H263             = 0x10b,
    CODEC_SORENSSON_H263   = 0x10c,
    CODEC_RXG2             = 0x10d,
    CODEC_WMV1             = 0x10e,
    CODEC_WMV2             = 0x10f,
    CODEC_WMV3             = 0x110,
    CODEC_VP6              = 0x111,
    CODEC_VP8              = 0x112,
    CODEC_VP9              = 0x113,
    CODEC_RX               = 0x114,
    CODEC_H264             = 0x115,
    CODEC_H265             = 0x116,
    CODEC_AVS              = 0x117,
    CODEC_MAX              = CODEC_AVS,
    CODEC_MIN              = CODEC_MJPEG,
} CodecType;

typedef enum PixelFmt_
{
    PIXEL_DEFAULT            = 0,

    PIXEL_YUV_PLANER_420     = 1,
    PIXEL_YUV_PLANER_422     = 2,
    PIXEL_YUV_PLANER_444     = 3,

    PIXEL_YV12               = 4,
    PIXEL_NV21               = 5,
    PIXEL_NV12               = 6,
    PIXEL_YUV_MB32_420       = 7,
    PIXEL_YUV_MB32_422       = 8,
    PIXEL_YUV_MB32_444       = 9,

    PIXEL_RGBA                = 10,
    PIXEL_ARGB                = 11,
    PIXEL_ABGR                = 12,
    PIXEL_BGRA                = 13,

    PIXEL_YUYV                = 14,
    PIXEL_YVYU                = 15,
    PIXEL_UYVY                = 16,
    PIXEL_VYUY                = 17,

    PIXEL_PLANARUV_422        = 18,
    PIXEL_PLANARVU_422        = 19,
    PIXEL_PLANARUV_444        = 20,
    PIXEL_PLANARVU_444        = 21,
    PIXEL_P010_UV             = 22,
    PIXEL_P010_VU             = 23,

    PIXEL_MIN = PIXEL_DEFAULT,
    PIXEL_MAX = PIXEL_PLANARVU_444,
} PixelFmt;

typedef enum ScaleDownRatio_
{
    ScaleNone,
    ScaleOneHalf,
    ScaleOneQuarter,
    ScaleOneEighth,
} ScaleDownRatio;

typedef enum RotationAngle_
{
    Angle_0,
    Angle_90,
    Angle_180,
    Angle_270,
} RotationAngle;

typedef struct DecodeParam_
{
    CodecType   codecType;
    PixelFmt    pixelFormat;

    unsigned int srcW;          //If you don't know, set 0.
    unsigned int srcH;          //If you don't know, set 0.
    unsigned int dstW;          //do not set it,it will be set by decoder.
    unsigned int dstH;          //do not set it,it will be set by decoder.
    ScaleDownRatio scaleRatio;  //0, 1/2, 1/4, 1/8, 16bit fill with 0.
    RotationAngle rotation;     //Clockwise,90 degree.
} DecodeParam;
typedef struct AV_Packet_t_
{
    unsigned long  id;
    long long      pts;

    unsigned char* pAddrVir0;   //output:YUV -> Y buf virAddr | input:decode virAddr
    unsigned char* pAddrVir1;   //output:YUV -> C buf virAddr
    unsigned char* pAddrPhy0;   //output:YUV -> Y buf phyAddr
    unsigned char* pAddrPhy1;   //output:YUV -> C buf phyAddr

    unsigned int   dataLen0;    //output:YUV -> Y buf length | input:decode length
    unsigned int   dataLen1;    //output:YUV -> C buf length
    void*          handler;     //release handle,Please don't modify it.
} AVPacket;

class AWVideoDecoderDataCallback
{
public:
    virtual int decoderDataReady(AVPacket* data) = 0;
};

class AWVideoDecoder
{
public:
    /*-------------------------------------------------------------------------
         * get the instance of AWVideoDecoder.
    -------------------------------------------------------------------------*/
    DPRCT_W static AWVideoDecoder* create(DecodeParam* param);
    static AWVideoDecoder* create();
    /*-------------------------------------------------------------------------
         * The AWVideoDecoder must be released after it is no longer used.
    -------------------------------------------------------------------------*/
    static void destroy(AWVideoDecoder* decoder);

    /***********************************************************
     Name:        init
     Description: initial the decoder.
     Return:      0: seccussful.
                  <0:failed!
    ************************************************************/
    virtual int init(DecodeParam* param, AWVideoDecoderDataCallback* cbk) = 0;
    /*-------------------------------------------------------------------------
         * Decode frame directly.
    -------------------------------------------------------------------------*/
    DPRCT_W virtual int decode(const void* inputBuf, unsigned int inputLen,
                               void* outputBuf, unsigned int outputLen) = 0;
    /*-------------------------------------------------------------------------
         * Decode frame directly,output phyAddr by requestPicture.
    -------------------------------------------------------------------------*/
    DPRCT_W virtual int decodeAsync(const void* inputBuf, unsigned int inputLen) = 0;
    /*-------------------------------------------------------------------------
         * get picture with phyaddr,must be release by releasePicture.
    -------------------------------------------------------------------------*/
    DPRCT_W virtual int requestPicture(AVPacket* picBuf) = 0;
    /*-------------------------------------------------------------------------
         *  release picture.
    -------------------------------------------------------------------------*/
    DPRCT_W virtual int releasePicture(AVPacket* picBuf) = 0;
    /***********************************************************
     Name:        decode
     Description: Decode the input data,
                  the encoded data will be output from AWVideoDecoderDataCallback.
     Return:      >0:Actual length of output data.
                  <0:decode failed!
    ************************************************************/
    virtual int decode(const AVPacket* inPacket) = 0;
	
    virtual ~AWVideoDecoder() {};
};

}

#endif

