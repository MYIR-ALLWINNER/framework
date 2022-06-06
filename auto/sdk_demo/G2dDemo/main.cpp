/***************************************
FileName:
Copyright:
Author:
Description:
***************************************/
//#include "ContentDisplay.h"
//#include "CsiCameraMplane.h"
//#include "hwdisp2.h"
#include "sunxiMemInterface.h"
#include <sys/time.h>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "type_compat.h"
#include "G2dApi.h"
//是否退出程序标志位
bool g_bQuitCapPro = false;

//ctrl+c消息捕获函数
void CtrlcMsgCb(int s)
{
    printf("===Caught Signal %d\n", s);
    g_bQuitCapPro = true;
}

int InitSignalCtrlC()
{
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = CtrlcMsgCb;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

/************Macro*********************/

/************Variable******************/

/************Function******************/
paramStruct_t m_DispMemOps;
paramStruct_t m_DispMemOps_half0;
paramStruct_t m_DispMemOps_half1;

paramStruct_t m_DispMemOps0;
paramStruct_t m_DispMemOps1;
paramStruct_t m_DispMemOps2;
paramStruct_t m_DispMemOps3;

int m_iVideoLayer0;
int ihalfWidth=2560 ,ihalfHeight=720 ;
int iWidth=2560 ,iHeight=1440 ;

int iSubWidth=1280 ,iSubHeight=720 ;

int ReadPicFileContent(char *pPicPath,paramStruct_t*pops,int size)
{
    int iRet = 0;

    
    iRet = allocOpen(MEM_TYPE_CDX_NEW, pops, NULL);
    if (iRet < 0) {
        printf("ion_alloc_open failed\n");
        return iRet;
    }
    pops->size = size;
    iRet = allocAlloc(MEM_TYPE_CDX_NEW, pops, NULL);
    if(iRet < 0) {
        printf("allocAlloc failed\n");
        return iRet;
    }

    FILE *fpff = fopen(pPicPath, "rb");
    if(NULL == fpff) {
        fpff = fopen(pPicPath, "rb");
        if(NULL == fpff) {
            printf("fopen %s ERR \n", pPicPath);
            allocFree(MEM_TYPE_CDX_NEW, pops, NULL);
            return -1;
        } else {
            printf("fopen %s OK \n", pPicPath);
            fread((void *)pops->vir, 1, size, fpff);
            fclose(fpff);
        }
    } else {
        printf("fopen %s OK \n", pPicPath);
        fread((void *)pops->vir, 1, size, fpff);
        fclose(fpff);
    }
	flushCache(MEM_TYPE_CDX_NEW,pops, NULL);

    return 0;
}
int WritePicFileContent(char *pPicPath,paramStruct_t*pops,int size)
{
    int iRet = 0;
	printf("WritePicFileContent size=%d \n",size);
	flushCache(MEM_TYPE_CDX_NEW,pops, NULL);

    FILE *fpff = fopen(pPicPath, "wb");
    if(NULL == fpff) {
        fpff = fopen(pPicPath, "wb");
        if(NULL == fpff) {
            printf("fopen %s ERR \n", pPicPath);
            allocFree(MEM_TYPE_CDX_NEW, pops, NULL);
            return -1;
        } else {
            printf("fopen %s OK \n", pPicPath);
            fwrite((void *)pops->vir, 1, size, fpff);
            fclose(fpff);
        }
    } else {
        printf("fopen %s OK \n", pPicPath);
        fwrite((void *)pops->vir, 1, size, fpff);
        fclose(fpff);
    }
	

    return 0;
}


int allocPicMem(paramStruct_t*pops,int size)
{
    int iRet = 0;

    iRet = allocOpen(MEM_TYPE_CDX_NEW, pops, NULL);
    if (iRet < 0) {
        printf("ion_alloc_open failed\n");
        return iRet;
    }
    pops->size =size;
    iRet = allocAlloc(MEM_TYPE_CDX_NEW, pops, NULL);
    if(iRet < 0) {
        printf("allocAlloc failed\n");
        return iRet;
    }

    return 0;
}
int freePicMem(paramStruct_t*pops)
{
    int iRet = 0;

	allocFree(MEM_TYPE_CDX_NEW, pops, NULL);

    return 0;
}

char *pPicPath0="/tmp/video0.yuv";
char *pPicPath1="/tmp/video1.yuv";
char *pPicPath2="/tmp/video2.yuv";
char *pPicPath3="/tmp/video3.yuv";

char *pcomph0PicPath0="/tmp/chvideo0.yuv";
char *pcomph1PicPath1="/tmp/chvideo1.yuv";

char *pcompPicPath0="/tmp/cvideo.yuv";


char *pdPicPath0="/tmp/dvideo0.yuv";
char *pdPicPath1="/tmp/dvideo1.yuv";
char *pdPicPath2="/tmp/dvideo2.yuv";
char *pdPicPath3="/tmp/dvideo3.yuv";
char *pdcompPicPath0="/tmp/dcvideo.yuv";

char *pRgbaOutPicPath="/tmp/outPic.rgba";

char *pRgbaInPicPath="/tmp/1024x600.rgba";

char *pYuvPicOutPath="/tmp/out.yuv";

#define CKFILE    "/tmp/ck.yuv"

using namespace g2dapi;


int main(int argc, char *argv[])
{
	if(argc <2)
	{
		printf("arc=%d \n",argc);
		exit(-1);
	}
    InitSignalCtrlC();
	
	printf("arc=%d  testid=%s\n",argc,argv[1]);

	int testid=atoi(argv[1]);
	
	struct timeval t1,t2;
    if(8 == testid){   //RGBA vertical convert
        iSubWidth = 1024;
        iSubHeight = 600;
        int inPicSize = iSubWidth*iSubHeight*4;
        ReadPicFileContent(pRgbaInPicPath,&m_DispMemOps0,inPicSize);
		
		printf("alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=%d\n",m_DispMemOps0.ion_buffer.fd_data.aw_fd);
		
		//reroll back
		WritePicFileContent(CKFILE,&m_DispMemOps0,inPicSize);
		
		//alloc output buff
        int outW = 1024;
        int outH = 600;
        int outPicSize = outW*outH*4;
		allocPicMem(&m_DispMemOps,outPicSize);  //output buf
		printf("alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=%d\n",m_DispMemOps.ion_buffer.fd_data.aw_fd);
		int g2dfd = g2dInit();
		
		t1.tv_sec = t1.tv_usec = 0;
	    t2.tv_sec = t2.tv_usec = 0;
		printf("start g2dflip:RGBA v flip \n");
		gettimeofday(&t1, NULL);
		
		stRECT src_rect={0,0,iSubWidth,iSubHeight};
		stRECT dst_rect={0,0,outW,outH};
		
		int src_fd = m_DispMemOps0.ion_buffer.fd_data.aw_fd;
		int dst_fd = m_DispMemOps.ion_buffer.fd_data.aw_fd;
		
		int flag =  (int)G2D_ROT_V;
		int fmt = (int)G2D_FORMAT_ABGR8888;
		int ret  = g2dClipByFd(g2dfd, src_fd,flag,fmt,iSubWidth,iSubHeight, 0, 0, iSubWidth, iSubHeight, dst_fd,fmt,outW, outH,0,0, outW, outH);
		
		gettimeofday(&t2, NULL);
		printf("RGBA v flip use time =%lld \n",int64_t(t2.tv_sec)*1000000000LL + int64_t(t2.tv_usec)*1000LL-(int64_t(t1.tv_sec)*1000000000LL + int64_t(t1.tv_usec)*1000LL));
		
		WritePicFileContent(pRgbaOutPicPath,&m_DispMemOps,outPicSize);
		
		g2dUnit(g2dfd);
		
		freePicMem(&m_DispMemOps);
		freePicMem(&m_DispMemOps0);
    }else if(5 == testid) {//rotate
        iSubWidth = 1280;
        iSubHeight = 720;
        int inPicSize = iSubWidth*iSubHeight*3/2;
        ReadPicFileContent(pPicPath0,&m_DispMemOps0,inPicSize);
		
		printf("alloc m_DispMemOps0.ion_buffer.fd_data.aw_fd=%d\n",m_DispMemOps0.ion_buffer.fd_data.aw_fd);
		
		//reroll back
		WritePicFileContent(CKFILE,&m_DispMemOps0,inPicSize);
		
		//alloc output buff
        int outW = 720;
        int outH = 1280;
        int outPicSize = outW*outH*3/2;
		allocPicMem(&m_DispMemOps,outPicSize);  //output buf
		printf("alloc m_DispMemOps.ion_buffer.fd_data.aw_fd=%d\n",m_DispMemOps.ion_buffer.fd_data.aw_fd);
		int g2dfd = g2dInit();
		
		t1.tv_sec = t1.tv_usec = 0;
	    t2.tv_sec = t2.tv_usec = 0;
		printf("start g2dClipByFd rotate \n");
		gettimeofday(&t1, NULL);
		
		stRECT src_rect={0,0,iSubWidth,iSubHeight};
		stRECT dst_rect={0,0,outW,outH};
		
		int src_fd = m_DispMemOps0.ion_buffer.fd_data.aw_fd;
		int dst_fd = m_DispMemOps.ion_buffer.fd_data.aw_fd;
		
		int flag =  (int)G2D_ROT_90;
		int fmt = (int)G2D_FORMAT_YUV420UVC_V1U1V0U0;
		int ret  = g2dClipByFd(g2dfd, src_fd,flag,fmt,iSubWidth,iSubHeight, 0, 0, iSubWidth, iSubHeight, dst_fd,fmt,outW, outH,0,0, outW, outH);
		
		gettimeofday(&t2, NULL);
		printf("g2dClipByFd rotate use time =%lld \n",int64_t(t2.tv_sec)*1000000000LL + int64_t(t2.tv_usec)*1000LL-(int64_t(t1.tv_sec)*1000000000LL + int64_t(t1.tv_usec)*1000LL));
		
		WritePicFileContent(pYuvPicOutPath,&m_DispMemOps,outPicSize);
		
		g2dUnit(g2dfd);
		
		freePicMem(&m_DispMemOps);
		freePicMem(&m_DispMemOps0);		

    }else if(3 == testid) {//4in 1 compose
		//read two file to sunximem
		ReadPicFileContent(pPicPath0,&m_DispMemOps0,iSubWidth*iSubHeight*3/2);
		ReadPicFileContent(pPicPath1,&m_DispMemOps1,iSubWidth*iSubHeight*3/2);
		ReadPicFileContent(pPicPath2,&m_DispMemOps2,iSubWidth*iSubHeight*3/2);
		ReadPicFileContent(pPicPath3,&m_DispMemOps3,iSubWidth*iSubHeight*3/2);

		//reroll back
		WritePicFileContent(CKFILE,&m_DispMemOps0,iSubWidth*iSubHeight*3/2);
		
		//alloc compse buff
		allocPicMem(&m_DispMemOps,iWidth*iHeight*3/2);

		//compose
		int g2dfd=g2dInit();
		
		t1.tv_sec = t1.tv_usec = 0;
	    t2.tv_sec = t2.tv_usec = 0;
		printf("start trans 4x 720p to 1x 2560x1440 compose \n");
		gettimeofday(&t1, NULL);
		#if 1
		int outfd = m_DispMemOps.ion_buffer.fd_data.aw_fd;
		int infd[4];
		infd[0] = m_DispMemOps0.ion_buffer.fd_data.aw_fd;
		infd[1] = m_DispMemOps1.ion_buffer.fd_data.aw_fd;
		infd[2] = m_DispMemOps2.ion_buffer.fd_data.aw_fd;
		infd[3] = m_DispMemOps3.ion_buffer.fd_data.aw_fd;
		int ret = -1;
		int flag =  (int)G2D_ROT_0;
		int fmt = (int)G2D_FORMAT_YUV420UVC_V1U1V0U0;
		ret  = g2dClipByFd(g2dfd, infd[0],flag,fmt,iSubWidth, iSubHeight,0,0, iSubWidth, iSubHeight,outfd,fmt, iSubWidth, iSubHeight,0,           0,        iWidth, iHeight);
		ret |= g2dClipByFd(g2dfd, infd[1],flag,fmt,iSubWidth, iSubHeight,0,0, iSubWidth, iSubHeight,outfd,fmt, iSubWidth, iSubHeight,iSubWidth,   0,        iWidth, iHeight);
		ret |= g2dClipByFd(g2dfd, infd[2],flag,fmt,iSubWidth, iSubHeight,0,0, iSubWidth, iSubHeight,outfd,fmt, iSubWidth, iSubHeight,0,        iSubHeight,  iWidth, iHeight);
		ret |= g2dClipByFd(g2dfd, infd[3],flag,fmt,iSubWidth, iSubHeight,0,0, iSubWidth, iSubHeight,outfd,fmt, iSubWidth, iSubHeight,iSubWidth,iSubHeight , iWidth, iHeight);
		
		#else
		//dont use g2dClip in t5
		g2dClip(g2dfd,(void *)m_DispMemOps0.phy, iSubWidth, iSubHeight, 0, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps.phy, iWidth, iHeight, 0, 0);
		g2dClip(g2dfd,(void *)m_DispMemOps0.phy, iSubWidth, iSubHeight, 0, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps.phy, iWidth, iHeight, iSubWidth, 0);
		g2dClip(g2dfd,(void *)m_DispMemOps0.phy, iSubWidth, iSubHeight, 0, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps.phy, iWidth, iHeight, 0, iSubHeight);
		g2dClip(g2dfd,(void *)m_DispMemOps0.phy, iSubWidth, iSubHeight, 0, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps.phy, iWidth, iHeight, iSubWidth, iSubHeight);
		#endif
		gettimeofday(&t2, NULL);
		printf("end trans 4x 720p to 1x 2560x1440 compose time =%lld \n",int64_t(t2.tv_sec)*1000000000LL + int64_t(t2.tv_usec)*1000LL-(int64_t(t1.tv_sec)*1000000000LL + int64_t(t1.tv_usec)*1000LL));
		
		//save compose buffer
		WritePicFileContent(pcompPicPath0,&m_DispMemOps,iWidth*iHeight*3/2);
		
		g2dUnit(g2dfd);
		
		freePicMem(&m_DispMemOps);
		freePicMem(&m_DispMemOps0);
		freePicMem(&m_DispMemOps1);
		freePicMem(&m_DispMemOps2);
		freePicMem(&m_DispMemOps3);

		
    }else if(2 == testid){  //2560x1440 -->4 720p
		//reada BIG file to sunximem
		ReadPicFileContent(pdcompPicPath0,&m_DispMemOps,iWidth*iHeight*3/2);

		//alloc de-compse buff
		allocPicMem(&m_DispMemOps0,iSubWidth*iSubHeight*3/2);
		allocPicMem(&m_DispMemOps1,iSubWidth*iSubHeight*3/2);
		allocPicMem(&m_DispMemOps2,iSubWidth*iSubHeight*3/2);
		allocPicMem(&m_DispMemOps3,iSubWidth*iSubHeight*3/2);

		//compose
		int g2dfd=g2dInit();
		
		//int g2dClip(int g2dHandle,void* psrc, int src_w, int src_h, int src_x, int src_y, int width, int height, void* pdst, int dst_w, int dst_h, int dst_x, int dst_y)
		t1.tv_sec = t1.tv_usec = 0;
	    t2.tv_sec = t2.tv_usec = 0;
		printf("start trans 1x [%dx%d]  to 4x [%dx%d] to decompose \n",iWidth,   iHeight, iSubWidth, iSubHeight);
		gettimeofday(&t1, NULL);
	#if 1
		int infd = m_DispMemOps.ion_buffer.fd_data.aw_fd;
		int outfd[4];
		outfd[0] = m_DispMemOps0.ion_buffer.fd_data.aw_fd;
		outfd[1] = m_DispMemOps1.ion_buffer.fd_data.aw_fd;
		outfd[2] = m_DispMemOps2.ion_buffer.fd_data.aw_fd;
		outfd[3] = m_DispMemOps3.ion_buffer.fd_data.aw_fd;
		int ret = -1;
		int flag =  (int)G2D_ROT_0;
		int fmt = (int)G2D_FORMAT_YUV420UVC_V1U1V0U0;
		ret  = g2dClipByFd(g2dfd, infd,flag,fmt,iSubWidth,iSubHeight,0,           0,          iWidth,   iHeight,   
                                  outfd[0], fmt,iSubWidth,iSubHeight,0,           0,          iSubWidth, iSubHeight);
        
		ret |= g2dClipByFd(g2dfd, infd,flag,fmt,iSubWidth,iSubHeight,0,           0,          iWidth,   iHeight,   
                                  outfd[1], fmt,iSubWidth,iSubHeight,0,           0,          iSubWidth, iSubHeight);
        
		ret |= g2dClipByFd(g2dfd, infd,flag,fmt,iSubWidth,iSubHeight,0,           0,          iWidth,   iHeight,   
                                  outfd[2], fmt,iSubWidth,iSubHeight,0,           0,          iSubWidth, iSubHeight);
        
		ret |= g2dClipByFd(g2dfd, infd,flag,fmt,iSubWidth,iSubHeight,0,           0,          iWidth,   iHeight,   
                                  outfd[3], fmt,iSubWidth,iSubHeight,0,           0,          iSubWidth, iSubHeight);
		
	#else
		//dont use g2dClip in t5
		g2dClip(g2dfd,(void *)m_DispMemOps.phy, iWidth, iHeight, 0, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps0.phy, iSubWidth, iSubHeight, 0, 0);

		g2dClip(g2dfd,(void *)m_DispMemOps.phy, iWidth, iHeight, iSubWidth, 0, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps1.phy, iSubWidth, iSubHeight, 0, 0);
		
		g2dClip(g2dfd,(void *)m_DispMemOps.phy, iWidth, iHeight, 0, iSubHeight, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps2.phy, iSubWidth, iSubHeight, 0, 0);
		
		g2dClip(g2dfd,(void *)m_DispMemOps.phy, iWidth, iHeight, iSubWidth, iSubHeight, iSubWidth, iSubHeight, \
						(void *)m_DispMemOps3.phy, iSubWidth, iSubHeight, 0, 0);
	#endif
		gettimeofday(&t2, NULL);
		printf("end trans 1x 2560x1440  to 4x 1280x720   time =%lld \n",int64_t(t2.tv_sec)*1000000000LL + int64_t(t2.tv_usec)*1000LL-(int64_t(t1.tv_sec)*1000000000LL + int64_t(t1.tv_usec)*1000LL));

		g2dUnit(g2dfd);
		
		//save de-compose buffer
		WritePicFileContent(pdPicPath0,&m_DispMemOps0,iSubWidth* iSubHeight*3/2);
		WritePicFileContent(pdPicPath1,&m_DispMemOps1,iSubWidth* iSubHeight*3/2);
		WritePicFileContent(pdPicPath2,&m_DispMemOps2,iSubWidth* iSubHeight*3/2);
		WritePicFileContent(pdPicPath3,&m_DispMemOps3,iSubWidth* iSubHeight*3/2);

		//free mem
		freePicMem(&m_DispMemOps);
		freePicMem(&m_DispMemOps0);
		freePicMem(&m_DispMemOps1);
		freePicMem(&m_DispMemOps2);
		freePicMem(&m_DispMemOps2);
    }
	else {
        printf("Invid Param\n");
    }
    return 0;
}

/**************************************
end
***************************************/

