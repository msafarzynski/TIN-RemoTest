#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#pragma once

class tcp_server{
	struct sockaddr_storage server;
	int sockfd, msgsock;
public:
	tcp_server();
	~tcp_server();					//zamyka wczesniej utworzony port
	int send_msg(const char* msg);	
	int receive_msg(char* msg);
	int accept_conn();
	void close_socket();
};
