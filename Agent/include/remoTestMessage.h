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
    char data[1016];
    enum Ttype{STOP, START_SCRIPT, SCRIPT, START_RESULT, RESULT}type;
    remoTestMessage(const char*);
    remoTestMessage(){};
    ~remoTestMessage(){};
    std::string getCommand();               //zmienia otrzymany komunikat w komende shellowa (+dopisuje & echo $! zeby dostac id processu)
    std::string getResponse();
    int getToolId();
};



#endif //TIN_REMOTESTMESSAGE_H
