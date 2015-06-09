#include <sys/wait.h>
#include "../include/agent.h"
agent::agent(){

	
}

agent::~agent(){

}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* send_msg(void *a) {
    agent* agent1 = (agent*) a;
    while(isPidRunning(agent1->command_pid));                             //script is running

    FILE* file = fopen("output.txt", "rb");
    if(file == NULL){
        perror("error reading output file");
        return nullptr;
    }
    remoTestMessage msg;
    msg.type = remoTestMessage::START_RESULT;
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
            std::cout << msg.data;
            if (fread(msg.data, 1, num, file) != num) break;
            agent1->getTcpModule()->send_msg(msg.getStringMessage().c_str());
            msg.type = remoTestMessage::RESULT;
            fileSize-=num;
            std::cout << "Size-num:" << fileSize << std::endl;
        }
    }
    fclose (file);
   // file = fopen("output.txt", "wb");
   // fclose (file);
    pthread_mutex_lock(&mutex);
    agent1->command_pid = -1;
    pthread_mutex_unlock(&mutex);
    pthread_kill(agent1->thread, 0);
}



int agent::receive_msg(char *msg) {
    if(tcp_module.accept_conn() > 0 )
        return 1;
    else {
        char buffer[1024];
        uint32_t size;
        int rval = 0;
        do {
            bzero(buffer, 1024);
          //  std::cout << "waiting for message" << std::endl;
            if ((rval = tcp_module.receive_msg(buffer)) == -1)
                return -1;
            else if(rval == 0)
                return 1;
            else{
                std::cout << "message-->" << buffer << std::endl;
                remoTestMessage message(buffer);
                if (message.type == remoTestMessage::STOP) {
                    kill_process();
                    continue;
                }
                else if (message.type == remoTestMessage::START_SCRIPT && command_pid == -1) {
                    std::cout << "START_SCRIPT" << std::endl;
                    size = message.size;
                    if((file = fopen("script.sh", "wb"))!=NULL){
                        int num = size < sizeof(message.data) ? size : sizeof(message.data);
                        fwrite(message.data, 1, num, file);
                        size -= num;
                    }
                }
                else if (message.type == remoTestMessage::SCRIPT && command_pid == -1) {
                    while (size > 0) {
                        std::cout << "SCRIPT" << std::endl;
                        int num = size < sizeof(message.data) ? size : sizeof(message.data);
                        fwrite(message.data, 1, num, file);
                        size -= num;
                    }
                }
                if(size==0 && command_pid == -1){
                    fclose(file);
                    execute();
                }
            }
        } while (rval != 0);
        tcp_module.close_socket();
    }
    return 0;

}

void agent::execute(){
    char pid[10];
    char buffer[256];
    bzero(buffer, 256);
    bzero(pid, 10);
    FILE* pipe = popen("sh script.sh>output.txt & echo $!", "r");
    if (pipe == nullptr)  return;
    if(fgets(pid, 10, pipe) == NULL || feof(pipe)) {                    //pobranie pid utworzonego procesu
        perror("error reading pid");                                //
        return;                                                    //
    }
    pthread_mutex_lock(&mutex);
    command_pid = atoi(pid);
    pthread_mutex_unlock(&mutex);
 /*   pid_t p = fork();
    if (p == (pid_t) -1) {
       perror("error creating process");
        return;
    } else if (p == 0) {    // CHILD

    } else {                // PARENT

    }
*/
    /*
    std::cout <<  "pid[]-->" << pid << std::endl;
    std::cout << "Agent pid: " << getpid() << std::endl;
    std::cout << "----pgid " << getpgrp() << std::endl;

    std::cout << "pid-->" << command_pid<< std::endl;
    */
    pclose(pipe);


   pthread_create(&thread, NULL,send_msg, this);
}

int agent::kill_process(){
    std::string comm = "pkill -TERM -P " + std::to_string(command_pid);
   // std::string comm = "kill -- -" + std::to_string(command_pid);
    std::cout << comm.c_str() << std::endl;
    if(command_pid != -1){
      // pkill(command_pid, 9);
       system(comm.c_str());
        command_pid = -1;
    }
    return 0;
}

bool isPidRunning(int pid){
    while(waitpid(-1, 0, WNOHANG) > 0) {
        // Wait for defunct....
    }

    if (0 == kill(pid, 0))
        return 1; // Process exists

    return 0;
}