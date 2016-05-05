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

/*
 * A partir de aca; metodos para todas las decisiones que toma el jugador
 * que requieren un envio de informacion el server
 */

void MegamanClient::operator()() {}

void MegamanClient::pick_stage(char stage_id) {
	this->client.send(&stage_id, sizeof(char));
}

MegamanClient::~MegamanClient() {
	this->client.shutdown();
}
