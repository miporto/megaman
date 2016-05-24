#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <iostream>
#include <string>
#include <gtkmm/entry.h>
#include <gtkmm/entrybuffer.h>

#include "MainWindow.h"
#include "AboutScreen.h"
#include "GladeLoader.h"
#include "SignalProtocol.h"
#include "common/communication/Packet.h"

#define CONTAINER_NAME "container"

MainWindow::MainWindow(const char* hostname, const char* port) :
		layout(), bg_image("resources/background.png"), client(hostname, port) {
	set_title("Mega Man");
	set_size_request(640, 480);
	set_border_width(0);
	//set_resizable(false);

	layout.put(bg_image, 0, 0);

	init_welcome_screen();
	layout.put(*welcome_screen, 280, 0);

	add(layout);

	show_all();
}

void MainWindow::init_signal_map() {
	sig_map[ABOUT_BACK] = welcome_screen;
}

void MainWindow::process_signal(int signal) {
	sig_map[signal]->show();
}

void MainWindow::on_new_game_btn_clicked() {
	std::cout << std::endl;
	layout.remove(*welcome_screen);
	//welcome_screen->hide();
	init_insert_name();
	layout.put(*insert_name, 250, 0);
}

void MainWindow::on_about_btn_clicked() {
	//welcome_screen->hide();
	layout.remove(*welcome_screen);
	about = (Gtk::Box*) new AboutScreen(this);
	layout.put(*about, 250, 0);
	//layout.show_all();
	//about->show();
}

void MainWindow::on_exit_game_btn_clicked() {
	std::cout << "Exit game" << std::endl;
	unset_application();
}

void MainWindow::on_confirm_name_btn_clicked(Gtk::Entry* text_entry) {
	std::cout << "Client started" << std::endl;
	this->client.connect_to_server();
	Glib::RefPtr<const Gtk::EntryBuffer> buffer = text_entry->get_buffer();
	Glib::ustring name = buffer->get_text();
	std::cout << name.c_str() << std::endl;
	std::string sname = name.raw();
	this->client.send_name(sname);
	init_stage_pick_screen();
	layout.remove(*insert_name);
	layout.put(*stage_pick, 250, 0);
	stage_pick->show();
}

void MainWindow::on_cancel_btn_clicked() {
	std::cout << "Going back to welcome screen" << std::endl;
	//insert_name->hide();
	layout.remove(*insert_name);
	layout.put(*welcome_screen, 250, 0);
	welcome_screen->show();
}

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

void MainWindow::init_insert_name() {
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

void MainWindow::init_stage_pick_screen() {
	stage_pick = NULL;
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"resources/stage_pick_box.glade", &stage_pick);
	Gtk::Button* btn = NULL;
	builder->get_widget("bombman_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::bind<char>(
						sigc::mem_fun(*this,
								&MainWindow::on_boss_pick_btn_clicked), BOMBMAN));
	}
}
void MainWindow::on_boss_pick_btn_clicked(char stage_id) {
	std::cout << "Boss selected" << std::endl;
	client.pick_stage(stage_id);
}

MainWindow::~MainWindow() {
}
