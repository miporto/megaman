#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "AboutScreen.h"
#include "GladeLoader.h"

AboutScreen::AboutScreen(MainWindow& main_w) :
		main_w(main_w) {
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"view/about.glade", this);
	Gtk::Button* btn = NULL;
	if (btn) {
		btn->signal_clicked().connect(
				sigc::mem_fun(*this, &AboutScreen::on_exit_btn_clicked));
	}

	show_all_children();
}

void AboutScreen::on_exit_btn_clicked() {
	signal_hide();
}
AboutScreen::~AboutScreen() {
}
