#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>


class StageRenderer : public Gtk::DrawingArea {
public:
    StageRenderer();
    ~StageRenderer();
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
private:
//    Cairo::SurfacePattern bg;
    Glib::RefPtr< Gdk::Pixbuf > bg;
};


#endif //MEGAMAN_STAGERENDERER_H
