#include <sys/socket.h>
#include <sys/un.h>
#include <utils/Thread.h>
#include <utils/KeyedVector.h>
#include <cutils/log.h>

#include "CallbackNotifier.h"
#include "DebugLevelThread.h"

DebugLevelThread::DebugLevelThread(void)
{
	ALOGD("DebugLevelThread construct\n");
	mCommandThread = new DoCommandThread(this);
	mCommandThread->startThread();
}

DebugLevelThread::~DebugLevelThread()
{
	if (mCommandThread != NULL) {
		mCommandThread->stopThread();
		mCommandThread.clear();
		mCommandThread = NULL;
	}
}

bool DebugLevelThread::commandThread()
{
	if (mCommandThread->getThreadStatus() == THREAD_STATE_EXIT) {
		ALOGD("DebugLevelThread exited\n");
		mCommandThread->stopThread();
		return false;
	}
	//printf("socket begin\n");

	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("Loglevel_server");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "Loglevel_server");
	server_len = sizeof(server_address);

	bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
	listen(server_sockfd, 5);
	int rev_data = 0;
	while (1) {
		ALOGD("Loglevel_server is waiting...\n");

		client_len = sizeof(client_address);
		client_sockfd =
			accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) & client_len);

		read(client_sockfd, &rev_data, sizeof(rev_data));
		ALOGD("server got a data :%d\n", rev_data);
		sdk_log_setlevel(rev_data);
		close(client_sockfd);
	}

	return true;
}
