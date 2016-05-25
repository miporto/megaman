#ifndef CAIRO_EXAMPLE_MYAREA_H_
#define CAIRO_EXAMPLE_MYAREA_H_

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

class MyArea: public Gtk::DrawingArea {
public:
	MyArea();
	virtual ~MyArea();
protected:
	//Override default signal handler:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

	Glib::RefPtr<Gdk::Pixbuf> m_image;
};

#endif /* CAIRO_EXAMPLE_MYAREA_H_ */
