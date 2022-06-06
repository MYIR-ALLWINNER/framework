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
#include <dirent.h>
#include<iostream>
#include "CameraFileCfg.h"
#include "StorageManager.h"
#include "AutoMount.h"

using namespace std;

dvr_factory **ppDvr = NULL;

/************Macro*********************/


/************Variable******************/
//int g_recordstatus = 0;

/************Function******************/
void AutoMountDev(void);


void RdyRecord(bool bRdy)
{
	dvr_factory **pDvrFac = ppDvr; //mod lss
	if(NULL == pDvrFac){
		printf("pDvrFac is NULL\n");
		return;
	}
	
	if(bRdy){
		for(; *pDvrFac != NULL; *pDvrFac++){
			int startup = config_get_startup((*pDvrFac)->mCameraId);
			if(startup)
				(*pDvrFac)->startRecord();
		}
	}else {
		for(; *pDvrFac != NULL; *pDvrFac++){
				(*pDvrFac)->stopRecord();
		}
	}
}

/**************************************
Function:
Description:
***************************************/
void AutoMountInit(void *usrdata)
{
    	NetlinkManager *nm;
	AutEvent *pevent = AutEvent::Instance();
	
	if (!(nm = NetlinkManager::Instance())) {
		SLOGE("Unable to create NetlinkManager");
		ALOGV("can't get the netlinkManager's instance\n");
	};

	pevent->setEventCb(AutoMountCallback, (void *) usrdata);
	if (nm->start()) {
		SLOGE("Unable to start NetlinkManager (%s)", strerror(errno));
	}

	AutoMountDev();
}

/**************************************
Function:
Description:

sd[a-z][0-9]    0:0 666            @/etc/mdev/udisk_insert
sd[a-z]            0:0 666        $/etc/mdev/udisk_remove

mmcblk1p[0-9]  0:0 666        @/etc/mdev/sdcard_insert
mmcblk1        0:0 666        $/etc/mdev/sdcard_remove

***************************************/
void AutoMountDev(void)
{
	DIR* dir;// = opendir("/dev/");//打开指定目录
	dirent* p = NULL;//定义遍历指针
	char sdbuf[SAVE_MAX][10],usbbuf[SAVE_MAX][10];
	int sdlen,usblen,i;

	char buf[300];
//	int cnt=0;
	int muti_en=MUTI_PARTS_EN;
	int rm_path_en=RM_PATH_EN;

	ALOGV("----AutoMountDev start----\n");
	
	printf("=AutoMountDev =\n");

	sdlen=0;
	usblen=0;

	dir=opendir("/dev/");
	while((p = readdir(dir)) != NULL)//开始逐个遍历
	{
		if(p->d_name[0] != '.')//d_name是一个char数组，存放当前遍历到的文件名
		{

			//sdcard
			if( (strlen(p->d_name)>=SDCARD_LEN) && (strstr(p->d_name,SDCARD_TYPE)!=NULL) ){
				ALOGV("scan sdcard  %s \n",p->d_name);

				if(sdlen<SAVE_MAX){
					strcpy(sdbuf[sdlen++],p->d_name);
				}
			}


			//usb
			if( (strlen(p->d_name)>=USB_LEN) && (strstr(p->d_name,USB_TYPE)!=NULL) ){
				if(strcmp(p->d_name,"sda")!=0){
					ALOGV("scan usb  %s \n",p->d_name);

					if(usblen<SAVE_MAX){
						strcpy(usbbuf[usblen++],p->d_name);
					}
					
				}
			}

		}
	}
	closedir(dir);//关闭指定目录

	// mount sdcard
	if(sdlen==0){
		//check
		dir=opendir("/mnt/sdcard/");
		if(dir!=NULL){
			i=0;
			while((p = readdir(dir)) != NULL){

				ALOGV("check sdcard 0  %s \n",p->d_name);

				if(p->d_name[0] != '.')
				{
					i++;
					ALOGV("check sdcard  %s \n",p->d_name);
					sprintf(buf,"umount /mnt/sdcard/%s",p->d_name);
					system(buf);
				}
			}

			closedir(dir);
            if(rm_path_en){
                sprintf(buf,"rm -rf /mnt/sdcard/");
                system(buf);
            }
		}
	}
	else if(sdlen==1){

		sprintf(buf,"/mnt/sdcard/%s",sdbuf[0]);
		if(!isMounted(buf)){
			ALOGV("mount sdcard 1 %s \n",sdbuf[0]);
			
			sprintf(buf,"mount -t vfat /dev/%s /mnt/sdcard/mmcblk1p1 -o defaults,noatime,async,iocharset=cp936",sdbuf[0]);
			system("mkdir -p /mnt/sdcard/mmcblk1p1");
			system(buf);

			sprintf(buf,"/mnt/sdcard/%s",sdbuf[0]);
			if(!isMounted(buf) && rm_path_en){
				sprintf(buf,"rm-rf /mnt/sdcard/%s",sdbuf[0]);
				system(buf);
			}
		}
	}
	else if(sdlen>1 && muti_en){


		for(i=0;i<sdlen;i++){

			sprintf(buf,"/mnt/sdcard/%s",sdbuf[i]);
			if(!isMounted(buf)){

				ALOGV("mount sdcard m %s \n",sdbuf[i]);
				
				sprintf(buf,"mkdir -p /mnt/sdcard/%s",sdbuf[i]);
				system(buf);
				sprintf(buf,"mount -t vfat /dev/%s /mnt/sdcard/%s -o defaults,noatime,async,iocharset=cp936",sdbuf[i],sdbuf[i]);
				
				system(buf);

				sprintf(buf,"/mnt/sdcard/%s",sdbuf[i]);
				if(!isMounted(buf) && rm_path_en){
					sprintf(buf,"rm -rf /mnt/sdcard/%s",sdbuf[i]);
					system(buf);
				}
			}
		}
		
	}


	// mount usb
	if(usblen==0){
		dir=opendir("/mnt/usb/");
		if(dir!=NULL){
			i=0;
			while((p = readdir(dir)) != NULL){

				if(p->d_name[0] != '.')
				{
					i++;
					ALOGV("check usb  %s \n",p->d_name);

					sprintf(buf,"umount /mnt/usb/%s",p->d_name);
					system(buf);
				}
			}
			closedir(dir);

            if(rm_path_en){
                sprintf(buf,"rm -rf /mnt/usb/");
                system(buf);
            }
		}

	}
	if(usblen==1){
		sprintf(buf,"/mnt/usb/usb1");
		if(!isMounted(buf)){

			ALOGV("mount usb 1 %s \n",usbbuf[0]);
			
			system("mkdir -p /mnt/usb/usb1");
			sprintf(buf,"mount -t vfat /dev/%s /mnt/usb/usb1 -o defaults,noatime,async,iocharset=cp936",usbbuf[0]);
			system(buf);

			sprintf(buf,"/mnt/usb/usb1");

			if(!isMounted(buf)){
				sprintf(buf,"rm -rf /mnt/usb/usb1");
				system(buf);
			}

		}

	}
	else if(usblen>1 && muti_en){
		for(i=0;i<usblen;i++){

			sprintf(buf,"mkdir -p /mnt/usb/%s",usbbuf[i]);
			if(!isMounted(buf)){

				ALOGV("mount usb m %s \n",usbbuf[i]);
				
				sprintf(buf,"mkdir -p /mnt/usb/%s",usbbuf[i]);
				system(buf);
				sprintf(buf,"mount -t vfat /dev/%s /mnt/usb/%s -o defaults,noatime,async,iocharset=cp936",usbbuf[i],usbbuf[i]);
				system(buf);

				sprintf(buf,"/mnt/usb/%s",usbbuf[i]);
				if(!isMounted(buf) && rm_path_en){
					sprintf(buf,"rm -rf /mnt/usb/%s",usbbuf[i]);
					system(buf);
				}
			}
		}
	}
	
}

/**************************************
Function:
Description:
***************************************/
void AutoMountCallback(NetlinkEvent * evt, void *usrdata)
{
	DIR* dir;
	dirent* p = NULL;//定义遍历指针
	char buf[600];
	int i;

	int muti_en=MUTI_PARTS_EN;
	int rm_path_en=RM_PATH_EN;
	int is_mouted;

	ALOGV("event act=%d %s ", evt->getAction(), evt->getSubsystem());

	int action = evt->getAction();
	const char *devtype = evt->findParam("DEVTYPE");

	if (action == NetlinkEvent::NlActionAdd) {
		//int major = atoi(evt->findParam("MAJOR"));
		//int minor = atoi(evt->findParam("MINOR"));
		//char nodepath[255];

		ALOGV("AutoMountCallback add  \n");


		if (!strcmp(devtype, "disk")) {

			ALOGV("AutoMountCallback disk  \n");

			ALOGV("line=%d,devtype=%s", __LINE__, devtype);
			//handleDiskAdded(dp, evt);
			char bufname[512];
			memset(bufname, 0, 512);
			//char tmpbuf[256];
			//char real_path[256];
			config_get_curfiledir(0, bufname);
			//int len = strlen(bufname);
			const char *tmp = evt->findParam("NPARTS");
			if (tmp) {
				int npart = atoi(tmp);

				if (npart == 0) {
					const char *devname = evt->findParam("DEVNAME");
					ALOGV("************devname=%s", devname);
					if (strstr(devname, "sd")!=NULL) {
						system("mkdir -p /mnt/usb/usb1");
						sprintf(buf,"mount -t vfat /dev/%s /mnt/usb/usb1 -o defaults,noatime,async,iocharset=cp936",devname);
						system(buf);
						sleep(1);
						sprintf(buf,"/mnt/usb/usb1");
						if(!isMounted(buf) && rm_path_en){
							sprintf(buf,"rm -rf /mnt/usb/");
							system(buf);
						}
					}
					else if (strstr(devname, "mmcblk1")!=NULL){
						system("mkdir -p /mnt/sdcard/mmcblk1p1");
						sprintf(buf,"mount -t vfat /dev/%s /mnt/sdcard/mmcblk1p1 -o defaults,noatime,async,iocharset=cp936",devname);
						system(buf);
						sleep(1);
						sprintf(buf,"/mnt/sdcard/%s",devname);
						if(!isMounted(buf) ){
							if(rm_path_en){
								sprintf(buf,"rm -rf /mnt/sdcard/");
								system(buf);
							}
						}else{
							is_mouted=true;
						}
					}
					else{
						ALOGV("mount fail \n");
					}
				}


				else if(npart>0 && muti_en){
					const char *devname = evt->findParam("DEVNAME");
					if (strstr(devname, "sd")!=NULL) {
						dir=opendir("/dev/");
						if(dir!=NULL){
							while((p = readdir(dir)) != NULL)
							{
								//usb
								if( (strlen(p->d_name)>=USB_LEN) && (strstr(p->d_name,USB_TYPE)!=NULL) ){

									sprintf(buf,"/mnt/usb/%s",p->d_name);
									if(!isMounted(buf)){

										ALOGV("in usb  %s \n",p->d_name);

										sprintf(buf,"mkdir -p /mnt/usb/%s",p->d_name);
										system(buf);
										sprintf(buf,"mount -t vfat /dev/%s /mnt/usb/%s -o defaults,noatime,async,iocharset=cp936",p->d_name,p->d_name);
										system(buf);
										sleep(1);
										sprintf(buf,"/mnt/usb/%s",p->d_name);
										if(!isMounted(buf) && rm_path_en){
											sprintf(buf,"rm -rf /mnt/usb/%s",p->d_name);
											system(buf);
										}
									}
								}
							}
							closedir(dir);
						}
					}
					else if (strstr(devname, "mmcblk1")!=NULL){

						dir=opendir("/dev/");
						if(dir!=NULL){
							while((p = readdir(dir)) != NULL)
							{
								//sdcard
								if( (strlen(p->d_name)>=SDCARD_LEN) && (strstr(p->d_name,SDCARD_TYPE)!=NULL) ){

									sprintf(buf,"/mnt/sdcard/%s",p->d_name);
									if(!isMounted(buf)){
										ALOGV("in sdcard  %s \n",p->d_name);

										sprintf(buf,"mkdir -p /mnt/sdcard/%s",p->d_name);
										system(buf);
										sprintf(buf,"mount -t vfat /dev/%s /mnt/sdcard/%s -o defaults,noatime,async,iocharset=cp936",p->d_name,p->d_name);
										system(buf);
										sleep(1);
										sprintf(buf,"/mnt/sdcard/%s",p->d_name);
										if(!isMounted(buf)){
											if(rm_path_en){
												sprintf(buf,"rm -rf /mnt/sdcard/%s",p->d_name);
												system(buf);
											}
										}else{
											is_mouted=true;
										}
									}
								}
							}
							closedir(dir);
						}
						
					}
					else{
						ALOGV("mount fail \n");
					}

					
				}
			}
			else {
				SLOGW("Kernel block uevent missing 'NPARTS'");
				//mDiskNumParts = 1;    
			}

			/*
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
			*/
			
			RdyRecord(true);
		}

	}
	else if (action == NetlinkEvent::NlActionRemove) {
		if (!strcmp(devtype, "disk")) {


			ALOGV("==AutoMountCallback remove===  \n");
	
			RdyRecord(false);

			const char *tmp = evt->findParam("NPARTS");
			if (tmp) {
				//int npart = atoi(tmp);
				const char *devname = evt->findParam("DEVNAME");
				char buf[300];
				

				ALOGV("AutoMountCallback remove %s \n",devname);

//				int cnt=0;
				
				if (strstr(devname, "mmcblk1")!=NULL){
					dir=opendir("/mnt/sdcard/");
					if(dir!=NULL){

						while((p = readdir(dir)) != NULL)
						{
							i=0;
							if(p->d_name[0] != '.')
							{

								ALOGV("out sdcard  %s \n",p->d_name);

								while(i<3){
									sprintf(buf,"umount /mnt/sdcard/%s",p->d_name);
									system(buf);

									sprintf(buf,"/mnt/sdcard/%s",p->d_name);
									if(isMounted(buf)){
										ALOGV("sdcard retry\n");
										i++;
										sleep(3);
									}else{
										ALOGV("sdcard break\n");
										break;
									}
								}
								if(i<3  && rm_path_en){
									sprintf(buf,"rm -rf  /mnt/sdcard/%s",p->d_name);
									system(buf);
								}
							}
						}
						closedir(dir);//关闭指定目录
					}
                    if(rm_path_en){
                        sprintf(buf,"rm -rf  /mnt/sdcard/");
                        system(buf);
                    }
				}

				if (strstr(devname, "sd")!=NULL){
					dir=opendir("/mnt/usb/");

					if(dir!=NULL){
						while((p = readdir(dir)) != NULL)
						{

							i=0;
							if(p->d_name[0] != '.' )
							{
								ALOGV("out usb  %s \n",p->d_name);

								while(i<3){
									sprintf(buf,"umount /mnt/usb/%s",p->d_name);
									system(buf);

									sprintf(buf,"/mnt/usb/%s",p->d_name);
									if(isMounted(buf)){
										ALOGV("usb retry\n");
										i++;
										sleep(3);
									}else{
										ALOGV("usb break\n");
										break;
									}
								}

								if(i<3 && rm_path_en){
									sprintf(buf,"rm -rf  /mnt/usb/%s",p->d_name);
									system(buf);
								}
							}
						}
						closedir(dir);//关闭指定目录
					}
                    if(rm_path_en){
                        sprintf(buf,"rm -rf  /mnt/usb/");
                        system(buf);
                    }
				}

			}
		}
	}
	
}


/**************************************
Function:
Description:
***************************************/
void enhanceUsbStability(NetlinkEvent *evt)
{
    char path[256];
    const char *tmp = evt->findParam("DEVNAME");
    char devname[4];
    FILE *fp;
    int msecs = 1000;

    if (tmp && !strncmp(tmp, "sd", 2)) {
       strncpy(devname,tmp,3);
       devname[3] = '\0';
       sprintf(path, "/sys/block/sda/events_poll_msecs", devname);

       //usleep(1000 * 1000);
       if ((fp = fopen(path, "r+ "))) {
           if (fprintf(fp, "%d\n", msecs) <= 0) {
               SLOGE("Failed to write %s (%s)", path, strerror(errno));
           }
           SLOGD("Success to write %d to %s ", msecs, path);
           fclose(fp);
       } else {
           SLOGE("Failed to open %s (%s)", path, strerror(errno));
       }
 }
}

/**************************************
end
***************************************/
