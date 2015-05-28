//
// Created by agata on 26.05.15.
//

#ifndef NADZORCA_NADZORCA_H
#define NADZORCA_NADZORCA_H


#include "../include/tcp_client.h"
#include "../include/FileParser.h"
#include <vector>

class nadzorca{
    std::vector<tcp_client> tcp_modules;
public:
    nadzorca(std::string confFileName);
    ~nadzorca(){};
};

#endif //NADZORCA_NADZORCA_H
