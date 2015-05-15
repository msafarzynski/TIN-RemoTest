  #include "../include/tcp_client.h"

 tcp_client::tcp_client(char* char_addr, int port){
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
      perror("Cannot create socket");
      return;
    }
    if(strchr(char_addr, '.') != NULL){
      hp = gethostbyname(char_addr);
      if(hp == NULL){
        perror("Invalid address");
        return;
      }
      memset((char*)&addr4, 0, sizeof(addr4));
      addr4.sin_family = AF_INET;
      memcpy((char*)&addr4.sin_addr, (char*)hp->h_addr, hp->h_length);
      addr4.sin_port = htons(port);
      if(connect(sockfd, (struct sockaddr*)&addr4, sizeof(addr4))==-1){
        perror("connecting stream socket");
        close(sockfd);
        return;
      }
    }
    else if(strchr(char_addr, ':') != NULL){
      hp = gethostbyname2(char_addr, AF_INET6);
      if(hp == NULL){
        perror("Invalid address");
        return;
      }
      memset((char*)&addr6, 0, sizeof(addr6));
      //addr6.sin6_len = sizeof(addr6);
      memcpy((char*)&addr6.sin6_addr, (char*)hp->h_addr, hp->h_length);
      addr6.sin6_family = AF_INET6;
      addr6.sin6_port = htons(port);
      if(connect(sockfd, (struct sockaddr*)&addr6, sizeof(addr6))==-1){
        perror("connecting stream socket");
        close(sockfd);
        return;
      }
    }
 }
 tcp_client::~tcp_client(){
  close(sockfd);
 }
 
 
 int tcp_client::write_msg(const char* msg){
    if(write(sockfd, msg, strlen(msg) == -1){
      perror("Writing on stream socket");
      return 1;
    }
  }
