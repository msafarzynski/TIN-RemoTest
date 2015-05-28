#include <iostream>
#include "include/agent.h"


int main() {
    std::cout << "Hello, World!" << std::endl << std::endl;

    char msg[] = "312345678jksdfbafjsbgjabfogijfgalbalfjbafdjkgbkfjbafkjgbndklgjfadngjkdshdkfgbkjdfghjkjhgfdswertgbvcxdfrtghybgvftyhnbvgh";
    char msg1[] = "0764873866749kjhgfdsdfvgbhnjhgvfdxdcfvgbhnbhgfdsdcfvgbgvfcvgbv";

    remoTestMessage mess(msg);
    remoTestMessage mess1(msg1);


    agent agent1;
    while(1)
        agent1.receive_msg(NULL);

    return 0;
}
