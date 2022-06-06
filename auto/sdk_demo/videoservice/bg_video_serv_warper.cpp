#ifdef BGVIDEO_SER

#include <gio/gio.h>   // GIO for dbus
#include <glib-2.0/glib.h>   // GLIB for main loop
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "libgdbusmediavideo.h"
#include "dbusmediavideoserver.h"
#include "dbusmediavideoCommon.h"
#include "background_video_player.h"
#include "dbusmediavideotype.h"

#include "AutPlayer.h"

int main()
{
	//init commution
	CBackGroundMediaVideo player;
	sMediaVideoServerInit(&player);
	
	sMediaVideoServRegSetCmdHandl((void *)player.handleShareMemControlCmd);

	while(1){
		sleep(1);
	}
	
	
}
#endif
