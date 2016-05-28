#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <gdkmm/pixbuf.h>
#include <glibmm/fileutils.h>
#include <gtkmm/drawingarea.h>

class StageRenderer : public Gtk::DrawingArea {
public:
    StageRenderer();
    ~StageRenderer();
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
private:
    Cairo::RefPtr<Cairo::SurfacePattern> bg;
};


#endif //MEGAMAN_STAGERENDERER_H
