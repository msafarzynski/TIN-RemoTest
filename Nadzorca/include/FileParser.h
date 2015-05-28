//Data: 2015-05-04
//Autor: Jakub Nalewajek
//Opis: Plik nagłówkowy klasy FileParser. Klasa ta ma na celu utworzyć listę adresów IPv4/IPv6 na podstawie zadanego pliku wejściowego.

#include <list>
#include <string>
#include <arpa/inet.h>
#include <fstream>
#include <cstring>
#include <assert.h>
using namespace std;
//typ Host to ustalona struktura, zawierajaca dane umozliwiajace polaczenie sie z hostem
typedef sockaddr_storage Host;
class FileParser
{
	string filename;
	public:
	int parseAddress(char* addressAsText, Host* nextHost);
	list<Host> getHosts();
	int setFilename(string _filename);
};