//
// Created by agata on 26.05.15.
//

#include "../include/nadzorca.h"

nadzorca::nadzorca(std::string confFileName) {
    FileParser parser;
    parser.setFilename(confFileName);
    list<Host> hosts = parser.getHosts();
    if(hosts.size() > 0)
        for(list<Host>::iterator i = hosts.begin(); i != hosts.end(); i++){
            sockaddr_storage stor = *i;
            tcp_modules.push_back(tcp_client(&stor));
        }
}
