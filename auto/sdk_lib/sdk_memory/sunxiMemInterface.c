#include "stdlib.h"
#include <stdio.h>

#include "memoryAdapter.h"
#include <sc_interface.h>
//#include <cutils/log.h>
#include "sunxiMemInterface.h"
#include "DmaIon.h"
#include <ion_mem_alloc.h>

#define SC_MEM_OPSS 0
#define ALOGD printf
#define ALOGE printf
#define ALOGV printf

int allocOpen(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	int ret = FAIL;
	if(NULL == param_in){
		ALOGE("allocOpen failed,param_in is null\n");
		return -1;
	}
	
	dma_mem_des_t* p =  param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        ret = IonAllocOpen();
		break;	
		
	case MEM_TYPE_CDX_NEW:
		#if SC_MEM_OPSS
    		p->ops = MemAdapterGetOpsS();
    		if(NULL != p->ops){
    			ret = CdcMemOpen((struct ScMemOpsS *)p->ops);
    		}else{
    			ALOGE("allocOpen failed,p->ops null\n");
    		}
		#else
    		p->ops = GetMemAdapterOpsS();  //MemAdapterGetOpsS
    		if(NULL != p->ops){
    			ret = SunxiMemOpen((struct SunxiMemOpsS *)p->ops);
    		}else{
    			ALOGE("allocOpen failed,p->ops null\n");
    		}
		#endif
		break;
		
	default:
		ALOGE("allocOpen: can't find memType=%d\n",memType);
		break;
	}

	return ret;
}

int allocClose(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	int ret = FAIL;
	if(NULL == param_in){
		ALOGE("allocClose failed,param_in is null\n");
		return -1;
	}
	dma_mem_des_t* p =  param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        return IonAllocClose();
		break;	
		
	case MEM_TYPE_CDX_NEW:
		if(NULL != p->ops){
    		#if SC_MEM_OPSS
    			CdcMemClose((struct ScMemOpsS *)p->ops);
            #else
    			SunxiMemClose((struct SunxiMemOpsS *)p->ops);
            #endif
			p->ops = NULL;
			ret = SUCCESS;
		}else{
			ALOGE("allocClose failed,p->ops null\n");
		}
		break;
		
	default:
		ALOGE("allocClose: can't find memType=%d\n",memType);
		break;
	}
	return ret;
}
int allocAlloc(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	int ret = FAIL;
	if(NULL == param_in){
		ALOGE("allocAlloc failed,input param is null\n");
		return ret;
	}
	
	dma_mem_des_t* p = param_in;
	p->memType = memType;
	switch(memType){
	case MEM_TYPE_DMA:
        p->vir = IonAlloc(p->size);
        p->phy = IonVir2phy((void*)p->vir);
        p->ion_buffer.vir = p->vir;
        p->ion_buffer.phy = p->phy; 
        p->ion_buffer.fd_data.aw_fd = IonVir2fd((void*)p->vir);
		ret = 0;
		break;	
		
	case MEM_TYPE_CDX_NEW:
		if(p->ops!=NULL){
		#if SC_MEM_OPSS
			p->vir = (unsigned long)CdcMemPalloc((struct ScMemOpsS *)p->ops, p->size,NULL,NULL);
			p->phy = (unsigned long)CdcMemGetPhysicAddress((struct ScMemOpsS *)p->ops, (void*)p->vir);
			//p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
        #else
			p->vir = (unsigned long)SunxiMemPalloc((struct SunxiMemOpsS *)p->ops, p->size);
			p->phy = (unsigned long)SunxiMemGetPhysicAddressCpu((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
			p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
        #endif
		}else{
			p->vir = 0;
			p->phy = 0;
		}
		ret = 0;
		break;

	default:
		ALOGE("allocAlloc: can't find memType=%d\n",memType);
		break;
	}

	return ret;
}

void allocFree(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	if(NULL == param_in){
		ALOGE("allocFree failed,input param is null\n");
		return;
	}
	dma_mem_des_t* p = param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        IonFree((void*)param_in->vir);
        memset(&p->ion_buffer,0,sizeof(p->ion_buffer));
		break;	
		
	case MEM_TYPE_CDX_NEW:
		if(p->ops!=NULL){
		#if SC_MEM_OPSS
			CdcMemPfree((struct ScMemOpsS *)p->ops, (void*)p->vir,NULL,NULL);
        #else
			SunxiMemPfree((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
        #endif
		}
		break;

	default:
		ALOGE("allocFree: can't find memType=%d\n",memType);
		break;
	}
}

int allocVir2phy(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	int ret = FAIL;
	if(NULL == param_in){
		ALOGE("allocVir2phy failed,input param is null\n");
		return -1;
	}
	
	dma_mem_des_t* p = param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        p->phy = IonVir2phy((void*)p->vir);
		break;	
		
	case MEM_TYPE_CDX_NEW:
		if(p->ops!=NULL){
		#if SC_MEM_OPSS
			p->phy = (unsigned long)CdcMemGetPhysicAddress((struct ScMemOpsS *)p->ops, (void*)p->vir);
			//p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
        #else
			p->phy = (unsigned long)SunxiMemGetPhysicAddressCpu((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
			p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
        #endif
		}else
			p->phy = 0;
		break;

	default:
		ALOGE("allocVir2phy: can't find memType=%d\n",memType);
		break;
	}
	
	return ret;
}

//warning !!!below function no test
int allocPhy2vir(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	int ret = FAIL;
	if(NULL == param_in){
		ALOGE("allocPhy2vir failed,input param is null\n");
		return -1;
	}
	
	dma_mem_des_t* p = param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        p->vir = IonPhy2vir((void*)p->phy);
		break;	
		
	case MEM_TYPE_CDX_NEW:
		if(p->ops!=NULL){
      		#if SC_MEM_OPSS
			p->vir = (unsigned long)CdcMemGetVirtualAddress((struct ScMemOpsS *)p->ops, (void*)p->phy);
			//p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct ScMemOpsS *)p->ops, (void*)p->vir);
            #else
			p->vir = (unsigned long)SunxiMemGetVirtualAddressCpu((struct SunxiMemOpsS *)p->ops, (void*)p->phy);
			p->ion_buffer.fd_data.aw_fd = SunxiMemGetBufferFd((struct SunxiMemOpsS *)p->ops, (void*)p->vir);
            #endif
		}			
		break;

	default:
		ALOGE("allocPhy2vir: can't find memType=%d\n",memType);
		break;
	}

	return ret;
}

void flushCache(unsigned int memType, dma_mem_des_t * param_in, void * param_out)
{
	if(NULL == param_in){
		ALOGE("flushCache failed,input param is null\n");
		return;
	}

	dma_mem_des_t* p = param_in;
	switch(memType){
	case MEM_TYPE_DMA:
        IonDmaSync(p->ion_buffer.fd_data.aw_fd);
		break;	
		
	case MEM_TYPE_CDX_NEW:
    	{
	    if(p->ops!=NULL)
      		#if SC_MEM_OPSS
            CdcMemFlushCache((struct ScMemOpsS *)p->ops,  (void*)p->vir, p->size);
            #else
		    SunxiMemFlushCache((struct SunxiMemOpsS *)p->ops, (void*)p->vir, p->size);
            #endif
    	}
		break;

	default:
		ALOGE("flushCache: can't find memType=%d\n",memType);
		break;
	}
}
