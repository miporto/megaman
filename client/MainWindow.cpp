#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <iostream>
#include <string>

#include "MainWindow.h"

MainWindow::MainWindow(const char* hostname, const char* port) :
		main_frame(), welcome_screen(), hostname(hostname), port(port) {
	set_title("Megaman");
	set_size_request(600, 400);
	set_border_width(6);
	init_welcome_screen();

//	// Set signal handlers
//	nw_game_btn.signal_clicked().connect(
//			sigc::mem_fun(*this, &MainWindow::on_new_game_btn_clicked));
//	exit_btn.signal_clicked().connect(
//			sigc::mem_fun(*this, &MainWindow::on_exit_game_btn_clicked));
//
//	// Add widgets
//	add(nw_game_btn);
//	add(exit_btn);
//
//	// Show widgets
//	nw_game_btn.show();
//	exit_btn.show();
}

void MainWindow::on_new_game_btn_clicked() {
//	skt = Socket();
//	Client client(skt, hostname, port);
	std::cout << "Client started" << std::endl;
}

void MainWindow::on_exit_game_btn_clicked() {
	std::cout << "Exit game" << std::endl;
}

MainWindow::~MainWindow() {
}

void MainWindow::init_welcome_screen() {
	GtkBuilder builder = load_glade_file("view/example.glade");
	Gtk::Button* btn = NULL;
	builder->get_widget("ex_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &MainWindow::on_new_game_btn_clicked));
	}
}

MainWindow::GtkBuilder MainWindow::load_glade_file(std::string filename) {
	GtkBuilder builder = Gtk::Builder::create();
	try {
		builder->add_from_file(filename);
	} catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	} catch (const Glib::MarkupError& ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
	//builder->get_widget_derived("", parent);
	return builder;
}
