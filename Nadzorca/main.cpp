#include <iostream>
#include "include/tcp_client.h"
#include "include/remoTestMessage.h"
#include "include/nadzorca.h"
#include <string>


int main() {
    std::cout << "Nadzorca" << std::endl << std::endl;

    std::string file = "hosts.txt";
    nadzorca nadzorca1(file);

  //  pthread_t thread = pthread_create()
    while(1) {
        nadzorca1.showAgentsIps();
        std::cout << "Prosze wybrac agenta do testow:   ";
        int agent;
        cin >> agent;

        std::cout << "Wybrano agenta " << agent << std::endl;

        std::cout << "Chcesz uruchomic skrypt czy zatrzymac dzialajacy? [u/z]" << std::endl;
        char op;
        cin >> op;
        if (op == 'z')
            nadzorca1.stopScript(agent);
        else {

            std::cout << "Podaj sciezke do pliku do wyslania:  ";
            std::string script;
            cin >> script;

            nadzorca1.send_script(script, agent);
        }
    }
    return 0;
}
