#ifndef __SERVER_H__
#define __SERVER_H__

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef int (* fn_set_cmd_handler)(int cmd,int val0,char* val1,void* out,void* pdat);

#ifdef  __cplusplus
extern "C" {
#endif

int sMediaVideoServRegSetCmdHandl(void* cb);
int sMediaVideoEmitSignal(int i_arg1,int i_arg2,int i_arg3);
int sMediaVideoServerInit(void *p);

#ifdef  __cplusplus
}
#endif

#endif
