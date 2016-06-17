#include <glibmm/fileutils.h>
#include <glibmm/main.h>
#include <glibmm/markup.h>
#include <iostream>
#include <string>
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
#include <vector>

#include "MainWindow.h"
#include "GameLoopThread.h"
#include "GladeLoader.h"
#include "common/communication/Packet.h"
#include "StageRenderer.h"


#define CONTAINER_NAME "container"

MainWindow::MainWindow(const char* hostname, const char* port) :
        bg_image("resources/background.png"), client(hostname, port) {
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
}

void MainWindow::on_cancel_btn_clicked() {
	std::cout << "Going back to welcome screen" << std::endl;
    insert_name->hide();
	welcome_screen->show();
}

// STAGE PICK SCREEN

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

void MainWindow::init_stage_pick_screen() {
	stage_pick = NULL;
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"resources/stage_pick_box.glade", &stage_pick);
    init_players(builder);
    trigger_waiting_loop();
	Gtk::Button* btn = NULL;
	builder->get_widget("bombman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
								&MainWindow::on_boss_pick_btn_clicked), BOMBMAN));
	}

	btn = NULL;
	builder->get_widget("fireman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
									  &MainWindow::on_boss_pick_btn_clicked),
						FIREMAN));
	}

	btn = NULL;
	builder->get_widget("sparkman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
									  &MainWindow::on_boss_pick_btn_clicked),
						SPARKMAN));
	}

	btn = NULL;
	builder->get_widget("magnetman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
									  &MainWindow::on_boss_pick_btn_clicked),
						MAGNETMAN));
	}

	btn = NULL;
	builder->get_widget("ringman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
									  &MainWindow::on_boss_pick_btn_clicked),
						RINGMAN));
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
    waiting_loop->end_waiting();
    waiting_loop->join();
    delete waiting_loop;
	client.pick_stage(stage_id);
    trigger_game_loop();
    iconify();
    stage_pick->hide();
}

void MainWindow::trigger_game_loop() {
    game_loop = new GameLoopThread(*this, client);
    game_loop->start();
}

void MainWindow::resume_stage_pick() {
    Glib::signal_idle().connect(sigc::mem_fun(*this,
                                               &MainWindow::show_stage_pick));
}

bool MainWindow::show_stage_pick() {
    deiconify();
    stage_pick->show();
    game_loop->join();
    //delete game_loop;
    return false;
}
MainWindow::~MainWindow() {
}
