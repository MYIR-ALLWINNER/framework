#include "msgq.h"

int msgQCreateA(msgQ_t *dwOSMsgQID,char *name,int maxcnt,int maxsize,int block)
{
	    mqd_t mqID;
		mq_attr_t attr;
		attr.mq_maxmsg = maxcnt;
		attr.mq_msgsize = maxsize;
		int omode=0;
		if(block >0 )
			omode =O_NONBLOCK;
			
		mqID = mq_open(name, O_RDWR | O_CREAT | O_EXCL|omode, 0666, &attr);
	
		if (mqID < 0)
		{
			if (errno == EEXIST)
			{
				mqID = mq_open(name, O_RDWR);
				if(mqID < 0)
				{
					printf("open message queue error...%s",strerror(errno));
					return -1;
				}
			}
			else
			{
				printf("-----open message queue error...%s",strerror(errno));
				return -1;
			}
		}else
		{
			printf("-----open message queue ok...%d",mqID);
		}
		*dwOSMsgQID = mqID;
		return 0;

}


int msgQCreate(msgQ_t *dwOSMsgQID,char *name,int maxcnt,int maxsize,int block)
{
	    mqd_t mqID;
		mq_attr_t attr;
		attr.mq_maxmsg = maxcnt;
		attr.mq_msgsize = maxsize;
		int omode=0;
		if(block >0 )
			omode =O_NONBLOCK;
			
		mqID = mq_open(name, O_RDWR | O_CREAT | O_EXCL|omode, 0666, &attr);
	
		if (mqID < 0)
		{
			if (errno == EEXIST)
			{
				mq_unlink(name);
				mqID = mq_open(name, O_RDWR | O_CREAT|omode, 0666, &attr);
	
				if(mqID < 0)
				{
					printf("open message queue error...%s",strerror(errno));
					return -1;
				}
			}
			else
			{
				printf("-----open message queue error...%s",strerror(errno));
				return -1;
			}
		}else
		{
			printf("-----open message queue ok...%d",mqID);
		}
		*dwOSMsgQID = mqID;
		return 0;

}
int msgQReceive(msgQ_t dwOSMsgQID, char *pMsg, int dwMsgLen, int dwMsgPrio)
{
	int sdwRevLen;
	int dwMsgAddr;

	do
	{
		sdwRevLen = mq_receive(dwOSMsgQID, pMsg, dwMsgLen, dwMsgPrio);
	}
	while((-1 == sdwRevLen) && (errno == EINTR));
	return sdwRevLen;
}
int msgQSend(msgQ_t dwOSMsgQID, char *pMsg, int dwMsgLen, int dwMsgPrio)
{
	return mq_send(dwOSMsgQID, pMsg, dwMsgLen, dwMsgPrio);
}
int msgQdestory(msgQ_t dwOSMsgQID)
{
	mq_close(dwOSMsgQID);
}
int msgQGetMsgCnt(msgQ_t dwOSMsgQID)
{
	struct mq_attr attr;
	
	if (-1 == mq_getattr(dwOSMsgQID, &attr))
	{
		printf("msgQGetMsgCnt: Fail to get message queue info of Linux!\n");
		return -1;
	}else
	{   
		//printf("msgQGetMsgCnt: qid %d openmax %d priomax %d cur =%d flag=%d max=%d size=%d \n",dwOSMsgQID,sysconf(_SC_MQ_OPEN_MAX),sysconf(_SC_MQ_PRIO_MAX),attr.mq_curmsgs,attr.mq_flags,attr.mq_maxmsg,attr.mq_msgsize);
	}
	
	return attr.mq_curmsgs;
}

