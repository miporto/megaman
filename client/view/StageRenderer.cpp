#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <gdkmm/pixbuf.h>
#include <glibmm/fileutils.h>

#include "StageRenderer.h"

StageRenderer::StageRenderer() : bg(Cairo::SurfacePattern::create(
        Cairo::ImageSurface::create_from_png("resources/background.png"))) {
    bg->set_extend(Cairo::EXTEND_REPEAT);
}

bool StageRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    cr->set_source(bg);
    cr->paint();
    return true;
}
