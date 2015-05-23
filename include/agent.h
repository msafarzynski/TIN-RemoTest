#ifndef TIN_AGENT_H
#define TIN_AGENT_H

#include "remoTestMessage.h"
#include "tcp_server.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <signal.h>

class agent{
	tcp_server tcp_module;
	pid_t command_pid;
public:
	agent();
	~agent();
	int send_msg(const char* msg);
	int receive_msg(char* msg);
	int execute_command(const char* command);
	int kill_process();
};

#endif
