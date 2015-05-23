//
// Created by Agata Debska on 22.05.15.
//
//klasa przechowujaca wiadomosc


#ifndef TIN_REMOTESTMESSAGE_H
#define TIN_REMOTESTMESSAGE_H

#include <string>
#include <iostream>

class remoTestMessage{
    enum Ttype {REQUEST, RESPONSE}type;
    struct Ttool{
        std::string stringTool[4] = {"iperf", "ping", "ethstats", "stop"};
        enum toolenum{
            IPERF, PING, ETHSTATS, STOP
        };
    }tool;
    std::string toolToString(int t){return tool.stringTool[t];}
public:
    std::string toolName;
    std::string options;

public:
    remoTestMessage(char*);
    ~remoTestMessage(){};
    std::string getCommand();
};



#endif //TIN_REMOTESTMESSAGE_H
