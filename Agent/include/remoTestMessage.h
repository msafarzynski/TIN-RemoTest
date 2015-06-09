#ifndef TIN_REMOTESTMESSAGE_H
#define TIN_REMOTESTMESSAGE_H

#include <cstring>
#include <iostream>
#define DATA_SIZE 1015

struct remoTestMessage{
    uint32_t size = 0;
    char data[DATA_SIZE];
    enum Ttype{STOP, START_SCRIPT, SCRIPT, START_RESULT, RESULT}type;
    remoTestMessage(const char*);
    remoTestMessage(){};
    ~remoTestMessage(){};
    std::string getStringMessage();
};



#endif //TIN_REMOTESTMESSAGE_H
