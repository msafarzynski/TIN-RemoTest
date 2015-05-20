#include "../include/tcp_server.h"

tcp_server::tcp_server(){

	struct addrinfo hints;
	struct addrinfo *res;
	char* myservice;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	if(getaddrinfo(NULL, myservice, &hints, &res) != 0){
		perror("error getaddrinfo");
		return;
	}

	sockfd = socket(res->ai_family, SOCK_STREAM, 0);

	if(-1 == sockfd) {
		perror("can not create socket");
		return;
	}
	if(bind(sockfd, (struct sockaddr*) res->ai_addr, sizeof(struct sockaddr)) == -1) {
		perror("error binding the socket");
		return;
	}
	listen(sockfd, 5);
	msgsock = accept(sockfd, (struct sockaddr*) 0, 0);
	if(msgsock == -1){
		perror("Accept");
		return;
	}
	else printf("Server is ready");
}

tcp_server::~tcp_server(){
	close(msgsock);
	close(sockfd);
}

int tcp_server::send_msg(const char* msg){
	if(send(msgsock, msg, strlen(msg), 0) == -1){
		perror("eroor sendin message");
		return 1;
	}
	return 0;
}

int tcp_server::receive_msg(char* msg){
	int rval;
	if(msg == NULL){
		perror("NULL buffer");
		return 1;
	}
	if((rval = recv(msgsock, msg, sizeof(msg), 0)) == -1){
		perror("Reading stream message");
		close(msgsock);
		return 1;
	}
	if(rval == 0){
		printf("Ending connection\n");
		close(msgsock);
	}
	else
		printf("Message --> %s\n", msg);
	return 0;
}
