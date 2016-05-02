#include <netdb.h>
#include <string.h>

#include "commonAddrInfo.h"

AddrInfo::AddrInfo(const char* hostname, const char* port, int flag) {
	struct addrinfo hints;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       // IPv4 (or AF_INET6 for IPv6)
	hints.ai_socktype = SOCK_STREAM; // TCP  (or SOCK_DGRAM for UDP)
	hints.ai_flags = flag;
	
	getaddrinfo(hostname, port, &hints, &(this->info));
}

struct addrinfo* AddrInfo::operator()() {
	return this->info;
}

AddrInfo::~AddrInfo() {
	freeaddrinfo(this->info);
}
		
ServerAddrInfo::ServerAddrInfo(const char* port) :
info(NULL, port, AI_PASSIVE) {}

struct addrinfo* ServerAddrInfo::operator()() {
	return this->info();
}

ServerAddrInfo::~ServerAddrInfo() {}
		
ClientAddrInfo::ClientAddrInfo(const char* hostname, const char* port) :
info(hostname, port, 0) {}

struct addrinfo* ClientAddrInfo::operator()() {
	return this->info();
}

ClientAddrInfo::~ClientAddrInfo() {}
