#include <cstdlib>
#include <gtkmm/application.h>

#include "common/Socket.h"
#include "Client.h"
#include "MainWindow.h"

#define HOSTNAME_POS 1
#define PORT_POS 2

int main(int argc, char** argv) {
    //if (argc != 3){return 1;}
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MainWindow mainwindow;

    // Shows the window and returns when it is closed.
    return app->run(mainwindow);
    //Socket skt;
    //Client client(skt, argv[HOSTNAME_POS], argv[PORT_POS]);
    //client();
}
