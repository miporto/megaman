#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "AboutScreen.h"
#include "GladeLoader.h"
#include "MainWindow.h"
#include "SignalProtocol.h"

AboutScreen::AboutScreen(MainWindow* main_w) :
		main_w(main_w) {
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"view/about.glade", &screen);
	Gtk::Button* btn = NULL;
	builder->get_widget("back_btn", btn);
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &AboutScreen::on_exit_btn_clicked));
	}
}

void AboutScreen::on_exit_btn_clicked() {
	main_w->process_signal(ABOUT_BACK);
}

Gtk::Box* AboutScreen::get_screen() {
	return screen;
}

AboutScreen::~AboutScreen() {}
