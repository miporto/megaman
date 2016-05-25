#ifndef MEGAMAN_GLADELOADER_H
#define MEGAMAN_GLADELOADER_H

#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <string>

class GladeLoader {
    public:
        typedef Glib::RefPtr<Gtk::Builder> ScreenBuilder;
        static ScreenBuilder load_glade_file
                (std::string filename, Gtk::Box** container);
        static ScreenBuilder load_glade_file
                (std::string filename, Gtk::Box* container);
};

#endif //MEGAMAN_GLADELOADER_H

