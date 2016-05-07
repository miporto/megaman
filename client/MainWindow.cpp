
#include <iostream>

#include "Client.h"
#include "MainWindow.h"
#include "common/Socket.h"

MainWindow::MainWindow(Socket& skt, const char* hostname, const char* port)
    : m_button("Start Game!"), skt(skt), hostname(hostname), port(port){
    // Sets the border width of the window.
    set_border_width(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_start_button_clicked));

    // This packs the button into the Window (a container).
    add(m_button);

    // The final step is to display this newly created widget...
    m_button.show();
}

MainWindow::~MainWindow() {}

void MainWindow::on_start_button_clicked() {
    Client client(skt, hostname, port);
    std::cout << "Client started" << std::endl;
}