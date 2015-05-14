  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <cstring>
  #include <unistd.h>
 
class tcp_client{
    struct sockaddr_in addr4;
    struct sockaddr_in6 addr6;
    struct hostent *hp;
    int sockfd;
 public:
  tcp_client(char* char_addr, int port);
  ~tcp_client();
  int write(const string& msg);
  int send(const string& msg);
