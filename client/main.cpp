#include <cstdlib>
#include <gtkmm/application.h>

#include "common/Socket.h"
#include "Client.h"
#include "MainWindow.h"

#define HOSTNAME_POS 1
#define PORT_POS 2

int main(int argc, char** argv) {
    if (argc != 3){return 1;}
    int argc1 = 1;
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc1, argv, "org.gtkmm.example");
    // Shows the window and returns when it is closed.
    Socket skt;
    MainWindow mainwindow(skt, argv[HOSTNAME_POS], argv[PORT_POS]);
    return app->run(mainwindow);

}
