#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <string>
#include <gtkmm/image.h>
#include <gtkmm/layout.h>
#include <gtkmm/entry.h>

#include "AboutWindow.h"
#include "Client.h"
#include "common/Socket.h"

class MainWindow: public Gtk::Window {
public:
	MainWindow(const char* hostname, const char* port);
	virtual ~MainWindow();

protected:
	Gtk::Layout layout;
	Gtk::Image bg_image;

	Gtk::Box* welcome_screen;
	Gtk::Box* insert_name;
	Gtk::Box* stage_pick;
	Gtk::Box* loading;
	Gtk::Box* about;

	AboutWindow* about_w;

	//Signal Handlers
	void on_new_game_btn_clicked();
	void on_about_btn_clicked();
	void on_exit_game_btn_clicked();
	void on_confirm_name_btn_clicked(Gtk::Entry* text_entry);
	void on_cancel_btn_clicked();

private:
	typedef Glib::RefPtr<Gtk::Builder> GtkBuilder;
	Client client;
	
	void init_welcome_screen();
	void init_insert_name();
	void init_stage_pick_screen();
	GtkBuilder load_glade_file(std::string filename, Gtk::Box** container);
};

#endif  // GTKMM_MAINWINDOW_H
