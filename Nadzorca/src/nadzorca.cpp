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
            if(client.isConnected()) {
                tcp_modules.push_back(client);
            }
        }
    for(std::vector<tcp_client>::iterator i =tcp_modules.begin(); i!= tcp_modules.end(); ++i){
        threads.push_back(pthread_t());
        pthread_create(&threads.back(), NULL, receiveOutput, &(*i));
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

    if (!feof (file) )
    {
        while(fileSize>0) {
            int num = fileSize < sizeof(msg.data) ? fileSize : sizeof(msg.data);
            if (fread(msg.data, 1, num, file) != num) break;
            tcp_modules[agentId].send_msg(msg.getStringMessage().c_str());
            msg.type = remoTestMessage::SCRIPT;
            fileSize-=num;
        }
    }
    fclose (file);

}

int nadzorca::stopScript(int agentId){
    remoTestMessage msg;
    msg.type = remoTestMessage::STOP;
    tcp_modules[agentId].send_msg(msg.getStringMessage().c_str());
}

void* receiveOutput(void* arg){
    while(true) {
        tcp_client *tcp_module = (tcp_client *) arg;
        char buffer[1024];
        uint32_t size;
        FILE* outFile;
        int rval = -1;
        while (rval != 0) {
            bzero(buffer, 1024);
            if ((rval = tcp_module->receive_msg(buffer)) == -1)
                continue;
            else if (rval == 0)
                continue;
            else {
                remoTestMessage message(buffer);
                if (message.type == remoTestMessage::START_RESULT) {
                    outFile = fopen((tcp_module->getIp()+".txt").c_str(), "w");
                    size = message.size;
                    int num = size < sizeof(message.data) ? size : sizeof(message.data);
                    fwrite(message.data, 1, num, outFile);
                    size -= num;
                }
                else if (message.type == remoTestMessage::RESULT) {
                    while (size > 0) {
                        int num = size < sizeof(message.data) ? size : sizeof(message.data);
                        fwrite(message.data, 1, num, outFile);
                        size -= num;
                    }
                }
                if(size == 0) {
                    fclose(outFile);
                    std::cout << "Received data from " << tcp_module->getIp() << std::endl;
                }
            }
        }
    }
}