#include "../include/agent.h"
agent::agent(){

	
}

agent::~agent(){

}

int agent::send_msg(const char *msg) {
    tcp_module.send_msg(msg);
    std::cout << "Response----------------" << std::endl << msg << std::endl;
}



int agent::receive_msg(char *msg) {
    if(tcp_module.accept_conn() > 0 )
        return 1;
    std::cout << "Connection accepted" << std::endl;
    char buffer[1024];
    FILE* file;
    uint32_t size;
    int rval;
    do {
        if (tcp_module.receive_msg(buffer) == -1)
            return -1;
        remoTestMessage message(buffer);
        if (message.type == remoTestMessage::STOP) {
            kill_process();
            return 0;
        }
        else if (message.type == remoTestMessage::START_SCRIPT) {
            size = message.size;
            file = fopen("script.sh", "w");
            int num = size < sizeof(message.data) ? size : sizeof(message.data);
            fwrite(message.data, 1, num, file);
            return 0;
        }
        else if (message.type == remoTestMessage::SCRIPT) {
            while (size > 0) {
                int num = size < sizeof(message.data) ? size : sizeof(message.data);
                if (tcp_module.receive_msg(buffer) == -1)
                    return -1;
                fwrite(message.data, 1, num, file);
                size -= num;
            }
            fclose(file);
            execute();
        }
    }while(rval != 0);
    tcp_module.close_socket();

}

void agent::execute(){
    FILE* pipe = popen("sh script.sh>output.txt & echo $!", "r");
    if (pipe == nullptr)  return;
    char pid[10];                                                   //
    if(feof(pipe) || fgets(pid, 10, pipe) == NULL){                 //pobranie pid utworzonego procesu
        perror("error reading pid");                                //
        return;                                                    //
    }                                                               //
    command_pid = atoi(pid);
    pclose(pipe);

}

int agent::kill_process(){
    std::string comm = "kill -SIGINT -- -"+command_pid;
    system(comm.c_str());
    std::cout << "Process killed" << std::endl;
    command_pid = -1;
    return 0;
}
