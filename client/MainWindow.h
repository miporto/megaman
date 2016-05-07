#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

#include "common/Socket.h"

class MainWindow : public Gtk::Window {

   public:
    MainWindow(Socket& skt, const char* hostname, const char* port);
    virtual ~MainWindow();

   protected:
    // Signal handlers:
    void on_start_button_clicked();

    // Member widgets:
    Gtk::Button m_button;

   private:
    Socket& skt;
    const char* hostname;
    const char* port;
};

#endif  // GTKMM_MAINWINDOW_H