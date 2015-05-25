#ifndef TIN_NADZORCA_H
#define TIN_NADZORCA_H

#include "remoTestMessage.h"
#include "tcp_client.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <pthread.h>

class nadzorca{
	tcp_server tcp_module;
	pid_t command_pid;
	pthread_t thread;
public:
	nadzorca();
	~nadzorca();
	int send_msg(const char* msg);
	int receive_msg(char* msg);
	int kill_process();
};

struct Targs{				//struktura przechowujaca argumenty dla funkcji watku
	FILE* pipe;
	agent* agent1;
	remoTestMessage message;
};

void* get_output(void*);		//dla podanego Targs zwraca wynik skryptu

#endif
