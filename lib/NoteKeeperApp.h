#pragma once
#ifndef NOTEKEEPERAPP_H
#define NOTEKEEPERAPP_H

#include <iostream>
#include <string.h>
#include "Note.h"

#include <gtkmm.h>

class NoteKeeperApp : public Gtk::Window {
public:
    NoteKeeperApp();

protected:
    // Обробники подій
    void on_confirm_button_clicked();

    void on_create_note_clicked();

    void on_delete_note_clicked();

    void on_view_notes_clicked();

    void on_create_backup_clicked();

private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Label welcomeLabel;
    Gtk::Entry adminEntry;
    Gtk::Button confirmButton;

    Gtk::ScrolledWindow scrollWindow;
    Gtk::TextView notesView;

    Gtk::Box buttonsBox{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button createNoteButton;
    Gtk::Button deleteNoteButton;
    Gtk::Button viewNotesButton;
    Gtk::Button backupButton;

    Note note;
};


#endif