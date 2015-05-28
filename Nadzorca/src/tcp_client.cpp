
#include "../include/tcp_client.h"

tcp_client::tcp_client(struct sockaddr_storage* addr){
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	char *server;
	int error;

	memset(&hints, 0, sizeof(hints));
	/* set-up hints structure */
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int s;
	char ip[256];																			//"3490"!!!
	char port[256];
	int port1;
	switch (addr->ss_family) {
		case AF_INET:
			inet_ntop(addr->ss_family, &((struct sockaddr_in *)addr)->sin_addr, ip, 256);
			port1 = ((struct sockaddr_in *)addr)->sin_port;
			break;
		case AF_INET6:
			inet_ntop(addr->ss_family, &((struct sockaddr_in6 *)addr)->sin6_addr, ip, 256);
			port1 = ((struct sockaddr_in6 *)addr)->sin6_port;
			break;
	}
	sprintf(port, "%d", port1);
	std::cout << port << std::endl;
	s = getaddrinfo(ip, port, &hints, &result);
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

char* tcp_client::getIp(){

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

