//Data: 2015-05-04
//Autor: Jakub Nalewajek
//Opis: Kod źródłowy klasy FileParser. Klasa ta ma na celu utworzyć listę adresów IPv4/IPv6 na podstawie zadanego pliku wejściowego.

#include <iostream>
#include "../include/FileParser.h"
int FileParser::parseAddress(char* addressAsText, Host* nextHost) //zwraca 1 - sukces, 0 - blad
{
    in_addr buf;
    in6_addr buf6;
    char port[4];
    int spacePos = (int)(strchr(addressAsText, ' ')-addressAsText);
    std::cout << spacePos << std::endl;
    char* ip = new char[spacePos];
    strncpy(ip, addressAsText, spacePos);
    std::cout << ip << std::endl;
    strncpy(port, addressAsText+spacePos+1, 4);
    std::cout << port << std::endl;
    if (inet_pton(AF_INET,ip,&buf) == 1) //sprawdza, czy mamy poprawny adres IPv4 i zapisuje go w buf
    {
        nextHost->ss_family=AF_INET;
        ((sockaddr_in *)nextHost)->sin_port = atoi(port);
        ((sockaddr_in *)nextHost)->sin_addr = buf;
        return 1;
    }
    if (inet_pton(AF_INET6, ip,&buf6) == 1)//jezeli nie IPv4, to moze IPv6?
    {
        nextHost->ss_family=AF_INET6;
        ((sockaddr_in6 *)nextHost)->sin6_port = atoi(port);
        ((sockaddr_in6 *)nextHost)->sin6_addr = buf6;
        return 1;
    }
    delete[] ip;
    return 0; // string nie zawiera poprawnego adresu IPv4/6
}
list<Host> FileParser::getHosts()
{
    fstream file;
    list<Host> hosts;
    Host nextHost;
    char addressAsText[256];
    file.open(filename, ios_base::in);
    if(file.good()) {
        while (!file.eof()) {
            file.getline(addressAsText, 256);
            if (strlen(addressAsText) && parseAddress(addressAsText, &nextHost))  //jezeli udalo sie uzyskac poprawny adres,
                hosts.push_back(nextHost); // dodajemy do listy
        }
    }
    file.close();
    return hosts;
}

int FileParser::setFilename(string _filename)
{
    filename = _filename;
}