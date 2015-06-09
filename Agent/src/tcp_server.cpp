#include <iostream>
#include "../include/tcp_server.h"

tcp_server::tcp_server(){

	struct addrinfo hints;
	struct addrinfo *result, *rp;
	char* myservice;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	int s = getaddrinfo(NULL, "3491", &hints, &result);
	if(s != 0){
		perror(gai_strerror(s));
		return;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {

		sockfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);
		if (sockfd == -1)
			continue;

		if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			std::cout << "Binded socket" << std::endl;
			break;                  /* Success */
		}
		close(sockfd);
	}
	if (rp == NULL) {
		// looped off the end of the list with no successful bind
		fprintf(stderr, "failed to bind socket\n");
		return;
	}
	freeaddrinfo(result);

	listen(sockfd, 5);

	std::cout << "Ready" << std::endl;

}

tcp_server::~tcp_server(){
	close(msgsock);
	close(sockfd);
}

void::tcp_server::close_socket(){
	close(msgsock);
}

int tcp_server::accept_conn(){
	msgsock = accept(sockfd, (struct sockaddr*) 0, 0);
	if(msgsock == -1){
		perror("Accept");
		return 1;
	}
	std::cout << "Connection accepted" << std::endl;
	return 0;
}

int tcp_server::send_msg(const char* msg){
	if(send(msgsock, msg, strlen(msg), 0) == -1){
		perror("error sending message");
		return -1;
	}
	return strlen(msg);
}

int tcp_server::receive_msg(char* msg){
	int rval;
	if(msg == NULL){
		perror("NULL buffer");
		return -1;
	}
	if((rval = recv(msgsock, msg, 1024, 0)) == -1){
		perror("Reading stream message");
		close(msgsock);
		return -1;
	}
	if(rval == 0){
		printf("Ending connection\n");
		close(msgsock);
		return 0;
	}
	return sizeof(msg);
}


