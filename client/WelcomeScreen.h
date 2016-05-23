#ifndef CLIENT_WELCOMESCREEN_H_
#define CLIENT_WELCOMESCREEN_H_

#include <gtkmm/box.h>

#include "MainWindow.h"

class WelcomeScreen: public Gtk::Box {
public:
	explicit WelcomeScreen(MainWindow* main_w);
	virtual ~WelcomeScreen();
private:
	MainWindow* main_w;
};

#endif /* CLIENT_WELCOMESCREEN_H_ */
