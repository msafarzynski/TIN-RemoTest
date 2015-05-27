#include "../include/tcp_client.h"

tcp_client::tcp_client(struct sockaddr_storage* addr){
	struct addrinfo hints;
	struct addrinfo *res;
	char* server, *hisservice;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int s = getaddrinfo("192.168.2.136", "3490", &hints, &result);
	if (s != 0) {
		perror(gai_strerror(s));
		return;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sockfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);
		if (sockfd == -1)
			continue;
		if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */
		close(sockfd);
	}

		if (rp == NULL) {               /* No address succeeded */
			fprintf(stderr, "Could not connect\n");
			exit(EXIT_FAILURE);
		}

		freeaddrinfo(result);           /* No longer needed */
	std::cout << "Connected to server" << std::endl;

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

