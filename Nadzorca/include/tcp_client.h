#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#pragma once

class tcp_client{
	struct sockaddr_storage server;
	int sockfd;
public:
	tcp_client(struct sockaddr_storage* addr);		//tworzy klienta tcp (laczy sie z podanym adresem ip)
	tcp_client();
	~tcp_client();					//zamyka wczesniej utworzony port
	int send_msg(const char* msg);			
	int receive_msg(char* msg);
	char* getIp();
};
