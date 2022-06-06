/*
 * Copyright (c) 2008-2021 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : autplayerTest.cpp
 * Description : test AUTPlayer class
 * Au xfang
 * date: 2020/3/18
 */
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "AutPlayer.h"

using namespace android;

#define PCM_SAVE_PATH "/tmp/out.pcm"
#define DEFUALT_FILE "/a.mp4"
static int gExitFlag;

static int saveToFile(char *str, void *p, int length) {
	FILE *fd;
	fd = fopen(str, "a");

	if (!fd) {
		printf("Open file error\n");
		return -1;
	}
	if (fwrite(p, 1, length, fd)) {
		fclose(fd);
		return 0;
	}else {
		printf("Write file fail\n");
		fclose(fd);
		return -1;
	}
	return 0;
}

int cb_func(int32_t msgType, void *user,void*data,int len)
{
	//printf("%s msgType=%d\n",__FUNCTION__,msgType);
	switch(msgType)
	{
	case 1:
		//printf("\n");
		break;
	case 2:     /*  EOS */
		printf("player notify eos\n");
		gExitFlag = 1;
		break;
	case 14:
		//printf("\n");
		break;		
	case 28:
		//printf("\n");
		break;
	case 128:
			static int cnt = 0;
			char buf[64];
			cnt++;
			sprintf(buf, PCM_SAVE_PATH);
			saveToFile(buf, data, len);
		break;
		
	default :
		printf("%s,msgType=%d is not handle\n",__FUNCTION__);
		break;
	}
}

int main(int argc, char *argv[])
{
	int ret = -1;
	gExitFlag = 0;
	
	int test=0;
	char url[64];
	memset(url,0 ,sizeof(url));
	
	if (argc == 1) {
		printf( "\033[1m\033[33m Usage:/autplayerTest <testcase>  <mediafile>\033[0m\n"
			"\033[1m\033[33m Usage:for example /autplayerTest 0 /call.wav\033[0m\n");
		exit(0);
	}else if (argc == 2) {
		test = atoi(argv[1]);
		strcpy(url,DEFUALT_FILE);
	}else if (argc == 3) {
		test = atoi(argv[1]);
		strcpy(url,argv[2]);
	}else{
		printf( "Usage:/autplayerTest testcase mediafile\n"
			"Usage:for example /autplayerTest 0 /call.wav\n");
		exit(0);
	}
	
	AUTPlayer* player = new AUTPlayer();
	
	player->setUserCb(cb_func, NULL);
	ret = player->setUrl(url);
	if(ret != 0){
        printf("set url errror\n");
        return -1;
    }
	
	switch(test){
	case 0:
	{
		ret = player->play();
		if(ret != 0){
			printf("call play errror\n");
			return -1;
		}
		sleep(1);
		ret = player->pause();
		if(ret != 0){
			printf("call play errror\n");
			return -1;
		}
		printf("app pause...\n");
		sleep(2);
		printf("app play again\n");
		ret = player->play();
		if(ret != 0){
			printf("call play errror\n");
			return -1;
		}
		break;
	}
	case 1:
	{
		MediaInfo * m = player->getMediaInfo();
		printf("nVideoStreamNum=%d nAudioStreamNum=%d,nSubtitleStreamNum=%d\n"
				"nDurationMs=%d\n",
				m->nVideoStreamNum,
				m->nAudioStreamNum,
				m->nSubtitleStreamNum,
				m->nDurationMs);
		if(m->nAudioStreamNum){
			printf("nSampleRate=%d nBitsPerSample=%d\n",
					m->pAudioStreamInfo->nSampleRate,
					m->pAudioStreamInfo->nBitsPerSample);
		}
		
		player->play();
		printf("getDuration=%d\n",player->getDuration());
		sleep(1);
		player->pause();
		printf("CurrentPosition=%d\n",player->getCurrentPosition());
		sleep(1);
		player->pause();
		break;
	}
	case 2:
	{
		player->seekto(2);
		player->play();
		sleep(1);
		player->pause();
		sleep(1);
		player->play();
		break;
	}
	case 3:
	{
		player->setSpeed(2);
		player->play();
		player->pause();
		player->play();
		break;
	}
	default :
	{
		break;
	}
	
	}
	while(!gExitFlag){
		sleep(1);
	}
	return 0;
}
