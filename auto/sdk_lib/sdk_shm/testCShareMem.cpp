#if 0
#include "CShareMem.h"
#define FLAG IPC_CREAT|IPC_EXCL|SHM_R|SHM_W 		//共享内存创建标志常量符号

int main()
{
	char *pAddrMemory;						   //定义字符指针用于指向获取共享内存首地址
	CShareMem *shareMemory = new CShareMem(0x900999,2000,FLAG);//创建共享内存操作对象
	if(shareMemory->createMemory() == false)			   //调用创建方法创建共享内存
	{
		cout<<"shareMemory->Create() false!"<<endl;		   //失败提示信息
	}
	if(shareMemory->attachMemory(pAddrMemory) == false)	           //attach挂接到共享内存
	{
		cout<<"shareMemory->attachMemory(pAddrMemory) false!"<<endl;
	}
	if(shareMemory->detachMemory(pAddrMemory) == false)	           //detach脱离共享内存
	{
		cout<<"shareMemory-> detachMemory (pAddrMemory) false"<<endl;
	}
	/*if(shareMemory->destroyMemory() == false)			  //销毁共享内存，实际应用可以去注视打开
	{
		cout<<"destroy share memory false!"<<endl;
	}*/
	delete shareMemory;
	return 0;
}
#endif