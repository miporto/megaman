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
#include <map>
#include <string>
#include <vector>

#include "client/communication/Client.h"
#include "common/communication/Socket.h"
#include "GameLoopThread.h"
#include "StageSurface.h"
#include "StageRenderer.h"
#include "GladeLoader.h"
#include "WaitingRoomThread.h"

class GameLoopThread;

class MainWindow: public Gtk::Window {
public:
	MainWindow(const char* hostname, const char* port);
    void trigger_game_loop();
    void halt_stage_pick();
	void resume_stage_pick();
    void new_player(const std::string &name);
	virtual ~MainWindow();

protected:
	Gtk::Layout layout;
	Gtk::Image bg_image;

    Gtk::Box main_frame;
    Gtk::Box* welcome_screen;
	Gtk::Box* about;
	Gtk::Box* insert_name;
	Gtk::Box* stage_pick;
	Gtk::Box* loading;
    std::string name;
	std::vector<Gtk::Box*> player_boxes;
    std::map<std::string, Gtk::Box*> players;

	GameLoopThread* game_loop;
    WaitingRoomThread* waiting_loop;

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
	void init_insert_name_screen();
	void init_stage_pick_screen();
	bool show_stage_pick();
    bool hide_stage_pick();
    void init_players(GladeLoader::ScreenBuilder &builder);
    void trigger_waiting_loop();
    void change_box_to_connected(Gtk::Box *box, const std::string &name);
};

#endif  // MAINWINDOW_H
