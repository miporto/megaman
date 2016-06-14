#ifndef SOCKET_H
#define SOCKET_H

#include <typeinfo>
#include <stddef.h>
#include <netdb.h>

#include "common/Thread.h"

#define SocketError_BUFFER_LEN 256

class SocketError : public std::exception {
	private:
		char error_msg[SocketError_BUFFER_LEN];
	
	public:
		SocketError() throw();
		const char* what() const throw();
		~SocketError() throw();
};

class Socket {
	private:
		int fd;
		bool is_disconnected;
	
	public:
		Socket();
		explicit Socket(int fd);
		void operator()(struct addrinfo* info);
		~Socket();
		void bind_and_listen(struct addrinfo* info);
		void connect(struct addrinfo* info);
		Socket* accept();
		void send(const char* buffer, size_t size);
		void receive(char* buffer, size_t size);
		void disconnect();
		bool disconnected();
		void shutdown();
};

#endif // SOCKET_H
