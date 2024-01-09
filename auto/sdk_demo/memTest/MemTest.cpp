#include <stdio.h>
#include <stdlib.h>
#include "sunxiMemInterface.h"

#define PIC_W  1280
#define PIC_H  720
#define NV21_PIC_SIZE  (PIC_W * PIC_H * 3/2)

dma_mem_des_t gMem;

#define MODULE_VERSION "V2.0.20220506"

int main(int argc, char** argv)
{
	printf("MemTest version:%s\n", MODULE_VERSION);
	int ret = allocOpen(MEM_TYPE_CDX_NEW, &gMem, NULL);
	if(ret < 0){
		printf("allocOpen failed.\n");
		return -1;
	}
	int testcnt = 0;
	while(1){
		printf("============================testcnt(%d)================================\n",testcnt++);
		gMem.size = NV21_PIC_SIZE;
		ret = allocAlloc(MEM_TYPE_CDX_NEW, &gMem, NULL);
		if(ret < 0){
			printf("allocAlloc failed.\n");
			return -1;
		}
		
		printf("alloc sucess!!!\n");
		printf("gMem.vir=%p gMem.phy=%p dmafd=%d,alloc len=%d\n",
				gMem.vir, gMem.phy, gMem.ion_buffer.fd_data.aw_fd, gMem.size);

		//save data to file
		memset((void *)gMem.vir,0x5A,gMem.size);
		flushCache(MEM_TYPE_CDX_NEW, &gMem, NULL);
		FILE *fd = fopen("./a.out", "w+");
		if (!fd) {
			printf("Open file error\n");
		}
		fwrite((void *)gMem.vir, 1, gMem.size, fd);
		fclose(fd);
		
		allocFree(MEM_TYPE_CDX_NEW, &gMem, NULL);

		sleep(3);
	}
	
	return 0;
}


