/*
 ** Copyright @allwinnertech.com 2020, 
 ** Creat it for fbdev multi-thread and multi-windows project, 
 ** you can nodify it, but if you modify, you must be responsible for the next work for the modification.
 ** http://www.allwinnertech.com
 ** if you have some doubt ,contact cuiyuntao<Jet Cui>@allwinnertech.com or the GPU team.
 ** Version 1.0, and the version 1.1 will soon....
 */

#include <pthread.h>
#include <stdlib.h>

#include <stdbool.h>
//#include <stdint.h>

#include "sunxi_display2.h"

enum{
	THREAD_KEY_CONTEXT = 0,

	THREAD_KEY_MAX,
}gl_key;

#ifndef RUKO_PLAT
	
#define LINUX_PLAT
	
#endif
//#define RUKO_PLAT
#ifndef FBO_SURFACE_NUM
#define FBO_SURFACE_NUM 3
#endif
typedef enum {
    RGBA8888 = 0,  // 32 bit RGBA, 8 bits each component
    RGB888,        // 24 bit RGB, 8 bits each component, packed into 32 bit
    RGB565,        // 16 bit RGB
    RGBA5551,      // 16 bit RGBA, 5 bit color components, 1 bit alpha
    RGBA4444,      // 16 bit RGBA, 4 bit components
    ALPHA8,        // 8 bit alpha surface, fixed color
    ETC1RGB8,      // ETC1 compressed image
    UYVY,          // 16 bit YUV 4:2:2
    YUY2,          // 16 bit YUV 4:2:2 YCbYCr
    UNKNOWN_gg        // should be last
} RoPixelFormat;

#define UNSUPPORT_FORMAT  0

struct list{
	struct list* pre;
	struct list* next;
};

typedef struct list aw_list;
typedef struct {
    int32_t width;  /* native screen width */
    int32_t height; /* native screen height */
    int8_t layer;   /* video, graphics, or overlay */
    int8_t buffers; /* single, double, or triple buffering */
    RoPixelFormat format;
    int preserved; /* enable EGL buffer preservation */
} aw_layer_info;

typedef struct gpu_surface {
	aw_list    list;
	EGLDisplay dpy;
	EGLSurface *surface;
	aw_layer_info layer_info;
	unsigned long long write_fbo;//start from 1 
	unsigned long long read_fbo;
	unsigned long long c_read_fbo;
	int64_t time_cap[FBO_SURFACE_NUM];
	GLuint tex[FBO_SURFACE_NUM];
	int fd[FBO_SURFACE_NUM];
	GLuint fbo[FBO_SURFACE_NUM];
	EGLImageKHR img[FBO_SURFACE_NUM];
	EGLSyncKHR sync[FBO_SURFACE_NUM];
	void* cpu_addr[FBO_SURFACE_NUM];
	struct disp_layer_config2 config;
	int layer;
	int channel;
	int zOder;
	int ref;
	int size;
	int destroyed;
}gpu_surface_t;

typedef enum{
	SWAP_BUFFER = 0,
	NEXT_VSYNC,
}msg_t;

struct mesg_pair_t {
	int disp;
	unsigned long long write_count;
	msg_t msg_info;
};

struct display_resoure{
	aw_list new_surface_list;
	aw_list surface_list;
	EGLDisplay id;
	int dis_num;
	int sockets[2];
	int epoll_fd;
	int game_over;
	int64_t time_cap;
	pthread_mutex_t notfiy_mutex;
	pthread_cond_t notfiy_mCond;
	pthread_mutex_t notfiy_mutex_render;
	pthread_cond_t notfiy_mCond_render;
	pthread_mutex_t surface_mutex; 
};

struct thread_context{
	gpu_surface_t *fb_surface;
	gpu_surface_t *read_surface;
	gpu_surface_t *write_surface;
	EGLContext ctx;
	int ref;
};

static inline void init_list(aw_list *list)
{
	list->next = list;
	list->pre = list;
}

static inline void add_list_tail(aw_list *head, aw_list *list_new)
{
	list_new->next = head;
	list_new->pre = head->pre;
	head->pre->next = list_new;
	head->pre = list_new;
}

static inline void del_list(aw_list *list_old)
{
	list_old->next->pre = list_old->pre;
	list_old->pre->next = list_old->next;
	init_list(list_old); 
}

static inline int list_empty(aw_list *list)
{
	return (list->pre == list) && (list->next == list);
}

static  inline void add_ref(gpu_surface_t *sur)
{
	sur->ref++;
}

static inline int dec_ref(gpu_surface_t *sur)
{
	sur->ref--;
	int cout = sur->ref;
	if (cout <= 0) {
		
		del_list(&sur->list);
		free((void*)sur);
	}
	return cout;
}
