#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "common/Socket.h"
#include "common/Thread.h"
#include "QuitProtected.h"
#include "Match.h"

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
