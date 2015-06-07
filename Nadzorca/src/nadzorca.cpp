//
// Created by agata on 26.05.15.
//

#include "../include/nadzorca.h"
#include "../include/remoTestMessage.h"

nadzorca::nadzorca(std::string confFileName) {
    FileParser parser;
    parser.setFilename(confFileName);
    list<Host> hosts = parser.getHosts();
    if(hosts.size() > 0)
        for(list<Host>::iterator i = hosts.begin(); i != hosts.end(); i++){
            sockaddr_storage stor = *i;
            tcp_client client = tcp_client(&stor);
            if(client.isConnected())
                 tcp_modules.push_back(client);
        }
}

void nadzorca::showAgentsIps(){
    std::cout << "----Podlaczone agenty-------------------------" << std::endl;
    int j = 0;
    for(vector<tcp_client>::iterator i = tcp_modules.begin(); i != tcp_modules.end(); i++){
        std::string ip;
        ip = (*i).getIp();
        std::cout << j << ":  " << ip << std::endl;
        j++;
    }
    std::cout << "----------------------------------------------" << std::endl;
}

int nadzorca::send_script(std::string fileName, int agentId){
    FILE* file = fopen(fileName.c_str(), "rb");
    if(file == NULL){
        perror("error reading script file");
        return 1;
    }
    remoTestMessage msg;
    msg.type = remoTestMessage::START_SCRIPT;
    fseek (file , 0 , SEEK_END);
    int fileSize = ftell (file);
    msg.size = (uint32_t) fileSize;
    rewind (file);
    std::cout << "Size:" << msg.size << std::endl;

    if (!feof (file) )
    {
        while(fileSize>0) {
            int num = fileSize < sizeof(msg.data) ? fileSize : sizeof(msg.data);
            std::cout << "num:" << num << std::endl;
            if (fread(msg.data, 1, num, file) != num) break;
            tcp_modules[agentId].send_msg(msg.getStringMessage().c_str());
            msg.type = remoTestMessage::SCRIPT;
            fileSize-=num;
            std::cout << "Size-num:" << fileSize << std::endl;
        }
    }
    fclose (file);

}

int nadzorca::stopScript(int agentId){
    remoTestMessage msg;
    msg.type = remoTestMessage::STOP;
    std::cout << "stop script-->" << msg.getStringMessage().c_str() << std::endl;
    tcp_modules[agentId].send_msg(msg.getStringMessage().c_str());
}

void* receiveOutput(void* arg){

}