#ifndef AW_VIDEO_DECORD
#define AW_VIDEO_DECORD

/************************************************************
    Copyright (c) 2018 by Allwinnertech Co., Ltd.

            http://www.allwinnertech.com

************************************************************
File Name           :
Version             :   release 1.0
Author              :   yuanguochao

Description         :   This decord is depend on Tinyalsa with cerdaX
                        for AllWinner Socs system.
                        It will be build with cerdaX,
                        plz read Makefile for more information.

                        There are two ways to decode video stream.

                        1.decode in another thread:
                        creat->SetDispConfig
                        startDecode             //creat a thread wait data to decode
                        sendFrameToDecoder...   //send one fream everytime.
                        stopDecode              //destroy decode thread
                        destroy

                        2.decode directly:
                        creat->SetDispConfig
                        decodeFrameDrectly...   //decode and display drectly.
                        destroy


History Information Description
Date                    Author                  Modification
2018.10.31             yuanguochao               Created file
************************************************************/

struct DispConfig
{
    int dispX;
    int dispY;
    int dispW;
    int dispH;

    int scrID;
    int chLID;
    int lyrID;
    int zorder;

    int dispFmt; //enum disp_pixel_format in sunxi_display2.h
};

namespace awh264vdecode
{

class AwH264VDecoder
{
public:
    /*-------------------------------------------------------------------------
         * get the instance of AwH264VDecoder.
         * The AwH264VDecoder must be released when it is no longer used.
    -------------------------------------------------------------------------*/
    static AwH264VDecoder* creat();

    /*-------------------------------------------------------------------------
         * The AwH264VDecoder must be released after it is no longer used.
    -------------------------------------------------------------------------*/
    static void destroy(AwH264VDecoder* decoder);

    /*-------------------------------------------------------------------------
         * set the display config .
         * If not be called, follow values will be set default.
          static const int DISP_X_DEFAULT = 0;
          static const int DISP_Y_DEFAULT = 0;
          static const int DISP_W_DEFAULT = 1024;
          static const int DISP_H_DEFAULT = 600;
          static const int SCR_ID_DEFAULT = 0;
          static const int CHL_ID_DEFAULT = 0;
          static const int LYR_ID_DEFAULT = 0;
          static const int ZORDER_DEFAULT = 2;
          static const int DISP_F_DEFAULT = DISP_FORMAT_YUV420_SP_VUVU;
    -------------------------------------------------------------------------*/
    virtual void SetDispConfig(DispConfig* config) = 0;

    /*-------------------------------------------------------------------------
         * To start the decode thread,
         * then h264 NalFragment data will be get in AwH264DataTransfer.
    -------------------------------------------------------------------------*/
    virtual void startDecode() = 0;

    /*-------------------------------------------------------------------------
         * send frame data to decoder and return immediately.
         * frame data will be decode and display in another thread.
    -------------------------------------------------------------------------*/
    virtual int sendFrameToDecoder(unsigned char* data, unsigned int len ) = 0;
    /*-------------------------------------------------------------------------
         * To stop the decode thread.
    -------------------------------------------------------------------------*/
    virtual void stopDecode() = 0;
    
    /*-------------------------------------------------------------------------
         * Decode frame directly.
         * If decode in this way,
         * DO NOT to call startDecode,sendFrameToDecoder and stopDecode.
    -------------------------------------------------------------------------*/
    virtual int decodeFrameDrectly(unsigned char* data, unsigned int len ) = 0;

    virtual ~AwH264VDecoder() {};
};

}

#endif

