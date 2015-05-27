  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <cstdio>
  #include <cstdlib>
  #include <cstring>
  #include <unistd.h>
 
#pragma once

class tcp_client{
    struct sockaddr_storage server;
    int sockfd;
 public:
  tcp_client(struct sockaddr_storage* addr);
  ~tcp_client();
  int send_msg(const char* msg);
  int receive_msg(char* msg);
};
