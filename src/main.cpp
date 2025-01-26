#include <iostream>
#include <string>

// #include "../lib/Note.h"

#include "../lib/NoteKeeperApp.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.notekeeper");

    NoteKeeperApp window;

    return app->run(window);
}
