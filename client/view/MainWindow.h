#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/layout.h>
#include <gtkmm/entry.h>
#include <gtkmm/socket.h>
#include <string>

#include "client/communication/Client.h"
#include "common/communication/Socket.h"
#include "StageSurface.h"
#include "StageRenderer.h"

class MainWindow: public Gtk::Window {
public:
	MainWindow(const char* hostname, const char* port);
	virtual ~MainWindow();

protected:
	Gtk::Layout layout;
	Gtk::Image bg_image;
    StageSurface* surface;

    Gtk::Box main_frame;
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
	void init_welcome_screen();
	void init_insert_name();
	void init_stage_pick_screen();
};

#endif  // MAINWINDOW_H
