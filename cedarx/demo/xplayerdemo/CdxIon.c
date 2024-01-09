/*
* Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
* All rights reserved.
*
* File : ionAlloc.c
* Description :
* History :
*   Author  : weihai <liweihai@allwinnertech.com>
*   Date    : 2017/07/21
*   Comment :
*
*
*/

//#define CONFIG_LOG_LEVEL    LOG_LEVEL_VERBOSE
#define LOG_TAG "ionAlloc"

#include <cdx_log.h>
#include <CdxIon.h>

#include <sys/ioctl.h>
#include <errno.h>
#include <sc_interface.h>
#include <memoryAdapter.h>
static struct ScMemOpsS *memops = NULL;

/*funciton begin*/
int CdxIonOpen()
{
    logd("begin ion_alloc_open \n");
    memops = MemAdapterGetOpsS();
    if(memops == NULL )
        return -1;
    else
        return CdcMemOpen(memops);
}

void CdxIonClose()
{
    CdcMemClose(memops);
}

// return virtual address: 0 failed
void * CdxIonPalloc(int size)
{
    return CdcMemPalloc(memops, size, NULL, NULL);
}

void CdxIonPfree(void * pbuf)
{
    return CdcMemPfree(memops, pbuf, NULL, NULL);
}

void *CdxIonVir2Phy(void * pbuf)
{
    return CdcMemGetPhysicAddress(memops, pbuf);
}


void * CdxIonPhy2Vir(void * pbuf)
{
    return CdcMemGetVirtualAddress(memops, pbuf);
}

void CdxIonFlushCache(void* startAddr, int size)
{
    CdcMemFlushCache(memops, startAddr, size);
    return;
}

