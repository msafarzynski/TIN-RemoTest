//
// Created by Agata Debska on 21.05.15.
//
//modul agenta wykorzystujacy modul serwera tcp

#ifndef TIN_AGENT_H
#define TIN_AGENT_H

#include "tcp_server.h"
#include "remoTestMessage.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <pthread.h>

class agent{
	tcp_server tcp_module;
	pid_t command_pid = -1;
	pthread_t thread;
public:
	agent();
	~agent();
	int send_msg(const char*);
	int receive_msg(char*);
	int kill_process();
	void execute();
};


#endif






