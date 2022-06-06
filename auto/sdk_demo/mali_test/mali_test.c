#include <stdio.h>

/*
 * Copyright (c) 2011-2013 Luc Verhaegen <libv@skynet.be>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Hello triangle, adapted for native display on libMali.so.
 */
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <sys/time.h>
#include <EGL/eglext.h>
#include <fbdev_window.h>

#define WIDTH 1280
#define HEIGHT 800
GLuint buffer2;


struct fbdev_window native_window = {
    .width = WIDTH,
    .height = HEIGHT,
};


static const char *vertex_shader_source =
    "attribute vec4 aPosition;    \n"
    "attribute vec4 aTexCoords;    \n"
    "varying vec2 yuvTexCoords;\n"
    "uniform float psize;\n"
    "uniform mat4 Mprojection;\n"
    "void main()                  \n"
    "{                            \n"
    "    yuvTexCoords = aTexCoords.xy;\n"
    "    gl_Position = Mprojection * aPosition; \n"
    "    gl_PointSize = psize;"
    "}\n";

static const char *fragment_shader_source =
    "#extension GL_OES_EGL_image_external : require\n"
    "precision highp float;\n"
    "uniform int sel;\n"
    "uniform sampler2D yuvTexSampler;\n"
    "uniform samplerExternalOES extTexSampler;\n"
    "varying vec2 yuvTexCoords;\n"
    "void main() {\n"
    " if (sel == 0)\n"
    "  gl_FragColor = texture2D(yuvTexSampler, yuvTexCoords);\n"
    "else\n"
    "  gl_FragColor = texture2D(extTexSampler, yuvTexCoords);\n"
    "}\n";

static GLfloat vVertices[] = {
		0.0f,  0.5f, 0.0f,
               -0.5f, -0.5f, 0.0f,
                0.5f, -0.9f, 0.0f,
                0.2f, -0.4f, 0.0f};
static GLfloat vVertices_01[] = {
                0.5f, 0.0f, 0.0f,
               -0.5f, 0.0f, 0.0f,
                0.0f, -0.5f, 0.0f};

static GLfloat vVertices_02[] = {
                0.5f, 0.0f, 0.0f,
               -0.5f, 0.0f, 0.0f,
                0.0f, -0.5f, 0.0f};

static GLfloat vTexCoords[] = {
		0.5f, 0.0f,
          	1.0f, 0.5f,
          	0.0f, 0.5f,
          	0.5f, 1.0f};

static GLfloat vTexCoords2[] = {
		0.5f, 0.75f,
          	0.75f, 0.5f,
          	0.25f, 0.5f,
          	0.5f, 0.25f};

static GLfloat proMatrix[] = {
		0.99255f, 0.14187f, 0.0f, 0.0f,
               -0.14187f, 0.99255f, 0.0f, 0.0f,
          	0.0f,     0.0f,     1.0f, 0.0f,
          	0.0f,     0.0f,     0.0f, 1.0f};

static GLfloat proMatrix1x1[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
          	0.0f, 1.0f, 0.0f, 0.0f,
          	0.0f, 0.0f, 1.0f, 0.0f,
          	0.0f, 0.0f, 0.0f, 1.0f};

static EGLint const config_attribute_list[] = {
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_BUFFER_SIZE, 32,

    EGL_STENCIL_SIZE, 0,
    EGL_DEPTH_SIZE, 0,

    EGL_SAMPLES, 4,

    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,

    EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PIXMAP_BIT,


    EGL_NONE
};

static EGLint window_attribute_list[] = {
    EGL_NONE
};

static const EGLint context_attribute_list[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

EGLDisplay egl_display;
EGLSurface egl_surface;

void Redraw(int x,int y, int width, int height, int sel)
{

    glViewport(x, y, width, height);

    if(sel) {
            glBindBuffer(GL_ARRAY_BUFFER, buffer2);
            glBufferSubData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3, sizeof(GLfloat)*9, vVertices_01);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
    }else{
            glBindBuffer(GL_ARRAY_BUFFER, buffer2);
            glBufferSubData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3, sizeof(GLfloat)*9, vVertices_02);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int main(int argc, char *argv[])
{
	EGLint egl_major, egl_minor;
	EGLConfig config;
	EGLint num_config;
	EGLContext context;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;
	GLint ret;
	GLint width, height;
	char *redbuffer;
	GLuint tex_a;
	GLuint tex_b;
	GLuint tex_c;
	GLuint gYuvTexSamplerHandle;
	GLuint gselHandle;
	GLuint gsizeHandle;
	GLuint proMatrixHandle;
	GLuint renderbuffers;
	GLuint renderbuffers2;
	GLuint fbo;
	GLuint fbo2;
	GLenum gleerr;

	egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if (egl_display == EGL_NO_DISPLAY) {
		fprintf(stderr, "Error: No display found!\n");
		return -1;
	}

	if (!eglInitialize(egl_display, &egl_major, &egl_minor)) {
		fprintf(stderr, "Error: eglInitialise failed!\n");
		return -1;
	}

	eglChooseConfig(egl_display, config_attribute_list, &config, 1,
	    &num_config);

	context = eglCreateContext(egl_display, config, EGL_NO_CONTEXT,
	           context_attribute_list);
	if (context == EGL_NO_CONTEXT) {
		printf("Error: eglCreateContext failed: 0x%08X\n",
	    		eglGetError());
		return -1;
	}

	/*egl_surface = eglCreateWindowSurface(egl_display, config,
	                 (EGLNativeWindowType)&native_window,
	                 window_attribute_list);*/
	egl_surface = eglCreateWindowSurface(egl_display, config,
	                 (EGLNativeWindowType)&native_window,
	                 window_attribute_list);

	if (egl_surface == EGL_NO_SURFACE) {
		printf("Error: eglCreateWindowSurface failed: "
	    	"0x%08X\n", eglGetError());
		return -1;
	}

	if (!eglQuerySurface(egl_display, egl_surface, EGL_WIDTH, &width) ||
		!eglQuerySurface(egl_display, egl_surface, EGL_HEIGHT, &height)) {
		printf("Error: eglQuerySurface failed: 0x%08X\n",
		    	eglGetError());
		return -1;
	}

	if (!eglMakeCurrent(egl_display, egl_surface, egl_surface, context)) {
		printf("Error: eglMakeCurrent() failed: 0x%08X\n",
		    	eglGetError());
		return -1;
	}
	eglSwapInterval(egl_display, 3);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertex_shader) {
		printf("Error: glCreateShader(GL_VERTEX_SHADER) "
		    	"failed: 0x%08X\n", glGetError());
		return -1;
	}

	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		char *log;

		printf("Error: vertex shader compilation failed!\n");
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			log = malloc(ret);
			glGetShaderInfoLog(vertex_shader, ret, NULL, log);
			printf( "%s", log);
		}
		return -1;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragment_shader) {
		printf("Error: glCreateShader(GL_FRAGMENT_SHADER) "
			"failed: 0x%08X\n", glGetError());
		return -1;
	}

	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		char *log;

		fprintf(stderr, "Error: fragment shader compilation failed!\n");
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			log = malloc(ret);
			glGetShaderInfoLog(fragment_shader, ret, NULL, log);
			fprintf(stderr, "%s", log);
		}
		return -1;
	}

	program = glCreateProgram();
	if (!program) {
		fprintf(stderr, "Error: failed to create program!\n");
		return -1;
	}

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glBindAttribLocation(program, 0, "aPosition");
	glBindAttribLocation(program, 1, "aTexCoords");
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &ret);
	if (!ret) {
		char *log;

		fprintf(stderr, "Error: program linking failed!\n");
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			log = malloc(ret);
			glGetProgramInfoLog(program, ret, NULL, log);
			fprintf(stderr, "%s", log);
		}
		return -1;
	}
	glUseProgram(program);

	gYuvTexSamplerHandle = glGetUniformLocation(program, "yuvTexSampler");
	glUniform1i(gYuvTexSamplerHandle, 0);
	gYuvTexSamplerHandle = glGetUniformLocation(program, "extTexSampler");
	glUniform1i(gYuvTexSamplerHandle, 1);
	proMatrixHandle = glGetUniformLocation(program, "Mprojection");
	gselHandle = glGetUniformLocation(program, "sel");
	gsizeHandle = glGetUniformLocation(program, "psize");


	int fd = open("/mnt/abgr8888_1280x720.bin", O_RDWR);
	redbuffer = malloc(1280*720*4);
	memset(redbuffer, 111, 1280*720*4);
	printf("fd = %d\n",fd);
	int retr = read(fd, redbuffer, 1280*720*4);
	close(fd);
// creat array data
	glGenBuffers(1, &buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vVertices, GL_STATIC_DRAW);

// creat the fbo
	glGenRenderbuffers(1, &renderbuffers);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffers);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, 800, 600);
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffers);

	glGenRenderbuffers(1, &renderbuffers2);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffers2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, 800, 600);
	glGenFramebuffers(1, &fbo2);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffers2);

// creat the texture
	glGenTextures(1, &tex_a);
	glBindTexture(GL_TEXTURE_2D, tex_a);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, redbuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	EGLImageKHR img = eglCreateImageKHR(egl_display, context, EGL_GL_RENDERBUFFER_KHR, (EGLClientBuffer)renderbuffers, NULL);
	if (img == EGL_NO_IMAGE_KHR) {
		printf("Error: failed: 0x%08X  %d\n",glGetError(),__LINE__); 
		return -1;
	}
	if(gleerr = eglGetError() != EGL_SUCCESS)
		printf("Error: failed: 0x%08X  %d\n",gleerr,__LINE__); 
	glGenTextures(1, &tex_b);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex_b);
	glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)img);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	img = eglCreateImageKHR(egl_display, context, EGL_GL_RENDERBUFFER_KHR, (EGLClientBuffer)renderbuffers2, NULL);
	if (img == EGL_NO_IMAGE_KHR) {
		printf("Error: failed: 0x%08x  %d\n", glGetError(),__LINE__); 
		return -1;
	}
	if(gleerr = eglGetError() != EGL_SUCCESS)
		printf("Error: failed: 0x%08x  %d\n", gleerr,__LINE__); 
	glGenTextures(1, &tex_c);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex_c);
	glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)img);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
//draw 2d to render buffer 0
	struct timeval tv;
	gettimeofday( &tv, NULL);
	long time_s1 = 1000 * (long)tv.tv_sec + (long)tv.tv_usec/1000;

	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_a);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glUniform1i(gselHandle, 0);

	glClearColor(1, 0.2, 0.2, 1.0);
	glLineWidth(15);
	glUniform1f(gsizeHandle, 8.0);

	glUniformMatrix4fv(proMatrixHandle, 1, GL_FALSE, proMatrix1x1);
	Redraw(0,0,800, 600, 1);

	glUniform1i(gselHandle, 1);
	glActiveTexture(GL_TEXTURE1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords2);
	glUniformMatrix4fv(proMatrixHandle, 1, GL_FALSE, proMatrix);

	glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex_b);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0, 0.2, 1, 1.0);

	Redraw(0,0,width, height, 7);

	eglSwapBuffers(egl_display, egl_surface);
// draw the rotate 
	int coutter = 20000;

	while(coutter--) {
		GLuint fbo_c;
		GLuint tex_d;
		GLuint tex_e;
		if (coutter%2) {
			fbo_c = fbo2;
			tex_d = tex_b;
			tex_e = tex_c;
		}else{
			fbo_c = fbo;
			tex_d = tex_c;
			tex_e = tex_b;
		}
    		
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_c);
		glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex_d);

		glUniformMatrix4fv(proMatrixHandle, 1, GL_FALSE, proMatrix);
		glClearColor(1.0, 0.2, 0.0, 1.0);
		Redraw(0,0,800, 600, 1);

		glBindTexture(GL_TEXTURE_EXTERNAL_OES, tex_e);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUniformMatrix4fv(proMatrixHandle, 1, GL_FALSE, proMatrix1x1);

		glClearColor(0, 0.2, 1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		Redraw(0,0,width/2, height/2, 0);
		Redraw(width/2,0,width/2, height/2, 0);
		Redraw(width/2,height/2,width/2, height/2, 0);
		Redraw(0,height/2,width/2, height/2, 0);
		Redraw(0,0,width, height, 0);

		eglSwapBuffers(egl_display, egl_surface);
		sleep(1);
	}
	gettimeofday( &tv, NULL);
	long time_s2 = 1000 * (long)tv.tv_sec + (long)tv.tv_usec/1000;
	printf("time: %ld ms. \n", time_s2 - time_s1);

	glDeleteTextures(1,&tex_a);
	glDeleteBuffers(1,&buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	free(redbuffer);
	eglDestroySurface(egl_display, egl_surface);
	eglMakeCurrent(egl_display,NULL,NULL,NULL);
	eglDestroyContext(egl_display, context);
	eglTerminate(egl_display);
	eglReleaseThread();
	return 0;
}
