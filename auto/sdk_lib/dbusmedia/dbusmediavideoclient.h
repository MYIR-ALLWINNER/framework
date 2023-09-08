#ifndef __LIB_CLIENT__
#define __LIB_CLIENT__

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef void (* fn_signal_handler)(int type,int val,int val1,void* pdat);

#ifdef  __cplusplus
extern "C" {
#endif

int cMediaVideoClientSetCmd( int in_arg1, int in_arg2, int in_arg3, const char* in_arg4,  int *out_arg2);
int cMediaVideoClientInit(void *p);
int cMediaVideoClientRegSingalHandl(void* cb);
int cMediaVideoClientDestory();

#ifdef  __cplusplus
}
#endif

#endif
