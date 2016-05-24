#include <cstdlib>
#include <gtkmm/application.h>

#include "common/communication/Socket.h"
#include "client/communication/Client.h"
#include "client/view/MainWindow.h"

#define HOSTNAME_POS 1
#define PORT_POS 2
#define ARGS_LEN 3

int main(int argc, char** argv) {
	if (argc != ARGS_LEN)
		return EXIT_FAILURE;

	int argc1 = 1;
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create
		(argc1, argv, "org.gtkmm.megaman");
	// Shows the window and returns when it is closed.
	MainWindow mainwindow(argv[HOSTNAME_POS], argv[PORT_POS]);
	return app->run(mainwindow);
}
