#ifndef __SUNXI_MEM_INTERFACE_H
#define __SUNXI_MEM_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DmaIon.h"

#define FAIL -1
#define SUCCESS 0

/* This struct is for many platform interface
 *
*/

#define MEM_TYPE_DMA 1
#define MEM_TYPE_CDX_NEW 2

typedef struct paramStruct {
	void* ops;
	unsigned int memType;
	unsigned long phy;
	unsigned long vir;
	unsigned int size;
	ion_buffer_node ion_buffer;
} paramStruct_t;
//ion one block Memory Descriptor
typedef paramStruct_t dma_mem_des_t;
int allocOpen(unsigned int memType, dma_mem_des_t * param_in,void * param_out);
int allocClose(unsigned int memType, dma_mem_des_t * param_in,void * param_out);
int allocAlloc(unsigned int memType, dma_mem_des_t * param_in,void * param_out);
void allocFree(unsigned int memType, dma_mem_des_t * param_in, void * param_out);
int allocVir2phy(unsigned int memType, dma_mem_des_t * param_in, void * param_out);
int allocPhy2vir(unsigned int memType, dma_mem_des_t * param_in, void * param_out);
void flushCache(unsigned int memType, dma_mem_des_t * param_in, void * param_out);
#ifdef __cplusplus
}
#endif

#endif