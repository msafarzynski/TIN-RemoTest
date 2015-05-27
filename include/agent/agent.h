#ifndef TIN_AGENT_H
#define TIN_AGENT_H

#include "remoTestMessage.h"
#include "tcp_server.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <pthread.h>

class agent{
	tcp_server tcp_module;
	pid_t command_pid;
	pthread_t thread;
public:
	agent();
	~agent();
	int send_msg(const char* msg);
	int receive_msg(char* msg);
	int kill_process();
	void execute();
};
#endif
