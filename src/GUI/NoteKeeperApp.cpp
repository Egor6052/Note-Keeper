#include <iostream>
#include <string.h>
#include <gtkmm.h>

#include "../../lib/NoteKeeperApp.h"


NoteKeeperApp::NoteKeeperApp() {
    set_title("Note Keeper");
    set_default_size(600, 400);

    // Встановлюємо головний контейнер
    vbox.set_margin_top(10);
    vbox.set_margin_bottom(10);
    vbox.set_margin_start(10);
    vbox.set_margin_end(10);

    vbox.set_spacing(10);
    add(vbox);

    // Лейбл вітання
    welcomeLabel.set_text("Welcome to the Note Keeper!");
    welcomeLabel.set_margin_bottom(10);
    welcomeLabel.set_halign(Gtk::ALIGN_CENTER);
    vbox.pack_start(welcomeLabel, Gtk::PACK_SHRINK);

    // Поле для вводу пароля адміністратора
    adminEntry.set_placeholder_text("Enter admin password...");
    adminEntry.set_visibility(false); // Робимо пароль прихованим
    adminEntry.set_margin_bottom(10);
    vbox.pack_start(adminEntry, Gtk::PACK_SHRINK);

    // Кнопка підтвердження
    confirmButton.set_label("Confirm Admin Password");
    confirmButton.signal_clicked().connect(sigc::mem_fun(*this, &NoteKeeperApp::on_confirm_button_clicked));
    vbox.pack_start(confirmButton, Gtk::PACK_SHRINK);

    // Текстова область для нотаток
    notesView.set_editable(false);
    notesView.set_wrap_mode(Gtk::WRAP_WORD);
    scrollWindow.add(notesView);
    scrollWindow.set_vexpand(true);
    scrollWindow.set_hexpand(true);
    vbox.pack_start(scrollWindow);

    // Панель кнопок
    createNoteButton.set_label("Create Note");
    createNoteButton.signal_clicked().connect(sigc::mem_fun(*this, &NoteKeeperApp::on_create_note_clicked));
    deleteNoteButton.set_label("Delete Note");
    deleteNoteButton.signal_clicked().connect(sigc::mem_fun(*this, &NoteKeeperApp::on_delete_note_clicked));
    viewNotesButton.set_label("View Notes");
    viewNotesButton.signal_clicked().connect(sigc::mem_fun(*this, &NoteKeeperApp::on_view_notes_clicked));
    backupButton.set_label("Create Backup");
    backupButton.signal_clicked().connect(sigc::mem_fun(*this, &NoteKeeperApp::on_create_backup_clicked));

    buttonsBox.set_spacing(5);
    buttonsBox.set_margin_top(10);
    buttonsBox.set_halign(Gtk::ALIGN_CENTER);
    buttonsBox.pack_start(createNoteButton);
    buttonsBox.pack_start(deleteNoteButton);
    buttonsBox.pack_start(viewNotesButton);
    buttonsBox.pack_start(backupButton);
    vbox.pack_start(buttonsBox, Gtk::PACK_SHRINK);

    show_all_children();
}

    // Обробники подій
void NoteKeeperApp::on_confirm_button_clicked() {
    std::string password = adminEntry.get_text();
    note.createPostgresUser(password);
    note.CreateTable();
    Gtk::MessageDialog dialog(*this, "Admin password confirmed!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}

void NoteKeeperApp::on_create_note_clicked() {
    Gtk::Dialog dialog("Create Note", *this);
    Gtk::Box* content = dialog.get_content_area();
    Gtk::Entry noteEntry;
    noteEntry.set_placeholder_text("Enter your note...");
    content->pack_start(noteEntry);
    noteEntry.show();

    dialog.add_button("Save", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);

    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        std::string message = noteEntry.get_text();
        note.setMessage(message);
        Gtk::MessageDialog successDialog(*this, "Note saved successfully!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        successDialog.run();
    }
}

void NoteKeeperApp::on_delete_note_clicked() {
    Gtk::Dialog dialog("Delete Note", *this);
    Gtk::Box* content = dialog.get_content_area();
    Gtk::Entry idEntry;
    idEntry.set_placeholder_text("Enter note ID...");
    content->pack_start(idEntry);
    idEntry.show();

    dialog.add_button("Delete", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);

    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        std::string id = idEntry.get_text();
        note.deleteMessage(id);
        Gtk::MessageDialog successDialog(*this, "Note deleted successfully!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        successDialog.run();
    }
}

void NoteKeeperApp::on_view_notes_clicked() {
    std::string notes = note.getNote();
    notesView.get_buffer()->set_text(notes);
}

void NoteKeeperApp::on_create_backup_clicked() {
    note.createBackup();
    Gtk::MessageDialog dialog(*this, "Backup created successfully!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}