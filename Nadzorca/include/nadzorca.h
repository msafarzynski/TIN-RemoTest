//
// Created by agata on 26.05.15.
//

#ifndef NADZORCA_NADZORCA_H
#define NADZORCA_NADZORCA_H


#include "../include/tcp_client.h"
#include "../include/FileParser.h"
#include <vector>
#include <pthread.h>
#include <stdlib.h>


class nadzorca{
    std::vector<tcp_client> tcp_modules;
    std::vector<pthread_t> threads;
public:
    nadzorca(std::string confFileName);
    ~nadzorca(){};
    void showAgentsIps();
    int send_script(std::string fileName, int);
    int stopScript(int);
};

extern pthread_mutex_t mutex;
void* receiveOutput(void* arg);



#endif //NADZORCA_NADZORCA_H
