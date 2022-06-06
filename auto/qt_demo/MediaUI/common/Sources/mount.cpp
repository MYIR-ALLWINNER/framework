#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/time.h>
#include <sdklog.h>
#include "CameraFileCfg.h"
#include "StorageManager.h"
#include "common/Header/mount.h"

void AutoMountCallback(NetlinkEvent * evt, void *usrdata);
/**************************************
Function:
Description:
***************************************/
mount::mount(void *usrdata)
{
    NetlinkManager *nm;
    AutEvent *pevent = AutEvent::Instance();

    if (!(nm = NetlinkManager::Instance())) {
        ALOGV("Unable to create NetlinkManager");
        //printf("can't get the netlinkManager's instance\n");
    };

    pevent->setEventCb(AutoMountCallback, (void *) usrdata);
    if (nm->start()) {
        ALOGV("Unable to start NetlinkManager (%s)");
    }
}


/**************************************
Function:
Description:
***************************************/
void AutoMountCallback(NetlinkEvent * evt, void *usrdata)
{
    ALOGV("event act=%d %s ", evt->getAction(), evt->getSubsystem());

    int action = evt->getAction();
    const char *devtype = evt->findParam("DEVTYPE");


    if (action == NetlinkEvent::NlActionAdd) {
        int major = atoi(evt->findParam("MAJOR"));
        int minor = atoi(evt->findParam("MINOR"));
        char nodepath[255];

        if (!strcmp(devtype, "disk")) {

            //enhanceUsbStability(evt);

            ALOGW("line=%d,devtype=%s", __LINE__, devtype);
            //handleDiskAdded(dp, evt);
            char bufname[512];
            memset(bufname, 0, 512);
            char tmpbuf[256];
            char real_path[256];
            config_get_curfiledir(0, bufname);
            int len = strlen(bufname);
            const char *tmp = evt->findParam("NPARTS");


            if (tmp) {
                int npart = atoi(tmp);
                if (npart == 0) {
                    const char *devname = evt->findParam("DEVNAME");
                    ALOGW("devname=%s", devname);


                    char buf[256];
                    if (strstr(devname, "sd")) {

                        system("mkdir -p /mnt/usb");
                        sprintf(buf,
                                "mount -t vfat /dev/%s /mnt/usb -o defaults,noatime,async,iocharset=cp936",
                                devname);
                    }
                    else if (strstr(devname, "mmcblk1"))
                        sprintf(buf,
                                "mount -t vfat /dev/%s /mnt/sdcard/mmcblk1p1 -o defaults,noatime,async,iocharset=cp936",
                                devname);
                    else
                        sprintf(buf, "echo mount fail > /dev/ttyS0");

                    system("mkdir -p /mnt/sdcard/mmcblk1p1");
                    system(buf);
                }
            }
            else {
                SLOGW("Kernel block uevent missing 'NPARTS'");
                //mDiskNumParts = 1;
            }
            strcpy(tmpbuf, bufname);
            for (int i = 0; i < len; i++) {
                if (tmpbuf[len - 1 - i] == '/') {
                    tmpbuf[len - 1 - i] = 0;
                }
                else {
                    break;
                }
            }

            int rmret = readlink(tmpbuf, real_path, sizeof(real_path));
            if (rmret < 0) {
                ALOGV("mount path not a symlink %s err=%d", tmpbuf, errno);

                strcpy(real_path, tmpbuf);
            }
            else {
                ALOGV("mount real path is %s \r\n", real_path);
            }
            for (int i = 0; i < 6; i++) {
                if (isMounted(real_path))
                    break;

                sleep(1);
            }

            /*
            if (g_recordstatus == 0) {
                pdvr1->startRecord();
                g_recordstatus = 1;
            }
            else
                ALOGE("record status error g_recordstatus=%d", g_recordstatus);
            */

        }

    }
    else if (action == NetlinkEvent::NlActionRemove) {
        if (!strcmp(devtype, "disk")) {

            /*
            if (g_recordstatus == 1) {
                pdvr1->storage_state=0;//tmp
                pdvr1->stopRecord();
                g_recordstatus = 0;
                ALOGE("sdcard has remove,stopRecord now,g_recordstatus=%d", g_recordstatus);

            }
            */

        }
    }

}

/**************************************
Function:
Description:
***************************************/
mount::~mount()
{

}

