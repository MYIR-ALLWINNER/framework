#ifndef INFO_GDBUS_COMMON_H
#define INFO_GDBUS_COMMON_H

#include <gio/gio.h> /* Bus define */

#define AW_GDBUS_MEDIAVIDEO_BUS_NAME    "com.aw.Gdbus.mediavideo"
#define AW_GDBUS_MEDIAVIDEO_OBJECT_PATH "/com/aw/Gdbus/mediavideo"
typedef int (*method_cb)(int msgType, char *dataPtr,int dalen,void *user);

typedef struct soutval{
int val0;
int val1;
int val2;
long long val3;
}soutval_t;

#endif