/*
 ** Copyright @allwinnertech.com 2020, 
 ** Creat it for fbdev multi-thread and multi-windows project, 
 ** you can nodify it, but if you modify, you must be responsible for the next work for the modification.
 ** http://www.allwinnertech.com
 ** if you have some doubt ,contact cuiyuntao<Jet Cui>@allwinnertech.com or the GPU team.
 ** Version 1.0, and the version 1.1 will soon....
 */

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES3/gl32.h>
#include <EGL/eglext.h>
#include <GLES2/gl2ext.h>

typedef struct gpu_context{
	#undef GL_ENTRY
	#undef EGL_ENTRY
	struct {
		#define EGL_ENTRY(_r, _api, ...) _r (*(_api))(__VA_ARGS__);
		#include "egl_entries.h"
	} egl;
	struct {
		#define GL_ENTRY(_r, _api, ...) _r (*(_api))(__VA_ARGS__);
		#include "entries.h"
	}gl2;
	#undef GL_ENTRY
	#undef EGL_ENTRY
	int init;
	int debug;
	int multi_context;
	struct thread_context *sunxi_ctx;
} gpu_context_t;

