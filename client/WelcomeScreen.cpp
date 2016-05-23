#include "GladeLoader.h"
#include "MainWindow.h"
#include "WelcomeScreen.h"

WelcomeScreen::WelcomeScreen(MainWindow* main_w) :
		main_w(main_w) {
	GladeLoader::ScreenBuilder builder = GladeLoader::load_glade_file(
			"view/welcome_screen.glade", this);
}

WelcomeScreen::~WelcomeScreen() {
}
