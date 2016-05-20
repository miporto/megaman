#ifndef CLIENT_ABOUTSCREEN_H_
#define CLIENT_ABOUTSCREEN_H_

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

#include "MainWindow.h"

class MainWindow;

class AboutScreen: public Gtk::Box {
private:
	MainWindow* main_w;
	void on_exit_btn_clicked();
public:
	explicit AboutScreen(MainWindow* main_w);
	virtual ~AboutScreen();
};

#endif /* CLIENT_ABOUTSCREEN_H_ */
