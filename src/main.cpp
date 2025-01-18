#include <iostream>
#include <string.h>
#include "../lib/Note.h"

int main(){
    Note note;

    std::string adminPassword;
    std::printf("Enter admin password: ");
    std::cin >> adminPassword;

    note.createPostgresUser(adminPassword);
    note.setName("user1");
    note.setPassword("psql");

    note.CreateTable();
    note.setMessage("This is a sample message.");
    std::cout << note.getNote() << std::endl;


    return 0;
}