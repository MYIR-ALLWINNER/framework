/*
 * This confidential and proprietary software should be used
 * under the licensing agreement from Allwinner Technology.

 * Copyright (C) 2020-2030 Allwinner Technology Limited
 * All rights reserved.

 * Author:zhengwanyu <zhengwanyu@allwinnertech.com>

 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Allwinner Technology Limited.
 */
#ifndef _RENDERENGINE_UAPI_H_
#define _RENDERENGINE_UAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

enum RotateType{
	/*do NOT do any scale when rotate*/
	RE_ROTATE_NO_ADAPTIVE_SCALE = 0,

	/*do adaptive scale to screen size with screen ratio when rotate*/
	RE_ROTATE_ADAPTIVE_SCALE_WITH_SCREEN_RATIO = 1,

	/*when rotate 90/270, spread fullscreen.*/
	/*when rotate other angles, do adaptive scale to screen size*/
	RE_ROTATE_ADAPTIVE_SCALE_WITH_SCREEN_RATIO_90_270_FULL_SCREEN = 2,

	/*do adaptive scale to screen size with layer ratio when rotate*/
	RE_ROTATE_ADAPTIVE_SCALE_WITH_LAYER_RATIO = 3,

	RE_ROTATE_TYPE_NUM,
};

struct RE_rect {
	unsigned int left;
	unsigned int top;
	unsigned int right;
	unsigned int bottom;
};

/*init/destroy rendering interface bellows*/
typedef void *RenderEngine_t;

RenderEngine_t renderEngineCreate(bool onScreen, unsigned char debug,
				unsigned int srcFormat, unsigned int dstFormat);
void renderEngineDestroy(RenderEngine_t RE);

struct RESurface {
	int srcFd;
	unsigned int srcDataOffset;

	unsigned int srcWidth, srcHeight;

	struct RE_rect srcCrop;

	union {
		struct RE_rect dstWinRect;
		struct RE_rect reserved0; //used by renderEngineDrawLayerOnScreenAtCentral()
	};

	float rotateAngle;
};


/*OnScreen rendering interface bellows*/
void renderEngineSetSurface(RenderEngine_t RE,
			struct RESurface *surface);
int renderEngineDrawOnScreenAtCentral(RenderEngine_t RE,
	 unsigned char rotateType);

int renderEngineDrawOnScreen(RenderEngine_t RE);

/*OffScreen rendering interface bellows*/
void renderEngineSetOffScreenTarget(RenderEngine_t RE,
				unsigned int screen_w,
				unsigned int screen_h,
				int dmaFd,
				unsigned int dataOffset);

/*@sync: return glflush sync value*/
int renderEngineDrawOffScreenAtCentral(
		      RenderEngine_t RE,
		      unsigned char rotateType,
		      void **sync);

int renderEngineDrawOffScreen(RenderEngine_t RE, void **sync);

/* wait for rendering finishment
 * Note: this sync can be used in IPC operation
 */
int renderEngineWaitSync(RenderEngine_t RE, void *sync);

#ifdef __cplusplus
}
#endif

#endif
