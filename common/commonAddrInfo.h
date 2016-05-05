#ifndef ADDR_INFO_H
#define ADDR_INFO_H

class AddrInfo {
	private:
		struct addrinfo* info;
		
	public:
		AddrInfo(const char* hostname, const char* port, int flag);
		struct addrinfo* operator()();
		~AddrInfo();
};

class ServerAddrInfo {
	private:
		AddrInfo info;
		
	public:
		explicit ServerAddrInfo(const char* port);
		struct addrinfo* operator()();
		~ServerAddrInfo();
};

class ClientAddrInfo {
	private:
		AddrInfo info;
		
	public:
		ClientAddrInfo(const char* hostname, const char* port);
		struct addrinfo* operator()();
		~ClientAddrInfo();
};

#endif // ADDR_INFO_H
