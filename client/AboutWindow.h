#ifndef CLIENT_ABOUTWINDOW_H_
#define CLIENT_ABOUTWINDOW_H_

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class AboutWindow: public Gtk::Window {
public:
	AboutWindow();
	virtual ~AboutWindow();
protected:
	Gtk::Label author_lbl;
	Gtk::Button exit_btn;

	void on_exit_btn_clicked();
};

#endif /* CLIENT_ABOUTWINDOW_H_ */
