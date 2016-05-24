#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/layout.h>
#include <gtkmm/entry.h>
#include <map>
#include <string>

#include "Client.h"
#include "common/Socket.h"

class MainWindow: public Gtk::Window {
public:
	MainWindow(const char* hostname, const char* port);
	void process_signal(int signal);
	virtual ~MainWindow();

protected:
	Gtk::Layout layout;
	Gtk::Image bg_image;

	Gtk::Box* welcome_screen;
	Gtk::Box* about;
	Gtk::Box* insert_name;
	Gtk::Box* stage_pick;
	Gtk::Box* loading;

	//Signal Handlers
	void on_new_game_btn_clicked();
	void on_about_btn_clicked();
	void on_exit_game_btn_clicked();
	void on_confirm_name_btn_clicked(Gtk::Entry* text_entry);
	void on_cancel_btn_clicked();
	void on_boss_pick_btn_clicked(char stage_id);

private:
	Client client;
	typedef std::map<int, Gtk::Box*> SignalsMap;
	SignalsMap sig_map;
	void init_signal_map();
	void init_welcome_screen();
	void init_insert_name();
	void init_stage_pick_screen();
};

#endif  // MAINWINDOW_H
