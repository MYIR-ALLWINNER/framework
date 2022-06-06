#include <errno.h>
#include <sdklog.h>
#include <stdlib.h>
#include <utils/Errors.h>
#include "DvrFactory.h"
#include "DvrRecordManager.h"

Mutex gfileLock;				//used to lock the gFilemanger
file_status_t gFilemanger;

//gAFileOccupySizePerMinMb = (bit_rate*60/8)+13 => bit_rate*7.5+13 ==>bit_rate*8+13 ==>(bit_rate>>20)<<8 + 13
unsigned int gAFileOccupySizePerMinMb;

void DvrRecordManagerInit(void)
{
	int i = 0;
	Mutex::Autolock locker(&gfileLock);
	gFilemanger.cur_file_idx = 0;
	gFilemanger.cur_max_filenum = 0;

	gFilemanger.timeout_second = 0;

	for (i = 0; i < CM_MAX_RECORDFILE_NUM; i++) {
		memset(gFilemanger.cur_filename[i], 0, CM_MAX_FILE_LEN);
		memset(gFilemanger.cur_file_thumbname[i], 0, CM_MAX_FILE_LEN);	//temp no use
	}

	for (i = 0; i < MAX_SUPPORT_CAM; i++) {
		memset(&gFilemanger.cur_filedir[i][0],0,CM_MAX_FILE_LEN);
	}
	gFilemanger.cur_dir_file_num = 0;

	gAFileOccupySizePerMinMb = 64;	//bit_rate=7M

}

int getFileSize(char *filename)
{
	struct stat statbuf;
	stat(filename, &statbuf);
	int size = statbuf.st_size >> 20;

	return size;
}

int getFileOccupySizeMb(char *filename)
{
	struct stat statbuf;
	stat(filename, &statbuf);
	//文件实际占用空间=st_blocksize * st_blocks
	//int blocksize = statbuf.st_blocksize;
	int blksize = statbuf.st_blocks >> 11;

	return blksize;
}
