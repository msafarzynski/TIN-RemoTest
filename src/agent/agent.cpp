#include "../../include/agent/agent.h"

Agent::Agent()
{
}

Agent::~Agent()
{
}

int Agent::send_msg(const char *msg) {
	tcp_module.send_msg(msg);
    std::cout << "Response----------------" << std::endl << msg << std::endl;
}

int Agent::receive_msg(char *msg) {
    if(tcp_module.receive_msg(msg) > 0)
       return 1;
    if(msg == NULL){
        perror("Something went wrong :/");
        return 1;
    }
    remoTestMessage message(msg);
    if(message.toolName == "stop"){
        kill_process();
        pthread_join(thread, nullptr);
        return 0;
    }

    std::string command = message.getCommand();
    std::cout << "Command: " << command << std::endl;

    FILE* pipe = popen(command.c_str(), "r");
    if (pipe == nullptr)  return 1;
    char pid[10];                                                   //
    if(feof(pipe) || fgets(pid, 10, pipe) == NULL){                 //pobranie pid utworzonego procesu
            perror("error reading pid");                            //
        return 1;                                                   //
    }                                                               //
    command_pid = atoi(pid);                                        //
    std::cout << "Process id: " << command_pid << std::endl;

    Targs* args = new Targs;
    args->pipe = pipe;
    args->message = message;
    if(pthread_create(&thread, NULL, &get_output, (void*)args) > 0){
        return 1;
    };

    std::cout << "Command running..." << std::endl;
    return 0;
}


void* get_output(void* args){
    Targs* arguments = (Targs*)args;
    char buffer[256];
    arguments->message.options = "";
    arguments->message.type = remoTestMessage::RESPONSE;
    while(!feof(arguments->pipe)) {
        if(fgets(buffer, 128, arguments->pipe) != NULL) {
            arguments->message.options += buffer;
            std::cout << buffer << std::endl;
        }
    }
    pclose(arguments->pipe);
    std::cout << "Tutaj!!!!!!!" << std::endl;
    arguments->agent1->send_msg(arguments->message.getResponse().c_str());

    pthread_exit(nullptr);
}

int Agent::kill_process(){
    kill(command_pid, SIGINT);
    std::cout << "Process killed" << std::endl;
    return 0;
}
