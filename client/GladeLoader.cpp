#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <iostream>
#include <string>

#include "GladeLoader.h"

#define CONTAINER_NAME "container"

GladeLoader::ScreenBuilder GladeLoader::load_glade_file
        (std::string filename, Gtk::Box** container) {
    ScreenBuilder builder = Gtk::Builder::create();
    try {
        builder->add_from_file(filename);
    } catch (const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    } catch (const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    } catch (const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    // All glade files loaded **must** have a top level container
    // (not a window, of any kind) named as CONTAINER_NAME
    builder->get_widget(CONTAINER_NAME, *container);
    return builder;
}
