//
// Created by Agata Debska on 23.05.15.
//
//klasa przechowujaca wiadomosc


#ifndef TIN_REMOTESTMESSAGE_H
#define TIN_REMOTESTMESSAGE_H

#include <cstring>
#include <iostream>

struct remoTestMessage{
    uint32_t size = 0;
    char data[1015];
    enum Ttype{STOP, START_SCRIPT, SCRIPT, START_RESULT, RESULT}type;
    remoTestMessage(const char*);
    remoTestMessage(){};
    ~remoTestMessage(){};
    std::string getStringMessage();
};



#endif //TIN_REMOTESTMESSAGE_H
