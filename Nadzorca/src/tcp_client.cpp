
#include "../include/tcp_client.h"

tcp_client::tcp_client(struct sockaddr_storage* addr){
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int error;
	server = *addr;
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
			inet_ntop(addr->ss_family, &((struct sockaddr_in *)&server)->sin_addr, ip, 256);
			port1 = ((struct sockaddr_in *)addr)->sin_port;
			break;
		case AF_INET6:
			inet_ntop(addr->ss_family, &((struct sockaddr_in6 *)&server)->sin6_addr, ip, 256);
			port1 = ((struct sockaddr_in6 *)addr)->sin6_port;
			break;
	}
	sprintf(port, "%d", port1);
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
			break;
	}

		if (rp == NULL) {
			fprintf(stderr, "Could not connect\n");
			sockfd=-1;
			return;
		}

		freeaddrinfo(result);
	std::cout << "Connected to server" << std::endl;

}

bool tcp_client::isConnected() {
	return sockfd!=-1?true:false;
}

std::string tcp_client::getIp(){
	char ip[256];
	if(server.ss_family == AF_INET)
		inet_ntop(server.ss_family, &((struct sockaddr_in *)&server)->sin_addr, ip, sizeof ip);
	else
		inet_ntop(server.ss_family, &((struct sockaddr_in6 *)&server)->sin6_addr, ip, sizeof ip);
	return std::string(ip);
}

tcp_client::~tcp_client(){
}

int tcp_client::send_msg(const char* msg){
	if(send(sockfd, msg, strlen(msg), 0) == -1){
		perror("Writing on stream socket");
		return 1;
		}
	}

int tcp_client::receive_msg(char* msg){
	int rval;
	if(msg == NULL){
		perror("NULL buffer");
		return -1;
	}
	if((rval = recv(sockfd, msg, 1024, 0)) == -1){
		perror("Reading stream message");
		close(sockfd);
		return -1;
	}
	if(rval == 0){
		printf("Ending connection\n");
		close(sockfd);
		return 0;
	}
	return sizeof(msg);
}

