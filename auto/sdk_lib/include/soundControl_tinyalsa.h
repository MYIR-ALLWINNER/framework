#ifndef SOUNDCONTROL_TINYALSA_H
#define SOUNDCONTROL_TINYALSA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tinyalsasoundlib.h"
#include "soundControl.h"
#include "outputCtrl.h"

typedef int (*autCallback_func)(int32_t msgType, void *user,void*data,int len);

SoundCtrl* SoundDeviceCreate();

int tinyalsaSetCallback(SoundCtrl* s, void *callback, void **pUserData);

#ifdef __cplusplus
} 
#endif

#endif
