/***************************************
FileName:
Copyright:
Author:
Description:
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/time.h>
#include <sdklog.h>

#include "audio_hal.h"
#include "Audio.h"
/************Macro*********************/

/************Variable******************/

/************Function******************/

/**************************************
Function:
Description:
***************************************/
void AudioInit(dvr_factory *dvr)
{
    sp < AudioCapThread > audiocap = new AudioCapThread();
	int hdl = audiocap->reqAudioSource(dvr->__dvr_audio_data_cb_timestamp,(void *)dvr);
	dvr->setAudioOps(audiocap, hdl);
}
/**************************************
end
***************************************/