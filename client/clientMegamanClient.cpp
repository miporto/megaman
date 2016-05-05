#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

#include "clientMegamanClient.h"
#include "common/commonAddrInfo.h"
#include "common/commonSocket.h"

MegamanClient::MegamanClient(Socket& client, const char* hostname, 
const char* port) : client(client) {
	struct addrinfo* ptr;
	bool connected = false;
	ClientAddrInfo info(hostname, port);
	
	for (ptr = info(); ptr != NULL && !connected; ptr = ptr->ai_next) {
		this->client(ptr);
		try {
			this->client.connect(ptr);
		} catch (const SocketError &e) {
			if (ptr->ai_next) 
				continue;
			else 
				throw;
		}
		connected = true;
	}
}

void MegamanClient::operator()() {

}

MegamanClient::~MegamanClient() {
	this->client.shutdown();
}
