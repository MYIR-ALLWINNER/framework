#ifndef __LIBVE_DECORDER2_H__
#define __LIBVE_DECORDER2_H__

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <pthread.h>
#include "vencoder.h"			//* video encode library in "LIBRARY/CODEC/VIDEO/ENCODER"

#include "vdecoder.h"
#include "sunxiMemInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

	void Libve_dec2(VideoDecoder ** mVideoDecoder, const void *in, void *out,
					VideoStreamInfo * pVideoInfo, VideoStreamDataInfo * dataInfo,
					VConfig * pVconfig, dma_mem_des_t *memParam);
	int Libve_init2(VideoDecoder ** mVideoDecoder, VideoStreamInfo * pVideoInfo,
					VConfig * pVconfig);
	int Libve_exit2(VideoDecoder ** mVideoDecoder);

#ifdef __cplusplus
}
#endif
#endif							/* __LIBVE_DECORDER2_H__ */
