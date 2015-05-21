#pragma once
#include "tcp_server.h"

class agent{
	tcp_server tcp_module;
public:
	agent();
	~agent();
	int send_msg(const char* msg);
	int receive_msg(char* msg);
};
