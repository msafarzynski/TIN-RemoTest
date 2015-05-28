#include <iostream>
#include "include/tcp_client.h"
#include "include/remoTestMessage.h"
#include "include/nadzorca.h"
#include <string>


int main() {
    std::cout << "Nadzorca" << std::endl << std::endl;

   std::string file = "hosts.txt";
    nadzorca nadzorca1(file);



    return 0;
}
