#include <iostream>
#include "include/agent.h"


int main() {

    std::cout << "---------------RemoTest--------------" << std::endl;
    agent agent1;
    while(1)
        agent1.receive_msg(NULL);

    return 0;
}
