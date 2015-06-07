#include <iostream>
#include "include/agent.h"


int main() {
    std::cout << "Hello, World!" << std::endl << std::endl;


    agent agent1;
    while(1)
        agent1.receive_msg(NULL);

    return 0;
}
