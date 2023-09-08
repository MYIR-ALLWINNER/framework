#ifndef __MSGQ_H
#define __MSGQ_H
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct mq_attr    mq_attr_t;
typedef mqd_t    msgQ_t;



#ifdef __cplusplus
extern "C" {
#endif
int msgQCreateA(msgQ_t *dwOSMsgQID,char *name,int maxcnt,int maxsize,int block);

int msgQCreate(msgQ_t *dwOSMsgQID,char *name,int maxcnt,int maxsize,int block);
int msgQReceive(msgQ_t dwOSMsgQID, char *pMsg, int dwMsgLen, int dwMsgPrio);
int msgQSend(msgQ_t dwOSMsgQID, char *pMsg, int dwMsgLen, int dwMsgPrio);
int msgQdestory(msgQ_t dwOSMsgQID);
int msgQGetMsgCnt(msgQ_t dwOSMsgQID);


#ifdef __cplusplus
}
#endif

#endif /* __MQ_H */ 

