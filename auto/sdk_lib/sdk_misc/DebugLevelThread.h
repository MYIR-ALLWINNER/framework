#ifndef _DEBUGLEVELTHREAD_H_
#define _DEBUGLEVELTHREAD_H_

using namespace android;
class DebugLevelThread {
  public:
	DebugLevelThread();			//construct
	~DebugLevelThread();
	bool commandThread();

	class DoCommandThread:public Thread {
		DebugLevelThread *mDebugLevelThread;
		ThreadState mThreadStatus;
	  public:
		 DoCommandThread(DebugLevelThread * debuglevel):
			Thread(false), mDebugLevelThread(debuglevel), mThreadStatus(THREAD_STATE_NULL) {
		} void startThread() {
			mThreadStatus = THREAD_STATE_RUNNING;
			run("DebugLevelThread", PRIORITY_NORMAL);
		} void stopThread() {
			mThreadStatus = THREAD_STATE_EXIT;
		}
		ThreadState getThreadStatus() {
			return mThreadStatus;
		}
		bool isThreadStarted() {
			return (mThreadStatus == THREAD_STATE_PAUSED)
				|| (mThreadStatus == THREAD_STATE_RUNNING);
		}
		virtual bool threadLoop() {
			return mDebugLevelThread->commandThread();
		}
	};
	sp < DoCommandThread > mCommandThread;

};

#endif
