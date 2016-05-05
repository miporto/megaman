#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "common/commonSocket.h"
#include "common/commonThread.h"
#include "QuitProtected.h"
#include "serverMatch.h"

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
