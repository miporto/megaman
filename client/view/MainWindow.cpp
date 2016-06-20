#include <glibmm/fileutils.h>
#include <glibmm/main.h>
#include <glibmm/markup.h>
#include <gtkmm/entry.h>
#include <gtkmm/entrybuffer.h>
#include <gtkmm/main.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "MainWindow.h"
#include "GameLoopThread.h"
#include "GladeLoader.h"
#include "common/communication/Packet.h"
#include "StageRenderer.h"


#define CONTAINER_NAME "container"

MainWindow::MainWindow(const char* hostname, const char* port) :
        bg_image("resources/background.png"), client(hostname, port) {
    waiting_loop = NULL;
    game_loop = NULL;
	set_title("Mega Man");
	set_size_request(640, 480);
    set_position(Gtk::WIN_POS_CENTER);
	set_border_width(0);
	layout.put(bg_image, 0, 0);
	init_welcome_screen();
    init_insert_name_screen();
    init_stage_pick_screen();
    main_frame.pack_start(*welcome_screen);
    main_frame.pack_start(*insert_name);
    main_frame.pack_start(*stage_pick);
    add(main_frame);
	show_all();
    insert_name->hide();
    stage_pick->hide();
}

void MainWindow::set_stage_as_completed(char id) {
    if (stages.count(id) != 0) stages[id] = false;
}

// WELCOME SCREEN
void MainWindow::init_welcome_screen() {
	welcome_screen = NULL;
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"resources/welcome_screen.glade", &welcome_screen);
	Gtk::Button* btn = NULL;
	builder->get_widget("start_game_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &MainWindow::on_new_game_btn_clicked));
	}
	builder->get_widget("about_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &MainWindow::on_about_btn_clicked));
	}
	builder->get_widget("exit_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &MainWindow::on_exit_game_btn_clicked));
	}
}

void MainWindow::on_new_game_btn_clicked() {
	std::cout << std::endl;
    welcome_screen->hide();
    insert_name->show();
}

void MainWindow::on_about_btn_clicked() {}

void MainWindow::on_exit_game_btn_clicked() {
	std::cout << "Exit game" << std::endl;
	unset_application();
}


// INSERT NAME SCREEN
void MainWindow::init_insert_name_screen() {
	insert_name = NULL;
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"resources/insert_name.glade", &insert_name);
	Gtk::Button* btn = NULL;
	Gtk::Entry* entry = NULL;
	builder->get_widget("name_entry", entry);
	builder->get_widget("confirm_name_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<Gtk::Entry*>(
						sigc::mem_fun(*this,
									  &MainWindow::on_confirm_name_btn_clicked),
						entry));
	}
	builder->get_widget("cancel_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &MainWindow::on_cancel_btn_clicked));
	}
}

void MainWindow::on_confirm_name_btn_clicked(Gtk::Entry* text_entry) {
	std::cout << "Client started" << std::endl;
	this->client.connect_to_server();
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = text_entry->get_buffer();
	Glib::ustring name = buffer->get_text();
	std::cout << name.c_str() << std::endl;
	std::string sname = name.raw();
	this->client.send_name(sname);
    this->name = sname;
    new_player(name);
    insert_name->hide();
	stage_pick->show();
    trigger_waiting_loop();
}

void MainWindow::on_cancel_btn_clicked() {
	std::cout << "Going back to welcome screen" << std::endl;
    insert_name->hide();
	welcome_screen->show();
}


// STAGE PICK SCREEN
void MainWindow::init_stage_pick_screen() {
	stage_pick = NULL;
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"resources/stage_pick_box.glade", &stage_pick);
    init_players(builder);
    std::map<std::string, char> bosses;
    bosses["bombman_btn"] = BOMBMAN;
    bosses["fireman_btn"] = FIREMAN;
    bosses["sparkman_btn"] = SPARKMAN;
    bosses["magnetman_btn"] = MAGNETMAN;
    bosses["ringman_btn"] = RINGMAN;
    for (auto const &it : bosses) {
        Gtk::Button* btn = NULL;
        builder->get_widget(it.first, btn);
        if (btn) {
            btn->signal_clicked().connect(sigc::bind<char>(sigc::mem_fun(*this,
                                          &MainWindow::on_boss_pick_btn_clicked),
                                                           it.second));
        }
        // Set all stages to playable
        stages[it.second] = true;
    }
}

void MainWindow::init_players(GladeLoader::ScreenBuilder &builder) {
    std::vector<std::string> glade_player_ids = {"player_1", "player_2",
                                                 "player_3", "player_4"};
    Gtk::Box *box = NULL;
    for (auto const &it : glade_player_ids) {
        builder->get_widget(it, box);
        if (box) {
            player_boxes.push_back(box);
        } else {
            std::cout << "ERROR INIT PLAYERS" << std::endl;
        }
        box = NULL;
    }
}

void MainWindow::trigger_waiting_loop() {
    waiting_loop = new WaitingRoomThread(*this, client);
    waiting_loop->start();
}

void MainWindow::new_player(const std::string &name) {
    if (players.count(name) == 0 && player_boxes.size() > 0) {
        Gtk::Box *box = player_boxes.back();
        player_boxes.pop_back();
        change_box_to_connected(box, name);
        players[name] = box;
    }
}

void MainWindow::change_box_to_connected(Gtk::Box *box, const std::string &name) {
    std::vector<Gtk::Widget*> children = box->get_children();
    for (auto const &it: children) {
        if (auto label = dynamic_cast<Gtk::Label*>(it)) {
            label->set_text(name);
        }
    }
}

void MainWindow::on_boss_pick_btn_clicked(char stage_id) {
	std::cout << "Boss selected" << std::endl;
	if (stages[stage_id]) {
        client.pick_stage(stage_id);
    } else {
        // TODO: launch a popup or something
        std::cout << "Level completed" << std::endl;
    }
}

void MainWindow::trigger_game_loop(char stage_id) {
    waiting_loop->join();
    game_loop = new GameLoopThread(*this, client, stage_id);
    game_loop->start();
    halt_stage_pick();
}

void MainWindow::halt_stage_pick() {
    Glib::signal_idle().connect(sigc::mem_fun(*this,
                                              &MainWindow::hide_stage_pick));
}
void MainWindow::resume_stage_pick() {
    Glib::signal_idle().connect(sigc::mem_fun(*this,
                                               &MainWindow::show_stage_pick));
    waiting_loop->start();
}

bool MainWindow::show_stage_pick() {
    deiconify();
    stage_pick->show();
    game_loop->join();
    delete game_loop;
    return false;
}

bool MainWindow::hide_stage_pick() {
    iconify();
    stage_pick->hide();
    return false;
}
MainWindow::~MainWindow() {
    if (waiting_loop) {
        waiting_loop->end_wait();
        waiting_loop->join();
        delete waiting_loop;
    }
}
