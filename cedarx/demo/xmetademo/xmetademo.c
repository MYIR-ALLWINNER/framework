/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : xmetademo.c
 * Description : xmetademo
 * History :
 *
 */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>

#include "cdx_config.h"
#include <cdx_log.h>
#include "xmetadataretriever.h"
#include "CdxTypes.h"
#include "CdxTime.h"

#define DEMO_FILE_NAME_LEN 256

//* the main method.
int main(int argc, char** argv)
{
    CEDARX_UNUSE(argc);
    CEDARX_UNUSE(argv);
    int ret;
    char * pOutUrl = NULL;

    printf("\n");
    printf("****************************************************************************\n");
    printf("* This program implements a simple player,\n");
    printf("* you can type commands to control the player.\n");
    printf("* To show what commands supported, type 'help'.\n");
    printf("* Such as usage:  ./xmetademo  /mnt/IntputVideo.mp4  .\n");
    printf("***************************************************************************\n");

    if(argc < 2)
    {
        printf("Usage:\n");
        printf("demoretriver filename \n");
        return -1;
    }

    cdx_int64 start = CdxMonoTimeUs();

    XRetriever* demoRetriver;
    demoRetriver = XRetrieverCreate();

    if(NULL == demoRetriver)
    {
        printf("create failed\n");
        return -1;
    }

    pOutUrl = calloc(DEMO_FILE_NAME_LEN, 1);
    if(pOutUrl == NULL)
    {
        printf("pOutUrl == NULL \n");
        return -1;
    }

    ret = XRetrieverSetDataSource(demoRetriver, argv[1], NULL);
    if(ret < 0)
    {
        free(pOutUrl);
        printf("set datasource failed\n");
        return -1;
    }
    printf("XRetrieverSetDataSource end \n\n");

    int width;
    XRetrieverGetMetaData(demoRetriver, METADATA_VIDEO_WIDTH, &width);

    int height;
    XRetrieverGetMetaData(demoRetriver, METADATA_VIDEO_HEIGHT, &height);

      int duration;
    XRetrieverGetMetaData(demoRetriver, METADATA_DURATION, &duration);

    printf("get metadata: w(%d), h(%d), duration(%d)\n\n", width, height, duration);

    XVideoFrame* videoFrame = NULL;
    videoFrame = XRetrieverGetFrameAtTime(demoRetriver, 0, 0);

    //save videoFrame
    sprintf(pOutUrl, "/mnt/pic_%dx%d.rgb", videoFrame->mWidth,videoFrame->mHeight);

    FILE* outFp = fopen(pOutUrl, "wb");
    if(outFp != NULL)
    {
        printf("saving picture : size: %d x %d , path: %s\n\n",
        videoFrame->mWidth, videoFrame->mHeight,pOutUrl);

        fwrite(videoFrame->mData, 1, videoFrame->mSize, outFp);
        fclose(outFp);
    }
    else
    {
        printf("saving picture failed: outFp == NULL \n");
    }

    (void)videoFrame;
    XRetrieverDestory(demoRetriver);

    if(pOutUrl != NULL)
    {
        free(pOutUrl);
        pOutUrl = NULL;
    }

    cdx_int64 end = CdxMonoTimeUs();
    printf("total need cost time is %lldms\n",(end - start)/1000);

    printf("\n");
    printf("*************************************************************************\n");
    printf("* Quit the program, goodbye!\n");
    printf("********************************************************************\n");
    printf("\n");

    return 0;
}

