//
// Created by Agata Debska on 23.05.15.
//

#include "../include/remoTestMessage.h"

remoTestMessage::remoTestMessage(char* message){
    std::string msg(message);
    type = (Ttype)std::stoi(msg.substr(0,1).c_str());
    toolName = toolToString(std::stoi(msg.substr(1,1).c_str()));
    options = msg.substr(2);
}

std::string remoTestMessage::getCommand(){
    return toolName + " " + options;        //moze srednik???
}
