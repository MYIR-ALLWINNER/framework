/*
* Copyright (c) 2008-2019 Allwinner Technology Co. Ltd.
* All rights reserved.
*
* File : CdxMmfParser.h
* Description :
* History :
*   Date    : 2019/11/19
*/

#ifndef CDX_MMF_PARSER_H
#define CDX_MMF_PARSER_H

typedef struct MmfObjectStruct
{
    cdx_int32    UID;
    cdx_int32    Dsize;
}MMFObjectT;

typedef struct MmfFormatStruct
{
    cdx_uint16 formaTag;
    cdx_int16 nChannel;
    cdx_int32 nSampleRate;
    cdx_int32 nBitsPerSample;//����ÿ���㴫������
    cdx_int32 nBitsRate;//����ÿ�ִ�������
    cdx_int16 nBlockAlign;//һ����������ռ�ֽڣ���һ֡�Ĵ�С
}MmfFormatT;

typedef struct MmfParserImplS
{
    //audio common
    CdxParserT  base;
    CdxStreamT  *stream; //���ļ������
    pthread_cond_t  cond;//��

    cdx_int64   ulDuration;//��Ƶʱ������λms
    cdx_int64   dFileSize;//�ļ��ܳ�
    cdx_int32   mErrno; //Parser ��ǰ״̬
    cdx_uint32  nFlags; //��������
    //mmf base
    MmfFormatT  MmfFormat;
    cdx_int64   pts;//��ǰpts
    cdx_int64   nHeadLen;//��Ƶ����ǰ�Ĳ��ֵĴ�С
    cdx_int64   pkt_length;//û�в��ŵ���Ƶ���ݴ�С
}MmfParserImplS;

#define    MMMD    0X444D4D4D
#define    CNTI    0X49544E43
#define    OPDA    0x4144504F
#define    ATR     0x00525441
#define    Atsq    0x71737441
#define    AspI    0x49707341
#define    Awa     0x00617741

#endif
