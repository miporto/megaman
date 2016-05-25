#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <glibmm/main.h>

#include "MyArea.h"

int main(int argc, char** argv) {
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Gtk::Window win;
	win.set_title("Cairo example");
	MyArea my_area;
	win.add(my_area);
	my_area.show();
	return app->run(win);
}
