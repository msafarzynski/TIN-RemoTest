//
// Created by Agata Debska on 23.05.15.
//

#include "../include/remoTestMessage.h"

remoTestMessage::remoTestMessage(const char* message){
    std::cout << message << std::endl;
    char buf;
    strncpy(&buf, message, 1);
    std::cout << buf << std::endl;
    int a = atoi(&buf);
    std::cout << a << std::endl;
    type = (Ttype)a;
    if(type != STOP){
        char buf1[8];
        strncpy(buf1, message+1, 8);
        size = atol(buf1);
        strncpy(data, message+9, sizeof(data));
    }
    std::cout << type << "  " << size << "  " << data << std::endl;
}
/*
std::string remoTestMessage::getResponse(){
    return "1" + std::to_string(getToolId()) + options;
}

int remoTestMessage::getToolId() {
    for(int i=0; i < tool.stringTool->size();i++){
        if(tool.stringTool[i] == toolName)
            return i;
    }
    return -1;
}
 */