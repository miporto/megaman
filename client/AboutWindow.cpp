#include <gtkmm/button.h>
#include <gtkmm/label.h>

#include "AboutWindow.h"

AboutWindow::AboutWindow() :
		exit_btn("Exit") {
	set_default_size(100, 100);
	set_title("About");
	author_lbl.set_label("About label");

	exit_btn.signal_clicked().connect(
			sigc::mem_fun(*this, &AboutWindow::on_exit_btn_clicked));
	add(author_lbl);
	add(exit_btn);
	show_all_children();
}

AboutWindow::~AboutWindow() {
	// TODO Auto-generated destructor stub
}

void AboutWindow::on_exit_btn_clicked() {
	signal_hide();
}
