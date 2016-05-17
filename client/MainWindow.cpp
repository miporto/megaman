#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <iostream>
#include <string>

#include "AboutWindow.h"
#include "MainWindow.h"

#define CONTAINER_NAME "container"

MainWindow::MainWindow(const char* hostname, const char* port) :
		main_frame(), layout(), bg_image("view/bg.jpg"), client(hostname, port) {
	set_title("Mega Man");
	set_size_request(640, 480);
	set_border_width(0);
	set_resizable(false);

	layout.put(bg_image, 0, 0);

	init_welcome_screen();
	main_frame.pack_start(*welcome_screen);
	//add(main_frame);
	layout.put(main_frame, 280, 0);

	add(layout);

	show_all();

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
	//TODO Cambiar pantalla a la de ingreso de nombre
}

void MainWindow::on_confirm_name_btn_clicked() {
	std::cout << "Client started" << std::endl;
	this->client.connect_to_server();
	//this->client.send_name(name);
}

void MainWindow::on_about_btn_clicked() {
	about_w = new AboutWindow();
	about_w->show();
}
void MainWindow::on_exit_game_btn_clicked() {
	std::cout << "Exit game" << std::endl;
	unset_application();
}

MainWindow::~MainWindow() {
}

void MainWindow::init_welcome_screen() {
	welcome_screen = NULL;
	GtkBuilder builder = load_glade_file("view/welcome_screen.glade",
			&welcome_screen);
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

MainWindow::GtkBuilder MainWindow::load_glade_file(std::string filename,
		Gtk::Box** container) {
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

	// All glade files loaded **must** have a top level container
	// (not a window, of any kind) named as CONTAINER_NAME
	builder->get_widget(CONTAINER_NAME, *container);
	return builder;
}
