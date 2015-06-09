#include <sys/wait.h>
#include "../include/agent.h"

agent::agent(){

	
}

agent::~agent(){

}

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

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

    if (!feof (file) )
    {
        while(fileSize>0) {
            bzero(msg.data, sizeof(msg.data));
            int num = fileSize < sizeof(msg.data) ? fileSize : sizeof(msg.data);
            if (fread(msg.data, 1, num, file) != num) break;
            agent1->getTcpModule()->send_msg(msg.getStringMessage().c_str());
            msg.type = remoTestMessage::RESULT;
            fileSize-=num;
        }
    }
    fclose (file);
    std::cout << "Result sent" << std::endl;
    pthread_mutex_lock(&mutex1);
    agent1->command_pid = -1;
    pthread_mutex_unlock(&mutex1);
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
            if ((rval = tcp_module.receive_msg(buffer)) == -1)
                return -1;
            else if(rval == 0)
                return 1;
            else{
                remoTestMessage message(buffer);
                if (message.type == remoTestMessage::STOP) {
                    kill_process();
                    continue;
                }
                else if (message.type == remoTestMessage::START_SCRIPT && command_pid == -1) {
                    size = message.size;
                    if((file = fopen("script.sh", "wb"))!=NULL){
                        int num = size < sizeof(message.data) ? size : sizeof(message.data);
                        fwrite(message.data, 1, num, file);
                        size -= num;
                    }
                }
                else if (message.type == remoTestMessage::SCRIPT && command_pid == -1) {
                    while (size > 0) {
                        int num = size < sizeof(message.data) ? size : sizeof(message.data);
                        fwrite(message.data, 1, num, file);
                        size -= num;
                    }
                }
                if(size==0 && command_pid == -1){
                    fclose(file);
                    std::cout << "Received script" << std::endl;
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
    std::cout << "Executing.." << std::endl;
    pthread_mutex_lock(&mutex1);
    command_pid = atoi(pid);
    pthread_mutex_unlock(&mutex1);

    pclose(pipe);


   pthread_create(&thread, NULL,send_msg, this);
}

int agent::kill_process(){
    std::string comm = "pkill -TERM -P " + std::to_string(command_pid);
    if(command_pid != -1){
       system(comm.c_str());
       command_pid = -1;
    }
    return 0;
}

bool isPidRunning(int pid){
    while(waitpid(-1, 0, WNOHANG) > 0) ;

    if (0 == kill(pid, 0))
        return 1; // Process exists

    return 0;
}