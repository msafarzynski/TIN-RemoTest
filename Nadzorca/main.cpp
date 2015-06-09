#include <iostream>
#include "include/tcp_client.h"
#include "include/remoTestMessage.h"
#include "include/nadzorca.h"
#include <string>


int main() {
    std::cout << "Nadzorca" << std::endl << std::endl;

    std::string file = "hosts.txt";
    nadzorca nadzorca1(file);

    while(1) {
        nadzorca1.showAgentsIps();
        pthread_mutex_lock(&mutex);
        std::cout << "Prosze wybrac agenta do testow:   ";
        pthread_mutex_unlock(&mutex);
        int agent = 0;
        cin >> agent;


        pthread_mutex_lock(&mutex);
        std::cout << "Wybrano agenta " << agent << std::endl;
        pthread_mutex_unlock(&mutex);


        pthread_mutex_lock(&mutex);
        std::cout << "Chcesz uruchomic skrypt czy zatrzymac dzialajacy? [u/z]" << std::endl;
        pthread_mutex_unlock(&mutex);
        char op;
        cin >> op;
        if (op == 'z')
            nadzorca1.stopScript(agent);
        else {
            pthread_mutex_lock(&mutex);
            std::cout << "Podaj sciezke do pliku do wyslania:  ";

            pthread_mutex_unlock(&mutex);

            std::string script;
            cin >> script;

            nadzorca1.send_script(script, agent);
        }
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}
