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
#ifndef _RENDERENGINE_H_
#define _RENDERENGINE_H_

#include <iostream>
#include <sstream>
#include <vector>

#include "renderengine_uapi.h"

using namespace std;

class RenderEngine {
public:
	/* @width/height: size of render result
	 * @onScreen: if render on screen
	 */
	RenderEngine(bool onScreen, unsigned int srcFmt,
				unsigned int dstFmt);
	~RenderEngine();

	void setOffScreenTarget(unsigned int screen_w,
				unsigned int screen_h,
				int dmaFd,
				unsigned int dataOffset);
	void setSurface(
		      struct RESurface *surface);
	int drawLayerOffScreenAtCentral(
		      unsigned char rotateType, void **sync);
	int drawLayerOffScreen(
		      void **sync);
	/* wait for rendering finishment
	 * Note: this sync can be used in IPC operation
	 */
	int waitSync(void *sync);


	int drawLayerOnScreenAtCentral(
		      unsigned char rotateType);
	int drawLayerOnScreen();
private:
	struct RE_Texture {
		void *img;
		unsigned int tex;
	};

	struct RE_Fbo {
		void *img;
		unsigned int tex;
		unsigned int fbo;
	};

	unsigned int view_width;
	unsigned int view_height;

	unsigned int srcFormat, dstFormat;

	//Only used in offscreen rendering
	int dstDmaFd;
	unsigned int dstDataOffset;

	void *REDisplay;
	void *REContext;
	void *RESurface;
	int egl_major, egl_minor;
	void *REConfig;

	void *shaderProgram;

	struct RE_Texture RETex;
	struct RE_Fbo REFbo;

	bool REOnScreen;

	vector<struct RESurface *> RESf;

	int initEGL(bool onScreen);
	int exitEGL();

	int initShader(const char *vertex, const char *fragment);
	int exitShader();

	int setupTexture(int dmafd, unsigned int dataOffset,
			 struct RE_Texture *retex,
			 unsigned int width, unsigned int height,
			 unsigned int format);
	int destroyTexture(struct RE_Texture *retex);

	int createFBO(int dmafd, unsigned int dataOffset,
		     unsigned int format, struct RE_Fbo *refbo);
	int destroyFBO(struct RE_Fbo *refbo);

	int drawLayerOnScreenCore(
		int srcFd,
		unsigned int srcDataOffset,
		unsigned int srcWidth, unsigned int srcHeight,
		struct RE_rect *srcCrop,
		float tX, float tY,
		float scaleX, float scaleY,
		float rotateAngle, unsigned char rotateType);

	int drawLayerOffScreenCore(
			int srcFd, unsigned int srcDataOffset,
			unsigned int srcWidth, unsigned int srcHeight,
			struct RE_rect *srcCrop,
			float tX, float tY,
			float scaleX, float scaleY,
			float rotateAngle, unsigned char rotateType);

	float getRotateScreenRatioAdaptiveScaleRate(
		float width, float height, float degree);
	float getRotateLayerRatioAdaptiveScaleRate(
		float screen_width, float screen_height,
        float layer_width, float layer_height,
        float degree);

	void getRotateScaleRate(
            float view_width, float view_height,
            float layer_width, float layer_height,
			float rotateAngle, unsigned char rotateType,
			float *widthRate, float *heightRate);
	void REdump(void);
};
#endif
