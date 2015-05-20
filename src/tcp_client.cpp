#include "../include/tcp_client.h"

tcp_client::tcp_client(struct sockaddr_storage* addr){
	struct addrinfo hints;
	struct addrinfo *res;
	char* server, *hisservice;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if(getaddrinfo(server, hisservice, &hints, &res) != 0){
		perror("error getaddrinfo");
		return;
	}

	sockfd = socket(res->ai_family, SOCK_STREAM, 0);
	if (sockfd == -1){
		perror("Cannot create socket");
		return;
	}

	if(connect(sockfd, (struct sockaddr*)&server, sizeof(struct sockaddr))==-1){
			perror("connecting stream socket");
			close(sockfd);
			return;
		}

}

tcp_client::~tcp_client(){
	close(sockfd);
}

int tcp_client::send_msg(const char* msg){
	if(send(sockfd, msg, strlen(msg), 0) == -1){
		perror("Writing on stream socket");
		return 1;
		}
	}

int tcp_client::receive_msg(char* msg){
	if(recv(sockfd, msg, 1024, 0) == -1){
		perror("error reading from socket");
		return 1;
	}
}

