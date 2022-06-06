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

namespace awstreamplayer
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

typedef enum TV_MODE_
{
    NONE,
    NTSC,
    PAL,
} TV_MODE;

typedef struct PlayerParam_
{
    unsigned int dispX;         //default value 0.
    unsigned int dispY;         //default value 0.
    unsigned int dispW;         //default value 1024.
    unsigned int dispH;         //default value 600.

    unsigned int cropX;         //default value 0.
    unsigned int cropY;         //default value 0.
    unsigned int cropW;         //default value 1024.
    unsigned int cropH;         //default value 600.

    unsigned int chLID;         //default value 0.
    unsigned int lyrID;         //default value 0.
    unsigned int zorder;        //default value 2.

    CodecType   codecType;      //default value h264.

    unsigned int srcW;          //If you don't know, set 0.
    unsigned int srcH;          //If you don't know, set 0.
    ScaleDownRatio scaleRatio;  //0, 1/2, 1/4, 1/8, 16bit fill with 0.
    RotationAngle rotation;     //Clockwise,90 degree.

    TV_MODE tvOut;         //CVBS out: 0 none,1 NTSC,2 PAL.
    unsigned int tvDispX;       //default value 0.
    unsigned int tvDispY;       //default value 0.
    unsigned int tvDispW;       //default value 720.
    unsigned int tvDispH;       //default value 480.
    
} PlayerParam;

class AWStreamPlayer
{
public:
    /*-------------------------------------------------------------------------
         * get the instance of AWStreamPlayer.
    -------------------------------------------------------------------------*/
    static AWStreamPlayer* create(PlayerParam* param);

    /*-------------------------------------------------------------------------
         * The AWStreamPlayer must be released after it is no longer used.
    -------------------------------------------------------------------------*/
    static void destroy(AWStreamPlayer* decoder);

    /*-------------------------------------------------------------------------
         * The reset decoder when pps/sps changed.
    -------------------------------------------------------------------------*/
    virtual void resetPPS() = 0;
    
    /*-------------------------------------------------------------------------
         * Hide display.
    -------------------------------------------------------------------------*/
    virtual void hideDisplay(bool hide) = 0;
    
    /*-------------------------------------------------------------------------
         * The reset display Paramter.
    -------------------------------------------------------------------------*/
    virtual void reset(PlayerParam* param) = 0;

    /*-------------------------------------------------------------------------
         * To start the decode thread,
         * then h264 NalFragment data will be get in AwH264DataTransfer.
    -------------------------------------------------------------------------*/
    virtual void startThread() = 0;

    /*-------------------------------------------------------------------------
         * send frame data to decoder and return immediately.
         * frame data will be decode and display in another thread.
    -------------------------------------------------------------------------*/
    virtual int sendFrameToThread(unsigned char* data, unsigned int len ) = 0;
    
    /*-------------------------------------------------------------------------
         * To stop the decode thread.
    -------------------------------------------------------------------------*/
    virtual void stopThread() = 0;
    
    /*-------------------------------------------------------------------------
         * Decode frame directly, no startThread .
    -------------------------------------------------------------------------*/
    virtual int decodeFrameDrectly(unsigned char* data, unsigned int len) = 0;

    virtual ~AWStreamPlayer() {};
};

}

#endif

