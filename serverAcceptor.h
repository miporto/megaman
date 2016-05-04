#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <vector>
#include <string>

#include "commonSocket.h"
#include "commonThread.h"

class QuitProtected {
	private:
		Mutex m;
		bool quit;
	
	public:
		QuitProtected();
		void switch_to_true();
		bool operator()();
		~QuitProtected();
};

class Acceptor : public Thread {
	private:
		Socket& server;
		Match& match;
		QuitProtected& quit;
		
	public:
		Acceptor(Socket& server, Match& match, QuitProtected& quit);
		void run();
		~Acceptor();
};

#endif // ACCEPTOR_H
