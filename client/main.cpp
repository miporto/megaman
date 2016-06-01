#include <cstdlib>
#include <gtkmm/application.h>
#include <string>

#include "view/MainWindow.h"
#include "view/StageSurface.h"

#define HOSTNAME_POS 1
#define PORT_POS 2
#define ARGS_LEN 3
#define APP_ARGC 1

int main(int argc, char** argv) {
	if (argc != ARGS_LEN)
		return EXIT_FAILURE;

	int app_argc = APP_ARGC;
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create
			(app_argc, argv, "org.gtkmm.megaman", Gio::APPLICATION_NON_UNIQUE);

	// Shows the window and returns when it is closed.
    MainWindow mainwindow(argv[HOSTNAME_POS], argv[PORT_POS]);

    return app->run(mainwindow);

//	Client client(argv[HOSTNAME_POS], argv[PORT_POS]);
//    client.connect_to_server();
//    std::string name = "ROK";
//    client.send_name(name);
//    client.pick_stage(1);
//    StageSurface stageSurface(client);
//    stageSurface.run();
//    return 0;
}
