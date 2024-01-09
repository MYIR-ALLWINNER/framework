#ifndef MYSHAREMEMORY_H
#define MYSHAREMEMORY_H
#include <iostream>
#include <string>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;
//共享内存操作类
class CShareMem
{
	public:
		CShareMem(int key, int size, int flag=0666|IPC_CREAT);		//共享内存操作类构造函数
		~CShareMem();					//共享内存操作类析构函数
		bool createMemory();					//创建共享内存方法
		bool destroyMemory();					//销毁共享内存方法
		bool attachMemory(char*& pmemoryAddr);			//attach共享内存方法
		bool detachMemory(char* pmemoryAddr);			//detach共享内存方法
		char *getShareMem(){
				return m_memoryAddr;
		}
		
	private:
		
		int m_key;									//共享内存key
		int m_size;									//共享内存大小
		int m_flag;									//共享内存创建标志
		int m_shmid;									//共享内存描述符
		char *m_memoryAddr;							        //共享内存地址指针
};
#endif