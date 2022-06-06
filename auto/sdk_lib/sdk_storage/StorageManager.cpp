#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include <sdklog.h>
#include <libgen.h>

#include "StorageManager.h"

unsigned long get_file_size(const char *path)
{
    unsigned long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
    {
        return filesize;
    }
    else
    {
        filesize = statbuff.st_size;
    }
    return filesize;
}

unsigned long long totalSize(const char *path)
{
    struct statfs diskinfo;
    if(statfs(path, &diskinfo) != -1)
    {
        unsigned long long blocksize = diskinfo.f_bsize;    //每个block里包含的字节数
        unsigned long long totalsize = blocksize * diskinfo.f_blocks;   //总的字节数，f_blocks为block的数目
        return (unsigned long long)(totalsize >> 20); //MB
    }
    return 0;

}

unsigned long long availSize(const char *path)
{
    struct statfs diskinfo;
    //unsigned long long availSize = 0;
    if(statfs(path, &diskinfo) != -1)
    {
        unsigned long long blocksize = diskinfo.f_bsize;    //每个block里包含的字节数
        unsigned long long freeDisk = diskinfo.f_bfree * blocksize; //剩余空间的大小
        //unsigned long long availableDisk = diskinfo.f_bavail * blocksize;   //可用空间大小
        //ALOGV("free %lld av %lld",freeDisk>>20,availableDisk>20);

        return (unsigned long long)(freeDisk >> 20); //MB
    }
    return 0;

}

int needDeleteFiles()
{
    unsigned long long as = availSize(MOUNT_PATH);
    unsigned long long ts = totalSize(MOUNT_PATH);
    ALOGV("[Size]:%lluMB/%lluMB, reserved:%lluMB", as, ts, RESERVED_SIZE);

    if (as <= RESERVED_SIZE)
    {
        ALOGE("!Disk FULL");
        return RET_DISK_FULL;
    }

    if (as <= LOOP_COVERAGE_SIZE)
    {
        ALOGE("!Loop Coverage");
        return RET_NEED_LOOP_COVERAGE;
    }

    return 0;
}
int isMounted(const char *checkPath)
{
    const char *path = "/proc/mounts";
    FILE *fp;
    char line[255];
    const char *delim = " \t";
    ALOGV(" isMount checkPath=%s \n",checkPath);
    if (!(fp = fopen(path, "r")))
    {
        ALOGE(" isMount fopen fail,path=%s\n",path);
        return 0;
    }
    memset(line,'\0',sizeof(line));
    while(fgets(line, sizeof(line), fp))
    {
        char *save_ptr = NULL;
        char *p        = NULL;
        //ALOGV(" isMount line=%s \n",line);
        if (line[0] != '/' || (strncmp("/dev/mmcblk",line,strlen("/dev/mmcblk")) != 0 &&
			 strncmp("/dev/sd",line,strlen("/dev/sd")) != 0) )
        {
            memset(line,'\0',sizeof(line));
            continue;
        }
        if ((p = strtok_r(line, delim, &save_ptr)) != NULL)
        {
            if ((p = strtok_r(NULL, delim, &save_ptr)) != NULL)
            {
                ALOGV(" isMount p=%s \n",p);
                if(strncmp(checkPath,p,strlen(checkPath) ) == 0)
                {
                    fclose(fp);
                    ALOGV(" isMount return 1\n");
                    return 1;
                }
            }
            //printf("line=%s",lineback);
            if(strlen(p)>1)
            {
                if(strstr(checkPath,p))
                {
                    fclose(fp);
                    ALOGV(" isMount dd return 1\n");
                    return 1;
                }
            }
        }

    }//end while(fgets(line, sizeof(line), fp))
    if(fp)
    {
        fclose(fp);
    }

   ALOGV("isMounted return 0 \n");

    return 0;
}
#define MAXSIZE 256
int  createdir(char *path)

{

    char data[MAXSIZE];

    //#判断是否是当前目录或/目录

    if((strcmp(path,".") == 0) || (strcmp(path,"/")==0))

        return -1;

    //#判断目录是否存在

    if(access(path,F_OK) == 0)
    {
        ALOGV("---path %s exit------",path);
        return 0;
    }
    else
    {

        //#保存目录

        strcpy(data,path);

        //#获取目录的父目录

        dirname(path);

        //#递归执行

        int ret=createdir(path);
        if(ret<0)
        {
            ALOGE("create dir %s fail",path);
            return -1;
        }

    }

    //#创建目录

    if(mkdir(data,0777) == -1)
    {

        ALOGE("mkdir error");
        return -1;


    }

    return 0;

}

