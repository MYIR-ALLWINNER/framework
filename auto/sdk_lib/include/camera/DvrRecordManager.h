#ifndef _DvrRecordManager_H
#define _DvrRecordManager_H

extern Mutex gfileLock;			//used to lock the gFilemanger
extern file_status_t gFilemanger;
extern unsigned int gAFileOccupySizePerMinMb;

extern void DvrRecordManagerInit(void);
extern int getFileSize(char *filename);
extern int getFileOccupySizeMb(char *filename);
#endif
