//
// Created by Agata Debska on 23.05.15.
//

#include "../include/remoTestMessage.h"

remoTestMessage::remoTestMessage(const char* message){
    char buf;
    strncpy(&buf, message, 1);
    int a = atoi(&buf);
    type = (Ttype)a;
    if(type != STOP){
        char buf1[4];
        strncpy(buf1, message+1, 4);
        size = atol(buf1);
        strncpy(data, message+5, sizeof(data));
    }
    else{
        size = 0;
        bzero(data, sizeof(data));
    }
}


std::string remoTestMessage::getStringMessage(){
    std::string Stype = std::to_string((int)type);
    if(type==STOP)
        return Stype;
    char s[8];
    sprintf(s, "%04d", size);
    std::string Ssize = std::string(s);
    return Stype + Ssize + std::string(data);
}