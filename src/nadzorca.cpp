#include "../include/nadzorca.h"

nadzorca::nadzorca(){
	
	
}

nadzorca::~nadzorca(){
	
}

int nadzorca::send_msg(const char *msg) {
	tcp_module.send_msg(msg);
	std::cout << "Response----------------" << std::endl << msg << std::endl;
}

int nadzorca::receive_msg(char *msg) {
	if(tcp_module.receive_msg(msg) > 0)
		return 1;
	if(msg == NULL){
		perror("Something went wrong :/");
		return 1;
	}
	remoTestMessage message(msg);
	

	
}
