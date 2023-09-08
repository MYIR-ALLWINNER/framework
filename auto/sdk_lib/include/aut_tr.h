
#ifndef __AUT_TR_H__
#define __AUT_TR_H__

#include "sunxi_tr.h"	
#ifdef __cplusplus
extern "C" {
#endif

#define ALIGN_16B(x) (((x) + (15)) & ~(15))
#define ALIGN_32B(x) (((x) + (31)) & ~(31))

typedef struct{
	int format;
	int width;
	int height;
	void*addr0;
	void *addr1;
	tr_mode mode; 
	void*outaddr0;
	void *outaddr1;

}frm_info_t;

typedef struct{
	tr_info transform;
	unsigned long trchan;
	int trfd;
	int tr_initdone;
}tr_obj;
int aut_imgtr_init(tr_obj *p);
int aut_imgtr_proc(tr_obj *p,frm_info_t *imginfo);
int aut_imgtr_release(tr_obj *p);
int aut_set_disp_rotate_mode(int mode);
int aut_get_disp_rotate_mode();

#ifdef __cplusplus
}
#endif
#endif
