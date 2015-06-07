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
#include <unistd.h>

class agent{
	tcp_server tcp_module;
	int command_pid = -1;
	pthread_t thread;
	FILE* file;
public:
	agent();
	~agent();
	tcp_server* getTcpModule(){ return &tcp_module; };
	int receive_msg(char*);
	int kill_process();
	void execute();
};


void* send_msg(void*);

#endif






