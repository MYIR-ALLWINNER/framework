#include <stdio.h>
#include <stdlib.h>
#include "sunxiMemInterface.h"

#define PIC_W  1280
#define PIC_H  720
#define NV21_PIC_SIZE  (PIC_W * PIC_H * 3/2)

#define PIC_PATH "./a.yuv"

dma_mem_des_t gMem;
char gPic[NV21_PIC_SIZE];

static int fillYuvData(int y, int c)
{
	memset(&gPic[0], y, PIC_W * PIC_H);  //fill Y zoom 
	memset(&gPic[PIC_W * PIC_H], c, PIC_W * PIC_H/2);  //fill C zoom
	
	//save to file
	FILE *fd = fopen(PIC_PATH, "w+");
	if (!fd) {
		printf("Open ./a.yuv error\n");
		return -1;
	}
	fwrite((void *)gPic, 1, NV21_PIC_SIZE, fd);
	fclose(fd);
	printf("%s success!!!\n",__FUNCTION__);
	return 0;
}

#include "hwdisp2.h"
static android::HwDisplay* gdisp;
static void showYuvPicDE(int dmafd, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    int screen_id=0;
	int ch_id = 0;
	int lyr_id = 0;

	if(gdisp == NULL){
		printf("gdisp is NULL");
		return ;
	}
	
	struct view_info frame={0,0,w,h};
	int layer0=gdisp->aut_hwd_layer_request(&frame,screen_id,ch_id,lyr_id);
	gdisp->aut_hwd_layer_sufaceview(layer0,&frame);

	struct src_info src={PIC_W, PIC_H, DISP_FORMAT_YUV420_SP_VUVU};
	gdisp->aut_hwd_layer_set_src(layer0, &src, 0,dmafd);
	
	struct view_info crop = {0,0,PIC_W, PIC_H};
	gdisp->aut_hwd_layer_set_rect(layer0,&crop);
	
	gdisp->aut_hwd_layer_set_zorder(layer0,6);
	
	gdisp->aut_hwd_layer_open(layer0);
	
}

static void releaseDE( unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    int screen_id=0;
	int ch_id = 1;
	int lyr_id = 0;
	
	if(gdisp == NULL){
		printf("gdisp is NULL");
		return ;
	}
	
	struct view_info frame={0, 0 ,w ,h};
	int layer0=gdisp->aut_hwd_layer_request(&frame,screen_id,ch_id,lyr_id);
	gdisp->aut_hwd_layer_close(layer0);
}

int main(int argc, char** argv)
{
	int y = 70;
	int c = 240;
	if(argc == 2){
		c = atoi(argv[1]);
	}else if(argc == 3){
		y = atoi(argv[1]);
		c = atoi(argv[2]);
	}
	printf("argc=%d y=%d c=%d\n",argc,y,c);
	fillYuvData(y,c);
	//fillYuvData(50,200);
	
	int ret = allocOpen(MEM_TYPE_DMA, &gMem, NULL);
	if(ret < 0){
		printf("allocOpen failed.\n");
		return -1;
	}
	
	int testcnt = 0;
	while(1){
		printf("============================testcnt(%d)================================\n",testcnt++);
		gMem.size = NV21_PIC_SIZE;
		ret = allocAlloc(MEM_TYPE_DMA, &gMem, NULL);
		if(ret < 0){
			printf("allocAlloc failed.\n");
			return -1;
		}
		
		printf("alloc sucess!!!\n");
		printf("gMem.vir=%p gMem.phy=%p dmafd=%d,alloc len=%d\n",
				gMem.vir, gMem.phy, gMem.ion_buffer.fd_data.aw_fd, gMem.size);
		
		//save data to file
		memset((void *)gMem.vir,0x5A,gMem.size);
		flushCache(MEM_TYPE_DMA, &gMem, NULL);
		FILE *fd = fopen("./a.out", "w+");
		if (!fd) {
			printf("Open file error\n");
		}
		fwrite((void *)gMem.vir, 1, gMem.size, fd);
		fclose(fd);
		
		memcpy((void *)gMem.vir ,gPic,NV21_PIC_SIZE);
		
		gdisp = android::HwDisplay::getInstance();
		int dmafd = gMem.ion_buffer.fd_data.aw_fd;
		
		int screenW = 1280;
		int screenH = 800;
		showYuvPicDE(dmafd,0,0,screenW,screenH);
		//system("cat /sys/class/disp/disp/attr/sys");
		printf("showing pic.\n");
		sleep(1);
		releaseDE(0,0,screenW,screenH);
		allocFree(MEM_TYPE_DMA, &gMem, NULL);
		memset(&gMem, 0 ,sizeof(gMem));
	}
	printf("exit.\n");
	return 0;
}


